/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:08:28 by mmensing          #+#    #+#             */
/*   Updated: 2023/02/01 20:08:28 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

/* function checks if c is any kind of whitespace
 * returns 0 if c is whitespace
 * returns 1 if c is something but whitespace	*/
int32_t	whitespace(char c)
{
	if ((c >= 1 && c <= 31) || c == 127)
		return (0);
	return (1);
}

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		error_msg("Error! Failed to get time of day!");
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	init_data(t_data *data, int32_t ac, char **av)
{
	int32_t	i;

	i = 1;
	if (ac != 5 && ac != 6)
		error_msg("Wrong input! usage: ./philo <arg> <arg> <arg> <arg>");
	data->amount_philos = ft_atoi(av[1]);
	if (data->amount_philos < 2)
		error_msg("Invalid input! Minimum 2 philosophers!");
	while (i < ac)
	{
		if (check_for_valid_arg(av[i]))
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
	if (ft_atoi(av[3]) + ft_atoi(av[4]) > ft_atoi(av[2]))
		error_msg("Invalid input! The time to eat and sleep must not \
		exceed the time to die!");
	data->start_program = get_time();
	data->philo_died = false;
}

/* function checks for valid input (only digits or whitespaces)
 * returns 1 for invalid input
 * returns 0 for valid input								*/
int32_t	check_for_valid_arg(char *av)
{
	int32_t	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]) && whitespace(av[i]))
			return (1);
		i++;
	}
	return (0);
}
