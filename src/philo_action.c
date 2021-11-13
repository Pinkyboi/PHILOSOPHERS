/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:57:18 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 01:27:59 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_eat(t_philo* philo)
{
    t_fork* smaller_fork;
    t_fork* bigger_fork;

    smaller_fork = &env->fork_list[get_smaller_fork(philo->id)];
    bigger_fork = &env->fork_list[get_bigger_fork(philo->id)];
    if (get_fork(philo, smaller_fork, bigger_fork))
    {
        philo->last_meal = get_current_time();
        print_action_message(philo->id, "is eating");
        msleep(env->params[time_to_eat]);
        if (++philo->eat_count == env->params[max_eat_count])
            env->philo_full++;
        clean_fork(philo, smaller_fork, bigger_fork);
    }
}

void    philo_sleep(t_philo* philo)
{
    print_action_message(philo->id, "is sleeping");
    msleep(env->params[time_to_sleep]);
}

void    philo_think(t_philo* philo)
{
    print_action_message(philo->id, "is thinking");
}
