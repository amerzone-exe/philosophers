/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 13:56:18 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t get_real_time(void)
{
	struct timeval time;
	size_t res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

#define print_debug(var, nb) printf(#var " = %" #nb "\n", var);
/*checker si le temps qu'il y a eu avec le dernier repas est plus elever que le time to die*/
int check_dead(t_philo *ptr_philo)
{
	size_t actual_time;
	size_t time_since_meal;
	size_t philo_last_meal;

	actual_time = get_real_time();
	pthread_mutex_lock(&ptr_philo->meal_mutex);
	philo_last_meal = ptr_philo->last_meal;
	pthread_mutex_unlock(&ptr_philo->meal_mutex);
	time_since_meal = actual_time - philo_last_meal;
	// printf("philo id = %d | time since meal %zu, last meal %zu, actual time %zu\n", ptr_philo->philo_id, time_since_meal, ptr_philo->last_meal, actual_time);
	// printf("philo id = %d | actual_time %zu\n", ptr_philo->philo_id, actual_time);
	// printf("philo id = %d | time since meal %zu\n", ptr_philo->philo_id, time_since_meal);
	// print_debug(ptr_philo->philo_id, d);
	// print_debug(actual_time, zu);
	// print_debug(ptr_philo->last_meal, zu);
	// print_debug(time_since_meal, zu);
	if (time_since_meal > ptr_philo->args->time_to_die)
		return (true);
	return (false);
}

// geter

// int		check(t_fork *fork)

// int		get_mutex_data()
// {

// }

// seter

/*faire des philo radins*/

// int	take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
// {
// 	pthread_mutex_lock(&right_fork->fork_mutex);
// 	if (right_fork->is_taken == 0)
// 	{
// 		right_fork->is_taken = 1;
// 		pthread_mutex_lock(&left_fork->fork_mutex);
// 		if (left_fork->is_taken == 0)
// 		{
// 			left_fork->is_taken = 1;
// 			mtx_print(philo, "has taken a fork");
// 			mtx_print(philo, "has taken a fork");
// 			pthread_mutex_unlock(&right_fork->fork_mutex);
// 			pthread_mutex_unlock(&left_fork->fork_mutex);
// 			return (1);
// 		}
// 		right_fork->is_taken = 0;
// 		pthread_mutex_unlock(&right_fork->fork_mutex);
// 		pthread_mutex_unlock(&left_fork->fork_mutex);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&right_fork->fork_mutex);
// 	return (0);
// }

bool compare_and_swap(t_shared_data data)
{
	bool succeed;

	succeed = false;
	/* lock data.mtx */
	/* if get data.value = dispo */
	/* 		set data.value = indispo*/
	/* 		succeed = true */
	/* unlock data.mtx */
	// return (succeed);
}

int take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	bool has_left = false;
	bool has_right = false;

	while (!is_done(philo))
	{
		/* ===> si !has_left, has_left = take left (compare and swap) */
			// si has_left => print taken fork
		/* ===> si !has_right, has_right = take right (compare and swap) */
			// si has_right => print taken fork
		/* ===> si has_left et has_right */
		/* return */
		/*	else
				usleep(xxx);
		*/
	}
}

// void	my_usleep(size_t time)
// {
// 	size_t start_time;

// 	start_time = get_real_time();
// 	while (get_real_time() - start_time < time)
// 	{
// 		usleep(500);
// 	}
// }

void drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->is_taken = 0;
	mtx_print(philo, "has drop a fork");
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	philo->right_fork->is_taken = 0;
	mtx_print(philo, "has drop a fork");
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

int update_meals(t_philo *philo)
{
	philo->nb_of_eat++;
	if (philo->nb_of_eat == philo->args->eat_max)
	{
		pthread_mutex_lock(&philo->full_mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->full_mutex);
		return (0);
	}
	return (1);
}

int philo_eating(t_philo *philo)
{
	mtx_print(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_real_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	update_meals(philo);
	usleep(philo->args->time_to_eat * 1000);
	// my_usleep(philo->args->time_to_eat);
	drop_forks(philo);
	return (1);
}

int is_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->done_mutex);
	if (philo->args->end_sim == true)
	{
		pthread_mutex_unlock(&philo->args->done_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->done_mutex);
	return (0);
}

void *routine(void *args)
{
	t_philo *philo;
	t_fork *right_fork;
	t_fork *left_fork;

	philo = (t_philo *)args;
	right_fork = philo->right_fork;
	left_fork = philo->left_fork;
	pthread_mutex_lock(&philo->args->mutex_start);
	pthread_mutex_unlock(&philo->args->mutex_start);
	mtx_print(philo, "is thinking");
	if (philo->philo_id % 2 == 0)
	{
		usleep(philo->args->time_to_eat * 1000);
		// my_usleep(100);
	}
	while (!is_done(philo))
	{
		// if (is_done(philo))
		// 	break ;
		// if (take_forks(philo, right_fork, left_fork))
		// {
		// take_forks(philo, right_fork, left_fork);
		philo_eating(philo);
		mtx_print(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		// my_usleep(philo->args->time_to_sleep);
		mtx_print(philo, "is thinking");
		// }
		// else
		// 	usleep(500);
	}
	return (NULL);
}
