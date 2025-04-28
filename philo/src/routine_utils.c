/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:31:24 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/05 09:59:57 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	try_take_first_fork(t_data *data, t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	pthread_mutex_lock(&data->end_simulation_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->end_simulation_mutex);
		pthread_mutex_unlock(&fork->fork);
		return (false);
	}
	pthread_mutex_unlock(&data->end_simulation_mutex);
	print_status(data, philo->id, "has taken a fork");
	return (true);
}

static bool	try_take_second_fork(t_data *data, t_philo *philo,
	t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&second->fork);
	pthread_mutex_lock(&data->end_simulation_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->end_simulation_mutex);
		pthread_mutex_unlock(&second->fork);
		pthread_mutex_unlock(&first->fork);
		return (false);
	}
	pthread_mutex_unlock(&data->end_simulation_mutex);
	print_status(data, philo->id, "has taken a fork");
	return (true);
}

void	take_forks(t_data *data, t_philo *philo)
{
	if (!philo || !data)
		return ;
	if (philo->id % 2)
	{
		if (!try_take_first_fork(data, philo, philo->right_fork))
			return ;
		if (!try_take_second_fork(data, philo, philo->right_fork,
				philo->left_fork))
			return ;
	}
	else
	{
		if (!try_take_first_fork(data, philo, philo->left_fork))
			return ;
		if (!try_take_second_fork(data, philo, philo->left_fork,
				philo->right_fork))
			return ;
	}
}

void	start_eating(t_data *data, t_philo *philo)
{
	if (!philo || !data)
		return ;
	pthread_mutex_lock(&data->end_simulation_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->end_simulation_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return ;
	}
	pthread_mutex_unlock(&data->end_simulation_mutex);
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	print_status(data, philo->id, "is eating");
	handmade_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

bool	should_continue_eating(t_philo *philo)
{
	t_data	*data;
	bool	continue_eating;

	data = philo->data;
	pthread_mutex_lock(&philo->meal_count_mutex);
	if (!philo->is_full && philo->meals_count < data->number_of_eat)
		continue_eating = true;
	else
		continue_eating = false;
	pthread_mutex_unlock(&philo->meal_count_mutex);
	return (continue_eating);
}
