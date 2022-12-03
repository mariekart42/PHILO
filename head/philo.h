/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/03 23:11:44 by mmensing         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	char			**av;
	int32_t			*philos;
}				t_philo;

// testing
void *something();
void error_msg(char *msg);


//		../files/check_input.c
void check_for_valid_arg(char *av);
void check_and_set_input(t_philo *data, int32_t ac, char **av_);



# endif