/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:52:43 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/04 18:49:57 by abenaiss         ###   ########.fr       */
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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct      s_rules
{
    long             philo_number;
    long             time_to_die;
    long             time_to_eat;
    long             time_to_sleep;
    long             number_of_times_eat;
}                   t_rules;

typedef struct      s_philosopher
{
    t_rules         game_rules;
    long            id;
    long            last_meal;
    long            dying_time;
    long            meal_number;
    pthread_t       tid;
}                   t_philosopher;



typedef struct      s_ochestrator
{
    t_rules         game_rules;
    t_philosopher   *philo_list;
    int             first_blood;
    long            execution_time;
    pthread_mutex_t *forks;
    pthread_mutex_t output_mutex;
    pthread_mutex_t death;
    int             full_counter;
}                   t_orchestrator;

t_orchestrator      *master;

long            ft_atoil(char* str);
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
void            init_orchestrator(char** args, int argc);
void            init_mutexs();