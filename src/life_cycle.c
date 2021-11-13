/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:00:14 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 02:34:41 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void*    watcher_life_cycle(void* arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!env->terminate)
    {
        if (get_current_time() - philo->last_meal > env->params[time_to_die])
        {
            print_action_message(philo->id, "died");
            env->terminate = true;
        }
        if (env->philo_full >= env->params[philo_number])
        {
            pthread_mutex_lock(&env->print_mutex);
            env->terminate = true;
        }
    }
    return (NULL);   
}

static void*   philo_life_cycle(void* arg)
{
    t_philo         *philo;
    int             action_index;
    t_philo_action  *g_philo_action[ACTION_NUMBER] = {
        &philo_eat,
        &philo_sleep,
        &philo_think
    };

    action_index = 0;
    philo = (t_philo*)arg;
    while (!env->terminate)
    {
        g_philo_action[action_index](philo);
        action_index++;
        action_index %= ACTION_NUMBER; 
    }
    return (NULL);
}

static void    clear_env(void)
{
    int i;

    i = -1;
    while(++i < env->params[philo_number])
        pthread_mutex_destroy(&env->fork_list[i].fork_lock);
    pthread_mutex_destroy(&env->print_mutex);
    free(env->fork_list);
    free(env->philo_list);
}

void    setting_dinner(void)
{
    int i;
    int failed_philo;
    int failed_watcher;

    env->start_time = get_current_time();
    i = -1;
    while (++i < env->params[philo_number])
    {
        env->philo_list[i].last_meal = get_current_time();
        failed_watcher = pthread_create(&env->philo_list[i].w_tid, NULL,
			watcher_life_cycle, (void *)&env->philo_list[i]);
        failed_philo = pthread_create(&env->philo_list[i].p_tid, NULL,
			philo_life_cycle, (void *)&env->philo_list[i]);
        if (failed_watcher || failed_philo)
            return ;
    }
    while (i--)
    {
        pthread_join(env->philo_list[i].w_tid, NULL);
        pthread_join(env->philo_list[i].p_tid, NULL);
    }
    clear_env();
}