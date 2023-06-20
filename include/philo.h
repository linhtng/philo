/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:54:45 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/10 19:55:53 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
	time_t          start_sim;
    int             num_philos;
    time_t          time_to_die;
    time_t          time_to_eat;
    time_t          time_to_sleep;
    int             must_eat;
    int             end_sim;
    pthread_t       ending_monitor;
    pthread_mutex_t ending_lock;
    pthread_mutex_t stamp_lock;
    pthread_mutex_t *forks;
    t_philo         **philos;
}	t_data;

typedef struct s_philo
{
	int             id;
    pthread_t       thread;
    int             fork_id[2];
    int             meal_count;
    pthread_mutex_t meal_count_lock;
    time_t          last_meal;
    pthread_mutex_t last_meal_lock;
    t_data          *data;
}	t_philo;

/* philo_check_input  */
int     valid_input(int arc, char **arv);
void    philo_usage(void);
int	    ft_atoi(const char *str);

#endif