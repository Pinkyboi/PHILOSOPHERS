/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:05:37 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/03 12:47:31 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int is_white_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v');
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

long ft_atoil(char* str)
{
    int i;
    long number;
    int sign;

    i = 0;
    number = 0;
    sign = 1;
    while(is_white_space(str[i]))
        i++;
    if(str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while(str[i] && is_digit(str[i]))
    {
        number = (number * 10) + (str[i] - '0');
        i++;
    }
    return (sign * number);
}