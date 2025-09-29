/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:10:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/28 13:19:50 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int string_is_valid(char *str);
void	check_args(int argc, char **argv);

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

static int string_is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		if (str[i] == '-')
			exit_error("You cannot enter a negative number");
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}