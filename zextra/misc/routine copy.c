/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:47:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 16:47:34 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// #define print_debug(var, nb) printf(#var " = %" #nb "\n", var);

size_t get_real_time(void)
{
	struct timeval time;
	size_t res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

// /*checker si le temps qu'il y a eu avec le dernier repas est plus elever que le time to die*/

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
	if (time_since_meal > ptr_philo->args->time_to_die)
		return (true);
	return (false);
}

bool fork_available(t_fork *fork)
{
	bool	available;

	available = false;
	pthread_mutex_lock(&fork->fork_mutex);
	if (fork->is_taken == 0)
		available = true;
	pthread_mutex_unlock(&fork->fork_mutex);
	return (available);
}

bool	get_fork(t_fork	*fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->is_taken = 1;
	pthread_mutex_unlock(&fork->fork_mutex);
	return (true);
}

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

// bool compare_and_swap(t_shared_data data)
// {
// 	bool succeed;

// 	succeed = false;
// 	/* lock data.mtx */
// 	/* if get data.value = dispo */
// 	/* 		set data.value = indispo*/
// 	/* 		succeed = true */
// 	/* unlock data.mtx */
// 	// return (succeed);
// }

void take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	bool has_left = false;
	bool has_right = false;

	while (!is_done(philo))
	{
		if (!has_right && fork_available(right_fork))
		{
			has_right = get_fork(right_fork);
			mtx_print(philo, "has taken a fork");
		}
		if (!has_left && fork_available(left_fork))
		{
			has_left = get_fork(left_fork);
			mtx_print(philo, "has taken a fork");
		}
		if (has_right && has_left)
			return ;
		else
			usleep(500);
	}
}

bool	my_usleep(size_t time, t_philo *philo)
{
	size_t start_time;
	bool	sim_is_done;

	sim_is_done = false;
	start_time = get_real_time();
	while (get_real_time() - start_time < time)
	{
		if (is_done(philo) == true)
		{
			sim_is_done = true;
			break ;
		}
		usleep(500);
	}
	return (sim_is_done);
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
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

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_real_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

bool philo_eating(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	mtx_print(philo, "is eating");
	update_last_meal(philo);
	update_meals(philo);
	sim_is_done = my_usleep(philo->args->time_to_eat, philo);
	drop_forks(philo);
	return (sim_is_done);
}

bool	is_done(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	pthread_mutex_lock(&philo->args->done_mutex);
	if (philo->args->end_sim == true)
		sim_is_done = true;
	pthread_mutex_unlock(&philo->args->done_mutex);
	return (sim_is_done);
}

bool	philo_sleeping(t_philo *philo)
{
	bool	sim_is_done;

	sim_is_done = false;
	mtx_print(philo, "is sleeping");
	sim_is_done = my_usleep(philo->args->time_to_sleep, philo);
	return (sim_is_done);
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
		my_usleep(philo->args->time_to_eat, philo);
	while (is_done(philo) == false)
	{
		take_forks(philo, right_fork, left_fork);
		if (philo_eating(philo))
			return (NULL);
		if (philo_sleeping(philo))
			return (NULL);
		mtx_print(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
