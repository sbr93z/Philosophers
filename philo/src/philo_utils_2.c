/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:00:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/16 09:55:30 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	check_simulation_status(t_philo *philo)
{
	bool	should_continue ;

	pthread_mutex_lock(&philo->data->end_simulation_mutex);
	should_continue = !philo->data->end_simulation;
	pthread_mutex_unlock(&philo->data->end_simulation_mutex);
	return (should_continue);
}

void	ft_sleep(t_data *data, t_philo *philo)
{
	long	start_time;

	if (!check_simulation_status(philo))
		return ;
	print_status(data, philo->id, "is sleeping");
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < data->time_to_sleep)
	{
		if (!check_simulation_status(philo))
			return ;
		usleep(100);
	}
	if (!check_simulation_status(philo))
		return ;
	think_routine(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	is_full;
	bool	should_continue ;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_simulation_mutex);
		should_continue = !philo->data->end_simulation;
		pthread_mutex_unlock(&philo->data->end_simulation_mutex);
		if (!should_continue)
			break ;
		pthread_mutex_lock(&philo->meal_count_mutex);
		is_full = (philo->is_full || (philo->data->number_of_eat != -1
					&& philo->meals_count >= philo->data->number_of_eat));
		pthread_mutex_unlock(&philo->meal_count_mutex);
		if (is_full)
			break ;
		eat(philo->data, philo);
		ft_sleep(philo->data, philo);
	}
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*philo;
	long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->last_meal_time_mutex);
		time_since_last_meal = get_timestamp() - philo->last_meal_time;
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		check_death_conditions(philo, time_since_last_meal);
		if (is_simulation_ended(philo))
			break ;
		usleep(100);
	}
	return (NULL);
}

void	think_routine(t_philo *philo)
{
	long	time_to_think;
	long	start_time;

	start_time = get_timestamp();
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	time_to_think = (philo->data->time_to_die - (get_timestamp()
				- philo->last_meal_time) - philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	print_status(philo->data, philo->id, "is thinking");
	while ((get_timestamp() - start_time) < time_to_think)
	{
		if (!check_simulation_status(philo))
			return ;
		usleep(100);
	}
}
