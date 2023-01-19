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

    check_input(ac, av);
    data.amount_philos = ft_atoi(av[1]);
    philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (!philos)
        error_msg("Error! Failed to malloc for philosopher!\n");
    philos->amount_philos = ft_atoi(av[1]);

// create mutexes:
    // mutex for each fork per philosopher
    // mutex for printing messages
    create_mutexes(&data);

// init philosopher with needed data:
    init_threads(philos, &data, av);

// create threads:
    execute_threads(philos);
printf(GRN"check\n"RESET);

// waiting for threads:
    waiting_for_threads(philos);

// destroy mutexes:
    destroy_mutexes(&data);

    free(philos);
    free(data.mutex_forks);
	return(0);
}



// init left and right fork to the philos