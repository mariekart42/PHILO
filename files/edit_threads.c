/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 05:08:58 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/16 15:32:32 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// checks if somebody died
// changes bool variable to
// 1 -> if somebody died
// 0 -> if everybody is alive
int32_t somebody_died(t_philo *s_philo)
{

	// if the status got already changed to somebody died
	pthread_mutex_lock(&s_philo->philo_data->m_somebody_died);
	if (s_philo->somebody_died == true)
	{
		pthread_mutex_unlock(&s_philo->philo_data->m_somebody_died);
		return (1);
	}
	
	// check if there is enough time left between eating last time and death time
	

	
	

	return (0);
}



void grab_forks(t_philo *s_philo)
{
	int64_t	curr_time;
	
	
// ------------------ for right forks -----------------------------------------
	// locking mutex for printing message and right fork
	pthread_mutex_lock(s_philo->right_fork);
	pthread_mutex_lock(&s_philo->philo_data->m_msg);
	
	// get current time
	curr_time = get_time() - s_philo->program_start_time;
	
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(s_philo))
	{
		pthread_mutex_unlock(s_philo->right_fork);
		pthread_mutex_unlock(&s_philo->philo_data->m_msg);
		return ;
	}
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(s_philo))
	{
		pthread_mutex_unlock(s_philo->right_fork);
		pthread_mutex_unlock(&s_philo->philo_data->m_msg);
		return ;
	}
	// printing unlocking mutex for printing the message
	printf("%lld %d Has taken a right fork\n", curr_time, s_philo->id);
	pthread_mutex_unlock(&s_philo->philo_data->m_msg);
	
	
// ------------------ now for left forks -----------------------------------------
	pthread_mutex_lock(s_philo->left_fork);
	pthread_mutex_lock(&s_philo->philo_data->m_msg);
	
	// get current time again cause time has passed
	curr_time = get_time() - s_philo->program_start_time;
	
	// if somebody died, unlock locked mutexes (preventing bullshit lol)
	if (somebody_died(s_philo))
	{
		pthread_mutex_unlock(s_philo->right_fork);
		pthread_mutex_unlock(s_philo->left_fork);
		pthread_mutex_unlock(&s_philo->philo_data->m_msg);
		return ;
	}
	printf("%lld %d Has taken a left fork\n", curr_time, s_philo->id);
	
	// unlock mutex for printing message
	pthread_mutex_unlock(&s_philo->philo_data->m_msg);
}

void *philo_routine(t_philo *s_philo)
{
	// getting time when the thread starts
	s_philo->program_start_time = get_time();
	s_philo->last_ate = s_philo->program_start_time;

	printf("current id: %d\n", s_philo->id);
	// get current timestamp
	
	// sleeping here if philo is uneven -> not sure about the time
	if (s_philo->id % 2 == 0)
	{
	printf(GRN"gen check in routine\n"RESET);
		s_philo->philo_data->num_of_philos = 69;
		printf("num philos: %d\n", s_philo->num_of_philos);
		// waiting longer if over 100 philos
		if (s_philo->num_of_philos > 100)
		{

	printf(GRN"check in routine\n"RESET);
			usleep(100);
		}
		else
		{
	printf(GRN"check in routine\n"RESET);
			
			usleep(1500);
		}
	}

	while (1)
	{
		grab_forks(s_philo);

// printf("philo  %d  in routine loop\n", philo->id);
		// eating();
		
		if (somebody_died(s_philo))
			break ;
		
		// break condition if the amount of times to eat got reached
		
		// sleeping(philo);
		
		// thinking(philo);
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

