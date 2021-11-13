/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:58:36 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 01:38:31 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long    get_milliseconds(unsigned int seconds, unsigned int microseconds)
{
    return (seconds * 1000 + microseconds / 1000);
}

long     get_current_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (get_milliseconds(tv.tv_sec, tv.tv_usec));
}
