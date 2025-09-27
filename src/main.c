/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 13:11:16 by jpiquet          ###   ########.fr       */
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
	// usleep(600);
	while (1)
	{
		i = 0;
		are_full = 0;
		while (i < nb_philo)
		{
			if (check_dead(&philo[i]))
			{
				mtx_print(&philo[i], "died");
				if (end_simulation(philo, args) == NULL)
					return (0);
			}
			pthread_mutex_lock(&philo[i].full_mutex);
			are_full += philo[i].is_full;
			pthread_mutex_unlock(&philo[i].full_mutex);
			if (are_full == args->nb_of_philo)
			{
				if (end_simulation(philo, args) == NULL)
					return (0);
			}
			++i;
		}
		usleep(500);
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
	i = 0;
	philo->args->start_time_global = get_real_time();
	while (i < philo->args->nb_of_philo)
	{
		philo[i].last_meal = philo->args->start_time_global;
		i++;
	}
	// printf("Start time = %zu\n", philo->args->start_time_global);
	pthread_mutex_unlock(&philo->args->mutex_start);
	// usleep(500);
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
	return (0);
}
