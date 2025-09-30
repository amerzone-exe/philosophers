/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:10:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/30 13:27:36 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	string_is_valid(char *str);
void		check_args(int argc, char **argv);

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

static int	string_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		exit_error("It can't be an empty string");
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] && str[i] == '+')
			i++;
		if (str[i] && str[i] == '-')
			exit_error("You can't enter a negative number");
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
