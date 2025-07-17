/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:58:55 by root              #+#    #+#             */
/*   Updated: 2025/07/16 20:08:16 by root             ###   ########.fr       */
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
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
}
