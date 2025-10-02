/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:10:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/02 11:29:56 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	string_is_valid(char *str);
int			check_args(int argc, char **argv);

int	check_args(int argc, char **argv)
{
	int	j;

	j = 1;
	if (argc == 5)
	{
		while (j < argc)
		{
			if (string_is_valid(argv[j]))
				return (1);
			j++;
		}
	}
	j = 1;
	if (argc == 6)
	{
		while (j < argc)
		{
			if (string_is_valid(argv[j]))
				return (1);
			j++;
		}
	}
	return (0);
}

static int	string_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (exit_error("It can't be an empty string"));
	while (str[i])
	{
		if (str[i] && str[i] == '+')
			i++;
		if (str[i] && str[i] == '-')
			return (exit_error("You can't enter a negative number"));
		if (!ft_isdigit(str[i]))
			return (exit_error("Only numbers are valid"));
		i++;
	}
	return (0);
}
