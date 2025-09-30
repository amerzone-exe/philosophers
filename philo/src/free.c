/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:52:43 by amerzone          #+#    #+#             */
/*   Updated: 2025/09/30 16:10:48 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_forks(t_fork *forks, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		pthread_mutex_destroy(&forks[i].fork_mutex);
		i++;
	}
}

void	destroy_fork(t_fork *fork, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		pthread_mutex_destroy(&fork[i].fork_mutex);
		i++;
	}
	free(fork);
}

void	destroy_args(t_args *args)
{
	pthread_mutex_destroy(&args->mutex_start);
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->done_mutex);
}

void	destroy_all(t_philo *philo, t_args *args, int until)
{
	int	i;

	i = 0;
	if (args->forks)
		destroy_fork(args->forks, args->nb_of_philo);
	destroy_args(args);
	if (philo)
	{
		while (i < until)
		{
			pthread_mutex_destroy(&philo[i].full_mutex);
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free(philo);
	}
}
