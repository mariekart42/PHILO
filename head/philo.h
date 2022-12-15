/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/15 00:50:47 by mmensing         ###   ########.fr       */
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


//colour shit
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"



typedef struct s_philo
{
	int32_t	test_val;
	
	pthread_t		thread;
	pthread_mutex_t	th_lock;
	
	int32_t		id;
	int32_t		dead;
	int32_t		eat;
	int32_t		sleep;
	int32_t		meal_count;
	int64_t		starting_time;
	int32_t		last_ate;
	
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;


	t_data	*philo_data;
	
}				t_philo;

typedef struct s_data
{
	char		**av;
	int32_t		num_of_philos;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	bool		somebody_died;
	t_philo		philo_access;
	
	pthread_mutex_t			*forks;
	pthread_mutex_t		msg;
	pthread_mutex_t		dead;
	
	
}				t_data;

// testing
// void *something();
void error_msg(char *msg);


//		main
// void destroy_threads(t_philo *philos);


//		../files/handle_input.c
int64_t get_time();
bool check_for_valid_arg(char *av);
void check_and_set_input(t_data *data, int32_t ac, char **av_);

//		../files/edit_threads.c
void *test_routine(void *philos_);
void join_threads(t_philo *philos, t_data *data);
void create_threads(t_philo *philos, t_data *data);

//		../files/philo_shit.c


# endif