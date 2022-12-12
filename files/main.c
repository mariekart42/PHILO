/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/12 19:47:10 by mmensing         ###   ########.fr       */
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

// return val needs always to be a void pointer 
void *ad_one(void *philos_)
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
		if (pthread_create(&philos[i].thread, NULL, &ad_one, (void *)philos))
			error_msg("threading faild");
			
		i++;
		printf("thread %d got created\n", i);
	}
	
	// i = 0;
	
	// // two different while loops cause otherwise thread gets created and when we wait for it right after it
	// // processes run successively and not at the same time
	// while (i < data->nums_of_philos)
	// {
	// 	// waiting for thread
	// 	// here we just need the value of thread so can use philos[i]
	// 	if (pthread_join(philos[i].thread, NULL))
	// 		error_msg("waiting for thread failed");
			
	// 	i++;
	// 	printf("waited for thread %d\n", i);
	// }
	
	// printf("reached point after waiting loop\n");
	
	// // after execution always destroy mutex
	// pthread_mutex_destroy(&philos->th_lock);
	// printf("reached point after destroy mutex\n");
}

// void destroy_threads(t_philo *philos, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nums_of_philos)
// 	{
// 		pthread_mutex_lock(&philos[i].th_lock);
// 		pthread_mutex_unlock(&philos[i].th_lock);
// 		pthread_join(philos[i].thread, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->nums_of_philos)
// 	{
// 		// pthread_mutex_destroy(&philos[i].th_lock);
// 		i++;
// 		printf("destroyed mutex %d\n", i);
// 	// 	// free(philos[i].name);
// 	}
// 		printf("still alright\n");
// 	// free(philos);
// }

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
