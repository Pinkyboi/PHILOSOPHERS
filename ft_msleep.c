/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:02:57 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/12 20:03:50 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_msleep(unsigned int delay_second)
{
    long    start_time;

    start_time = get_current_time();
    while (get_current_time() <= start_time + delay_second)
    {
        if (env->terminate)
            return ;
        usleep(10);
    }
}