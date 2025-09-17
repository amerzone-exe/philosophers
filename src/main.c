/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/17 09:35:23 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_thread(t_philo *philo)
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
	usleep(500);
	pthread_mutex_unlock(&philo->args->mutex_start);
	i = 0;
	while (i < philo->args->nb_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit_error("Error when creating threads");
		i++;
	}
}

int main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		check_args(argc, argv);
		args = init_args(argv, argc);
		philo = init_philosophers(&args);
		create_thread(philo);
	}
	else if (argc < 5)
		exit_error("Not enought argument");
	else
		exit_error("Too many argument");
	
	pthread_mutex_destroy(&args.died_mutex);
	pthread_mutex_destroy(&args.print_mutex);
	free(args.forks);
	free(philo);
	destroy_mutexes(philo);
	
	return (0);
}
