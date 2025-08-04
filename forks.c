/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:26:25 by skuik             #+#    #+#             */
/*   Updated: 2025/08/04 18:49:28 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->config->philo_nbr;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->state->forks[right]);
		print_it(philo, "has taken a fork");
		pthread_mutex_lock(&philo->state->forks[left]);
		print_it(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->state->forks[left]);
		print_it(philo, "has taken a fork");
		pthread_mutex_lock(&philo->state->forks[right]);
		print_it(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->config->philo_nbr;
	pthread_mutex_unlock(&philo->state->forks[left]);
	pthread_mutex_unlock(&philo->state->forks[right]);
}
