/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:26:25 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 23:29:53 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mark_philo_fed(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->state_lock);
	philo->fed = 1;
	philo->state->full_philos++;
	pthread_mutex_unlock(&philo->state->state_lock);
}

void	is_eating(t_philo *philo)
{
	int	running;

	pthread_mutex_lock(&philo->state->simulation_lock);
	running = philo->state->is_running;
	pthread_mutex_unlock(&philo->state->simulation_lock);
	if (!running)
		return ;
	pthread_mutex_lock(&philo->food_lock);
	philo->lastmeal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->food_lock);
	print_it(philo, "is eating");
	if (philo->meal_count == philo->config->snacks)
		mark_philo_fed(philo);
	delay(philo->config->t_eat);
}

void	is_sleeping(t_philo *philo)
{
	int	running;

	pthread_mutex_lock(&philo->state->simulation_lock);
	running = philo->state->is_running;
	pthread_mutex_unlock(&philo->state->simulation_lock);
	if (!running)
		return ;
	print_it(philo, "is sleeping");
	delay(philo->config->t_sleep);
}

void	is_thinking(t_philo *philo)
{
	int	running;

	pthread_mutex_lock(&philo->state->simulation_lock);
	running = philo->state->is_running;
	pthread_mutex_unlock(&philo->state->simulation_lock);
	if (!running)
		return ;
	print_it(philo, "is thinking");
	delay(1);
}
