/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:10:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/12 14:38:45 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

void check_for_valid_arg(char *av)
{
	int32_t i = 1;

	while (av[i] != '\0')
	{
		if (ft_isdigit(av[i]) && av[i] != ' ')
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
	// check later also if arguments make sense etc (if that makes sense lol)
}

void check_and_set_input(t_data *data, int32_t ac, char **av_)
{
	int32_t i;
	
	i = 0;
	if (ac != 5)
		error_msg("Wrong input! usage: ./philo <param> <param> <param> <param>");
	while (i < ac)
	{
		check_for_valid_arg(av_[i]);
		i++;
	}
	data->nums_of_philos = ft_atoi(av_[1]);
	data->av= av_;
}
