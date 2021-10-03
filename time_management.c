/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:46:36 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/03 12:46:50 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_milliseconds(unsigned int seconds, unsigned int microseconds)
{
    return(seconds * 1000 + microseconds / 1000);
}

int     get_current_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (get_milliseconds(tv.tv_sec, tv.tv_usec));
}