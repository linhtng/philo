/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:51:46 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/04 21:14:20 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	philo_ending(t_data *data)
{
	int	end;

	end = FALSE;
	pthread_mutex_lock(&data->ending_lock);
	if (data->end_game)
		end = TRUE;
	pthread_mutex_unlock(&data->ending_lock);
	return (end);
}

static int	philo_died(t_data *data, t_philo *philo)
{
	int	ret;

	ret = FALSE;
	pthread_mutex_lock(&philo->last_eat_lock);
	if ((sim_time_now(data->begin_t) - philo->last_eat_time)
		>= data->time_to_die * 1000)
	{
		ret = TRUE;
		print_logs(philo, "died");
		pthread_mutex_lock(&data->ending_lock);
		data->end_game = 1;
		pthread_mutex_unlock(&data->ending_lock);
	}
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (ret);
}

static int	done_eating(t_data *data, t_philo *philo, int *done_eat)
{
	int	ret;

	ret = FALSE;
	if (!data->must_eat)
		return (ret);
	pthread_mutex_lock(&philo->done_eating_lock);
	if (philo->done_eating)
	{
		ret = TRUE;
		*done_eat += 1;
	}
	pthread_mutex_unlock(&philo->done_eating_lock);
	return (ret);
}

void	*end_game_check(void *sim_data)
{
	t_data	*data;
	int		i;
	int		done_eat;

	done_eat = 0;
	data = (t_data *)sim_data;
	while (1)
	{
		usleep(500);
		i = 0;
		done_eat = 0;
		while (i < data->num_philos && done_eat != data->num_philos)
		{
			if (done_eating(data, data->philos[i], &done_eat) == FALSE)
			{
				if (philo_died(data, data->philos[i]))
					return (NULL);
			}
			i++;
		}
		if (done_eat == data->num_philos)
			return (NULL);
	}
}
