#include "../head/philo.h"

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

/* function checks if c is any kind of whitespace
 * returns 0 if c is whitespace
 * returns 1 if c is something but whitespace	*/
int32_t whitespace(char c)
{
	if ((c >= 1 && c <= 31) || c == 127)
		return (0);
	return (1);
}

/* function checks for valid input (only digits or whitespaces)
 * returns 1 for invalid input
 * returns 0 for valid input								*/
int32_t check_for_valid_arg(char *av)
{
	int32_t i = 0;

	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]) && whitespace(av[i]))
			return (1);
		i++;
	}
	return (0);
	// check later also if arguments make sense etc (if that makes sense lol)
}

void check_input(t_data *data, int32_t ac, char **av)
{
    int32_t i;

    i = 0;
    if (ac != 5 && ac != 6)
        error_msg("Wrong input! usage: ./philo <param> <param> <param> <param>");
	if (ft_atoi(av[1]) < 2)
		error_msg("Invalid input! Minimum 2 philosophers!");
	while (i < ac)
	{
		if (check_for_valid_arg(av[i]))
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
    if (data->tt_eat + data->tt_sleep > data->tt_die)
		error_msg("Invalid input! The time to eat and sleep must not exceed the time to die!");


}

void init_data(t_data *data, t_philo *philos, int32_t ac, char **av)
{
    data->av = av;
    data->amount_philos = ft_atoi(av[1]);

    // !! till now no need for the next 4 inits
    data->tt_die = ft_atoi(av[2]);
    data->tt_eat = ft_atoi(av[3]);
    data->tt_sleep = ft_atoi(av[4]);
    if (ac == 6)
		data->times_philo_eats = ft_atoi(av_[5]);

    // init philosophers with needed data

}

void create_mutexes(t_data *data)
{
    int32_t i = 0;

// create philos amount of mutexes for forks
    data->forks = malloc(sizeof(pthread_mutex_t) * data->amount_philos);
    if (!data->forks)
        error_msg("Error! Failed to malloc for forks!");
    while (i < data->amount_philos)
    {
        if (pthread_mutex_init(&data->mutex_forks[i], NULL))
            error_msg("Error! Failed to create mutex for fork!");
        i++;
    }

// create mutex for left and right fork
    if (pthread_mutex_init(&data->mutex_left_fork, NULL))
        error_msg("Error! Failed to create mutex for left fork!");
    if (pthread_mutex_init(&data->mutex_right_fork, NULL))
        error_msg("Error! Failed to create mutex for right fork!");

// create mutex for messages
    if (pthread_mutex_init(&data->mutex_message, NULL))
        error_msg("Error! Failed to create mutex for message!");
}

void init_threads(t_data *data, t_philo *philo)
{
    int32_t i = 0;

    while (i < data->amount_philos)
    {
        philo[i].tt_die = data->av[2];
        philo[i].tt_eat = data->av[3];
        philo[i].tt_sleep = data->av[4];

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
    waiting_for_threads(data, philos);
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

void philo_routine(t_philo *philo)
{
    philo->time_routine_start = get_time();
}

int main(int32_t ac, char **av)
{
    t_data  data;
    t_philo *philos = NULL;

    // check for valid input
    check_input(&data, ac, av);

    init_data(&data, philos, ac, av);

    philos = malloc(sizeof(t_philo) * data.num_of_philos);
    if (!philos)
        error_msg("Error! Failed to malloc for philosopher!\n");

// create mutexes:
    // mutex for each fork per philosopher
    // mutex for left and right fork
    // mutex for printing messages
    create_mutexes(&data);

// init philosopher with needed data:
    init_threads(&data, philos);

// create threads:
    execute_threads(&data, philos);

// destroy mutexes:

		

}