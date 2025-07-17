/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:00:12 by root              #+#    #+#             */
/*   Updated: 2025/07/16 20:06:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	is_philo_full(t_philo *philo)
{
	if (philo->data->meals_required == -1)
		return (false);
	pthread_mutex_lock(philo->meals_mutex);
	if (philo->meals_eaten >= philo->data->meals_required)
	{
		pthread_mutex_unlock(philo->meals_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->meals_mutex);
	return (false);
}

bool	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		perror("Failed to lock left fork");
		return (false);
	}
	print_state(philo, "has taken a left fork");
	return (true);
}

bool	take_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		perror("Failed to lock right fork");
		return (false);
	}
	print_state(philo, "has taken a right fork");
	return (true);
}
