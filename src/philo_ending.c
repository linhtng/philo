/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:51:46 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/22 19:51:48 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int philo_ending(t_data *data)
{
    int end;

    end = FALSE;
    if (!mutex_lock_secured(&data->ending_lock))
        end = LOCK_ERROR;
    if (data->end_game)
        end = TRUE;
    pthread_mutex_unlock(&data->ending_lock);
    return (end);
}

void	*end_game_check(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        if (philo_died(data->philos[i]))
            return (NULL);
        i++;
    }
    if (data->must_eat && done_eating(data))
        return (NULL);
}
