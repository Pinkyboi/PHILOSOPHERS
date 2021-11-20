/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:58:39 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/20 08:40:09 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_action_message(t_philo *philo, const char* message)
{
    long    event_time;

    pthread_mutex_lock(philo->print_mutex);
    event_time = get_current_time() - (*philo->start_time);
    if (!(*philo->terminate))
        printf("[%ld ms] philosopher id: %d %s\n", event_time, philo->id + 1, message);
    pthread_mutex_unlock(philo->print_mutex);
}
