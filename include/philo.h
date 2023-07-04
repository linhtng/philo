/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:54:45 by thuynguy          #+#    #+#             */
/*   Updated: 2023/07/04 21:37:47 by thuynguy         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_data
{
	struct timeval	begin_t;
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	volatile int	must_eat_done;
	pthread_mutex_t	done_eating_lock;
	volatile int	end_game;
	pthread_t		ending_monitor;
	pthread_mutex_t	ending_lock;
	pthread_mutex_t	logs;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				fork_id[2];
	int				meal_count;
	long long		last_eat_time;
	pthread_mutex_t	last_eat_lock;
	t_data			*data;
}	t_philo;

enum	e_ending
{
	FALSE,
	TRUE,
	LOCK_ERROR,
};

/* philo_check_input  */
int			valid_input(int arc, char **arv);
void		philo_usage(void);
int			ft_atoi(const char *str);

/* philo_utils */
int			ft_putstr_fd(char *s, int fd);
void		destroy_data(t_data *data);
int			mutex_lock_secured(pthread_mutex_t *mutex);

/* philo_init */
t_data		*init_data(char **arv);

/* philo_time */
long long	get_time_ms(struct timeval begin);
long long	sim_time_now(struct timeval begin);
void		ft_usleep(t_data *data, long long sleep_time);

/* philo_action */
int			philo_eat(t_philo *philo, t_data *data);

/* philo_ending */
int			philo_ending(t_data *data);
void		*end_game_check(void *sim_data);

/* philo_main */
int			print_logs(t_philo *philo, char *state);

#endif
