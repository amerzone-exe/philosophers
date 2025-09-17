/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:10:53 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/17 09:58:59 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_last_args(char *argv)
{
	int i;

	i = 0;
	while (is_whitespace(argv[i]) && argv[i])
		i++;
	if (!is_bracket (argv[i]) || !argv[i])
		exit_error("Last argument isn't valid");
	i++;
	if (argv[i] == '+')
		i++;
	if (argv[i] == '-')
		exit_error("You can't use a negative number");
	if (!ft_isdigit(argv[i]) || !argv[i])
		exit_error("Only numbers are valid");
	while(ft_isdigit(argv[i]) && argv[i])
		i++;
	if (!is_bracket (argv[i]) || !argv[i])
		exit_error("Last argument isn't valid");
	i++;
	while (is_whitespace(argv[i]) && argv[i])
		i++;
	if (argv[i] != '\0')
		exit_error("Last argument isn't valid");
}

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
		// check_last_args(argv[argc - 1]);
	}
}
