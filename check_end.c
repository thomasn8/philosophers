/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:34:39 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/20 16:49:50 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_table_infos *table, int n)
{
	int	i;

	i = 0;
	get_time_in_ms(table->time, table->time->prog_start);
	while (i < n)
	{
		if ((table->time->timestamp_in_ms - table->philos[i].last_meal)
			> table->args->time_to_die)
		{
			get_time_in_ms(table->time, table->time->prog_start);
			printf("%s%d %d died%s\n", RED, table->time->timestamp_in_ms,
				table->philos[i].id, DEFAULT);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_meals(t_table_infos *table, int n)
{
	int	i;

	i = 0;
	get_time_in_ms(table->time, table->time->prog_start);
	while (i < n)
	{
		if (table->philos[i].count_meals < table->args->meals_goal)
			break ;
		if (i == n - 1)
		{
			get_time_in_ms(table->time, table->time->prog_start);
			printf("%s%d MIAM! All philosophers had %d meals.%s\n", GREEN,
				table->time->timestamp_in_ms, table->args->meals_goal, DEFAULT);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_end_looper(t_table_infos *table, int n)
{
	int	check_delay;

	check_delay = 1000;
	while (1)
	{
		if (check_death(table, n))
			return (1);
		if (table->args->meals_goal > 0)
		{
			if (check_meals(table, n))
				return (2);
		}		
		usleep(check_delay);
	}
	return (0);
}
