#include "../head/philo.h"

void philo_routine(t_philo *philo)
{
// printf(BLU"in routine philo: %d\n"RESET, philo->id);
    philo->time_routine_start = get_time();
	philo->finished_eating = philo->time_routine_start;
// waiting for philosopher longer if id is !%2=0
	if (philo->id % 2 == 0)
	{
		if (philo->amount_philos < 100)
			usleep(100);
		else
			usleep(1500);
	}
    while (1)
    {
		// printf("before grab fork\n");
		grab_forks(philo);
		// printf("before grab eating\n");
		eating(philo);


	// printf("philo %d was eating\n", philo->id);
		// if (philosopher_died(philo) == true)
		if (philo->access->philo_died == true)
		{
			pthread_mutex_lock(&philo->access->mutex_message);
			// printf(MAG"DEAD after eating\n"RESET);
			pthread_mutex_unlock(&philo->access->mutex_message);
			break ;
		}
		if (philo->eaten_meals == philo->times_philo_eats)
			break ;
		sleeping(philo);
	// printf("philo %d was sleeping\n", philo->id);

		thinking(philo);
		// printf("after thinking\n");
	// printf("philo %d thought\n", philo->id);
    }
	// printf("OUT OF LOOP Philo id: %d\n", philo->id);
}


void grab_forks(t_philo *philo)
{
	int64_t current_time;

	// check if the right fork is in usage rn, if yes it will wait here
	pthread_mutex_lock(philo->mutex_right_fork);
	pthread_mutex_lock(&philo->access->mutex_message);

	// current time is the difference bewteen time rn and the time
	// when the routine started
	current_time = get_time() - philo->time_program_starts;
// printf("current time: %lld\n")
	// if in the meantime a philosopher died, need to unlock mutexes
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(philo->mutex_right_fork);
		pthread_mutex_unlock(&philo->access->mutex_message);
		return ;
	}

	printf("%lld %d has taken a right fork\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);

	// same for left fork
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

	printf("%lld %d has taken a left fork\n", current_time, philo->id);
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
		// printf("philo died in eating\n");
		return ;
	}
	printf("%lld %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
	finished_eating_time = get_time() + philo->tt_eat;

// printf(BLU"\tcurrent:\t%lld\n\tfin eat:\t%lld\n"RESET, current_time, philo->finished_eating);
	while (get_time() <= finished_eating_time)
	{
		if (philosopher_died(philo) == true)
		{
		// printf("died in eating in while loop\n");
			pthread_mutex_unlock(philo->mutex_left_fork);
			pthread_mutex_unlock(philo->mutex_right_fork);
			return ;
		}
		// 100 just as smol random number
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
	printf("%lld %d is sleeping\n", current_time, philo->id);
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
	printf("%lld %d is thinking\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->access->mutex_message);
}

/* function checks if a philosopher already died in the process
 * returns false if no philosopher died
 * returns true if one philosopher died						*/
bool philosopher_died(t_philo *philo)
{
	// philosopher is dead if:
	//	- starved before eating

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
		// printf("BLA\n");
		return (true);
	}

	pthread_mutex_unlock(&philo->access->mutex_death);
	return (false);
}

