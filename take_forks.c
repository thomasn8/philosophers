/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:21:21 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/09 10:18:18 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_meal_check(unsigned int *last_meal, t_time *timer,
	unsigned int time_to_die, unsigned int prog_start)
{
	get_time_in_ms(timer, prog_start);
	if ((timer->timestamp_in_ms - *last_meal) > time_to_die)
		return (0);
	return (1);
}

static void	take_2_forks(
	int index, t_table_infos *table, t_fork *fork_1, t_fork *fork_2)
{
	int	id;

	id = table->philos[index].id;
	pthread_mutex_lock(&table->mutex2);
	if (fork_2->state == FREE)
	{
		fork_2->state = id;
		pthread_mutex_unlock(&table->mutex2);
		fork_1->state = id;
		pthread_mutex_unlock(&table->mutex);
		table->philos[index].fork_in_hands += 2;
		get_time_in_ms(table->philos[index].timer, table->time->prog_start);
		if (last_meal_check(&table->philos[index].last_meal,
				table->philos[index].timer, table->args->time_to_die,
				table->time->prog_start))
		{
			printf("%d %s%d has taken a fork%s\n",
				table->philos[index].timer->timestamp_in_ms,
				YELLOW, id, DEFAULT);
			printf("%d %s%d has taken a fork%s\n",
				table->philos[index].timer->timestamp_in_ms,
				YELLOW, id, DEFAULT);
		}
	}
}

static void	state_change(t_philo *philo, t_time *timer, unsigned int prog_start)
{
	philo->count_meals++;
	get_time_in_ms(timer, prog_start);
	philo->last_meal = timer->timestamp_in_ms;
	printf("%d %s%d is eating%s\n",
		timer->timestamp_in_ms, CYAN, philo->id, DEFAULT);
}

void	take_forks_and_start_eating(int index, t_table_infos *table, int n)
{
	int	id;
	int	n2;

	id = table->philos[index].id;
	n2 = n;
	pthread_mutex_lock(&table->mutex);
	if (table->forks[index].state == FREE)
	{
		if (id != n2)
			take_2_forks(index, table, &table->forks[index],
				&table->forks[index + 1]);
		else
			take_2_forks(index, table, &table->forks[index],
				&table->forks[0]);
	}
	if (table->philos[index].fork_in_hands == 2
		&& last_meal_check(&table->philos[index].last_meal,
			table->philos[index].timer, table->args->time_to_die,
			table->time->prog_start))
		state_change(&table->philos[index],
			table->philos[index].timer, table->time->prog_start);
}
