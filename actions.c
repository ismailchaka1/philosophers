/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:21:04 by root              #+#    #+#             */
/*   Updated: 2025/07/16 17:27:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_eat(t_philo *philo)
{
	(void)philo; // Placeholder - remove when implementing actual eating logic
	return (true);
}

bool	kill_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	print_state(philo, "died");
	return (false);
}