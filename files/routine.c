#include "../head/philo.h"

void philo_routine(t_philo *philo)
{
    philo->time_routine_start = get_time();
	philo->finished_eating = philo->time_routine_start;
	if (philo->id % 2 == 0)
	{
		if (philo->amount_philos < 100)
			usleep(100);
		else
			usleep(1500);
	}
    while (1)
    {
		grab_forks(philo);
		eating(philo);
		if (philo->access->philo_died == true)
		{
			pthread_mutex_lock(&philo->access->mutex_message);
			pthread_mutex_unlock(&philo->access->mutex_message);
			break ;
		}
		if (philo->eaten_meals == philo->times_philo_eats)
			break ;
		sleeping(philo);
		thinking(philo);
    }
}

void grab_forks(t_philo *philo)
{
	int64_t current_time;

	pthread_mutex_lock(philo->mutex_right_fork);
	pthread_mutex_lock(&philo->access->mutex_message);
	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(philo->mutex_right_fork);
		pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	printf(GRN"%lld %d has taken a "RESET"right"GRN" fork\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
	pthread_mutex_lock(philo->mutex_left_fork);
	pthread_mutex_lock(&philo->access->mutex_message);
	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(philo->mutex_right_fork);
		pthread_mutex_unlock(philo->mutex_left_fork);
		pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	printf(GRN"%lld %d has taken a "RESET"left"GRN" fork\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
}

void eating(t_philo *philo)
{
	int64_t		current_time;
	int64_t		finished_eating_time;

	current_time = get_time() - philo->time_program_starts;
	pthread_mutex_lock(&philo->access->mutex_message);
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	printf(CYN"%lld %d is eating\n"RESET, current_time, philo->id);
	// printf("%lld %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
	finished_eating_time = get_time() + philo->tt_eat;
	while (get_time() <= finished_eating_time)
	{
		if (philosopher_died(philo) == true)
		{
			pthread_mutex_unlock(philo->mutex_left_fork);
			pthread_mutex_unlock(philo->mutex_right_fork);
			return ;
		}
		usleep(100);
	}
	philo->finished_eating = get_time();
	pthread_mutex_unlock(philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
	philo->eaten_meals++;
}

void sleeping(t_philo *philo)
{
	int64_t		current_time;
	int64_t		finished_sleeping_time;

	pthread_mutex_lock(&philo->access->mutex_message);
	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	printf(BLU"%lld %d is sleeping\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
	finished_sleeping_time = get_time() + philo->tt_sleep;
	while (get_time() <= finished_sleeping_time)
	{
		if (get_time() - philo->finished_eating >= philo->tt_die)
			break ;
		usleep(100);
	}
	if (philosopher_died(philo) == true)
		return ;
}

void thinking(t_philo *philo)
{
	int64_t		current_time;

	pthread_mutex_lock(&philo->access->mutex_message);
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->access->mutex_message);
		return;
	}
	current_time = get_time() - philo->time_program_starts;
	printf(YEL"%lld %d is thinking\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
}

/* function checks if a philosopher already died in the process
 * returns false if no philosopher died
 * returns true if one philosopher died						*/
bool philosopher_died(t_philo *philo)
{
	int64_t		current_time;

	pthread_mutex_lock(&philo->access->mutex_death);
	if (philo->access->philo_died == true)
	{
		pthread_mutex_unlock(&philo->access->mutex_death);
		return (true);
	}
	if ((get_time() - philo->finished_eating) >= philo->tt_die)
	{
		pthread_mutex_lock(&philo->access->mutex_message);
		current_time = get_time() - philo->time_program_starts;
		printf(RED"%lld %d died\n"RESET, current_time, philo->id);
		pthread_mutex_unlock(&philo->access->mutex_message);
		philo->access->philo_died = true;
		pthread_mutex_unlock(&philo->access->mutex_death);
		return (true);
	}
	pthread_mutex_unlock(&philo->access->mutex_death);
	return (false);
}
