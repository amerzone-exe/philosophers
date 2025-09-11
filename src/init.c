/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 16:24:03 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philosophers(t_args *args)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!philo)
	{
		free(args->forks);
		exit_error("Error during malloc of philosophers");
	}
	while (i < args->nb_of_philo)
	{
		philo[i].philo_id = i;
		philo[i].args = args;
		philo[i].left_fork = &args->forks[i];
		philo[i].right_fork = &args->forks[(i + 1) % args->nb_of_philo];
		philo[i].has_eaten = false;
		philo[i].nb_of_eat = 0;
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
		i++;
	}
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
		pthread_mutex_init(&forks[i].fork_mutex, NULL);
		i++;
	}
	return (forks);
}

t_args init_args(char **argv, int argc)
{
	t_args 	args;
	char	*last_param;

	args.nb_of_philo = my_atoi(argv[1]);
	args.time_to_die = my_atoi(argv[2]);
	args.time_to_eat = my_atoi(argv[3]);
	args.time_to_sleep = my_atoi(argv[4]);
	if (argc == 6)
	{
		last_param = ft_strtrim(argv[5], "[] ");
		if (!last_param)
			exit_error("Malloc error in strtrim");
		args.eat_max = my_atoi(last_param);
		free(last_param);
	}
	else 
		args.eat_max = 0;
	args.forks = init_forks(args.nb_of_philo);
	pthread_mutex_init(&args.fork_mutex, NULL);
	pthread_mutex_init(&args.print_mutex, NULL);
	pthread_mutex_init(&args.died_mutex, NULL);
	return (args);
}
