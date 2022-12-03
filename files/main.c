/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/03 23:12:31 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// delete later, just for testing
int32_t brr = 0;
// pthread_mutex_t	mutex;

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

// return val needs always to be a void pointer 
void *ad_one(void *data)
{
	printf("i'm a thread lol\n");
	// protect programm for race condition
	// pthread_mutex_lock(&data->mutex);
	brr++;
	// pthread_mutex_unlock(&data->mutex);
	return(NULL);
}

void create_threads(t_philo *data, int32_t nums_of_philos)
{
	int32_t i = 0;

	// init mutex
	pthread_mutex_init(&data->mutex, NULL);
printf("nums of philoes: %d\n", nums_of_philos);
	while (i < nums_of_philos)
	{
printf("check\n");
		// creating thread
		// need adress here so not threads[i] but threads+i!!
		if (pthread_create(&data->thread, NULL, &ad_one, NULL))
			error_msg("threading faild");
		data->philos[i] = (int32_t)data->thread;
		i++;
		printf("thread %d got created\n", i);
	}
	
	i = 0;
	// two different while loops cause otherwise thread gets created and when we wait for it right after it
	// processes run successively and not at the same time
	while (i < nums_of_philos)
	{
		// waiting for thread
		// here we just need the value of thread so can use threads[i]
		data->thread = data->philos[i];
		if (pthread_join(&data->thread, NULL))
			error_msg("waiting for thread failed");
		i++;
		printf("waited for thread %d\n", i);
	}
	
	// // after execution always destroy mutex
	// pthread_mutex_destroy(&mutex);
}

int main(int32_t ac, char *av[])
{
	t_philo	data;
	
	check_and_set_input(&data, ac, av);
	create_threads(&data, ft_atoi(av[1]));
}