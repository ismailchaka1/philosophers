#ifndef PHILO_H
#define PHILO_H


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum philo_state {
    EAT,
    SLEEP,
    THINK,
    FULL,
    IDLE,
    DEAD
} philo_state;

typedef struct s_philo {
    int id;
    int meals_eaten;
    long long last_meal_time;
    struct s_data *data;
    philo_state state;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *state_mutex;
    pthread_mutex_t *meals_mutex;
    pthread_mutex_t *last_meal_mutex;
} t_philo;

typedef struct s_data {
    int num_philos;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int meals_required;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_t *philo_threads;
    t_philo *philos;
} t_data;

void error_exit(void);
int ft_atoi(char *str);
void init_parsing(char **av, t_data *data);
void error_exit(void);
size_t get_current_time(void);
int ft_usleep(size_t milliseconds);

#endif