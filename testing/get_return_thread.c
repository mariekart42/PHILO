/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:01:30 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/04 16:11:35 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

void *get_return()
{
	printf("in thread:\n");
	int32_t *result;
	int32_t val;
	
	val = 69;
	result = malloc(sizeof(int32_t));
	*result = val;
	return ((void *)result);

}

int main()
{
	int32_t *something;

	// create mutex
	pthread_mutex_t mutex;
	
	pthread_mutex_init(&mutex, NULL);
	
	// create thread
	pthread_t thread;
	
	if (pthread_create(&thread, NULL, &get_return, NULL))
		return (1);
	
	// wait for thread to finish
	// recieving return value of 'get_return' in 'something'
	if (pthread_join(thread, (void **)&something))
		return (2);
		
	printf("value in main: %d\n", *something);
	free(something);
}