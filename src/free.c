/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:52:43 by amerzone          #+#    #+#             */
/*   Updated: 2025/09/17 17:01:40 by jocelyn          ###   ########.fr       */
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

void	*destroy_fork(t_fork *fork, int until)
{
	int	i;

	i = 0;
	perror("mutex init error");
	while (i < until)
	{
		pthread_mutex_destroy(&fork[i].fork_mutex);
		i++;
	}
	free(fork);
	return (NULL);
}

// void	destroy_args(t_args *args)
// {
	
// }