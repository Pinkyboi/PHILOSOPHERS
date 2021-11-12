/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:00:09 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/01 15:01:28 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t  is_white(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int     my_atoi(char* string)
{
    int     i;
    int     sign;
    long    nb;

    i = 0;
    while (is_white(string[i]))
        i++;
    sign = 1;
    if((string[i] == '-' || string[i] == '+')
        && (!(string[i] == '+' && i++) || (string[i] == '-' && i++)))
        sign = -1;
    nb = 0;
    while (string[i] >= '0' && string[i] <= '9')
    {
        nb = (nb * 10 + (string[i] - '0'));
        if(nb * 10 + (string[i] - '0') >= INT_MAX)
            return (sign == -1 ? INT_MIN : INT_MAX);
        i++;
    }
    return (nb * sign);
}