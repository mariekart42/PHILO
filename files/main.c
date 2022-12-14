/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/14 00:51:49 by mmensing         ###   ########.fr       */
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


int main(int32_t ac, char *av[])
{
	t_philo	philos;
	t_data	data;
	
	philos.test_val = 0;
	
	// check for amount and if only digits
	// set av and all arguments to struct varibles
	// set all forsk to true
	check_and_set_input(&data, ac, av);
	
	// init mutex -> called th_lock
	pthread_mutex_init(&philos.th_lock, NULL);
	
	// creating nums_of_philos amount of threads
	// calling routine function (passing current philo to it)
	create_threads(&philos, &data);
			
	
	join_threads(&philos, &data);
	
	
	// destroy mutex
	pthread_mutex_destroy(&philos.th_lock);
}
