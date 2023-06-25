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

int philo_died(t_data *data, t_philo *philo)
{
    int ret;

    ret = FALSE;
    printf("line 32\n");
    if (!mutex_lock_secured(&philo->last_eat_lock))
    {
        printf("line 34\n");
        return (LOCK_ERROR);
    }
    if ((get_curr_time() - philo->last_eat_time) >= data->time_to_die)
    {
        ret = TRUE;
        printf("line 37\n");
        print_logs(philo, "died");
        printf("line 39\n");
        if (mutex_lock_secured(&data->ending_lock))
        {
            data->end_game = 1;
            pthread_mutex_unlock(&data->ending_lock);
        }
    }
    pthread_mutex_unlock(&philo->last_eat_lock);
    return (ret);
}

int done_eating(t_data *data)
{
    int ret;

    ret = FALSE;
    if (!mutex_lock_secured(&data->done_eating_lock))
        return (LOCK_ERROR);
    if (data->must_eat_done == data->num_philos)
    {
        ret = TRUE;
        if (mutex_lock_secured(&data->ending_lock))
        {
            data->end_game = 1;
            pthread_mutex_unlock(&data->ending_lock);
        }
    }
    pthread_mutex_unlock(&data->done_eating_lock);
    return (ret);
}

void	*end_game_check(void *sim_data)
{
    t_data  *data;
    int     i;
    int     stop;

    i = 0;
    stop = 0;
    data = (t_data *)sim_data;
    ft_usleep(data, data->time_to_die);
    while (!stop)
    {
        while (i < data->num_philos)
        {
            printf("line 81\n");
            if (philo_died(data, data->philos[i]))
            {
                printf("line 84\n");
                stop = 1;
                break ;
            }
            i++;
        }
        if (!stop && data->must_eat && done_eating(data))
            stop = 1;
    }
    return (NULL);
}
