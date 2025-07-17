/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:16 by root              #+#    #+#             */
/*   Updated: 2025/07/16 19:10:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_philo_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->meals_mutex);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(philo->meals_mutex);
	return (meals);
}

uint64_t	get_philo_last_meal(t_philo *philo)
{
	uint64_t	last_meal_time;

	pthread_mutex_lock(philo->last_meal_mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (last_meal_time);
}

t_philo_state	get_philo_state(t_philo *philo)
{
	t_philo_state	state;

	pthread_mutex_lock(philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->state_mutex);
	return (state);
}

int	get_simulation_flag(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->print_mutex);
	flag = data->simulation_flag;
	pthread_mutex_unlock(&data->print_mutex);
	return (flag);
}
