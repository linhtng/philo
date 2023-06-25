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

void	print_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		printf("philo %d 1st picks fork %d then fork %d\n", 
		data->philos[i]->id, data->philos[i]->fork_id[0], data->philos[i]->fork_id[1]);
		i++;
	}
}

int	print_logs(t_philo *philo, char *state)
{
	unsigned long	time;
	t_data			*data;

	data = philo->data;
	if (!mutex_lock_secured(&data->logs))
		return (0);
	if (philo_ending(data) != FALSE)
	{
		pthread_mutex_unlock(&data->logs);
		return (0);
	}
	time = get_curr_time() - data->start_time;
	printf("%lu %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&data->logs);
	return (1);
}

void	*philos_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!mutex_lock_secured(&philo->last_eat_lock))
		return (NULL);
	philo->last_eat_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->last_eat_lock);
	if (!(philo->id % 2))
	{
		if (!print_logs(philo, "is sleeping"))
			return (NULL);
		ft_usleep(philo->data,philo->data->time_to_sleep);
		if (!print_logs(philo, "is thinking"))
			return (NULL);
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
	}
}

int	philo_sim(t_data *data)
{
	int	i;

	data->start_time = get_curr_time();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i]->thread_id, NULL, 
			&philos_routine, data->philos[i]))
			return (ft_putstr_fd("philo thread creation failed\n", 2));
		i++;
	}
	if (pthread_create(&data->ending_monitor, NULL, &end_game_check, data))
			return (ft_putstr_fd("end_game thread creation failed\n", 2));
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
		printf("Invalid arguments.\n");
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
