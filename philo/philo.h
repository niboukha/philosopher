/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:24 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/20 18:40:12 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct t_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct t_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	p;
}					t_mutex;

typedef struct t_philo
{
	int				id;
	long long		start_time;
	long long		last_meal;
	t_mutex			*mutex;
	t_data			data;
}					t_philo;

int			ft_atoi(char *str);
void		*philosophers(void *p);
long long	calcul_time_ms(void);
void		ft_usleep(int i);
void		init_philo(char **av, int ac, t_philo *f);
int			stop_phils(t_philo *f);
void		ft_print(t_philo *f, const char *txt, int x);
int			check_args(char **av, int ac);

#endif