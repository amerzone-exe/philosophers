/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/29 09:47:45 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_done(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	pthread_mutex_lock(&philo->args->done_mutex);
	if (philo->args->end_sim == true)
		sim_is_done = true;
	pthread_mutex_unlock(&philo->args->done_mutex);
	return (sim_is_done);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_fork	*right_fork;
	t_fork	*left_fork;

	philo = (t_philo *)args;
	right_fork = philo->right_fork;
	left_fork = philo->left_fork;
	pthread_mutex_lock(&philo->args->mutex_start);
	pthread_mutex_unlock(&philo->args->mutex_start);
	mtx_print(philo, "is thinking");
	if (philo->philo_id % 2 == 0)
		my_usleep(philo->args->time_to_eat / 2, philo);
	while (is_done(philo) == false)
	{
		take_forks(philo, right_fork, left_fork);
		if (philo_eating(philo))
			return (NULL);
		if (philo_sleeping(philo))
			return (NULL);
		mtx_print(philo, "is thinking");
	}
	return (NULL);
}
