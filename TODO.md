# philo
- Check valid input:
  - Check if number of argument is correct
  - Check if all given argv[] contains digits only
  - Convert them to integers and check that they are between 0 to INT_MAX. Number of philos must be between 1 and 200.
- Parse given parameters to struct data which contains all the data and pointer to a linked list of t_philo. 
  typedef struct s_data
  {
    time_t			start_time;
    int	        nb_philos;
    time_t			time_to_die;
    time_t			time_to_eat;
    time_t			time_to_sleep;
    int				  must_eat_times;
    int			    sim_end;
    pthread_mutex_t	die_monitor_lock;
    pthread_mutex_t	print_lock;
    pthread_mutex_t	*fork_locks;
    t_philo			**philos;
  }	t_data;
- Each note in t_philo contains a struct that store data for each philo: his id, thread id, mutex lock for fork and for last meal time. Could have pointer to the struct data as well.
  typedef struct s_philo
  {
    pthread_t			thread;
    int		        id;
    int		        times_ate;
    int		        fork[2];
    pthread_mutex_t		meal_time_lock;
    time_t				last_meal;
    t_data				*data;
  }	t_philo;
  
  - Create thread for each philo and if number of philo is more than one, create a thread to monitor their dead.
  - When the simulation ends, i.e. when all philos have eaten must_eat_times or when a philo dies:
     - wait for all threads to be joined using pthread_join
     - destroy all the mutexes created 
     - free all the allocated data
