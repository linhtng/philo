/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:04:27 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/22 21:04:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int philo_take_fork(t_philo *philo, t_data *data)
{
    int ret;

    ret = TRUE;
    if (!mutex_lock_secured(&data->forks[philo->fork_id[0]]))
        return (0);
    if (!print_logs(philo, "has taken a fork"))
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
        ret = FALSE;
    pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
    pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
    return (ret);
}

int philo_eat(t_philo *philo, t_data *data)
{
    int ret;

    ret = TRUE;
    if (!philo_take_fork)
        return (0);
    ft_usleep(philo->data, philo->data->time_to_sleep);
}
