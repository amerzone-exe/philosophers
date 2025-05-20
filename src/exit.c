/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/05 14:45:24 by jpiquet          ###   ########.fr       */
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
		pthread_mutex_destroy(&philo[i].mutex);
		i++;
	}
}
