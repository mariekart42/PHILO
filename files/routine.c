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
    }


}

void eating(t_philo *philo)
{
	int64_t	current_time;

	usleep(philo->tt_eat * 1000);
	current_time = get_time() - philo->time_routine_start;

	pthread_mutex_lock(&philo->mutex_message);
	printf("%lld %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_message);

}

void sleeping(t_philo *philo)
{
	int64_t		current_time;

	current_time = get_time() - philo->time_routine_start;

	usleep(philo->tt_sleep * 1000);
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

	pthread_mutex_lock(&philo->mutex_death);



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
	if (philo_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_left_fork);
		pthread_mutex_unlock(&philo->mutex_message);
		return ;
	}

	printf("%lld %d Has taken a left fork\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(&philo->mutex_message);

	// same for right fork
	pthread_mutex_lock(&philo->mutex_right_fork);
	pthread_mutex_lock(&philo->mutex_message);

	if (philo_died(philo) == true)
	{
		pthread_mutex_unlock(&philo->mutex_right_fork);
		pthread_mutex_unlock(&philo->mutex_message);
		return ;
	}

	printf("%lld %d Has taken a right fork\n", current_time, philo->id)
	pthread_mutex_unlock(&philo->mutex_right_fork);
	pthread_mutex_unlock(&philo->mutex_message);
}


// !! finish grab fork function
//		write a "if died" function
//		-> not 100% sure about it

// sleeping, eating function prolly crap
//	-> prolly needs to protected with more mutexes lol
// really times 1000 for unsleep??

// how long is a philosopher thinking?