#include "../head/philo.h"

void	grab_forks(t_philo *philo)
{
	int64_t	current_time;

	pthread_mutex_lock(philo->mutex_right_fork);
	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(philo->mutex_right_fork);
		// pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	pthread_mutex_lock(&philo->access->mutex_message);
	printf(GRN"%lld %d has taken a right fork\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
			printf(RED"test\n"RESET);
	pthread_mutex_lock(philo->mutex_left_fork);
	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(philo->mutex_right_fork);
		pthread_mutex_unlock(philo->mutex_left_fork);
		// pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	pthread_mutex_lock(&philo->access->mutex_message);
	printf(GRN"%lld %d has taken a left fork\n"RESET, current_time, philo->id);

	pthread_mutex_unlock(&philo->access->mutex_message);
}

void	eating(t_philo *philo)
{
	int64_t		current_time;
	int64_t		finished_eating_time;

	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
		return ;
	pthread_mutex_lock(&philo->access->mutex_message);
	printf(CYN"%lld %d is eating\n"RESET, current_time, philo->id);
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

void	sleeping(t_philo *philo)
{
	int64_t		current_time;
	int64_t		finished_sleeping_time;

	current_time = get_time() - philo->time_program_starts;
	if (philosopher_died(philo) == true)
	{
		// pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}
	pthread_mutex_lock(&philo->access->mutex_message);
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

void	thinking(t_philo *philo)
{
	int64_t		current_time;

	if (philosopher_died(philo) == true)
		return ;
	pthread_mutex_lock(&philo->access->mutex_message);
	current_time = get_time() - philo->time_program_starts;
	printf(YEL"%lld %d is thinking\n"RESET, current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
}

/* function checks if a philosopher already died in the process
 * returns false if no philosopher died
 * returns true if one philosopher died						*/
bool	philosopher_died(t_philo *philo)
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
