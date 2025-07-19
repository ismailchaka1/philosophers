/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:58:55 by root              #+#    #+#             */
/*   Updated: 2025/07/19 00:58:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	set_last_eat_time(p, get_current_time());
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_to_eat - 10);
	while (get_simulation_flag(p->data))
	{
		// print the state of the philosopher
		if (get_philo_state(p) == DEAD)
			printf("Philosopher %d is dead\n", p->id);
		else if (get_philo_state(p) == EAT)
			printf("Philosopher %d is EAT\n", p->id);
		else if (get_philo_state(p) == SLEEP)
			print_state(p, "is SLEEP");
		else if (get_philo_state(p) == THINK)
			print_state(p, "is THINK");
		else if (get_philo_state(p) == FULL)
			print_state(p, "is FULL");
		else if (get_philo_state(p) == IDLE)
			print_state(p, "is IDLE");
		if (!is_philo_full(p) && philo_eat(p) == false)
			break ;
		if (get_philo_state(p) == DEAD)
			break ;
		if (!is_philo_full(p) && philo_sleep(p) == false)
			break ;
		if (get_philo_state(p) == DEAD)
			break ;
		if (!is_philo_full(p) && philo_think(p) == false)
			break ;
	}
	return (NULL);
}

void *check_death_philo(void *data_ptr)
{
	int		i;
	t_data	*table;

	table = (t_data *)data_ptr;
	i = 0;
	while (i < table->num_philos)
	{
		if (get_current_time()
			- get_philo_last_meal(&table->philos[i]) > table->time_to_die)
		{
			print_state(&table->philos[i], "died");
			set_simulation_flag(table, false);
			kill_philos(table);
			break ;
		}
		i++;
		if (i == table->num_philos)
			i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philos == 1)
	{
		if (!kill_philo(&data->philos[0]))
			return ;
	}
	while (i < data->num_philos)
	{
		pthread_create(&data->philo_threads[i], NULL, philo_routine,
			&data->philos[i]);
		i++;
	}
	// pthread_create(&data->full_meals_thread, NULL, check_full_meals, data);
	pthread_create(&data->death_philo_thread, NULL, check_death_philo, data);
	i = 0;
	pthread_join(data->death_philo_thread, NULL);
	while (i < data->num_philos)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
}
