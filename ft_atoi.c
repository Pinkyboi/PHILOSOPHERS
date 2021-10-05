/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:05:37 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/05 17:30:55 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INT_MAX +2147483647
#define INT_MIN -2147483648

int    ft_atoi(char* str)
{
    int    base = 0;
    int    sign = 1;

    while (*str == ' ')
        str++;

    if (*str == '+' || *str == '-')
    {
        sign = 1 - 2 * (*str == '-');
        str++;
    }

    while (*str >= '0' && *str <= '9')
    {
        if (base > INT_MAX / 10 || (base == INT_MAX / 10 && ((*str - '0') > 7)))
        {
            if (sign == -1)
                return INT_MIN;
            return INT_MAX;
        }
        base = base * 10 + (*str - '0');
        str++;
    }
    return base * sign;
}