/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/16 12:04:08 by mmensing         ###   ########.fr       */
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


#define RETURN


typedef struct s_data
{
	char		**av;
	int32_t		num_of_philos;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	bool		somebody_died;
	// t_philo		philo_access;
	int64_t		program_start_time;
	int32_t		meal_count;
	
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_msg;
	pthread_mutex_t		m_somebody_died;
	
	
}				t_data;

typedef struct s_philo
{	
	pthread_t		thread;
	// pthread_mutex_t	th_lock;
	
	// index of philosopher
	int32_t		id;
	
	// status if philo died
	bool		somebody_died;
	
	// time to eat, die and sleep
	int32_t		tt_eat;
	int32_t		tt_die;
	int32_t		tt_sleep;
	
	int32_t		last_ate;
	
	
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;


	t_data	*philo_data;
	
}				t_philo;

// testing
// void *something();
void error_msg(char *msg);


//		main
// void destroy_threads(t_philo *philos);


//		../files/handle_input.c
int64_t get_time();
int32_t check_for_valid_arg(char *av);
void check_and_set_input(t_data *data, int32_t ac, char **av_);

//		../files/edit_threads.c
void *test_routine(void *philos_);
void join_threads(t_philo *philos, t_data *data);
void create_threads(t_philo *philos, t_data *data);

//		../files/philo_shit.c


# endif