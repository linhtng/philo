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
    {
        pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
        pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
        ret = FALSE;
    }
    return (ret);
}

int update_meal_info(t_philo *philo, t_data *data)
{
    if (!mutex_lock_secured(&philo->last_eat_lock))
        return (0);
    philo->last_eat_time = get_curr_time();
    pthread_mutex_unlock(&philo->last_eat_lock);
    if (data->must_eat)
    {
        if (!mutex_lock_secured(&philo->last_eat_lock))
            return (0);
    }
}

int philo_eat(t_philo *philo, t_data *data)
{
    int ret;

    ret = FALSE;
    if (!philo_take_fork)
        return (0);
    if (print_logs(philo, "is eating"))
    {
        if (update_meal_info(philo, data))
        {
            ft_usleep(philo->data, philo->data->time_to_eat);
            ret = TRUE;
        }
    }
    pthread_mutex_unlock(&data->forks[philo->fork_id[0]]);
    pthread_mutex_unlock(&data->forks[philo->fork_id[1]]);
    return (ret);
}
