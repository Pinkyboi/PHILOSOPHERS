/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:54:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/05 18:38:44 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_action_message(int philo_id, const char* message)
{
    int    event_time;

    event_time = get_current_time() - master->execution_time;
    pthread_mutex_lock(&master->output_mutex);
    if(!master->first_blood)
    {
        printf("%d philosopher id: %d\t%s\n", event_time, philo_id + 1, message);
        if(!ft_strcmp(message, "died"))
            master->first_blood = 1;
    }
    pthread_mutex_unlock(&master->output_mutex);
}

void    philo_eat(t_philosopher* philo)
{
    lock_forks(philo);
    if (get_current_time() >= philo->dying_time)
        print_action_message(philo->id, "died");
}

void    philo_sleep(t_philosopher *philo)
{
    print_action_message(philo->id, "is sleeping");
    usleep(philo->game_rules.time_to_sleep_us);
    if (get_current_time() >= philo->dying_time)
        print_action_message(philo->id, "died");
}

void    philo_think(t_philosopher *philo)
{
    print_action_message(philo->id, "is thinking");
    if (get_current_time() >= philo->dying_time)
        print_action_message(philo->id, "died");
}
























































































// void    philo_eat(t_philosopher *philo)
// {
//     int id;

//     id = philo->id;
//     if (get_current_time() + philo->game_rules.time_to_eat > philo->dying_time)
//     {
//         pthread_mutex_lock(&g_mutex);
//         master->first_blood = philo->id;
//         pthread_mutex_unlock(&g_mutex);
//     }
//     pthread_mutex_lock(&g_mutex[id]);
//     pthread_mutex_lock(&g_mutex[id+1]);

//     print_action_message(id, "is eating");
//     usleep(philo->game_rules.time_to_eat);
//     philo->dying_time += philo->game_rules.time_to_die;

//     // master->forks[id] = 0;
//     // master->forks[(id + 1) % master->game_rules.philo_number] = 0;
//     pthread_mutex_unlock(&g_mutex[id]);
//     pthread_mutex_unlock(&g_mutex[id+1]);

    
// }
