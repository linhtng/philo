/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:21:10 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/22 19:21:12 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

unsigned long	get_curr_time(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(t_data *data, unsigned long sleep_time)
{
	unsigned long	stop_point;

	stop_point = get_curr_time() + sleep_time;
    while (get_curr_time() < stop_point)
    {
        if (philo_ending(data) != FALSE)
            break ;
        usleep(500);
    }
}
