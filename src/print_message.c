/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:58:39 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 00:29:05 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_action_message(int philo_id, const char* message)
{
    long    event_time;

    pthread_mutex_lock(&env->print_mutex);
    event_time = get_current_time() - env->start_time;
    if (!env->terminate)
        printf("[%ld ms] philosopher id: %d %s\n", event_time, philo_id + 1, message);
    if (!env->terminate)
        pthread_mutex_unlock(&env->print_mutex);
}
