/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/30 18:54:32 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->args->mutex_start);
	while (i < philo->args->nb_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			pthread_mutex_unlock(&philo->args->mutex_start);
			end_simulation(philo, philo->args, i);
			return ;
		}
		i++;
	}
	i = 0;
	philo->args->start_time_global = get_real_time();
	while (i < philo->args->nb_of_philo)
	{
		philo[i].last_meal = philo->args->start_time_global;
		i++;
	}
	pthread_mutex_unlock(&philo->args->mutex_start);
	watch_philo(philo, philo->args, philo->args->nb_of_philo);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philo;

	philo = NULL;
	if (argc == 5 || argc == 6)
	{
		check_args(argc, argv);
		init_args(&args, argv, argc);
		philo = init_philosophers(&args);
		create_thread(philo);
	}
	else if (argc < 5)
		exit_error("Not enough arguments");
	else
		exit_error("Too many arguments");
	destroy_all(philo, &args, args.nb_of_philo);
	return (0);
}
