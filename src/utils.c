/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:20:26 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/29 15:10:20 by jpiquet          ###   ########.fr       */
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

static int	is_sep(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*scpy;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_sep(s1[start], set))
		start++;
	while (end >= start && is_sep(s1[end], set))
		end--;
	scpy = malloc(sizeof(char) * (end - start + 2));
	if (scpy == 0)
		return (NULL);
	i = 0;
	while (start <= end)
		scpy[i++] = s1[start++];
	scpy[i] = '\0';
	return (scpy);
}

void	exit_error(const char *str)
{
	// printf("%s\n", str);
	perror(str);
	exit (1);
}

int	is_whitespace(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	is_bracket(int c)
{
	if (c == '[' || c == ']')
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
