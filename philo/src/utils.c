/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:20:26 by jpiquet           #+#    #+#             */
/*   Updated: 2025/10/02 12:20:26 by jpiquet          ###   ########.fr       */
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

int	check_int_max(long long n, int sign, int *error)
{
	if ((n * sign) > INT_MAX)
	{
		*error = 1;
		return (exit_error("Stay under int max"));
	}
	if ((n * sign) < INT_MIN)
	{
		*error = 1;
		return (exit_error("It can't be a negative number"));
	}
	return (0);
}

int	my_atoi(const char *nptr, int *error)
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
		if (check_int_max(n, sign, error))
			return (-1);
		i++;
	}
	return ((int)n * sign);
}
