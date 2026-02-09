/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:43:39 by eates             #+#    #+#             */
/*   Updated: 2023/09/07 21:45:23 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if ((argc != 5 && argc != 6) || !control(argv))
		return (print_invalid_arguments(), 1);
	create_table(&table, argc, argv);
	if (!table.number_of_philosophers)
		return (printf("There is not philosoher!!!\n"), 0);
	philo(&table);
	clear(&table);
	if (table.has_die)
		printf("\033[0;36m[%llu] \033[0;31m%d id philo died\n",
			current()
			- table.starting_time_of_process, table.id_of_philo_which_died);
	return (0);
}
