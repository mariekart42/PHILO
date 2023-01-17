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

void create_mutexes(t_philo *philos)
{
    int32_t i = 0;
// create philos amount of mutexes for forks
printf("ämount philoa: %d\n", philos->amount_philos);
    philos->mutex_forks = malloc(sizeof(pthread_mutex_t) * philos->amount_philos);
    if (!philos->mutex_forks)
        error_msg("Error! Failed to malloc for forks!");
    while (i < philos->amount_philos)
    {
        printf(GRN"loop check\n"RESET);
        if (pthread_mutex_init(&philos->mutex_forks[i], NULL))
            error_msg("Error! Failed to create mutex for fork!");
        i++;
    }

printf("check before seg\n");
// create mutex for left and right fork
    if (pthread_mutex_init(&philos->mutex_left_fork, NULL))
        error_msg("Error! Failed to create mutex for left fork!");
    if (pthread_mutex_init(&philos->mutex_right_fork, NULL))
        error_msg("Error! Failed to create mutex for right fork!");

// create mutex for messages
    if (pthread_mutex_init(&philos->mutex_message, NULL))
        error_msg("Error! Failed to create mutex for message!");

// create mutex for death of philosopher
    if (pthread_mutex_init(&philos->mutex_death, NULL))
        error_msg("Error! Failed to create mutex for death of philosopher!");

}

void init_threads(t_philo *philo, char **av)
{
    int32_t i = 0;

    while (i < philo->amount_philos)
    {
        philo[i].tt_die = ft_atoi(av[2]);
        philo[i].tt_eat = ft_atoi(av[3]);
        philo[i].tt_sleep = ft_atoi(av[4]);

        philo[i].id = i + 1;
        i++;
    }
}

void execute_threads(t_philo *philos)
{
    int32_t i = 0;
    printf("amount philos: %d\n", philos->amount_philos);
    while (i < philos->amount_philos)
    {
printf("thread: %d got created\n", philos[i].id);
    	// creating thread and pass current philosopher to routine function
		if (pthread_create(&philos[i].thread, NULL, (void *)philo_routine, &philos[i]))
			error_msg("Error! Failes to create thread!");
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

void destroy_mutexes(t_philo *philos)
{
	int32_t i = 0;
	
	// destroy mutexes for all forks
	while (i < philos->amount_philos)
	{
		if (pthread_mutex_destroy(&philos->mutex_forks[i]))
			error_msg("Error! Failed to destroy mutex for fork!");
		i++;
	}
	
	if (pthread_mutex_destroy(&philos->mutex_message))
		error_msg("Error! Failed to destroy mutex for messages!");
	
	if (pthread_mutex_destroy(&philos->mutex_death))
		error_msg("Error! Failed to destroy mutex for death");

	if (pthread_mutex_destroy(&philos->mutex_left_fork))
		error_msg("Error! Failed to destroy mutex for left_fork");
	if (pthread_mutex_destroy(&philos->mutex_right_fork))
		error_msg("Error! Failed to destroy mutex for right_fork");
	return ;
}