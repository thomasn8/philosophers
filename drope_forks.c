/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drope_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:41:08 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/08 22:47:40 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	drope_1_fork(int index, t_table_infos *table, t_fork *fork)
{
	int	id;

	id = table->philos[index].id;
	if (fork->state == id)
	{
		fork->state = FREE;
		table->philos[index].fork_in_hands--;
	}
}

void	drope_forks_and_sleep(int index, t_table_infos *table, int n)
{
	int	id;

	id = table->philos[index].id;
	drope_1_fork(index, table, &table->forks[index]);
	if (id != n)
		drope_1_fork(index, table, &table->forks[index + 1]);
	else
		drope_1_fork(index, table, &table->forks[0]);
	if (table->philos[index].fork_in_hands == 0)
	{
		get_time_in_ms(table->philos[index].timer, table->time->prog_start);
		printf("%d %s%d is sleeping%s\n",
			table->philos[index].timer->timestamp_in_ms, BLUE, id, DEFAULT);
	}
}
