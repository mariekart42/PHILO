/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:45:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/16 15:44:17 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

// delete later, just for testing
// int32_t brr = 0;
// pthread_mutex_t	mutex;

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void init_threads(t_philo *s_philo, t_data *s_data)
{
	int32_t i = 0;

	while (i < s_data->num_of_philos)
	{
		printf(GRN"debug check\n"RESET);

		s_philo[i].id = i + 1;
		printf(YEL"current id: %d\n"RESET, s_philo[i].id);
		
		s_philo[i].tt_die = s_data->time_to_die;
		s_philo[i].tt_eat = s_data->time_to_eat;
		s_philo[i].tt_sleep = s_data->time_to_sleep;
		
		s_philo[i].meal_count = 0;
		
		
		// philos[i].last_ate = data->program_start_time;
		// philo[i].right_fork = &info->forks[i];
		// philo[i].left_fork = &info->forks[(i + 1) % info->number_of_philo];
		// philo[i].philo_info = info;
		// philo[i].start_of_the_program = info->start;
		// philo[i].nbr_of_philo = info->number_of_philo;

		i++;
	}

}


// function returns 1 if something goes wrong
// returns 0 if everthing went well
int32_t init_mutexes(t_data *s_data)
{
	int32_t i = 0;
	
	// for every philosopher we need one fork
	// a fork is protected with one mutex, fo we need 'amount of philos' fork-mutexes
	s_data->m_forks = malloc(sizeof(pthread_mutex_t) * s_data->num_of_philos);
	if (s_data->m_forks == NULL)
		error_msg("Error! Failed to malloc for forks!");
		
	while (i < s_data->num_of_philos)
	{
		// creating a mutex for each fork
		if (pthread_mutex_init(&s_data->m_forks[i], NULL))
			error_msg("Error! Failed to create mutex for fork!");
		i++;
	}
	
	// create here mutex also for displaying messages
	if (pthread_mutex_init(&s_data->m_msg, NULL))
		error_msg("Error! Failed to create mutex for 'msg'!");
		
	// create here mutex for status if somebody died
	if (pthread_mutex_init(&s_data->m_somebody_died, NULL))
		error_msg("Error! Failed to create mutex for 'somebody_died'!");
	
	return (0);
}

void destroy_mutexes(t_data *s_data)
{
	int32_t i = 0;
	
	// destroy mutexes for all forks
	while (i < s_data->num_of_philos)
	{
		if (pthread_mutex_destroy(&s_data->m_forks[i]))
			error_msg("Error! Failed to destroy mutex for fork!");
		i++;
	}
	
	// destroy mutex for printing messages
	if (pthread_mutex_destroy(&s_data->m_msg))
		error_msg("Error! Failed to destroy mutex for messages!");
	
	if (pthread_mutex_destroy(&s_data->m_somebody_died))
		error_msg("Error! Failed to destroy mutex for death_status");
	return ;
}

int main(int32_t ac, char *av[])
{
	// testing gettime
	int64_t time;
	time  = get_time();
	printf(YEL"get_time: %lld\n"RESET, time);


	t_philo	*s_philo = NULL;
	t_data	s_data;
	
	
	
	// check for amount and if only digits
	// set av and all arguments to struct varibles
	// set all forsk to true
	check_and_set_input(&s_philo, &s_data, ac, av);

	printf(GRN"debug check\n"RESET);
	// init mutexes for:
	//	- philo_amount of forks
	//	- printing messages to the console
	//	- if somebody died
	init_mutexes(&s_data);
	
	
	// malloc for philos the amount af philos
	s_philo = malloc(sizeof(t_philo) * s_data.num_of_philos);
	if (!s_philo)
		error_msg("malloc philosophers failed");
	
	init_threads(s_philo, &s_data);
	
	// creating nums_of_philos amount of threads
	// calling routine function (passing current philo to it)
	create_threads(s_philo, &s_data);
			
	
	join_threads(s_philo, &s_data);
	
	
	// destroy mutexes
	destroy_mutexes(&s_data);
	// pthread_mutex_destroy(&philos->th_lock);
}
