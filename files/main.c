#include "../head/philo.h"

// av[1] = amount philos
// av[2] = tt die
// av[3] = tt eat
// av[4] = tt sleep
// ( av[5] = meal times )

int main(int32_t ac, char **av)
{
    // t_data  data;
    t_philo *philos = NULL;

    check_input(ac, av);
// printf("am: %d\n", philos->amount_philos);
    philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (!philos)
        error_msg("Error! Failed to malloc for philosopher!\n");
    philos->amount_philos = ft_atoi(av[1]);

    // init_data(&data, philos, ac, av);

// create mutexes:
    // mutex for each fork per philosopher
    // mutex for left and right fork
    // mutex for printing messages
    create_mutexes(philos);
printf(GRN"check\n"RESET);

// init philosopher with needed data:
    init_threads(philos, av);

// create threads:
    execute_threads(philos);

// waiting for threads:
    waiting_for_threads(philos);

// destroy mutexes:
    destroy_mutexes(philos);
		
}



// init left and right fork to the philos