/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:52:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/05 17:46:19 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

typedef struct      s_rules
{
    int             philo_number;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_eat_us;
    int             time_to_sleep_us;
    int             number_of_times_eat;
}                   t_rules;

typedef struct      s_philosopher
{
    t_rules         game_rules;
    pthread_t       tid;
    int             id;
    int             last_meal;
    int             dying_time;
    int             meal_number;
}                   t_philosopher;



typedef struct      s_ochestrator
{
    t_rules         game_rules;
    t_philosopher   *philo_list;
    int             first_blood;
    int             full_counter;
    int             execution_time;
    pthread_mutex_t *forks;
    pthread_mutex_t output_mutex;
}                   t_orchestrator;

t_orchestrator      *master;

long            ft_atoi(char* str);
int             ft_strcmp(const char *s1, const char *s2);
long            get_milliseconds(unsigned int seconds, unsigned int microseconds);
int             get_current_time(void);
void            print_action_message(int philo_id, const char* message);
void            philo_sleep(t_philosopher *philo);
void            philo_eat(t_philosopher *philo);
void            philo_think(t_philosopher *philo);
int             forks_status(int id);
void*           callback(void *arg);
void            threads_master(t_orchestrator *orch);
void            init_philosophers(t_orchestrator *master);
void            init_master(char** args, int argc);
void            init_mutexs();
void            lock_forks(t_philosopher *philo);