/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:51:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/28 15:01:39 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "philo_struct.h"

int			watch_philo(t_philo *philo, t_args *args);
void		*end_simulation(t_philo *philo, t_args *args, int until);
static int	check_dead(t_philo *ptr_philo);

/*check si les philo sont mort ou si ils ont tous fini de manger*/

int	watch_philo(t_philo *philo, t_args *args)
{
	int	i;
	int	nb_philo;
	int	are_full;

	nb_philo = args->nb_of_philo;
	while (1)
	{
		i = 0;
		are_full = 0;
		while (i < nb_philo)
		{
			if (check_dead(&philo[i]))
			{
				mtx_print(&philo[i], "died");
				if (end_simulation(philo, args, nb_philo) == NULL)
					return (0);
			}
			pthread_mutex_lock(&philo[i].full_mutex);
			are_full += philo[i].is_full;
			pthread_mutex_unlock(&philo[i].full_mutex);
			if (are_full == nb_philo)
			{
				if (end_simulation(philo, args, nb_philo) == NULL)
					return (0);
			}
			++i;
			usleep(100);
		}
		usleep(500);
	}
}

/* Check if the time since last meal of a philo is superior as the time to die*/

static int check_dead(t_philo *ptr_philo)
{
	size_t actual_time;
	size_t time_since_meal;
	size_t philo_last_meal;

	actual_time = get_real_time();
	pthread_mutex_lock(&ptr_philo->meal_mutex);
	philo_last_meal = ptr_philo->last_meal;
	pthread_mutex_unlock(&ptr_philo->meal_mutex);
	time_since_meal = actual_time - philo_last_meal;
	if (time_since_meal > ptr_philo->args->time_to_die)
		return (true);
	return (false);
}

/* End the simulation by telling to all the philo thats someone died or is full */

void	*end_simulation(t_philo *philo, t_args *args, int until)
{
	int	i;
	
	pthread_mutex_lock(&args->done_mutex);
	philo->args->end_sim = true;
	pthread_mutex_unlock(&args->done_mutex);
	i = 0;
	while (i < until)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (NULL);
}
