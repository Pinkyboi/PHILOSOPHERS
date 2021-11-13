/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:51:45 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/13 00:37:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char** argv)
{
    env = (t_env *)malloc(sizeof(t_env));
    if (argc != 5 && argc != 6)
    {
        write(1, USAGE_MESSAGE, 105);
        exit(-1);
    }
    initialize_env(argc, argv);
    setting_dinner();
}