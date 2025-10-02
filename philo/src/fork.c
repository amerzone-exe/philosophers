/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:07:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/02 17:11:13 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork);
void		drop_forks(t_philo *philo);
static bool	try_take_fork(t_fork *fork);

void	take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	bool	has_left;
	bool	has_right;

	has_left = false;
	has_right = false;
	while (!is_done(philo))
	{
		if (!has_right && try_take_fork(right_fork))
		{
			has_right = true;
			mtx_print(philo, "has taken a fork");
		}
		if (!has_left && try_take_fork(left_fork))
		{
			has_left = true;
			mtx_print(philo, "has taken a fork");
		}
		if (has_right && has_left)
			return ;
		else
			usleep(500);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

static bool	try_take_fork(t_fork *fork)
{
	bool	taken;

	taken = false;
	pthread_mutex_lock(&fork->fork_mutex);
	if (fork->is_taken == 0)
	{
		fork->is_taken = 1;
		taken = true;
	}
	pthread_mutex_unlock(&fork->fork_mutex);
	return (taken);
}
