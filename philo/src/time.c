/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:50:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/29 09:50:17 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Usleep that check if the simulation is already done */

bool	my_usleep(size_t time, t_philo *philo)
{
	size_t	end_time;

	end_time = get_real_time() + time;
	while (get_real_time() < end_time)
	{
		if (is_done(philo) == true)
			return (true);
		usleep(500);
	}
	return (false);
}

/* Get time in ms */

size_t	get_real_time(void)
{
	struct timeval	time;
	size_t			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}
