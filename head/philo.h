/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/12 18:26:02 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

// libft
# include "../include/libft/libft.h"

typedef struct s_data
{
	char			**av;
	int32_t		nums_of_philos;
	
}				t_data;

typedef struct s_philo
{
	int32_t	test_val;
	pthread_t		thread;
	pthread_mutex_t	th_lock;
	
}				t_philo;


// testing
// void *something();
void error_msg(char *msg);


//		main
// void destroy_threads(t_philo *philos);


//		../files/check_input.c
void check_for_valid_arg(char *av);
void check_and_set_input(t_data *data, int32_t ac, char **av_);


# endif