/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:11:12 by eates             #+#    #+#             */
/*   Updated: 2023/08/27 18:11:13 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				state;
}	t_fork;

typedef struct s_philo
{
	struct s_table	*table;
	int				id;
	pthread_t		t;
	u_int64_t		starting_time;
	int				num_of_eat;
}	t_philo;

typedef struct s_table
{
	t_philo			**philos;
	t_fork			*forks;
	pthread_t		control_die;
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				has_die;
	int				optional_finish;
	int				id_of_philo_which_died;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		starting_time_of_process;
	pthread_mutex_t	thinking;
	pthread_mutex_t	die;
	pthread_mutex_t	starting_time;
	pthread_mutex_t	finish_optional;
}	t_table;

u_int64_t	ft_uatoi(const char *str);
void		print_invalid_arguments(void);
int			control(char **argv);
void		clear(t_table *table);
void		init_philos(t_table *table);
void		create_table(t_table *table, int argc, char **argv);
u_int64_t	current(void);
void		passing_time(u_int64_t msec);
int			check_die(t_table *table);
void		waiting(t_philo *philo, int id, int fork_id1, int fork_id2);
int			fork_operation(t_philo *philo, int id, int fork_id1, int fork_id2);
int			life(t_philo *philo, int id, int fork_id1, int fork_id2);
void		*t_func(void *tmp);
void		*die(t_table *table, int id);
void		*die_control(void *tmp);
void		philo(t_table *t);

#endif
