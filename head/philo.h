/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:30:14 by mmensing          #+#    #+#             */
/*   Updated: 2023/02/01 20:09:43 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
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
	char			**av;
	int32_t			amount_philos;
	int64_t			start_program;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	mutex_death;
	bool			philo_died;
}				t_data;

typedef struct s_philo
{	
	int32_t			eaten_meals;
	int32_t			amount_philos;
	int32_t			id;
	int64_t			time_routine_start;
	int64_t			time_program_starts;
	int64_t			finished_eating;
	int64_t			tt_die;
	int64_t			tt_eat;
	int64_t			tt_sleep;
	int64_t			times_philo_eats;
	pthread_t		thread;
	pthread_mutex_t	*mutex_left_fork;
	pthread_mutex_t	*mutex_right_fork;
	t_data			*access;
}				t_philo;

//      main.c
void	philo_routine(t_philo *philo);

//      mutex.c
void	create_mutexes(t_data *data);
void	destroy_mutexes(t_data *data);

//      threads.c
void	init_threads(t_philo *philo, t_data *data, char **av, int32_t ac);
void	execute_threads(t_philo *philos);
void	waiting_for_threads(t_philo *philos);

//      routine.c
void	grab_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
bool	philosopher_died(t_philo *philo);

//      utils.c
int32_t	whitespace(char c);
void	error_msg(char *msg);
int64_t	get_time(void);
void	init_data(t_data *data, int32_t ac, char **av);
int32_t	check_for_valid_arg(char *av);

#endif