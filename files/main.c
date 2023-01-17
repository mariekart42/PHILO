#include "../head/philo.h"

// av[1] = amount philos
// av[2] = tt die
// av[3] = tt eat
// av[4] = tt sleep
// ( av[5] = meal times )

int main(int32_t ac, char **av)
{
    t_data  data;
    t_philo *philos = NULL;

// actually no need of these 2
    data.av = av;
    data.amount_philos = ft_atoi(av[1]);

    philos->amount_philos = ft_atoi(av[1]);

    // check for valid input
    check_input(ac, av);

    // init_data(&data, philos, ac, av);

    philos = malloc(sizeof(t_philo) * data.amount_philos);
    if (!philos)
        error_msg("Error! Failed to malloc for philosopher!\n");

// create mutexes:
    // mutex for each fork per philosopher
    // mutex for left and right fork
    // mutex for printing messages
    create_mutexes(&data, philos);

// init philosopher with needed data:
    init_threads(&data, philos);

// create threads:
    execute_threads(&data, philos);

// waiting for threads:
    waiting_for_threads(&data, philos);

// destroy mutexes:

		

}