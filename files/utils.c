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

// void init_data(t_data *data, t_philo *philos, int32_t ac, char **av)
// {
//     data->av = av;
//     data->amount_philos = ft_atoi(av[1]);

//     // !! till now no need for the next 4 inits
//     // data->tt_die = ft_atoi(av[2]);
//     // data->tt_eat = ft_atoi(av[3]);
//     // data->tt_sleep = ft_atoi(av[4]);
//     // if (ac == 6)
// 	// 	data->times_philo_eats = ft_atoi(av_[5]);

// }

void create_mutexes(t_data *data, t_philo *philos)
{
    int32_t i = 0;

// create philos amount of mutexes for forks
    philos->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->amount_philos);
    if (!philos->mutex_forks)
        error_msg("Error! Failed to malloc for forks!");
    while (i < data->amount_philos)
    {
        if (pthread_mutex_init(&philos->mutex_forks[i], NULL))
            error_msg("Error! Failed to create mutex for fork!");
        i++;
    }

// create mutex for left and right fork
    if (pthread_mutex_init(&philos->mutex_left_fork, NULL))
        error_msg("Error! Failed to create mutex for left fork!");
    if (pthread_mutex_init(&philos->mutex_right_fork, NULL))
        error_msg("Error! Failed to create mutex for right fork!");

// create mutex for messages
    if (pthread_mutex_init(&philos->mutex_message, NULL))
        error_msg("Error! Failed to create mutex for message!");
}

void init_threads(t_data *data, t_philo *philo)
{
    int32_t i = 0;

    while (i < data->amount_philos)
    {
        philo[i].tt_die = ft_atoi(data->av[2]);
        philo[i].tt_eat = ft_atoi(data->av[3]);
        philo[i].tt_sleep = ft_atoi(data->av[4]);

        philo[i].id = i + 1;
        i++;
    }
}

void execute_threads(t_data *data, t_philo *philos)
{
    int32_t i = 0;

    while (i < data->amount_philos)
    {
    	// creating thread and pass current philosopher to routine function
		if (pthread_create(&philos[i].thread, NULL, (void *)philo_routine, &philos[i]))
			error_msg("Error! Failes to create thread!");
        i++;
    }
}

void waiting_for_threads(t_data *data, t_philo *philos)
{
    int32_t i = 0;

    while (i < data->amount_philos)
    {
        if (pthread_join(philos[i].thread, NULL))
            error_msg("Error! Failed to execute thread!");
        i++;

    }
}