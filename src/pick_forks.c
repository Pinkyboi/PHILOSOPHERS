/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:30:51 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/20 08:36:12 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short    wait_turn(t_philo *philo, t_fork* fork)
{
    while (!(*philo->terminate))
    {
        if (fork->users[curent_user] == -1 && philo->id != fork->users[past_user])
            return (1);
        usleep(10);
    }
    return (0);
}

static void     attribute_fork(t_philo *philo, t_fork* fork)
{
    fork->users[curent_user] = philo->id;
    fork->users[past_user] = philo->id;
    print_action_message(philo, "picked a fork");   
}

static short    is_fork_available(t_philo *philo, t_fork* fork)
{
    if(fork->users[curent_user] == -1 && philo->id != fork->users[past_user])
        return (1);
    return (0);
}    

static short    execute_philo(t_philo *philo)
{
    while (!(*philo->terminate))
        usleep(10);
    return (0);
}

int             get_fork(t_philo *philo, t_fork* smaller_fork, t_fork* bigger_fork)
{
    pthread_mutex_lock(&smaller_fork->fork_lock);
    if (pthread_mutex_lock(&bigger_fork->fork_lock))
        return (execute_philo(philo));
    if (is_fork_available(philo, smaller_fork)
            && is_fork_available(philo, bigger_fork))
    {
        attribute_fork(philo, bigger_fork);
        attribute_fork(philo, smaller_fork);
        pthread_mutex_unlock(&bigger_fork->fork_lock);
        pthread_mutex_unlock(&smaller_fork->fork_lock);
        return (1);
    }
    pthread_mutex_unlock(&bigger_fork->fork_lock);
    pthread_mutex_unlock(&smaller_fork->fork_lock);
    if (wait_turn(philo, smaller_fork) && wait_turn(philo, bigger_fork))
        return (get_fork(philo, smaller_fork, bigger_fork));
    return (0);
}
