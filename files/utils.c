#include "../head/philo.h"

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int64_t get_time()
{
    struct timeval  time;

    if (gettimeofday(&time, NULL) < 0)
        error_msg("Error! Failed to get time of day!");
    return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void create_mutexes(t_data *data)
{
    int32_t i = 0;

    data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->amount_philos);
    if (!data->mutex_forks)
        error_msg("Error! Failed to malloc for forks!");

// create philos amount of mutexes for forks
    while (i < data->amount_philos)
    {
        if (pthread_mutex_init(&data->mutex_forks[i], NULL))
            error_msg("Error! Failed to create mutex for fork!");
        i++;
    }

// create mutex for messages
    if (pthread_mutex_init(&data->mutex_message, NULL))
        error_msg("Error! Failed to create mutex for message!");

// create mutex for death of philosopher
    if (pthread_mutex_init(&data->mutex_death, NULL))
        error_msg("Error! Failed to create mutex for death of philosopher!");
}

void init_threads(t_philo *philo, t_data *data, char **av)
{
    int32_t i = 0;

    while (i < data->amount_philos)
    {
        philo[i].id = i + 1;
        philo[i].tt_die = ft_atoi(av[2]);
        philo[i].tt_eat = ft_atoi(av[3]);
        philo[i].tt_sleep = ft_atoi(av[4]);
        philo[i].eaten_meals = 0;
        philo[i].finished_eating = data->start_program;
        philo[i].mutex_right_fork = &data->mutex_forks[i];
        philo[i].mutex_left_fork = &data->mutex_forks[(i + 1) % data->amount_philos];
        philo[i].access = data;
        philo[i].time_program_starts = data->start_program;
        philo[i].amount_philos = data->amount_philos;
        philo[i].philo_died = false;
        i++;
    }
}

void execute_threads(t_philo *philos)
{
    int32_t i = 0;

    while (i < philos->amount_philos)
    {
    	// creating thread and pass current philosopher to routine function
		if (pthread_create(&philos[i].thread, NULL, (void *)philo_routine, &philos[i]))
			error_msg("Error! Failed to create thread!");
printf(YEL"thread: %d got created\n"RESET, philos[i].id);
        i++;
    }
}

void waiting_for_threads(t_philo *philos)
{
    int32_t i = 0;

    while (i < philos->amount_philos)
    {
    printf("waited for thread: %d\n", philos->id);
        if (pthread_join(philos[i].thread, NULL))
            error_msg("Error! Failed to execute thread!");
        i++;
    }
}

void destroy_mutexes(t_data *data)
{
	int32_t i = 0;
	
	// destroy mutexes for all forks
	while (i < data->amount_philos)
	{
		if (pthread_mutex_destroy(&data->mutex_forks[i]))
			error_msg("Error! Failed to destroy mutex for fork!");
		i++;
	}
	
	if (pthread_mutex_destroy(&data->mutex_message))
		error_msg("Error! Failed to destroy mutex for messages!");
	
	if (pthread_mutex_destroy(&data->mutex_death))
		error_msg("Error! Failed to destroy mutex for death");
}