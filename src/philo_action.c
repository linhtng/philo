/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:04:27 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/04 21:06:36 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	philo_take_fork(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	if (!mutex_lock_secured(&data->forks[philo->fork_id[0]]))
		return (0);
	if (!print_logs(philo, "has taken a fork")
		|| (philo->fork_id[0] == philo->fork_id[1]))
	{
		pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
		return (0);
	}
	if (!mutex_lock_secured(&data->forks[philo->fork_id[1]]))
	{
		pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
		return (0);
	}
	if (!print_logs(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
		pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
		ret = FALSE;
	}
	return (ret);
}

int	update_meal_info(t_philo *philo, t_data *data, int *sim_cont)
{
	if (!mutex_lock_secured(&philo->last_eat_lock))
		return (0);
	philo->last_eat_time = sim_time_now(data->begin_t);
	pthread_mutex_unlock(&philo->last_eat_lock);
	*sim_cont = TRUE;
	if (data->must_eat)
	{
		philo->meal_count++;
		if (philo->meal_count == data->must_eat)
		{
			*sim_cont = FALSE;
			if (!mutex_lock_secured(&philo->done_eating_lock))
				return (0);
			philo->done_eating++;
			pthread_mutex_unlock(&philo->done_eating_lock);
		}
	}
	return (1);
}

int	philo_eat(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	if (!philo_take_fork(philo, data))
		return (0);
	if (update_meal_info(philo, data, &ret))
	{
		if (!print_logs(philo, "is eating"))
			ret = FALSE;
		ft_usleep(philo->data, philo->data->time_to_eat);
	}
	pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
	pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
	return (ret);
}
