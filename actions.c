/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:21:04 by root              #+#    #+#             */
/*   Updated: 2025/07/19 00:57:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_forks(t_philo *philo)
{
	if (get_philo_state(philo) == DEAD)
		return (false);
	if (philo->data->num_philos == 1)
		kill_philo(philo);
	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo) == false)
			return (false);
		if (take_left_fork(philo) == false)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
	}
	else
	{
		if (take_left_fork(philo) == false)
			return (false);
		if (take_right_fork(philo) == false)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
	}
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	if (get_philo_state(philo) == DEAD)
		return (false);
	if (take_forks(philo) == false)
		return (false);
	set_philo_state(philo, EAT);
	print_state(philo, "is eating");
	set_philo_last_meal(philo, get_current_time());
	set_philo_meals(philo, get_philo_meals(philo) + 1);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
	return (true);
}

bool	kill_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	print_state(philo, "died");
	return (false);
}

bool	philo_sleep(t_philo *philo)
{
	if (get_philo_state(philo) == DEAD)
		return (false);
	set_philo_state(philo, SLEEP);
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	return (true);
}

bool	philo_think(t_philo *philo)
{
	long	t_think;

	if (get_philo_state(philo) == DEAD)
		return (false);
	t_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (t_think < 0)
	{
		t_think = 0;
	}
	print_state(philo, "is thinking");
	if (philo->data->num_philos % 2)
		ft_usleep(t_think * 0.5);
	return (true);
}
