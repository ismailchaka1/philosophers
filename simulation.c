
#include "philo.h"

void print_state(t_philo *philo, char *state)
{
    long long timestamp;
    
    pthread_mutex_lock(&philo->data->print_mutex);
    timestamp = get_current_time() - philo->data->start_time;
    printf("%lld %d %s\n", timestamp, philo->id, state);
    pthread_mutex_unlock(&philo->data->print_mutex);
}




void *philo_routine(void *philo)
{
    t_philo *p = (t_philo *)philo;
    set_last_eat_time(p, get_current_time());
    
    if (p->id % 2 == 0)
        ft_usleep(p->data->time_to_eat / 2);
    
    while (p->data->simulation_flag == true)
    {
        print_state(p, "is thinking");
        ft_usleep(p->data->time_to_sleep);
        
        print_state(p, "is eating");
        set_last_eat_time(p, get_current_time());
        ft_usleep(p->data->time_to_eat);
        set_philo_meals(p, get_philo_meals(p) + 1);
        
        // Check if philosopher has eaten enough meals
        if (p->data->meals_required > 0 && get_philo_meals(p) >= p->data->meals_required)
        {
            set_philo_state(p, FULL);
            print_state(p, "is full");
            return NULL;
        }
        
        print_state(p, "is sleeping");
        ft_usleep(p->data->time_to_sleep);
        
        // Check if philosopher has died
        if ((long long)(get_current_time() - get_philo_last_meal(p)) > (long long)p->data->time_to_die)
        {
            set_philo_state(p, DEAD);
            print_state(p, "died");
            set_simulation_flag(p->data, false);
            return NULL;
        }
        
        ft_usleep(100); // Small delay to avoid busy waiting
    }
    return (NULL);
}

void start_simulation(t_data *data)
{
    int i;
    i = 0;
    if (data->num_philos == 1)
    {
        if (!kill_philo(&data->philos[0]))
            return;
    }   
    
    // Create all threads
    while (i < data->num_philos)
    {
        pthread_create(&data->philo_threads[i], NULL, philo_routine, &data->philos[i]);
        i++;
    }
    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philo_threads[i], NULL);
        i++;
    }
}
