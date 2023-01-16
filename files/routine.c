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

    // while (1)
    // {

    // // grab forks
	// 	grab_forks(philo);

    // // eat

    // // sleep

    // // think
    // }

	while (grab_forks(philo) !=)
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

	printf("%lld %d Has taken a right fork\n", curr_time, s_philo->id);

	pthread_mutex_lock(&philo->mutex_right_fork);

}


// !! finish grab fork function
//		write a "if died" function
