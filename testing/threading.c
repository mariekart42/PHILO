/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:29:01 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/03 22:43:38 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../head/philo.h"

// race condition protector
pthread_mutex_t mutex;

int brr = 0;

void error_msg(char *msg)
{
	// write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

// return val needs always to be a void pointer 
void *something()
{
	printf("i'm a thread lol\n");
	
	// protect programm for race condition
	pthread_mutex_lock(&mutex);
	brr++;
	pthread_mutex_unlock(&mutex);
	return(NULL);
}

int  main()
{
	// creating a thread
	pthread_t t1;
	pthread_t t2;
	
	// initioalize mutex variable
	pthread_mutex_init(&mutex, NULL);

	// cheaking if threading was sucsessfull
	// returns 0 if success, somthing else if not
	if (pthread_create(&t1, NULL, &something, NULL))
		error_msg("threading faild");
	if (pthread_create(&t2, NULL, &something, NULL))
		error_msg("threading faild");
	
	// always need to wait for threads -> called join (dunno why)
	// also checking for waiting
	if (pthread_join(t1, NULL))
		error_msg("waiting for thread failed");
	if (pthread_join(t2 , NULL))
		error_msg("waiting for thread failed");
	
	// destroy mutex
	pthread_mutex_destroy(&mutex);

}