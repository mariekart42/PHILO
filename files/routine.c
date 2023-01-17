#include "../head/philo.h"

void philo_routine(t_philo *philo)
{
    philo->time_routine_start = get_time();

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

    // grab forks
		grab_forks(philo);

    // eat
		eating(philo);

    // sleep
		sleeping(philo);

    // think
		thinking(philo);

		if (philosopher_died(philo) == true)
		{
			printf(MAG"DEATTTTTTTHHHHH\n"RESET);
			exit(0);
		}
    }


}

void eating(t_philo *philo)
{
	int64_t		current_time;
	// int64_t		finished_eating_time;

	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_left_fork);
		pthread_mutex_unlock(&philo->mutex_right_fork);
		return ;
	}
	current_time = get_time() - philo->time_routine_start;
	philo->finished_eating = current_time + philo->tt_eat;

	pthread_mutex_lock(&philo->mutex_message);
	printf("%lld %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_message);

	while (current_time <= philo->finished_eating)
	{
		if (philosopher_died(philo) == true)
		{
			pthread_mutex_unlock(&philo->mutex_left_fork);
			pthread_mutex_unlock(&philo->mutex_right_fork);
			return ;
		}
		// 100 just as smol random number
		usleep(100);
	}
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(&philo->mutex_right_fork);
}

void sleeping(t_philo *philo)
{
	int64_t		current_time;
	int64_t		finished_sleeping_time;

	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_left_fork);
		pthread_mutex_unlock(&philo->mutex_right_fork);
		return ;
	}

	current_time = get_time() - philo->time_routine_start;
	finished_sleeping_time = current_time + philo->tt_sleep;

	pthread_mutex_lock(&philo->mutex_message);
	printf("%lld %d is sleeping\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_message);
}

void thinking(t_philo *philo)
{
	int64_t		current_time;

	current_time = get_time() - philo->time_routine_start;

// how long is he thinking lol??

	pthread_mutex_lock(&philo->mutex_message);
	printf("%lld %d is thinking\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_message);
}

/* function checks if a philosopher already died in the process
 * returns false if no philosopher died
 * returns true if one philosopher died						*/
bool philosopher_died(t_philo *philo)
{
	// philosopher is dead if:
	//	- starved before eating

	int64_t		current_time;

	pthread_mutex_lock(&philo->mutex_death);

	if (philo->philo_died == true)
	{
		pthread_mutex_unlock(&philo->mutex_death);
		return (true);
	}
	if ((get_time() - philo->finished_eating) >= philo->tt_die)
	{
		pthread_mutex_lock(&philo->mutex_message);
		current_time = get_time() - philo->time_routine_start;
		printf(RED"%lld %d died\n"RESET, current_time, philo->id);
		pthread_mutex_unlock(&philo->mutex_message);
		philo->philo_died = true;
		pthread_mutex_unlock(&philo->mutex_death);
		return (true);
	}

	pthread_mutex_unlock(&philo->mutex_death);
	return (false);
}

void grab_forks(t_philo *philo)
{
	int64_t current_time;

	// check if the left fork is in usage rn, if yes it will wait here
	pthread_mutex_lock(&philo->mutex_left_fork);
	pthread_mutex_lock(&philo->mutex_message);

	// current time is the difference bewteen time rn and the time
	// when the routine started
	current_time = get_time() - philo->time_routine_start;

	// if in the meantime a philosopher died, need to unlock mutexes
	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_left_fork);
		pthread_mutex_unlock(&philo->mutex_message);
		return ;
	}

	printf("%lld %d has taken a fork\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(&philo->mutex_message);

	// same for right fork
	pthread_mutex_lock(&philo->mutex_right_fork);
	pthread_mutex_lock(&philo->mutex_message);

	if (philosopher_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_right_fork);
		pthread_mutex_unlock(&philo->mutex_message);
		return ;
	}

	printf("%lld %d has taken a fork\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_right_fork);
	pthread_mutex_unlock(&philo->mutex_message);
}
