/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:59:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/04 21:21:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	print_logs(t_philo *philo, char *state)
{
	long long	time;
	t_data		*data;

	data = philo->data;
	if (!mutex_lock_secured(&data->logs))
		return (0);
	if (philo_ending(data) != FALSE)
	{
		pthread_mutex_unlock(&data->logs);
		return (0);
	}
	time = get_time_ms(data->begin_t);
	printf("%lld %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&data->logs);
	return (1);
}

void	*philos_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
	{
		if (!print_logs(philo, "is sleeping"))
			return (NULL);
		ft_usleep(philo->data, philo->data->time_to_sleep);
	}
	while (1)
	{
		if (!philo_eat(philo, philo->data))
			return (NULL);
		if (!print_logs(philo, "is sleeping"))
			return (NULL);
		ft_usleep(philo->data, philo->data->time_to_sleep);
		if (!print_logs(philo, "is thinking"))
			return (NULL);
		usleep(200 - philo->id + 1);
	}
}

int	philo_sim(t_data *data)
{
	int	i;

	gettimeofday(&data->begin_t, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i]->thread_id, NULL,
				&philos_routine, data->philos[i]))
		{
			printf("philo thread creation failed\n");
			return (0);
		}
		i++;
	}
	if (pthread_create(&data->ending_monitor, NULL, &end_game_check, data))
	{
		printf("end_game thread creation failed\n");
		return (0);
	}
	return (1);
}

int	wait_threads(t_data *data)
{
	int	i;
	int	join_err;

	i = 0;
	join_err = 0;
	while (i < data->num_philos)
	{
		join_err += pthread_join(data->philos[i]->thread_id, NULL);
		i++;
	}
	join_err += pthread_join(data->ending_monitor, NULL);
	return (join_err);
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
		return (0);
	}
	data = init_data(arv);
	if (!data)
	{
		printf("Initializing data failed.\n");
		return (0);
	}
	philo_sim(data);
	if (wait_threads(data))
		printf("pthread_join returned error.\n");
	destroy_data(data);
	return (0);
}
