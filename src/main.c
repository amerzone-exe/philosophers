/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 23:00:59 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*termine la simulation et indique a tous les philos qu'ils doivent s'arreter*/
void	*end_simulation(t_philo *philo, t_args *args)
{
	int	i;
	
	pthread_mutex_lock(&args->done_mutex);
	philo->args->end_sim = true;
	pthread_mutex_unlock(&args->done_mutex);
	// while (i < args->nb_of_philo)
	// {
	// 	pthread_mutex_lock(&philo[i].done_mutex);
	// 	philo[i].end_sim = true;
	// 	pthread_mutex_unlock(&philo[i].done_mutex);
	// 	i++;
	// }
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			destroy_all(philo, args, args->nb_of_philo);
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
	usleep(500);
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
			// pthread_mutex_lock(&args->print_mutex);
			are_full += philo[i].is_full;
			// if (are_full != 0)
			// (
			// 	printf("p201 2 diedhilo %d are full = %d\n", philo[i].philo_id, are);
			// )
			// pthread_mutex_unlock(&args->print_mutex);
			pthread_mutex_unlock(&philo[i].full_mutex);
			if (are_full == args->nb_of_philo)
			{
				// pthread_mutex_lock(&args->print_mutex);
				// printf("-----------------------------END SIMU\n");
				// pthread_mutex_unlock(&args->print_mutex);
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
	philo->args->start_time_global = get_real_time();
	pthread_mutex_unlock(&philo->args->mutex_start);
	usleep(500);
	if (watch_philo(philo, philo->args))
		return (0);
	return (1);
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
		exit_error("Not enough argument");
	else
		exit_error("Too many argument");
	// pthread_mutex_destroy(&args.died_mutex);
	// pthread_mutex_destroy(&args.print_mutex);
	// free(philo);
	// destroy_fork(args.forks, args.nb_of_philo);
	// destroy_mutexes(philo);
	return (0);
}
