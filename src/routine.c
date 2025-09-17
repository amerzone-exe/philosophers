/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/17 17:18:09 by jocelyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_real_time()
{
	struct	timeval time;
	size_t res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	init_time_philo(t_philo *philo)
{
	philo->start_time = get_real_time();
	philo->last_meal = get_real_time();
}

/*checker si le temps qu'il y a eu avec le dernier repas est plus elever que le time to die*/
int	check_dead(t_philo philo)
{
	size_t	actual_time;
	size_t	time_since_meal;

	actual_time = get_real_time();
	pthread_mutex_lock(&philo.meal_mutex);
	time_since_meal = actual_time - philo.last_meal;
	pthread_mutex_unlock(&philo.meal_mutex);
	if (time_since_meal > philo.args->time_to_die)
		return (true);
	return (false);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	if (philo->right_fork->is_taken == 0)
	{
		philo->right_fork->is_taken = 1;
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (philo->left_fork->is_taken == 0)
		{
			philo->left_fork->is_taken = 1;
			mtx_print(philo, "has taken a fork");
			mtx_print(philo, "has taken a fork");
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			return (1);
		}
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		philo->right_fork->is_taken = 0;
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (0);
}

void	my_usleep(size_t time)
{
	size_t start_time;

	start_time = get_real_time();
	while (get_real_time() - start_time < time)
	{
		usleep(500);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	if (philo->left_fork->is_taken == 1)
		philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	if (philo->right_fork->is_taken == 1)
		philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	update_meals(t_philo *philo)
{
	philo->nb_of_eat++;
	if (philo->nb_of_eat == philo->args->eat_max)
	{
		pthread_mutex_lock(&philo->full_mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->full_mutex);
	}
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_real_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	mtx_print(philo, "is eating");
	my_usleep(philo->args->time_to_eat);
	drop_forks(philo);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->args->mutex_start);
	pthread_mutex_unlock(&philo->args->mutex_start);
	init_time_philo(philo);
	if (philo->philo_id % 2 == 0)
		my_usleep(philo->args->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->done_mutex);
		if (philo->is_done)
		{
			pthread_mutex_unlock(&philo->done_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->done_mutex);
		if (take_forks(philo))
		{
			philo_eating(philo);
			mtx_print(philo, "is sleeping");
			my_usleep(philo->args->time_to_sleep);
			mtx_print(philo, "is thinking");
		}
		usleep(100);
	}
	return (NULL);
}
