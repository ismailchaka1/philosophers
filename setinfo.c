/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:18:15 by root              #+#    #+#             */
/*   Updated: 2025/07/16 19:36:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_state	set_philo_state(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(philo->state_mutex);
	philo->state = state;
	pthread_mutex_unlock(philo->state_mutex);
	return (state);
}

int	set_simulation_flag(t_data *data, bool flag)
{
	pthread_mutex_lock(&data->print_mutex);
	data->simulation_flag = flag;
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

uint64_t	set_philo_last_meal(t_philo *philo, uint64_t time)
{
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (time);
}

void	set_philo_meals(t_philo *philo, int meals)
{
	pthread_mutex_lock(philo->meals_mutex);
	philo->meals_eaten = meals;
	pthread_mutex_unlock(philo->meals_mutex);
}

uint64_t	set_last_eat_time(t_philo *philo, uint64_t time)
{
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (time);
}
