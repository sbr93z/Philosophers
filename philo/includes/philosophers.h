/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:47:07 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/16 09:54:03 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_count;
	long				last_meal_time;
	pthread_mutex_t		meal_count_mutex;
	pthread_mutex_t		last_meal_time_mutex;
	pthread_mutex_t		is_full_mutex;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	pthread_t			death_thread_id;
	struct s_data		*data;
	bool				is_full;
}						t_philo;

typedef struct s_data
{
	long				number_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_eat;
	long				start_simulation;
	int					end_simulation;
	bool				last_meal_finished;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		is_full_mutex;
	pthread_mutex_t		end_simulation_mutex;
	int					finished_philosophers;
	pthread_mutex_t		finished_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

int						parsing(t_data data, int ac, char **av);
int						init_data(t_data *data, int ac, char **av);
void					init_fork(t_fork *fork, int id);
void					init_philosopher(t_data *data, int id);
int						init_philosophers_and_forks(t_data *data);
long					get_current_time(void);
int						ft_atoi(const char *nptr);
void					ft_free_ressources(t_data *data);
void					eat(t_data *data, t_philo *philo);
void					ft_sleep(t_data *data, t_philo *philo);
void					*routine(void *arg);
long					get_timestamp(void);
void					*check_death(void *arg);
void					take_forks(t_data *data, t_philo *philo);
void					start_eating(t_data *data, t_philo *philo);
void					check_death_conditions(t_philo *philo,
							long time_since_last_meal);
bool					should_continue_eating(t_philo *philo);
void					print_status(t_data *data, int philo_id, char *message);
bool					all_philosophers_are_full(t_data *data);
void					handmade_usleep(long int timetosleep, t_data *data);
void					init_philo_mutexes(t_philo *philo, t_data *data);
bool					is_simulation_ended(t_philo *philo);
void					think_routine(t_philo *philo);
#endif