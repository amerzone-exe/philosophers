/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 17:47:41 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->args->mutex_start);
	while (i < philo->args->nb_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			exit_error("Error when creating threads");
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
	if (watch_philo(philo, philo->args))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philo = NULL;

	if (argc == 5 || argc == 6)
	{
		check_args(argc, argv);
		init_args(&args, argv, argc)
		// philo = init_philosophers(&args);
		// create_thread(philo);
	}
	else if (argc < 5)
		exit_error("Not enough argument");
	else
		exit_error("Too many argument");
	printf("nb_of_philo = %d\n", args.nb_of_philo);
	destroy_all(philo, &args, args.nb_of_philo);
	return (0);
}
