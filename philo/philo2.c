/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:34:04 by eates             #+#    #+#             */
/*   Updated: 2023/09/07 21:34:31 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

u_int64_t	current(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Gettimeofday malfunctioned!!\n"), 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	passing_time(u_int64_t msec)
{
	u_int64_t	starting_time;

	starting_time = current();
	while (current() - starting_time < msec)
		usleep(100);
}

int	check_die(t_table *table)
{
	pthread_mutex_lock(&table->die);
	if (table->has_die)
		return (pthread_mutex_unlock(&table->die), 1);
	pthread_mutex_unlock(&table->die);
	return (0);
}

void	waiting(t_philo *philo, int id, int fork_id1, int fork_id2)
{
	pthread_mutex_lock(&philo->table->thinking);
	while (philo->table->forks[fork_id1].state == (id % 2 == 0)
		|| philo->table->forks[fork_id2].state == (id % 2 == 0))
	{
		pthread_mutex_unlock(&philo->table->thinking);
		usleep(100);
		pthread_mutex_lock(&philo->table->thinking);
	}
	pthread_mutex_unlock(&philo->table->thinking);
}

int	fork_operation(t_philo *philo, int id, int fork_id1, int fork_id2)
{
	pthread_mutex_lock(&philo->table->forks[fork_id2].fork);
	if (check_die(philo->table))
		return (1);
	printf("\033[0;36m[%llu] \033[0;32m%d id philo has taken a fork\n",
		current() - philo->table->starting_time_of_process, id);
	if (philo->table->number_of_philosophers == 1 && id == 1)
		return (1);
	pthread_mutex_lock(&philo->table->thinking);
	if (id % 2 == 0)
		philo->table->forks[fork_id2].state = 1;
	else if (!(philo->table->number_of_philosophers % 2)
		|| id != philo->table->number_of_philosophers)
		philo->table->forks[fork_id2].state = 0;
	pthread_mutex_unlock(&philo->table->thinking);
	pthread_mutex_lock(&philo->table->forks[fork_id1].fork);
	if (check_die(philo->table))
		return (1);
	printf("\033[0;36m[%llu] \033[0;32m%d id philo has taken a fork\n",
		current() - philo->table->starting_time_of_process, id);
	pthread_mutex_lock(&philo->table->thinking);
	if (id % 2 == 0)
		philo->table->forks[fork_id1].state = 1;
	else if (!(philo->table->number_of_philosophers % 2 == 1 && id == 1))
		philo->table->forks[fork_id1].state = 0;
	return (pthread_mutex_unlock(&philo->table->thinking), 0);
}
