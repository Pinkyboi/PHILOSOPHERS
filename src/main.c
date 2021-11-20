/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:51:45 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/20 09:25:53 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void error_handler(short error_code)
{
    if (!error_code)
        return ;
    printf("\033[0;31m");
    printf("Error : ");
    printf("\033[0m");
    if (error_code == ERR_WRONG_PARAM_NUMBER)
        printf("%s\n", "Usage: ./philo [philosopher's number]"
            "[time to die] [time to eat] [time to sleep]"
            "[max number of meals]\n");
    if (error_code == ERR_MALLOC)
        printf("%s\n", "Internal error, please try again.");
    if (error_code == ERR_NEGATIVE)
        printf("%s\n", "No passed parameter should be negative.");
    if (error_code == ERR_ZERO)
        printf("%s\n", "No passed parameter should be null.");
    exit(-1);
}

int main(int argc, char** argv)
{
    t_env *env;

    if (argc != 5 && argc != 6)
        error_handler(ERR_WRONG_PARAM_NUMBER);
    env = (t_env *)malloc(sizeof(t_env));
    if (!env)
        error_handler(ERR_MALLOC);
    error_handler(initialize_env(env, argc, argv));
    setting_dinner(env);
}