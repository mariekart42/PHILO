/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:10:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/16 15:44:52 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

int64_t get_time()
{
	struct timeval s_time;
	
	if (gettimeofday(&s_time, NULL) < 0)
		error_msg("Error! Failed to get timeofday!");

// *1000 to get from micro to millisecond
// /1000 to get from 
	return ((s_time.tv_usec / 1000) + (s_time.tv_sec * 1000));
}


/* function checks if c is any kind of whitespace
 * returns 0 if c is whitespace
 * returns 1 if c is something but whitespace	*/
int32_t whitespace(char c)
{
	if ((c >= 1 && c <= 31) || c == 127)
		return (0);
	return (1);
}

/* function checks for valid input (only digits or whitespaces)
 * returns 1 for invalid input
 * returns 0 for valid input								*/
int32_t check_for_valid_arg(char *av)
{
	int32_t i = 0;

	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]) && whitespace(av[i]))
			return (1);
		i++;
	}
	return (0);
	// check later also if arguments make sense etc (if that makes sense lol)
}

void check_and_set_input(t_philo **s_philo, t_data *s_data, int32_t ac, char **av_)
{
	int32_t i;
	i = 1;
	if (ac != 5 && ac != 6)
		error_msg("Wrong input! usage: ./philo <param> <param> <param> <param>");
	
	while (i < ac)
	{
		if (check_for_valid_arg(av_[i]))
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
	s_data->num_of_philos = ft_atoi(av_[1]);
	if (s_data->num_of_philos < 2)
		error_msg("Invalid input! Minimum 2 philosophers!");
	printf("num philos data: %d\n", s_data->num_of_philos);
	int32_t bitch;
	bitch = s_data->num_of_philos;
	printf("bitch: %d\n", bitch);
	
	*s_philo->num_of_philos = bitch;
	printf("num philos philo: %d\n", s_philo->num_of_philos);
	


	printf(GRN"check and set input\n"RESET);
	s_data->time_to_die = ft_atoi(av_[2]);
	s_data->time_to_eat = ft_atoi(av_[3]);
	s_data->time_to_sleep = ft_atoi(av_[4]);
	if (s_data->time_to_eat + s_data->time_to_sleep > s_data->time_to_die)
		error_msg("Invalid input! The time to eat and sleep must not exceed the time to die!");
	s_philo->meal_count = 0;
	if (ac == 6)
		s_philo->meal_count = ft_atoi(av_[5]);
	
	s_data->somebody_died = false;

	s_data->av = av_;	// do i even need av again?

}
