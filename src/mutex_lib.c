/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:44:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/26 10:30:45 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mtx_print(t_philo *philo, char *s)
{
	size_t timestamp;

	if (is_done(philo))
		return ;
	pthread_mutex_lock(&philo->args->done_mutex);
	if (philo->args->end_sim == true)
	{
		pthread_mutex_unlock(&philo->args->done_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->args->print_mutex);
	timestamp = get_real_time() - philo->args->start_time_global;
	printf("%zu %d %s\n", timestamp, philo->philo_id, s);
	pthread_mutex_unlock(&philo->args->print_mutex);
	pthread_mutex_unlock(&philo->args->done_mutex);
}
