/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:17:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/17 17:04:14 by jocelyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include "philo_struct.h"

char	*ft_strtrim(char const *s1, char const *set);
int		my_atoi(const char *nptr);

// parsing

void	check_args(int argc, char **argv);
int 	string_is_valid(char *str);
int		is_bracket(int c);
int		is_whitespace(int c);
int		ft_isdigit(int c);

void	exit_error(const char *str);
void	destroy_mutexes(t_philo *philo);

// init

t_philo	*init_philosophers(t_args *args);
t_fork	*init_forks(int nb_philo);
void	*init_args(t_args *args, char **argv, int argc);

// routine

size_t	get_real_time();
void	init_time_philo(t_philo *philo);
int		check_dead(t_philo philo);
void	*routine(void *args);

// mutex_lib

void	mtx_print(t_philo *philo, char *s);

// free

void	*destroy_fork(t_fork *fork, int until);
void	free_forks(t_fork *forks, t_args *args);


#endif