/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocelyn <jocelyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:22:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/01 14:29:33 by jocelyn          ###   ########.fr       */
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

int	exit_and_destroy(t_args *args, const char *str)
{
	destroy_fork(args->forks, args->nb_of_philo);
	destroy_args(args);
	printf("%s\n", str);
	return (1);
}
