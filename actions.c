/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:54:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/04 18:50:54 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_action_message(int philo_id, const char* message)
{
    long    event_time;

    event_time = get_current_time() - master->execution_time;
    pthread_mutex_lock(&master->output_mutex);
    printf("%ld philosopher id: %d\t%s\n", event_time, philo_id + 1, message);
    if(!strcmp(message, "died"))
        exit(0);
    pthread_mutex_unlock(&master->output_mutex);
}

void    philo_sleep(t_philosopher *philo)
{
    if (get_current_time() + philo->game_rules.time_to_sleep > philo->dying_time)
        print_action_message(philo->id, "died");
    print_action_message(philo->id, "is sleeping");
    usleep(philo->game_rules.time_to_sleep * 1000);
}

int     get_smaller_fork(int philo_id)
{
    return MIN(philo_id , (philo_id + 1) % master->game_rules.philo_number);
}

int     get_bigger_fork(int philo_id)
{
    return MAX(philo_id , (philo_id + 1) % master->game_rules.philo_number);
}

void     lock_forks(t_philosopher *philo)
{
    pthread_mutex_lock(&master->forks[get_smaller_fork(philo->id)]);
    if (!pthread_mutex_lock(&master->forks[get_bigger_fork(philo->id)]))
    {
        print_action_message(philo->id, "is eating");
        usleep(philo->game_rules.time_to_eat * 1000);
        philo->dying_time += philo->game_rules.time_to_die;
        philo->meal_number += 1;
        if (philo->meal_number == master->game_rules.number_of_times_eat)
            master->full_counter += 1;
        pthread_mutex_unlock(&master->forks[get_bigger_fork(philo->id)]);
    }
    pthread_mutex_unlock(&master->forks[get_smaller_fork(philo->id)]);
}

void    philo_eat(t_philosopher* philo)
{
    int     id;

    id = philo->id;
    if (get_current_time() + philo->game_rules.time_to_eat > philo->dying_time)
        print_action_message(philo->id, "died");
    lock_forks(philo);
}
void    philo_think(t_philosopher *philo)
{
    if (get_current_time() > philo->dying_time)
        print_action_message(philo->id, "died");
    print_action_message(philo->id, "is thinking");
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
