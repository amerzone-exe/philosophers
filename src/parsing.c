/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:10:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 17:35:00 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_args(int argc, char **argv)
{
	int	j;

	j = 1;
	if (argc == 5)
	{
		while (j < argc)
		{
			if (!string_is_valid(argv[j]))
				exit_error("Only numbers are valid");
			j++;
		}
	}
	j = 1;
	if (argc == 6)
	{
		while (j < argc)
		{
			if (!string_is_valid(argv[j]))
				exit_error("Only numbers are valid");
			j++;
		}
	}
}
