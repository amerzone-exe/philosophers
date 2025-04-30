/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:17:36 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/29 19:25:50 by jpiquet          ###   ########.fr       */
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
	pthread_mutex_t fork;
	int is_taken;
	int id_fork;
}t_fork;

typedef struct s_args
{
	t_fork *forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int eat_max;
	int nb_of_philo;
}t_args;

typedef struct s_philo
{
	int philo_id;
	int has_eat;
	pthread_t thread;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_args	*args;
}t_philo;

int		my_atoi(const char *nptr);
void	check_args(int argc, char **argv);
void	exit_error(const char *str);
int		is_bracket(int c);
int		ft_isdigit(int c);
int 	string_is_valid(char *str);
int		is_whitespace(int c);
char	*ft_strtrim(char const *s1, char const *set);

#endif