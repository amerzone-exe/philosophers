/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/02 15:37:01 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_error(const char *str)
{
	printf("%s\n", str);
	return (1);
}

void	*exit_null(const char *str)
{
	printf("%s\n", str);
	return (NULL);
}

void	*exit_and_destroy(t_args *args, const char *str)
{
	destroy_fork(args->forks, args->nb_of_philo);
	destroy_args(args);
	printf("%s\n", str);
	return (NULL);
}
