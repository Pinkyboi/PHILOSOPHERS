/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:03:06 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 00:35:56 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int min(int number1, int number2)
{
    if (number1 < number2)
        return (number1);
    return (number2);
}

static int max(int number1, int number2)
{
    if (number1 > number2)
        return (number1);
    return (number2);
}

int     get_smaller_fork(int philo_id)
{
    return min(philo_id, (philo_id + 1) % env->params[philo_number]);
}

int     get_bigger_fork(int philo_id)
{
    return max(philo_id, (philo_id + 1) % env->params[philo_number]);
}