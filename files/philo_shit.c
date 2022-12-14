/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:40:01 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/13 13:48:29 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/philo.h"

void init_philos(t_philo *philo)
{
    
}

void philo_loop(t_philo *philo, t_data *data)
{
    int32_t i = 0;
    
    init_philos(philo);
    while (1)
    {
        if (philo->forks[i] == true && philo->forks[i+1] == true)
            philo_eat();
    }
}