/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:54:47 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/16 09:55:13 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

static void	update_meal_status(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_count_mutex);
	philo->meals_count++;
	if (philo->data->number_of_eat != -1
		&& philo->meals_count >= philo->data->number_of_eat)
	{
		philo->is_full = true;
		pthread_mutex_lock(&data->finished_mutex);
		data->finished_philosophers++;
		if (data->finished_philosophers >= data->number_of_philo)
		{
			pthread_mutex_lock(&data->end_simulation_mutex);
			data->end_simulation = 1;
			pthread_mutex_unlock(&data->end_simulation_mutex);
		}
		pthread_mutex_unlock(&data->finished_mutex);
	}
	pthread_mutex_unlock(&philo->meal_count_mutex);
}

void	eat(t_data *data, t_philo *philo)
{
	bool	should_continue ;

	if (!philo || !data)
		return ;
	take_forks(data, philo);
	pthread_mutex_lock(&data->end_simulation_mutex);
	should_continue = !data->end_simulation;
	pthread_mutex_unlock(&data->end_simulation_mutex);
	if (should_continue)
		start_eating(data, philo);
	update_meal_status(data, philo);
}

void	check_death_conditions(t_philo *philo, long time_since_last_meal)
{
	if (time_since_last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->end_simulation_mutex);
		if (!philo->data->end_simulation)
		{
			philo->data->end_simulation = 1;
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("%ld %d died\n", get_timestamp()
				- philo->data->start_simulation, philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
		}
		pthread_mutex_unlock(&philo->data->end_simulation_mutex);
	}
}

bool	is_simulation_ended(t_philo *philo)
{
	bool	should_continue;

	pthread_mutex_lock(&philo->data->end_simulation_mutex);
	should_continue = !philo->data->end_simulation;
	pthread_mutex_unlock(&philo->data->end_simulation_mutex);
	return (!should_continue);
}
