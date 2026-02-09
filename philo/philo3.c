/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:40:20 by eates             #+#    #+#             */
/*   Updated: 2023/09/07 21:40:34 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life(t_philo *philo, int id, int fork_id1, int fork_id2)
{
	printf("\033[0;36m[%llu] \033[0;32m%d id philo is eating\n",
		current() - philo->table->starting_time_of_process, id);
	passing_time(philo->table->time_to_eat);
	philo->num_of_eat++;
	pthread_mutex_lock(&philo->table->starting_time);
	philo->starting_time = current();
	pthread_mutex_unlock(&philo->table->starting_time);
	pthread_mutex_unlock(&philo->table->forks[fork_id1].fork);
	pthread_mutex_unlock(&philo->table->forks[fork_id2].fork);
	if (check_die(philo->table))
		return (1);
	printf("\033[0;36m[%llu] \033[0;32m%d id philo is sleeping\n",
		philo->starting_time - philo->table->starting_time_of_process, id);
	passing_time(philo->table->time_to_sleep);
	if (check_die(philo->table))
		return (1);
	printf("\033[0;36m[%llu] \033[0;32m%d id philo is thinking\n",
		current() - philo->table->starting_time_of_process, id);
	return (0);
}

void	*t_func(void *tmp)
{
	t_philo		*philo;
	int			id;
	int			fork_id1;
	int			fork_id2;

	philo = (t_philo *)tmp;
	id = philo->id;
	fork_id1 = id - 1;
	fork_id2 = id * !(id == philo->table->number_of_philosophers);
	while (1)
	{
		if (philo->num_of_eat
			== philo->table->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philo->table->finish_optional);
			philo->table->optional_finish++;
			return (pthread_mutex_unlock(&philo->table->finish_optional), NULL);
		}
		waiting(philo, id, fork_id1, fork_id2);
		if (fork_operation(philo, id, fork_id1, fork_id2))
			return (NULL);
		if (life(philo, id, fork_id1, fork_id2))
			return (NULL);
	}
}

void	*die(t_table *table, int id)
{
	pthread_mutex_lock(&table->die);
	table->has_die = 1;
	table->id_of_philo_which_died = id;
	pthread_mutex_unlock(&table->die);
	return (pthread_mutex_unlock(&table->starting_time), NULL);
}

void	*die_control(void *tmp)
{
	t_table	*table;
	int		i;

	table = (t_table *)tmp;
	while (1)
	{
		pthread_mutex_lock(&table->finish_optional);
		if (table->optional_finish == table->number_of_philosophers)
			return (NULL);
		pthread_mutex_unlock(&table->finish_optional);
		i = -1;
		while (++i < table->number_of_philosophers)
		{
			pthread_mutex_lock(&table->starting_time);
			if (current() - table->philos[i]->starting_time
				> table->time_to_die)
				return (die(table, i + 1));
			pthread_mutex_unlock(&table->starting_time);
		}
		passing_time(1);
	}
}

void	philo(t_table *t)
{
	int	i;

	pthread_mutex_init(&t->thinking, NULL);
	pthread_mutex_init(&t->die, NULL);
	pthread_mutex_init(&t->starting_time, NULL);
	pthread_mutex_init(&t->finish_optional, NULL);
	i = -1;
	t->starting_time_of_process = current();
	while (++i < t->number_of_philosophers)
	{
		t->philos[i]->starting_time = t->starting_time_of_process;
		pthread_create(&(t->philos[i]->t), NULL, t_func, t->philos[i]);
	}
	pthread_create(&(t->control_die), NULL, die_control, t);
	i = -1;
	while (++i < t->number_of_philosophers)
		pthread_join(t->philos[i]->t, NULL);
	pthread_join(t->control_die, NULL);
}
