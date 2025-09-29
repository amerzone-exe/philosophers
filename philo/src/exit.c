/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/29 12:01:20 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(const char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}

void	exit_and_destroy(t_args *args, const char *str)
{
	printf("args->nb_of_philo = %d\n", args->nb_of_philo);
	destroy_fork(args->forks, args->nb_of_philo);
	destroy_args(args);
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}
