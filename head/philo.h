/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2023/01/15 19:24:44 by mmensing         ###   ########.fr       */
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



typedef struct s_data
{
    int32_t     amount_philos;
    char        **av;
    
//  !! till now i dont need the next 4 here!
    // int32_t     tt_die;
    // int32_t     tt_eat;
    // int32_t     tt_sleep;
    // int32_t     times_philo_eats;
    
    // array of forks -> amount of philosophers forks
    pthread_mutex_t *mutex_forks;
    pthread_mutex_t mutex_left_fork;
    pthread_mutex_t mutex_right_fork;
    pthread_mutex_t mutex_message;
    
	
}				t_data;

typedef struct s_philo
{	
    pthread_t   thread;
    
    int32_t     tt_die;
    int32_t     tt_eat;
    int32_t     tt_sleep;
    int32_t     times_philo_eats;
    
    int64_t     time_routine_start;
	
}				t_philo;



# endif