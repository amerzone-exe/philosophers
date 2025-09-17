/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/17 17:31:36 by jocelyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*termine la simulation et indique a tous les philos qu'ils doivent s'arreter*/
void	*end_simulation(t_philo *philo, t_args *args)
{
	int	i;
	
	i = 0;
	while (i < args->nb_of_philo)
	{
		pthread_mutex_lock(&philo[i].done_mutex);
		philo[i].is_done = true;
		pthread_mutex_unlock(&philo[i].done_mutex);
		i++;
	}
	i = 0;
	while (i < philo->args->nb_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit_error("Error when creating threads");
		i++;
	}
	return (NULL);
}

/*check si les philo sont mort ou si ils ont tous fini de manger*/
int	watch_philo(t_philo *philo, t_args *args)
{
	int	i;
	int	nb_philo;
	int	are_full;

	nb_philo = args->nb_of_philo;
	are_full = 0;
	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			if (check_dead(philo[i]))
			{
				mtx_print(&philo[i], "died");
				if (end_simulation(philo, args) == NULL)
					return (0);
			}
			pthread_mutex_lock(&philo[i].full_mutex);
			are_full += philo[i].is_full;
			pthread_mutex_unlock(&philo[i].full_mutex);
			if (are_full == args->eat_max)
			{
				if (end_simulation(philo, args) == NULL)
					return (0);
			}
			i++;
		}
	}
}

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
	usleep(500);
	pthread_mutex_unlock(&philo->args->mutex_start);
	if (watch_philo(philo, philo->args))
		return (0);
}

int main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		check_args(argc, argv);
		if (!init_args(&args, argv, argc))
			exit(EXIT_FAILURE);
		philo = init_philosophers(&args);
		create_thread(philo);
	}
	else if (argc < 5)
		exit_error("Not enought argument");
	else
		exit_error("Too many argument");
	pthread_mutex_destroy(&args.died_mutex);
	pthread_mutex_destroy(&args.print_mutex);
	free(philo);
	destroy_fork(args.forks, args.nb_of_philo);
	destroy_mutexes(philo);
	return (0);
}
