/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/14 00:58:11 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// for threads
# include <pthread.h>

// for get time 
#include <sys/time.h>

// libft
# include "../include/libft/libft.h"


typedef struct s_philo
{
	int32_t	test_val;
	
	pthread_t		thread;
	pthread_mutex_t	th_lock;
	bool			*forks;
	int32_t			*philos;
	
}				t_philo;

typedef struct s_data
{
	char		**av;
	int32_t		num_of_philos;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	t_philo		philo_access;
	int32_t		id;
	
}				t_data;

// testing
// void *something();
void error_msg(char *msg);


//		main
// void destroy_threads(t_philo *philos);


//		../files/check_input.c
bool check_for_valid_arg(char *av);
void check_and_set_input(t_data *data, int32_t ac, char **av_);

//		../files/edit_threads.c
void *test_routine(void *philos_);
void join_threads(t_philo *philos, t_data *data);
void create_threads(t_philo *philos, t_data *data);

//		../files/philo_shit.c


# endif