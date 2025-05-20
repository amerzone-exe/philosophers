/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/05 14:59:53 by jpiquet          ###   ########.fr       */
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

// void	*routine(void *args)
// {
// 	t_philo	*philo;
// 	int		i;
// 	struct timeval before;
// 	struct timeval after;

// 	i = 0;
// 	philo = (t_philo *)args;
// 	if (philo->philo_id % 2 == 1)
// 		usleep(100);
// 	gettimeofday(&before, NULL);
// 	// printf("philo [%d]\n", philo->philo_id);
// 	while(1)
// 	{
// 		if (philo->left_fork->is_taken == 0 && philo->right_fork->is_taken == 0)
// 		{
// 			gettimeofday(&before, NULL);
// 			pthread_mutex_lock(&philo->left_fork->fork);
// 			philo->left_fork->is_taken = 1;
// 			printf("%ld %d has taken a fork\n", before.tv_usec / 1000, philo->philo_id);
// 			pthread_mutex_lock(&philo->right_fork->fork);
// 			philo->right_fork->is_taken = 1;
// 			printf("%ld %d has taken a fork\n", before.tv_usec / 1000, philo->philo_id);
// 			printf("%ld %d is eating\n", before.tv_usec, philo->philo_id);
// 			usleep(philo->args->time_to_eat);
// 			philo->has_eat++;
// 			pthread_mutex_unlock(&philo->left_fork->fork);
// 			pthread_mutex_unlock(&philo->right_fork->fork);
// 			philo->left_fork->is_taken = 0;
// 			philo->right_fork->is_taken = 0;
// 			gettimeofday(&before, NULL);
// 			printf("%ld %d is sleeping\n", before.tv_usec, philo->philo_id);
// 			usleep(philo->args->time_to_sleep);
// 			gettimeofday(&before, NULL);
// 		}
// 		// printf("before = %ld\n", before.tv_usec);
// 		// printf("time to sleep = %d\n", philo->args->time_to_sleep);
// 		printf("%ld %d is thinking\n", before.tv_usec, philo->philo_id);
// 		// printf("after = %ld\n", after.tv_usec);
// 		// long time;
// 		// time = after.tv_usec - before.tv_usec;
// 		// printf("time to die = %ld\n", time);
// 		// exit(0);
// 		while (philo->left_fork->is_taken == 1 && philo->right_fork->is_taken == 1)
// 		{
// 			gettimeofday(&after, NULL);
// 			if (((after.tv_usec - before.tv_usec) / 1000) > philo->args->time_to_die)
// 			{
// 				gettimeofday(&before, NULL);
// 				printf("%lu %d is dead\n", before.tv_usec, philo->philo_id);
// 				// return (NULL);
// 				exit(1);
// 			}
// 		}
// 		if (philo->has_eat == philo->args->eat_max)
// 		{
// 			gettimeofday(&before, NULL);
// 			printf("philo[%d] is full\n", philo->philo_id);
// 			return (NULL);
// 		}
// 	}
// }

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