/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:08:12 by mmensing          #+#    #+#             */
/*   Updated: 2023/02/01 20:08:12 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

void	create_mutexes(t_data *data)
{
	int32_t	i;

	i = 0;
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->amount_philos);
	if (!data->mutex_forks)
		error_msg("Error! Failed to malloc for forks!");
	while (i < data->amount_philos)
	{
		if (pthread_mutex_init(&data->mutex_forks[i], NULL))
			error_msg("Error! Failed to create mutex for fork!");
		i++;
	}
	if (pthread_mutex_init(&data->mutex_message, NULL))
		error_msg("Error! Failed to create mutex for message!");
	if (pthread_mutex_init(&data->mutex_death, NULL))
		error_msg("Error! Failed to create mutex for death of philosopher!");
}

void	destroy_mutexes(t_data *data)
{
	int32_t	i;

	i = 0;
	while (i < data->amount_philos)
	{
		if (pthread_mutex_destroy(&data->mutex_forks[i]))
			error_msg("Error! Failed to destroy mutex for fork!");
		i++;
	}
	if (pthread_mutex_destroy(&data->mutex_message))
		error_msg("Error! Failed to destroy mutex for messages!");
	if (pthread_mutex_destroy(&data->mutex_death))
		error_msg("Error! Failed to destroy mutex for death");
}
