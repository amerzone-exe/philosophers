/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/02 14:05:52 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		philo_mutex_init(t_philo *philo, t_args *args);
static int		init_mutex_args(t_args *args);
static t_fork	*init_forks(int nb_philo);

t_philo	*init_philosophers(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!philo)
		return (NULL);
	while (i < args->nb_of_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].args = args;
		philo[i].left_fork = &args->forks[i];
		philo[i].right_fork = &args->forks[(i + 1) % args->nb_of_philo];
		philo[i].is_full = 0;
		philo[i].nb_of_eat = 0;
		philo[i].last_meal = 0;
		philo[i].end_sim = &args->end_sim;
		i++;
	}
	if (!philo_mutex_init(philo, args))
		return (exit_null("Error during philo mutexes initialisation"));
	return (philo);
}

int	init_args(t_args *args, char **argv, int argc)
{
	int	error;

	error = 0;
	args->nb_of_philo = my_atoi(argv[1], &error);
	if (args->nb_of_philo == 0)
		return (exit_error("Need at least one philosopher"));
	args->time_to_die = my_atoi(argv[2], &error);
	args->time_to_eat = my_atoi(argv[3], &error);
	args->time_to_sleep = my_atoi(argv[4], &error);
	if (argc == 6)
	{
		args->eat_max = my_atoi(argv[5], &error);
		if (args->eat_max == 0)
			return (exit_error("Need at least 1 meal"));
	}
	else
		args->eat_max = -1;
	if (error)
		return (1);
	args->end_sim = false;
	args->forks = init_forks(args->nb_of_philo);
	if (!args->forks || init_mutex_args(args))
		return (1);
	return (0);
}

static t_fork	*init_forks(int nb_philo)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * nb_philo);
	if (!forks)
		return (exit_null("Error during forks allocation"));
	while (i < nb_philo)
	{
		forks[i].is_taken = false;
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL))
		{
			destroy_fork(forks, i);
			return (exit_null("Error during fork mutexes initialisation"));
		}
		i++;
	}
	return (forks);
}

static int	philo_mutex_init(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&philo[i].full_mutex, NULL))
		{
			destroy_all(philo, args, i);
			return (0);
		}
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL))
		{
			pthread_mutex_destroy(&philo[i].full_mutex);
			destroy_all(philo, args, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutex_args(t_args *args)
{
	if (pthread_mutex_init(&args->mutex_start, NULL))
	{
		destroy_fork(args->forks, args->nb_of_philo);
		return (exit_error("Error during args mutexes initialisation"));
	}
	if (pthread_mutex_init(&args->print_mutex, NULL))
	{
		pthread_mutex_destroy(&args->mutex_start);
		destroy_fork(args->forks, args->nb_of_philo);
		return (exit_error("Error during args mutexes initialisation"));
	}
	if (pthread_mutex_init(&args->done_mutex, NULL))
	{
		pthread_mutex_destroy(&args->mutex_start);
		pthread_mutex_destroy(&args->print_mutex);
		destroy_fork(args->forks, args->nb_of_philo);
		return (exit_error("Error during args mutexes initialisation"));
	}
	return (0);
}
