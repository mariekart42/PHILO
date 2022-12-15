/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/15 00:09:48 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// delete later, just for testing
// int32_t brr = 0;
// pthread_mutex_t	mutex;

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void init_threads(t_philo *philos, t_data *data)
{
	int32_t i = 0;

	while (i < data->num_of_philos)
	{
		printf(GRN"debug check\n"RESET);

		philos[i].id = i + 1;
		printf(YEL"current id: %d\n"RESET, philos[i].id);
		philos[i].dead = data->time_to_die;
		philos[i].eat = data->time_to_eat;
		philos[i].sleep = data->time_to_sleep;
		philos[i].meal_count = 0;
		
		// philo[i].last_time_ate = info->start;
		// philo[i].right_fork = &info->forks[i];
		// philo[i].left_fork = &info->forks[(i + 1) % info->number_of_philo];
		// philo[i].philo_info = info;
		// philo[i].start_of_the_program = info->start;
		// philo[i].nbr_of_philo = info->number_of_philo;

		i++;
	}

}


// function returns 1 if something goes wrong
// returns 0 if everthing went well
int32_t init_mutexes(t_data *data)
{
	int32_t i = 0;
	
	// for every philosopher we need one fork
	// a fork is protected with one mutex, fo we need 'amount of philos' fork-mutexes
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (data->forks == NULL)
		error_msg("Error! Failed to malloc for forks!");
		
	while (i < data->num_of_philos)
	{
		// creating a mutex for each fork
		if (pthread_mutex_init(&data->forks[i], NULL))
			error_msg("Error! Failed to create mutex for fork!");
		i++;
	}
	
	// create here mutex also for displaying messages
	if (init_mutex_init(&data->msg, NULL))
		error_msg("Error! Failed to create mutex for 'msg'!");
		
	// create here mutex for status if somebody died
	if (init_mutex_init(&data->somebody_died, NULL))
		error_msg("Error! Failed to create mutex for 'somebody_died'!");
	
	return (0);
}

void destroy_mutexes(t_data *data)
{
	return ;
}

int main(int32_t ac, char *av[])
{
	t_philo	*philos = NULL;
	t_data	data;
	
	
	// printf(GRN"debug check\n"RESET);
	
	// check for amount and if only digits
	// set av and all arguments to struct varibles
	// set all forsk to true
	check_and_set_input(&data, ac, av);
	
	
	// init mutexes for:
	//	- philo_amount of forks
	//	- printing messages to the console
	//	- if somebody died
	init_mutexes(&data);
	
	
	// malloc for philos the amount af philos
	philos = malloc(sizeof(t_philo) * data.num_of_philos);
	if (!philos)
		error_msg("malloc philosophers failed");
	
	init_threads(philos, &data);
	
	// creating nums_of_philos amount of threads
	// calling routine function (passing current philo to it)
	create_threads(philos, &data);
			
	
	join_threads(philos, &data);
	
	
	// destroy mutexes
	destroy_mutexes(&data);
	// pthread_mutex_destroy(&philos->th_lock);
}
