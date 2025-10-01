/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:17:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/01 14:33:38 by jocelyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include "philo_struct.h"

// parsing

int		check_args(int argc, char **argv);

// exit

int		exit_error(const char *str);
void	*exit_null(const char *str);
int		exit_and_destroy(t_args *args, const char *str);

// utils

int		my_atoi(const char *nptr);
int		is_whitespace(int c);
int		ft_isdigit(int c);

// init

t_philo	*init_philosophers(t_args *args);
int		init_args(t_args *args, char **argv, int argc);

// fork

void	take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork);
void	drop_forks(t_philo *philo);

// watch

int		watch_philo(t_philo *philo, t_args *args, int nb_philo);
void	end_simulation(t_philo *philo, t_args *args, int until);

// routine

bool	is_done(t_philo *philo);
void	*routine(void *args);

// action

bool	philo_eating(t_philo *philo);
bool	philo_sleeping(t_philo *philo);

// time

bool	my_usleep(size_t time, t_philo *philo);
size_t	get_real_time(void);

// mutex_lib

void	mtx_print(t_philo *philo, char *s);
void	mtx_print_die(t_philo *philo, char *s);

// free

void	destroy_fork(t_fork *fork, int until);
void	destroy_args(t_args *args);
void	destroy_all(t_philo *philo, t_args *args, int until);
void	free_forks(t_fork *forks, t_args *args);

#endif