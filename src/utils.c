/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:20:26 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/27 17:34:27 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	is_whitespace(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
	return (0);
}

int string_is_valid(char *str)
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

int	my_atoi(const char *nptr)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-' || nptr[i] == '[')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - 48);
		if ((n * sign) > INT_MAX)
			return (INT_MAX);
		if ((n * sign) < INT_MIN)
			return (INT_MIN);
		i++;
	}
	return ((int)n * sign);
}