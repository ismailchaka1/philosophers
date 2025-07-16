#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum philo_state
{
	EAT,
	SLEEP,
	THINK,
	FULL,
	IDLE,
	DEAD
}					philo_state;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	struct s_data	*data;
	philo_state		state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*state_mutex;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	*last_meal_mutex;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_required;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	bool			simulation_flag;
	pthread_t		*philo_threads;
	t_philo			*philos;
}					t_data;

void				error_exit(void);
int					ft_atoi(char *str);
void				init_parsing(char **av, t_data *data);
void				init_threads(t_data *data);
void				init_philos(t_data *data);
void				init_forks(t_data *data);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				start_simulation(t_data *data);
void				*philo_routine(void *philo);
void				cleanup_data(t_data *data);
void				print_state(t_philo *philo, char *state);

// Getter functions
int					get_philo_meals(t_philo *philo);
uint64_t			get_philo_last_meal(t_philo *philo);
philo_state			get_philo_state(t_philo *philo);
int					get_simulation_flag(t_data *data);

// Setter functions
philo_state			set_philo_state(t_philo *philo, philo_state state);
int					set_simulation_flag(t_data *data, bool flag);
uint64_t			set_philo_last_meal(t_philo *philo, uint64_t time);
void				set_philo_meals(t_philo *philo, int meals);
uint64_t			set_last_eat_time(t_philo *philo, uint64_t time);

// Action functions
bool				philo_eat(t_philo *philo);
bool				kill_philo(t_philo *philo);

#endif