/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:28:50 by root              #+#    #+#             */
/*   Updated: 2025/07/16 19:34:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].state = IDLE;
		data->philos[i].data = data;
		data->philos[i].state_mutex = malloc(sizeof(pthread_mutex_t));
		data->philos[i].meals_mutex = malloc(sizeof(pthread_mutex_t));
		data->philos[i].last_meal_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->philos[i].state_mutex, NULL);
		pthread_mutex_init(data->philos[i].meals_mutex, NULL);
		pthread_mutex_init(data->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_forks(data);
}

void	init_threads(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		error_exit();
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	if (!data->forks)
	{
		free(data->philos);
		error_exit();
	}
	data->philo_threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data->num_philos);
	if (!data->philo_threads)
	{
		free(data->philos);
		free(data->forks);
		error_exit();
	}
	init_philos(data);
}

void	init_parsing(char **av, t_data *data)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_required = ft_atoi(av[5]);
	else
		data->meals_required = -1;
	data->simulation_flag = true;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		error_exit();
	if (av[5] && data->meals_required <= 0)
		error_exit();
	pthread_mutex_init(&data->print_mutex, NULL);
	data->simulation_flag = true;
	data->start_time = get_current_time();
	init_threads(data);
}
