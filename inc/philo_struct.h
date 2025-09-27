/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:53:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 13:32:20 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
#define PHILO_STRUCT_H

#include "philosophers.h"

/* creer une structure qui puisse etre envoyé dans 
les fonctions qui check les variable mutexé*/

typedef struct s_fork
{
	unsigned int	is_taken;
	pthread_mutex_t	fork_mutex;
}t_fork;

typedef struct s_args
{
	t_fork			*forks;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	bool			end_sim;
	pthread_mutex_t	done_mutex;
	int				eat_max;
	int 			nb_of_philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex_start;
	size_t			start_time_global;
}t_args;

typedef struct s_philo
{
	unsigned int	philo_id;
	int				nb_of_eat;
	bool			*end_sim;
	int				is_full;
	pthread_mutex_t	full_mutex;
	size_t			last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_args			*args;
}t_philo;

#endif