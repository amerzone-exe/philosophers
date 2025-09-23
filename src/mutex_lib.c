/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:44:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 22:30:29 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mtx_print(t_philo *philo, char *s)
{
	size_t timestamp;

	if (is_done(philo))
		return ;
	timestamp = get_real_time() - philo->start_time;
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%zu %d %s\n", timestamp, philo->philo_id, s);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
