/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:39:54 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/15 17:20:22 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *args)
{
	struct timeval time;
	t_philo *data;

	data = (t_philo *)args;
	gettimeofday(&time, NULL);
	time.tv_usec = time.tv_usec * 1000;
	while (1)
	{
		printf("data->which_philo = %d\n", data->which_philo);
		if (data->which_philo == 0)
		{
			pthread_mutex_lock(&data->mutex[data->which_philo]);
			pthread_mutex_lock(&data->mutex[data->nb_of_philo - 1]);
			// gettimeofday(&time, NULL);
			printf("Philosopher %d has taken a fork\n", data->which_philo);
			// gettimeofday(&time, NULL);
			printf("Philosopher %d is eating\n", data->which_philo);
			usleep(data->time_to_eat);
			pthread_mutex_unlock(&data->mutex[data->which_philo]);
			pthread_mutex_unlock(&data->mutex[data->nb_of_philo - 1]);
		}
		else
		{
			pthread_mutex_lock(&data->mutex[data->which_philo - 1]);
			pthread_mutex_lock(&data->mutex[data->which_philo]);
			gettimeofday(&time, NULL);
			printf("At %ld : philosopher %d has taken a fork\n", time.tv_usec, data->which_philo);
			gettimeofday(&time, NULL);
			printf("At %ld : philosopher %d is eating\n", time.tv_usec, data->which_philo);
			usleep(data->time_to_eat);
			pthread_mutex_unlock(&data->mutex[data->which_philo - 1]);
			pthread_mutex_unlock(&data->mutex[data->which_philo]);
		}
		gettimeofday(&time, NULL);
		printf("At %ld : philosopher %d is sleeping\n", time.tv_usec, data->which_philo);
		usleep(data->time_to_sleep);
		gettimeofday(&time, NULL);
		printf("At %ld : philosopher %d is thinking\n", time.tv_usec, data->which_philo);
		printf("At %ld : philosopher %d died\n", time.tv_usec, data->which_philo);
	}
	return (NULL);
}

//initialiser la structure de donnée t_philo;
t_philo	*t_philo_init(char **argv, int nb_philo)
{
	t_philo *data;
	int	j;
	int i;

	i = 0;
	j = 0;
	printf("nb_philo = %d\n", nb_philo);
	data = malloc(sizeof(t_philo) * nb_philo);
	if (!data)
	{
		perror("malloc error");
		exit (EXIT_FAILURE);
	}
	data->mutex = malloc(sizeof(pthread_mutex_t) * nb_philo);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->nb_of_philo = nb_philo;
	while (j < nb_philo)
	{
		data[j].which_philo = j + 1;
		j++;
	}
	return (data);
}

int	main(int argc, char **argv)
{
	int	i;
	int nb_philo;
	int j;
	struct timeval time;
	pthread_t *thread;
	t_philo *data;

	nb_philo = atoi(argv[1]);
	printf("error 1\n");
	data = t_philo_init(argv, nb_philo);
	printf("error 2\n");
	thread = malloc(sizeof(pthread_t) * nb_philo);
	if (!thread)
	{
		perror("malloc error");
		return (1);
	}
	//initialiser tous les mutex du tableau de mutex
	j = 0;
	while (j < nb_philo)
	{
		pthread_mutex_init(&data->mutex[j], NULL);
		j++;
	}
	//créer chaques thread de 0 à nombre de philo
	while (i < nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &routine, &data[i]))
		{
			perror("Thread create error");
			return (1);
		}
		printf("created thread [%d]\n", i);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(thread[i], NULL))
		{
			perror("Thread join error");
			return (1);
		}
		i++;
	}
	j = 0;
	while (j < nb_philo)
	{
		pthread_mutex_destroy(&data->mutex[j]);
		j++;
	}
	// printf("time = %ld || micro sec = %ld\n", time.tv_sec, time.tv_usec);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int	i;
// 	int nb_philo;
// 	struct timeval time;
// 	pthread_t *thread;
// 	t_philo data;
	
// 	i = 0;
// 	nb_philo = atoi(argv[1]);
// 	thread = malloc(sizeof(pthread_t) * nb_philo);
// 	if (!thread)
// 	{
// 		perror("malloc error");
// 		return (1);
// 	}
// 	pthread_mutex_init(&data.mutex, NULL);
// 	while (i < nb_philo)
// 	{
// 		if (pthread_create(&thread[i], NULL, &routine, (void *)&data))
// 		{
// 			perror("Thread create error");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	while (i < nb_philo)
// 	{
// 		if (pthread_join(thread[i], NULL))
// 		{
// 			perror("Thread join error");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	// printf("time = %ld || micro sec = %ld\n", time.tv_sec, time.tv_usec);
// 	return (0);
// }
