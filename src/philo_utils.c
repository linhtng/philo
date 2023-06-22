/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:39:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/20 16:39:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
    while (str[i])
        i++;
    return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
	if (fd == 2)
		return (0);
	return (1);
}

int	mutex_lock_secured(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		ft_putstr_fd("mutex lock failed\n", 2);
		return (0);
	}
	return (1);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i]->last_eat_lock);
		if (data->philos[i])
			free(data->philos[i]);
		i++;
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->ending_lock);
	pthread_mutex_destroy(&data->logs);
	free(data);
}
