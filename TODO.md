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
      pthread_t	  sim_end_monitor;
      pthread_mutex_t	print_lock;
      pthread_mutex_t	*fork_locks;
      t_philo			**philos;
    }	t_data;
  
- Each note in t_philo contains a struct that store data for each philo: his id, thread id, mutex lock for fork and for last meal time. Could have pointer to the struct data as well.
  typedef struct s_philo
  
    {
      pthread_t			thread;
      int		        id;
      int		        meal_count;
      int		        fork[2];
      pthread_mutex_t		meal_count_lock;
      pthread_mutex_t		meal_time_lock;
      time_t				last_meal;
      t_data				*data;
    }	t_philo;
  
  - Create thread for each philo and if number of philo is more than one, create a thread to monitor their dead.
  - If there is only one philo, he will only has 1 fork, thus won't be able to eat. He will just pick up that fork, wait until time_to_die, then die.
  - Philo thread routine: eat, sleep, and think, repeat until the sim ends. To avoid deadlock, philosophers with an even id will wait 1ms i.e. start the routine by thinking for 1ms 
  before trying to pick up forks, allowing philosophers with an odd id to pick up the fork first.
    - Initial thinking routine for even id philos:
      - write the thinking message
      - put the process to be idle for 1ms
    - Eat routine: 
      -  lock the fork mutex
      -  write the pick-up fork message
      -  lock the other fork mutex
      -  write the pick-up fork message
      -  eat, i.e. write the eating message, update the last_meal_time. If needed, update the meal_count.
      -  put the process to be idle for time_to_eat amount of time
      -  put the forks down, so unlock the forks mutex
    - Sleep & think routine
      -  write the sleep message
      -  put the process to be idle for time_to_sleep amount of time
      -  Wake up and start thinking: write the thinking message

  - Waits for a small delay at the beginning of each threads execution, so that all threads start at the same time with the same start time.
  This helps make sure that the death monitor thread is synchronized with the philos threads.
  - If there is only one philo, he will only has 1 fork, thus won't be able to eat. He will just pick up that fork, wait until time_to_die, then die.
  - Sim_end_monitor thread: constantly check if end conditions has been reached and if yes, set the sim_end flag to be 1, so the philo threads will stop looping.
     - Check if current_time - last_meal >= time_to_die -> write died message
     - If must_eat_times was specified, check if meal_count >= must_eat-times
  - When the simulation ends, i.e. when all philos have eaten must_eat_times or when a philo dies:
     - wait for all threads to be joined using pthread_join
     - destroy all the mutexes created 
     - free all the allocated data
