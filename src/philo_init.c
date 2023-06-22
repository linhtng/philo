/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:23:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/22 19:23:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!forks)
		return (0);
	i = 0;
	data->forks = forks;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->ending_lock, NULL)
		|| pthread_mutex_init(&data->logs, NULL) || !init_forks)
	{
		ft_putstr_fd("Mutex init error\n", 2);
		return (0);
	}	
	return (1);
}

void	forks_order(t_data *data, t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork_id[0] = philo->id;
		if (philo->id == data->num_philos)
			philo->fork_id[0] = 0;
		philo->fork_id[1] = philo->id - 1;
	}
	else
	{
		philo->fork_id[0] = philo->id - 1;
		philo->fork_id[1] = philo->id;
		if (philo->id == data->num_philos)
			philo->fork_id[1] = 0;
	}
}

int	init_philo(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **) malloc(sizeof(t_philo *) * data->num_philos);
	if (!philos)
		return (ft_putstr_fd("Malloc error philos.\n", 2));
	i = 0;
	data->philos = philos;
	while (i < data->num_philos)
	{
		philos[i] = (t_philo *) malloc(sizeof(t_philo));
		if (!philos[i])
			return (0);
		memset(philos[i], 0, sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->data = data;
		forks_order(data, philos[i]);
		if (pthread_mutex_init(&philos[i]->last_eat_lock, NULL)
			|| pthread_mutex_init(&philos[i]->meal_count_lock, NULL))
			return (ft_putstr_fd("Mutex init error.\n", 2));
		i++;
	}
	return (1);
}

t_data	*init_data(char **arv)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(&data));
	data->num_philos = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arv[5])
		data->must_eat = ft_atoi(arv[5]);
	if (!init_philo(data) || !init_data_mutex(data))
	{
		destroy_data(data);
		return (NULL);
	}
	return (data);
}
