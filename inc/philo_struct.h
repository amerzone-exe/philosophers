/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:53:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 17:54:43 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
#define PHILO_STRUCT_H

#include "philosophers.h"

typedef struct s_fork
{
	unsigned int	is_taken;
	pthread_mutex_t	fork_mutex;
}t_fork;

typedef struct s_args
{
	t_fork			*forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long 			eat_max;
	unsigned int 	nb_of_philo;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	died_mutex;
	bool			philo_died;
}t_args;

typedef struct s_philo
{
	unsigned int	philo_id;
	unsigned int	nb_of_eat;
	bool			has_eaten;
	long long		start_time;
	long long		last_meal;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_args			*args;
}t_philo;

#endif