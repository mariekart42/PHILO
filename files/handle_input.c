/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:10:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/13 13:34:44 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

bool check_for_valid_arg(char *av)
{
	int32_t i = 1;

	while (av[i] != '\0')
	{
		if (ft_isdigit(av[i]) && av[i] != ' ')
			return (false);
		i++;
	}
	return (true);
	// check later also if arguments make sense etc (if that makes sense lol)
}

void check_and_set_input(t_data *data, int32_t ac, char **av_)
{
	int32_t i;
	
	i = 0;
	if (ac != 5 && ac != 6)
		error_msg("Wrong input! usage: ./philo <param> <param> <param> <param>");
	
	while (i < ac)
	{
		if (check_for_valid_arg(av_[i]) == false)
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
	data->num_of_philos = ft_atoi(av_[1]);
	data->time_to_die = ft_atoi(av_[2]);
	data->time_to_eat = ft_atoi(av_[3]);
	data->time_to_sleep = ft_atoi(av_[4]);
	data->av = av_;
	
	// set all forks to true
	while (i < data->num_of_philos)
	{
		data->philo_access.forks[i] = true;
		i++;
	}
}
