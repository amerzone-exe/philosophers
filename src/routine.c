/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 18:58:00 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_real_time()
{
	struct	timeval time;
	size_t res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	init_time_philo(t_philo *philo)
{
	philo->start_time = get_real_time();
	philo->last_meal = get_real_time();
}

int	check_dead(t_philo *philo)
{
	size_t	actual_time;
	size_t	time_since_meal;

	actual_time = get_real_time;
	time_since_meal = actual_time - philo->last_meal;
	if (time_since_meal > philo->args->time_to_die)
		return (true);
	return (false);
}

void	*routine(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->args->mutex_start);
	pthread_mutex_unlock(&philo->args->mutex_start);
	init_time_philo(philo);
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (philo->right_fork->is_taken == 0)
		{
			philo->right_fork->is_taken == 1;
			mtx_print(philo, "has taken a fork");
		}
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (philo->left_fork->is_taken == 0)
		{
			philo->left_fork->is_taken == 1;
			mtx_print(philo, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (philo->left_fork->is_taken == 0)
		{
			philo->left_fork->is_taken == 1;
			mtx_print(philo, "has taken a fork");
		}
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (philo->right_fork->is_taken == 0)
		{
			philo->right_fork->is_taken == 1;
			mtx_print(philo, "has taken a fork");
		}
	}
	mtx_print(philo, "is eating");
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}
