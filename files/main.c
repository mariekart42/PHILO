#include "../head/philo.h"

void	philo_routine(t_philo *philo)
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
			exit(0);
		sleeping(philo);
		thinking(philo);
	}
}

int	main(int32_t ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	init_data(&data, ac, av);
	create_mutexes(&data);
	philos = malloc(sizeof(t_philo) * data.amount_philos);
	if (!philos)
		error_msg("Error! Failed to malloc for philosopher!\n");
	init_threads(philos, &data, av, ac);
	execute_threads(philos);
	waiting_for_threads(philos);
	destroy_mutexes(&data);
	free(philos);
	free(data.mutex_forks);
	return (0);
}
