/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:50:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/28 15:39:37 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Usleep that check if the simulation is already done */

bool	my_usleep(size_t time, t_philo *philo)
{
	size_t end_time;

	end_time = get_real_time() + time;
	while (get_real_time() < end_time)
	{
		if (is_done(philo) == true)
			return (true);
		usleep(500);
	}
	return (false);
}

// bool	my_usleep(size_t time, t_philo *philo)
// {
// 	// size_t start_time;
// 	size_t end_time;
// 	bool	sim_is_done;

// 	sim_is_done = false;
// 	// start_time = get_real_time();
// 	end_time = get_real_time() + time;
// 	while (get_real_time() - start_time < time)
// 	{
// 		if (is_done(philo) == true)
// 		{
// 			sim_is_done = true;
// 			break ;
// 		}
// 		usleep(500);
// 	}
// 	return (sim_is_done);
// }

// bool	my_usleep(size_t time, t_philo *philo)
// {
// 	size_t start_time;
// 	bool	sim_is_done;

// 	sim_is_done = false;
// 	start_time = get_real_time();
// 	while (get_real_time() - start_time < time && !is_done(philo))
// 	{
// 		usleep(100);
// 	}
// 	return (sim_is_done);
// }

/* Get time in ms */

size_t get_real_time(void)
{
	struct timeval time;
	size_t res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}
