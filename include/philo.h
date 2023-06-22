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
	unsigned long   start_time;
    int             num_philos;
    unsigned long   time_to_die;
    unsigned long   time_to_eat;
    unsigned long   time_to_sleep;
    int             must_eat;
    int             end_game;
    pthread_t       ending_monitor;
    pthread_mutex_t ending_lock;
    pthread_mutex_t logs;
    pthread_mutex_t *forks;
    t_philo         **philos;
}	t_data;

typedef struct s_philo
{
	int             id;
    pthread_t       thread_id;
    int             fork_id[2];
    int             meal_count;
    pthread_mutex_t meal_count_lock;
    unsigned long   last_eat_time;
    pthread_mutex_t last_eat_lock;
    t_data          *data;
}	t_philo;

enum	e_ending
{
	FALSE,
    TRUE,
    LOCK_ERROR,
};

/* philo_check_input  */
int             valid_input(int arc, char **arv);
void            philo_usage(void);
int	            ft_atoi(const char *str);

/* philo_utils */
int	            ft_putstr_fd(char *s, int fd);
void	        destroy_data(t_data *data);
int	            mutex_lock_secured(pthread_mutex_t *mutex);

/* philo_init */
t_data	        *init_data(char **arv);

/* philo_time */
unsigned long	get_curr_time(void);
void	        ft_usleep(t_data *data, unsigned long sleep_time);

/* philo_action */
int             philo_eat(t_philo *philo, t_data *data);

/* philo_ending */
int             philo_ending(t_data *data);

#endif