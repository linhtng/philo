# philo
- Check valid input:
  - Check if number of argument is correct
  - Check if all given argv[] contains digits only
  - Convert them to integers and check that they are between 0 to INT_MAX. Number of philos must be between 1 and 200.
- Parse given parameters to struct data which contains all the data and pointer to a linked list of t_philo. 
  ```
  typedef struct s_data
  {
  	struct timeval	begin_t;
  	int				num_philos;
  	long long		time_to_die;
  	long long		time_to_eat;
  	long long		time_to_sleep;
  	int				must_eat;
  	volatile int	end_game;
  	pthread_t		ending_monitor;
  	pthread_mutex_t	ending_lock;
  	pthread_mutex_t	logs;
  	pthread_mutex_t	*forks;
  	t_philo			**philos;
  }	t_data;
  ```
- Each note in t_philo contains a struct that store data for each philo: his id, thread id, mutex lock for fork and for last meal time. Could have pointer to the struct data as well.
  ```
  typedef struct s_philo
  {
  	int				id;
  	pthread_t		thread_id;
  	int				fork_id[2];
  	int				meal_count;
  	volatile int	done_eating;
  	pthread_mutex_t	done_eating_lock;
  	long long		last_eat_time;
  	pthread_mutex_t	last_eat_lock;
  	t_data			*data;
  }	t_philo;
  ```
- Create thread for each philo and if number of philo is more than one, create a thread to monitor their dead.
- If there is only one philo, he will only has 1 fork, thus won't be able to eat. He will just pick up that fork, wait until time_to_die, then die.
- Philo thread routine for
  - odd id: eat, sleep, and think, repeat until the sim ends.
  - even id: sleep, eat, think, repeat until the sim ends.
  
  By doing this, philosophers with an odd id is able to pick up the forks and starts eating before the even id philos. This helps avoid deadlock.
- Additionally, to avoid deadlock, we impose this strict fork acquisition order: philos with odd id are right-handed, i.e. they always 1st pick up the fork on their right, then pick up the fork on their left. On the contrary, philos with even id are left-handed, they always 1st pick up the fork on their left, then pick up the fork on their right. For example, philos id 1 picks up fork 1 then picks fork 0, while philos id 2 picks up fork 1 then picks fork 2.
- Eat routine: 
      -  lock the fork mutex
      -  write the pick-up fork message
      -  lock the other fork mutex
      -  write the pick-up fork message
      -  eat, i.e. write the eating message, update the last_meal_time. If needed, update the done_eating variable.
      -  put the process to be idle for time_to_eat amount of time
      -  put the forks down, so unlock the forks mutex
- Sleep & think routine
      -  write the sleep message
      -  put the process to be idle for time_to_sleep amount of time
      -  Wake up and start thinking: write the thinking message, then think (using the sleep function) for a little amount of time

- End_game thread: Waits for a small delay at the beginning of each philo examination. This thread constantlys check if end conditions has been reached and if yes, set the sim_end flag to be 1, so the philo threads will stop looping. Conditions:
     - current_time - last_meal >= time_to_die -> write died message
     - If must_eat was specified, done_eating philos equals to the number of philos
- When the simulation ends, i.e. when all philos have eaten must_eat_times or when a philo dies:
     - wait for all threads to be joined using pthread_join
     - destroy all the mutexes created 
     - free all the allocated data
