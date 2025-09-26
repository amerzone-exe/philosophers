/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/24 13:03:05 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(const char *str)
{
	perror(str);
	exit (1);
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_of_philo)
	{
		pthread_mutex_destroy(&philo[i].full_mutex);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
}
