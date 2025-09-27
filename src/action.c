/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:56:59 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 18:03:14 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool		philo_eating(t_philo *philo);
bool		philo_sleeping(t_philo *philo);
static void	update_meals(t_philo *philo);
static void	update_last_meal(t_philo *philo);

bool philo_eating(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	mtx_print(philo, "is eating");
	update_last_meal(philo);
	update_meals(philo);
	sim_is_done = my_usleep(philo->args->time_to_eat, philo);
	drop_forks(philo);
	return (sim_is_done);
}

bool	philo_sleeping(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	mtx_print(philo, "is sleeping");
	sim_is_done = my_usleep(philo->args->time_to_sleep, philo);
	return (sim_is_done);
}

static void	update_meals(t_philo *philo)
{
	philo->nb_of_eat++;
	if (philo->nb_of_eat == philo->args->eat_max)
	{
		pthread_mutex_lock(&philo->full_mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->full_mutex);
	}
}

static void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_real_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}