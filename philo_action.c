/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:57:18 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/12 20:15:41 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_fork(t_philo *philo, t_fork *smaller_fork, t_fork *bigger_fork)
{
    bigger_fork->users[curent_user] = -1;
    bigger_fork->users[past_user] = philo->id;
    print_action_message(philo->id, "dropped a fork");
    smaller_fork->users[curent_user] = -1;
    smaller_fork->users[past_user] = philo->id;
    print_action_message(philo->id, "dropped a fork");
}

short    wait_turn(t_philo *philo, t_fork* fork)
{
    while(!env->terminate)
    {
        if(fork->users[curent_user] == -1 && philo->id != fork->users[past_user])
            return (1);
        usleep(10);
    }
    return (0);
}

short     wait_for_fork(t_philo *philo, t_fork* fork)
{
    pthread_mutex_lock(&fork->fork_lock);
    if(fork->users[curent_user] == -1 && philo->id != fork->users[past_user])
    {
        pthread_mutex_unlock(&fork->fork_lock);
        fork->users[curent_user] = philo->id;
        fork->users[past_user] = philo->id;
        print_action_message(philo->id, "picked a fork");
        return (1);
    }
    pthread_mutex_unlock(&fork->fork_lock);
    if (wait_turn(philo, fork))
        return(wait_for_fork(philo, fork));
    return (0);
}    

int    get_fork(t_philo *philo, t_fork* smaller_fork, t_fork* bigger_fork)
{

    if(!wait_for_fork(philo, smaller_fork))
        return (0);
    if(!wait_for_fork(philo, bigger_fork))
        return (0);
    return (1);
}

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
        philo->eat_count++;
        ft_msleep(env->params[time_to_eat]);
        clean_fork(philo, smaller_fork, bigger_fork);
    }
}

void    philo_sleep(t_philo* philo)
{
    print_action_message(philo->id, "is sleeping");
    ft_msleep(env->params[time_to_sleep]);
}

void    philo_think(t_philo* philo)
{
    print_action_message(philo->id, "is thinking");
}
