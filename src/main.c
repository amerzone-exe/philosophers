/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/07 15:05:55 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	struct	timeval actual_time;
	struct	timeval last_meal;

	gettimeofday(&actual_time, NULL);
	/*wait for all odd philo----------------------------*/
	if (philo->philo_id % 2 != 0)
		usleep(100);
	
	/*getting forks phase-------------------------------*/
	
	while(1)//(actual_time.tv_usec - last_meal.tv_usec) < philo->args->time_to_die)
	{
		if (philo->left_fork->is_taken == 0)
		{
			pthread_mutex_lock(&philo->args->fork_mutex);
			philo->left_fork->is_taken = 1;
			gettimeofday(&actual_time, NULL);
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("%ld %d as taken a fork\n", actual_time.tv_usec / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
			pthread_mutex_unlock(&philo->args->fork_mutex);
		}
		if (philo->right_fork->is_taken == 0)
		{
			pthread_mutex_lock(&philo->args->fork_mutex);
			philo->right_fork->is_taken = 1;
			gettimeofday(&actual_time, NULL);
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("%ld %d as taken a fork\n", actual_time.tv_usec / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
			pthread_mutex_unlock(&philo->args->fork_mutex);
		}
		
		/*eating phase-------------------------------*/
		
		// printf("philo %d left fork = %d right fork %d\n", philo->philo_id, philo->left_fork->is_taken, philo->right_fork->is_taken);
		
		if (philo->left_fork->is_taken == 1 && philo->right_fork->is_taken == 1)
		{
			gettimeofday(&actual_time, NULL);
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("%ld %d is eating\n", actual_time.tv_usec / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
			usleep(philo->args->time_to_eat * 1000);
			philo->nb_of_eat += 1;
			philo->has_eaten = true;
			gettimeofday(&last_meal, NULL); //time of the last meal
			pthread_mutex_lock(&philo->args->fork_mutex);
			philo->left_fork->is_taken = 0;
			// pthread_mutex_unlock(&philo->args->fork_mutex);
			// pthread_mutex_lock(&philo->args->fork_mutex);
			philo->right_fork->is_taken = 0;
			pthread_mutex_unlock(&philo->args->fork_mutex);
		}
		
		/*if philo is full-----------------------------*/
		
		if (philo->args->eat_max != 0 && philo->nb_of_eat == philo->args->eat_max)
		{
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("philo : %d is full\n", philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
			return (NULL);
		}
		
		/*sleeping phase-------------------------------*/
		
		if (philo->has_eaten == true)
		{
			gettimeofday(&actual_time, NULL);
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("%ld %d is sleeping\n", actual_time.tv_usec / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
			usleep(philo->args->time_to_sleep * 1000);
		}
		
		/*thinking phase-------------------------------*/
		
		gettimeofday(&actual_time, NULL);
		pthread_mutex_lock(&philo->args->print_mutex);
		printf("%ld %d is thinking\n", actual_time.tv_usec / 1000, philo->philo_id);
		pthread_mutex_unlock(&philo->args->print_mutex);
		
		/*if a philo dies------------------------------*/
		
		if ((actual_time.tv_usec - last_meal.tv_usec) > (philo->args->time_to_die * 1000))
		{
			pthread_mutex_lock(&philo->args->died_mutex);
			philo->args->philo_died = true;
			pthread_mutex_unlock(&philo->args->died_mutex);
			gettimeofday(&actual_time, NULL);
			pthread_mutex_lock(&philo->args->print_mutex);
			printf("%ld %d died\n", actual_time.tv_usec / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->args->print_mutex);
		}
		if (philo->args->philo_died == true)
			return(NULL);
	}
	return (NULL);
}

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
	philo->args = args;
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
		forks[i].id_fork = i;
		forks[i].is_taken = 0;
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

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			exit_error("Error when creating threads");
		i++;
	}
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
	pthread_mutex_destroy(&args.fork_mutex);
	
	//free fork
	free(args.forks);
	//destroy mutexes
	free(philo);
	//free philo
	destroy_mutexes(philo);
	
	return (0);
}
