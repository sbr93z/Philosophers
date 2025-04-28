/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:30:24 by sferrad           #+#    #+#             */
/*   Updated: 2025/02/26 17:09:54 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result * sign);
}

int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parsing(t_data data, int ac, char **av)
{
	int		i;
	long	val;

	if (ac >= 5 && ac <= 6)
	{
		i = 1;
		while (i < ac)
		{
			if (!is_digit_str(av[i]))
				return (0);
			val = ft_atoi(av[i]);
			if (val <= 0 || val > INT_MAX)
				return (0);
			i++;
		}
		if (data.number_of_philo > 200)
			return (0);
		return (1);
	}
	return (0);
}
