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

static int	philo_take_fork(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	pthread_mutex_lock(&data->forks[philo->fork_id[0]]);
	if (!print_logs(philo, "has taken a fork")
		|| (philo->fork_id[0] == philo->fork_id[1]))
	{
		pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
		return (0);
	}
	pthread_mutex_lock(&data->forks[philo->fork_id[1]]);
	if (!print_logs(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
		pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
		ret = FALSE;
	}
	return (ret);
}

static void	update_meal_info(t_philo *philo, t_data *data, int *sim_cont)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat_time = sim_time_now(data->begin_t);
	pthread_mutex_unlock(&philo->last_eat_lock);
	*sim_cont = TRUE;
	if (data->must_eat)
	{
		philo->meal_count++;
		if (philo->meal_count == data->must_eat)
		{
			*sim_cont = FALSE;
			pthread_mutex_lock(&philo->done_eating_lock);
			philo->done_eating++;
			pthread_mutex_unlock(&philo->done_eating_lock);
		}
	}
}

int	philo_eat(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	if (!philo_take_fork(philo, data))
		return (0);
	update_meal_info(philo, data, &ret);
	if (!print_logs(philo, "is eating"))
		ret = FALSE;
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
	pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
	return (ret);
}
