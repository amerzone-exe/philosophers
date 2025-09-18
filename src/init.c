/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/18 14:35:39 by jocelyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_mutex_init(t_philo *philo, t_args *args)
{
	int	i;

	i = -1;
	while (i++ < args->nb_of_philo)
	{
		if (pthread_mutex_init(&philo[i].full_mutex, NULL))
		{
			destroy_all(philo, args, i);
			return (0);
		}
		if (pthread_mutex_init(&philo[i].done_mutex, NULL))
		{
			pthread_mutex_destroy(&philo[i].full_mutex);
			destroy_all(philo, args, i);
			return (0);
		}
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL))
		{
			pthread_mutex_destroy(&philo[i].full_mutex);
			pthread_mutex_destroy(&philo[i].done_mutex);
			destroy_all(philo, args, i);
			return (0);
		}
	}
	return (1);
}

t_philo	*init_philosophers(t_args *args)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!philo)
	{
		destroy_fork(args->forks, args->nb_of_philo);
		destroy_args(args);
		exit_error("Error during malloc of philosophers");
	}
	while (i < args->nb_of_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].args = args;
		philo[i].left_fork = &args->forks[i];
		philo[i].right_fork = &args->forks[(i + 1) % args->nb_of_philo];
		philo[i].is_full = 0;
		philo[i].end_sim = false;
		philo[i].nb_of_eat = 0;
		i++;
	}
	if (!philo_mutex_init(philo, args))
		exit_error("Error during intialisation of mutexes");
	return (philo);
}

t_fork	*init_forks(int nb_philo)
{
	int	i;
	t_fork *forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * nb_philo);
	if (!forks)
		exit_error("Error during malloc for forks");
	while (i < nb_philo)
	{
		forks[i].is_taken = false;
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL))
			return (destroy_fork(forks, i));
		i++;
	}
	return (forks);
}

int	init_mutex_args(t_args *args)
{
	if (pthread_mutex_init(&args->mutex_start, NULL))
	{
		destroy_fork(args->forks, args->nb_of_philo);
		return (0);
	}
	if (pthread_mutex_init(&args->print_mutex, NULL))
	{
		pthread_mutex_destroy(&args->mutex_start);
		destroy_fork(args->forks, args->nb_of_philo);
		return (0);
	}
	if (pthread_mutex_init(&args->died_mutex, NULL))
	{
		pthread_mutex_destroy(&args->mutex_start);
		pthread_mutex_destroy(&args->print_mutex);
		destroy_fork(args->forks, args->nb_of_philo);
		return (0);
	}
	return (1);
}

int	init_args(t_args *args, char **argv, int argc)
{
	args->nb_of_philo = my_atoi(argv[1]);
	args->time_to_die = my_atoi(argv[2]);
	args->time_to_eat = my_atoi(argv[3]);
	args->time_to_sleep = my_atoi(argv[4]);
	if (argc == 6)
		args->eat_max = my_atoi(argv[5]);
	else 
		args->eat_max = -1;
	args->forks = init_forks(args->nb_of_philo);
	if (!args->forks)
		return (0);
	if (!init_mutex_args(args))
		return (0);
	return (1);
}
