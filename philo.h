/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:06:23 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 19:59:25 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_philo	t_philo;

typedef struct s_config
{
	int							snacks;
	int							philo_nbr;
	long				start_time;
	size_t						t_die;
	size_t						t_eat;
	size_t						t_sleep;
}								t_config;

typedef struct s_state
{
	int							all_meal_count;
	int							full_philos;
	int							is_running;
	pthread_mutex_t				*forks;
	pthread_mutex_t				print_lock;
	pthread_mutex_t				simulation_lock;
	pthread_mutex_t				state_lock;
	pthread_t					routine;
	t_philo						**philos;
	t_config					*config;
}								t_state;

typedef struct s_philo
{
	int							fork1;
	int							fork2;
	int							id;
	int							fed;
	int							meal_count;
	size_t						lastmeal;
	pthread_t					thread;
	pthread_mutex_t				food_lock;
	t_state						*state;
	t_config					*config;
}								t_philo;

//free_all.c
void			free_all(t_state *state);

//helper_funcs.c
int				ft_atoi(const char *str);
int				check_args(char *argv[], int argc);
void			*philo_actions(void *arg);

//helper_funcs2.c
void			print_it(t_philo *philo, char *msg);
void			*is_dead(t_state *state, int i);
int				is_running(t_philo *philo);
int				configload(char **argv, t_config *config, int argc);

//init.c
int				init_state(t_state *state, t_config *config);
int				init_thread(t_state *state);

//philo_routine.c
void			is_eating(t_philo *philo);
void			is_sleeping(t_philo *philo);
void			is_thinking(t_philo *philo);

//forks.c
void			take_forks(t_philo *philo);
void			put_forks(t_philo *philo);

//simulations.c
void			*philo_process(void *arg);
void			*routine(void *arg);

//utils3.c
void			print_it(t_philo *philo, char *msg);
unsigned long	get_time(void);
void			delay(int duration);
int				check_philo_death(t_state *state, int i);
long get_long(t_philo *philo, long val);

#endif