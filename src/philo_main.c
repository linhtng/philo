/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:59:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/10 20:04:21 by thuynguy         ###   ########.fr       */
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

int	init_philo(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **) malloc(sizeof(t_philo *) * data->num_philos);
	if (!philos)
		return (0);
	i = 0;
	data->philos = philos;
	while (i < data->num_philos)
	{
		philos[i] = (t_philo *) malloc(sizeof(t_philo));
		if (!philos[i])
			return (0);
		if (data->must_eat)
		{
			if (pthread_mutex_init(&philos[i]->meal_count_lock, NULL))
				return (0);
		}
		if (pthread_mutex_init(&philos[i]->last_meal_lock, NULL))
			return (0);
		memset(philos[i], 0, sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->data = data;
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
	memset(data, 0, sizeof(data));
	data->num_philos = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arv[5])
		data->must_eat = ft_atoi(arv[5]);
	if (!init_forks(data) || !init_philo(data) || !init_mutex_lock(data))
		return (NULL);
}

int	main(int arc, char **arv)
{
	t_data	*data;

	if (arc < 5 || arc > 6)
	{
		philo_usage();
		return (0);
	}
	if (!valid_input(arc, arv))
	{
		printf("Invalid arguments.\n");
		free(data);
	}
	data = init_data(arv);
	return (0);
}
