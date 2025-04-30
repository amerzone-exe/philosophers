/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/29 20:11:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	take_forks(t_philo *philo)
// {
// 	struct timeval timestamp;
	
// 	gettimeofday(&timestamp, NULL);
// 	pthread_mutex_lock(&philo->left_fork.fork);
// 	printf("[%lu] philo %d has taken a fork\n", timestamp.tv_usec, philo->philo_id);
// 	philo->left_fork.is_taken = 1;
// 	pthread_mutex_lock(&philo->right_fork.fork);
// 	printf("[%lu] philo %d has taken a fork\n", timestamp.tv_usec, philo->philo_id);
// 	printf("[%lu] philo %d is eating\n", timestamp.tv_usec, philo->philo_id);
// 	philo->left_fork.is_taken = 1;
// 	usleep(200);
// }

void	*routine(void *args)
{
	t_philo	*philo;
	int		i;
	struct timeval before;
	struct timeval after;

	i = 0;
	philo = (t_philo *)args;
	if (philo->philo_id % 2 == 1)
		usleep(100);
	gettimeofday(&before, NULL);
	// printf("philo [%d]\n", philo->philo_id);
	while(1)
	{
		if (philo->left_fork->is_taken == 0 && philo->right_fork->is_taken == 0)
		{
			gettimeofday(&before, NULL);
			pthread_mutex_lock(&philo->left_fork->fork);
			philo->left_fork->is_taken = 1;
			printf("%lu %d has taken a fork\n", before.tv_usec, philo->philo_id);
			pthread_mutex_lock(&philo->right_fork->fork);
			philo->right_fork->is_taken = 1;
			printf("%lu %d has taken a fork\n", before.tv_usec, philo->philo_id);
			printf("%lu %d is eating\n", before.tv_usec, philo->philo_id);
			usleep(philo->args->time_to_eat);
			philo->has_eat++;
			pthread_mutex_unlock(&philo->left_fork->fork);
			pthread_mutex_unlock(&philo->right_fork->fork);
			philo->left_fork->is_taken = 0;
			philo->right_fork->is_taken = 0;
			gettimeofday(&before, NULL);
			printf("%lu %d is sleeping\n", before.tv_usec, philo->philo_id);
		}
		usleep(philo->args->time_to_sleep);
		gettimeofday(&before, NULL);
		printf("%lu %d is thinking\n", before.tv_usec, philo->philo_id);
		gettimeofday(&after, NULL);
		printf("time to die = %d\n", time);
		if (((after.tv_sec - before.tv_sec) *1000) > philo->args->time_to_die)
		{
			gettimeofday(&before, NULL);
			printf("%lu %d is dead\n", before.tv_usec, philo->philo_id);
			return (NULL);
		}
		if (philo->has_eat == philo->args->eat_max)
		{
			gettimeofday(&before, NULL);
			printf("philo[%d] is full\n", philo->philo_id);
			return (NULL);
		}
	}
}

// void	*routine(void *args)
// {
// 	t_philo	*philo;
// 	int		i;

// 	i = 0;
// 	philo = (t_philo *)args;
// 	if (philo->philo_id % 2 == 1)
// 		usleep(100);
// 	while(1)
// 	{
// 		pthread_mutex_lock(&philo->left_fork);
// 		printf("[time_stamp] philo %d has taken a fork", philo->philo_id);
// 		pthread_mutex_lock(&philo->right_fork);
// 		printf("[time_stamp] philo %d has taken a fork", philo->philo_id);
// 		printf("[time_stamp] philo %d is eating", philo->philo_id);
// 		usleep(20000);
// 		pthread_mutex_unlock(&philo->left_fork);
// 		pthread_mutex_unlock(&philo->right_fork);
		
				
// 	}
// }

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		pthread_mutex_destroy(&args->forks[i].fork);
		i ++;
	}
}

t_philo	*init_philosophers(t_args *args)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->nb_of_philo);
	philo->args = args;
	if (!philo)
	{
		destroy_mutexes(args);
		
	}
	while (i < args->nb_of_philo)
	{
		philo[i].philo_id = i;
		philo[i].args = args;
		philo[i].left_fork = &args->forks[i];
		philo[i].right_fork = &args->forks[(i + 1) % args->nb_of_philo];
		philo[i].has_eat = 0;
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
		pthread_mutex_init(&forks[i].fork, NULL);
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
	args.forks = init_forks(args.nb_of_philo);
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
	return (0);
}
