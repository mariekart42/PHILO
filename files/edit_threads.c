/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 05:08:58 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/13 05:12:45 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// return val needs always to be a void pointer 
void *test_routine(void *philos_)
{
	t_philo *philos;
	
	philos = (t_philo *)philos_;
	// printf("i'm a thread lol\n");
	// printf("data: %p\n", data);
	pthread_mutex_lock(&philos->th_lock);
	philos->test_val++;
	printf("data.test_val: %d\n", philos->test_val);
	pthread_mutex_unlock(&philos->th_lock);

	// protect programm for race condition
	// pthread_mutex_lock(&data->mutex);
	// brr++;
	// pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

void create_threads(t_philo *philos, t_data *data)
{
	int32_t i = 0;

	// init mutex
	// pthread_mutex_init(&philos->th_lock, NULL);
	
	printf("nums of philos: %d\n", data->nums_of_philos);

	while (i < data->nums_of_philos)
	{
		// printf("check\n");
		
		// creating thread
		if (pthread_create(&philos[i].thread, NULL, &test_routine, (void *)philos))
			error_msg("threading faild");
			
		i++;
		printf("thread %d got created\n", i);
	}
}

void join_threads(t_philo *philos, t_data *data)
{
	int32_t i;
	i = 0;
	
	// two different while loops cause otherwise thread gets created and when we wait for it right after it
	// processes run successively and not at the same time
	while (i < data->nums_of_philos)
	{
		// waiting for thread
		// here we just need the value of thread so can use philos[i]
		if (pthread_join(philos[i].thread, NULL))
			error_msg("waiting for thread failed");
			
		i++;
		printf("waited for thread %d\n", i);
	}
}

