/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/13 05:12:36 by mmensing         ###   ########.fr       */
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
	
	// init mutex -> called th_lock
	pthread_mutex_init(&philos.th_lock, NULL);

	check_and_set_input(&data, ac, av);
	// exit(0);
	create_threads(&philos, &data);
	
	// destroy_threads(&philos, &data);
	
	join_threads(&philos, &data);
	
	// destroy mutex
	pthread_mutex_destroy(&philos.th_lock);

	// error happens while destroy mutex -> read into it


}
