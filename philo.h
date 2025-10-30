#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_phil
{
	pthread_t		id;
	int				index;
	pthread_mutex_t	fork_mutex;
	long			last_meal_in_ms;
	long			meals;
	long			full;
	struct s_phil	*neighbour;
	struct s_data	*data;
	pthread_mutex_t	phil_mutex;
}	t_phil;

typedef struct	s_data
{
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	long	num_phils;
	long	to_die;
	long	to_eat;
	long	to_sleep;
	long	must_eat;
	long	threads_created;
	long	threads_running;
	long	start_in_ms;
	t_phil	*phils;
	long	death;
	long	all_full;
}	t_data;

typedef enum e_phil_state
{
	FORK_OWN,
	FORK_NEIGH,
	RELEASE_OWN,
	RELEASE_NEIGH,
	EATING,
	SLEEPING,
	THINKING,
	DIYING,
}	t_phil_state;

// progrm utils
int		ft_atol(char *s);
int		init_data(t_data *data, char **argv);
int		init_phils(t_data *data);
void	ft_log(t_phil *phil, int action);
void	terminate(t_data *data);
int	check_data(t_data *data);

// time utils
long	gettime_in_us(void);
long	make_timestamp_in_ms(long start);
void	custom_usleep(long usec, t_data *data);

// routines
void	*monitor_death(void *arg);
void	*ft_phil(void *arg);
void	*ft_phil_single(void *arg);
int		all_threads_running(pthread_mutex_t *mutex, long *threads, long num_phils);
void	ft_eating(t_phil *phil);
void	ft_sleeping(t_phil *phil);
void	ft_thinking(t_phil *phil);

//mutex helpers
void	setlong(pthread_mutex_t *mutex, long *dest, long value);
long	getlong(pthread_mutex_t *mutex, long *src);

#endif
