/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:57:18 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/20 09:41:05 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_eat(t_philo* philo)
{
    t_fork* smaller_fork;
    t_fork* bigger_fork;
    int     fork_number;

    fork_number = philo->params[philo_number];
    smaller_fork = &philo->fork_list[get_smaller_fork(philo->id, fork_number)];
    bigger_fork = &philo->fork_list[get_bigger_fork(philo->id, fork_number)];
    if (get_fork(philo, smaller_fork, bigger_fork))
    {
        philo->last_meal = get_current_time();
        print_action_message(philo, GREEN_TEXT"is eating"COLOR_ESC);
        msleep(philo->terminate, philo->params[time_to_eat]);
        if (++philo->eat_count == philo->params[max_eat_count])
            philo->philo_full++;
        clean_fork(philo, smaller_fork, bigger_fork);
    }
}

void    philo_sleep(t_philo* philo)
{
    print_action_message(philo, GREEN_TEXT"is sleeping"COLOR_ESC);
    msleep(philo->terminate, philo->params[time_to_sleep]);
}

void    philo_think(t_philo* philo)
{
    print_action_message(philo, GREEN_TEXT"is thinking"COLOR_ESC);
}
