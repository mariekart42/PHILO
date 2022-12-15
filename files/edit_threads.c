/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 05:08:58 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/15 01:08:15 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// checks if somebody died
// changes bool variable to
// true -> if somebody died
// false -> if everybody is alive
void somebody_died(t_philo *philo)
{
	
}



void grab_forks(t_philo *philo)
{
	int64_t	curr_time;
	
	
// ------------------ for right forks -----------------------------------------
	// locking mutex for printing message and right fork
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->philo_data->msg);
	
	// get current time
	curr_time = get_time() - philo->starting_time;
	
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->philo_data->msg);
		return ;
	}
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->philo_data->msg);
		return ;
	}
	// printing unlocking mutex for printing the message
	printf("%lld %d Has taken a right fork\n", curr_time, philo->id);
	pthread_mutex_unlock(&philo->philo_data->msg);
	
	
// ------------------ now for left forks -----------------------------------------
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->philo_data->msg);
	
	// get current time again cause time has passed
	curr_time = get_time() - philo->starting_time;
	
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->philo_data->msg);
		return ;
	}
	printf("%lld %d Has taken a left fork\n", curr_time, philo->id);
	
	// unlock mutex for printing message
	pthread_mutex_unlock(&philo->philo_data->msg);
}

void *philo_routine(t_philo *philo)
{
	
	// getting time when the thread starts
	philo->starting_time = get_time();
	philo->last_ate = philo->starting_time;
	printf("current id: %d\n", philo->id);
	// get current timestamp
	
	// sleeping here if philo is uneven -> not sure about the time
	if (philo->id % 2 == 0)
	{
		// waiting longer if over 100 philos
		if (philo->philo_data->num_of_philos > 100)
			usleep(100);
		else
			usleep(1500);
	}

	while (1)
	{
		grab_forks(philo);

		// eating();
		
		if (somebody_died(philo))
			break ;
		
		// break condition if the amount of times to eat got reached
		
		sleeping(philo);
		
		thinking(philo);
	}
	return (NULL);
}

void create_threads(t_philo *s_philos, t_data *s_data)
{
	int32_t i = 0;
	
	printf("nums of philos: %d\n", s_data->num_of_philos);

	while (i < s_data->num_of_philos)
	{	
		// creating thread and pass current philosopher to routine function
		if (pthread_create(&s_philos[i].thread, NULL, (void *)philo_routine, &s_philos[i]))
			error_msg("Error! Failes to create thread!");
			
		i++;
		printf("thread %d got created and is in routine\n", i);
	}
}

void join_threads(t_philo *philos, t_data *data)
{
	int32_t i;
	i = 0;
	
	// two different while loops cause otherwise thread gets created and when we wait for it right after it
	// processes run successively and not at the same time
	while (i < data->num_of_philos)
	{
		// waiting for thread
		// here we just need the value of thread so can use philos[i]
		if (pthread_join(philos[i].thread, NULL))
			error_msg("waiting for thread failed");
			
		i++;
		printf("waited for thread %d\n", i);
	}
}

