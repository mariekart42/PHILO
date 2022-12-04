/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return_multi_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:11:53 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/04 21:42:13 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_threads
{
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
	int32_t			*threads_array;
	
}				t_threads;

typedef struct s_data
{
	t_threads	*philos;
}				t_data;

int	ft_atoi(const char *str)
{
	int		val;
	int		minus;
	int		i;

	val = 0;
	minus = 1;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] != '\0') && (str[i] >= 48 && str[i] <= 57))
	{
		val = 10 * val + str[i] - 48;
		i++;
	}
	return (val * minus);
}

void *get_result(void *args)
{
	printf("in  get_result\n");
	int32_t val;
	int32_t *result;

	val = 69;
	result = malloc(sizeof(int32_t));
	return ((void *)result);
}

void	create_ac_amount_of_threads(t_threads *th, t_data *data, int32_t iters)
{
	printf("\nin thread: \n");
	
	// create threads
	int32_t i = 0;
	while (i < iters)
	{
		// printf("before creating\n");
		if (pthread_create(&th->thread_id, NULL, &get_result, NULL))
		{
			printf("something went wrong creating thread\n");
			exit(EXIT_FAILURE);
		}
		// printf("after creating\n");
		i++;
		printf("created thread: %d\n", i);
	}
	i = 0;
	int32_t *result;
	// waiting for thread to finish and get return value
	while (i < iters)
	{
		printf("joining here\n");
		pthread_mutex_lock(&th->mutex);
		if (pthread_join(th->thread_id, (void **)&result))
		{
			printf("something went wrong waiting for thread\n");
			exit(EXIT_FAILURE);
		}
		i++;
		printf("waited for thread: %d\n", i);
		printf("address of thread: %p\n", result);
		pthread_mutex_unlock(&th->mutex);
		// if (result)
		// 	free(result);
	}




	printf("thread end: \n\n");
}

int main(int32_t ac, char **av)
{
	if (ac != 2)
	{
		printf("invalid input\n");
		return (1);
	}
	
	t_data	data;
	t_threads th;

	create_ac_amount_of_threads(&th, &data, ft_atoi(av[1]));
	pthread_mutex_destroy(&th.mutex);
}