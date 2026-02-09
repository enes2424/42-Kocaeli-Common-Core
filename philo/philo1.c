/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:11:04 by eates             #+#    #+#             */
/*   Updated: 2023/08/27 18:11:05 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	print_invalid_arguments(void)
{
	printf("Invalid Arguments!!!\n");
	printf("Your program should take the following arguments:\n");
	printf("[1] number_of_philosophers\n");
	printf("[2] time_to_die\n");
	printf("[3] time_to_eat\n");
	printf("[4] time_to_sleep\n");
	printf("[5] number_of_times_each_philosopher_must_eat (optional)\n");
}

int	control(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		if (argv[i][0] == '+')
			j++;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
	}
	return (1);
}

void	clear(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
		free(table->philos[i]);
	free(table->philos);
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_mutex_destroy(&table->forks[i].fork);
	pthread_mutex_destroy(&table->thinking);
	pthread_mutex_destroy(&table->die);
	pthread_mutex_destroy(&table->starting_time);
	pthread_mutex_destroy(&table->finish_optional);
	free(table->forks);
}

void	init_philos(t_table *table)
{
	int	i;

	table->philos
		= malloc(sizeof(t_philo *) * (table->number_of_philosophers));
	i = 0;
	while (++i <= table->number_of_philosophers)
	{
		table->philos[i - 1] = malloc(sizeof(t_philo));
		table->philos[i - 1]->id = i;
		table->philos[i - 1]->table = table;
		table->philos[i - 1]->num_of_eat = 0;
	}
}

void	create_table(t_table *table, int argc, char **argv)
{
	int	i;

	table->number_of_philosophers = ft_uatoi(argv[1]);
	if (!table->number_of_philosophers)
		return ;
	table->time_to_die = ft_uatoi(argv[2]);
	table->time_to_eat = ft_uatoi(argv[3]);
	table->time_to_sleep = ft_uatoi(argv[4]);
	table->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_uatoi(argv[5]);
	table->forks = malloc(sizeof(t_fork) * table->number_of_philosophers);
	table->has_die = 0;
	table->optional_finish = 0;
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		table->forks[i].state = (i == 0)
			* (table->number_of_philosophers % 2 == 1);
		pthread_mutex_init(&table->forks[i].fork, NULL);
	}
	init_philos(table);
}
