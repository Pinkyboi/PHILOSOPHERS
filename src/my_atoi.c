/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:00:09 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/23 17:58:10 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define INT_MAX +2147483647
#define INT_MIN -2147483648

static size_t	is_white(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static double	clip_min_max(double min, double max, double value)
{
	if (value >= max)
		return (max);
	if (value <= min)
		return (min);
	return (value);
}

int	my_atoi(char *string)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	while (is_white(string[i]))
		i++;
	sign = 1;
	if (string[i] == '-')
		sign = -1;
	if (string[i] == '-' || string[i] == '+')
		i++;
	nb = 0;
	i--;
	while (nb <= INT_MAX && string[++i] >= '0' && string[i] <= '9')
		nb = (nb * 10 + (string[i] - '0'));
	return (clip_min_max(INT_MIN, INT_MAX, nb * sign));
}
