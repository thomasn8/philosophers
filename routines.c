/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:43:41 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/08 22:53:48 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think_while_fork_is_busy(int index, t_table_infos *table, int n)
{
	if (table->philos[index].id != n)
	{
		while (table->forks[index].state != FREE
			|| table->forks[index + 1].state != FREE)
			return (1);
		return (0);
	}
	else
	{
		while (table->forks[index].state != FREE
			|| table->forks[0].state != FREE)
			return (1);
		return (0);
	}
	return (-1);
}

void	routine_all(int index, t_table_infos *table, int n)
{
	while (think_while_fork_is_busy(index, table, n) == 1)
		usleep(100);
	take_forks_and_start_eating(index, table, n);
	usleep(table->args->time_to_eat * 1000);
	drope_forks_and_sleep(index, table, n);
	usleep(table->args->time_to_sleep * 1000);
	get_time_in_ms(table->philos[index].timer, table->time->prog_start);
	if (last_meal_check(&table->philos[index].last_meal,
			table->philos[index].timer, table->args->time_to_die,
			table->time->prog_start))
		printf("%d %s%d is thinking%s\n",
			table->philos[index].timer->timestamp_in_ms, MAGENTA,
			table->philos[index].id, DEFAULT);
}
