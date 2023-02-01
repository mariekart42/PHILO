#include "../head/philo.h"

void	init_threads(t_philo *philo, t_data *data, char **av, int32_t ac)
{
	int32_t	i;

	i = 0;
	while (i < data->amount_philos)
	{
		philo[i].id = i + 1;
		philo[i].tt_die = ft_atoi(av[2]);
		philo[i].tt_eat = ft_atoi(av[3]);
		philo[i].tt_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].times_philo_eats = ft_atoi(av[5]);
		// philo[i].times_philo_eats = ft_atoi(av[5]);
		philo[i].eaten_meals = 0;
		philo[i].finished_eating = data->start_program;
		philo[i].mutex_right_fork = &data->mutex_forks[i];
		philo[i].mutex_left_fork = \
							&data->mutex_forks[(i + 1) % data->amount_philos];
		philo[i].access = data;
		philo[i].time_program_starts = data->start_program;
		philo[i].amount_philos = data->amount_philos;
		i++;
	}
}

void	execute_threads(t_philo *philos)
{
	int32_t	i;

	i = 0;
	printf("amount philos: %d\n", philos->amount_philos);
	while (i < philos->amount_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, \
											(void *)philo_routine, &philos[i]))
			error_msg("Error! Failed to create thread!");
		i++;
		usleep(100);
	}
}

void	waiting_for_threads(t_philo *philos)
{
	int32_t	i;

	i = 0;
	while (i < philos->amount_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			error_msg("Error! Failed to execute thread!");
		i++;
	}
}
