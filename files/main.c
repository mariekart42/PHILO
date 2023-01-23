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

    init_data(&data, ac, av);
    create_mutexes(&data);
    philos = malloc(sizeof(t_philo) * data.amount_philos);
    if (!philos)
        error_msg("Error! Failed to malloc for philosopher!\n");
    init_threads(philos, &data, av);
    execute_threads(philos);
    waiting_for_threads(philos);
    destroy_mutexes(&data);
    free(philos);
    free(data.mutex_forks);
	return(0);
}
