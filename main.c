/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:01:48 by root              #+#    #+#             */
/*   Updated: 2025/07/16 19:01:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].state_mutex)
		{
			pthread_mutex_destroy(data->philos[i].state_mutex);
			free(data->philos[i].state_mutex);
		}
		if (data->philos[i].meals_mutex)
		{
			pthread_mutex_destroy(data->philos[i].meals_mutex);
			free(data->philos[i].meals_mutex);
		}
		if (data->philos[i].last_meal_mutex)
		{
			pthread_mutex_destroy(data->philos[i].last_meal_mutex);
			free(data->philos[i].last_meal_mutex);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->philo_threads)
		free(data->philo_threads);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		init_parsing(av, &data);
		start_simulation(&data);
		cleanup_data(&data);
	}
	else
		error_exit();
	return (0);
}
