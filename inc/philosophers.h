/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:17:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/07 13:42:43 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_fork
{
	unsigned int	is_taken;
	unsigned int	id_fork;
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
	pthread_mutex_t	died_mutex;
	bool			philo_died;
}t_args;

typedef struct s_philo
{
	unsigned int	philo_id;
	unsigned int	nb_of_eat;
	bool			has_eaten;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_args			*args;
}t_philo;

char	*ft_strtrim(char const *s1, char const *set);
int		my_atoi(const char *nptr);

void	check_args(int argc, char **argv);
int 	string_is_valid(char *str);
int		is_bracket(int c);
int		is_whitespace(int c);
int		ft_isdigit(int c);

void	exit_error(const char *str);
void	destroy_mutexes(t_philo *philo);

#endif