/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:48:15 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/12 20:05:50 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

int main()
{
    // get current time fucntion: gettimeofday
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
      printf("seconds : %ld\nmicro seconds : %ld\n",
    current_time.tv_sec, (long int)current_time.tv_usec);
    
    usleep(1000);

    gettimeofday(&current_time, NULL);
      printf("seconds : %ld\nmicro seconds : %ld\n",
    current_time.tv_sec, (long int)current_time.tv_usec);

}

