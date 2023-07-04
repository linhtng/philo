/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:21:10 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/04 21:27:44 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

long long	get_time_ms(struct timeval begin)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - begin.tv_sec) * 1000
		+ (now.tv_usec - begin.tv_usec) / 1000);
}

long long	sim_time_now(struct timeval begin)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - begin.tv_sec) * 1000000
		+ (now.tv_usec - begin.tv_usec));
}

void	ft_usleep(t_data *data, long long sleep_time)
{
	long long	stop_point;

	stop_point = sim_time_now(data->begin_t) + sleep_time * 1000;
	while (sim_time_now(data->begin_t) < stop_point)
	{
		if (philo_ending(data) != FALSE)
			break ;
		usleep(500);
	}
}
