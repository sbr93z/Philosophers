/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:39:45 by sferrad           #+#    #+#             */
/*   Updated: 2025/02/26 17:06:07 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->end_simulation_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->end_simulation_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->last_meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->end_simulation_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->finished_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->end_simulation_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->last_meal_mutex);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_eat = ft_atoi(av[5]);
	else
		data->number_of_eat = -1;
	data->end_simulation = 0;
	data->last_meal_finished = false;
	data->finished_philosophers = 0;
	if (!init_mutexes(data))
		return (0);
	if (!init_philosophers_and_forks(data))
		return (0);
	if (!data->forks || !data->philos)
	{
		ft_free_ressources(data);
		return (0);
	}
	return (1);
}

void	print_status(t_data *data, int philo_id, char *message)
{
	bool	should_print;

	pthread_mutex_lock(&data->end_simulation_mutex);
	should_print = !data->end_simulation;
	pthread_mutex_unlock(&data->end_simulation_mutex);
	if (should_print)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d %s\n", get_timestamp() - data->start_simulation,
			philo_id, message);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

void	handmade_usleep(long int timetosleep, t_data *data)
{
	long	start;
	long	current;
	bool	should_continue ;

	start = get_timestamp();
	while (1)
	{
		current = get_timestamp();
		if (current - start >= timetosleep)
			break ;
		pthread_mutex_lock(&data->end_simulation_mutex);
		should_continue = !data->end_simulation;
		pthread_mutex_unlock(&data->end_simulation_mutex);
		if (!should_continue)
			break ;
		usleep(50);
	}
}
