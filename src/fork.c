/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:07:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/28 15:21:48 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork);
void drop_forks(t_philo *philo);
static bool fork_available(t_fork *fork);
static bool	get_fork(t_fork	*fork);

void take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	bool has_left = false;
	bool has_right = false;

	while (!is_done(philo))
	{
		if (!has_right && fork_available(right_fork))
		{
			has_right = get_fork(right_fork);
			mtx_print(philo, "has taken a fork");
		}
		if (!has_left && fork_available(left_fork))
		{
			has_left = get_fork(left_fork);
			mtx_print(philo, "has taken a fork");
		}
		if (has_right && has_left)
			return ;
		else
			usleep(500);
	}
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

static bool fork_available(t_fork *fork)
{
	bool	available;

	available = false;
	pthread_mutex_lock(&fork->fork_mutex);
	if (fork->is_taken == 0)
		available = true;
	pthread_mutex_unlock(&fork->fork_mutex);
	return (available);
}

static bool	get_fork(t_fork	*fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->is_taken = 1;
	pthread_mutex_unlock(&fork->fork_mutex);
	return (true);
}
