/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:20:12 by niboukha          #+#    #+#             */
/*   Updated: 2023/05/24 18:20:20 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <stdatomic.h>

typedef struct t_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_eat;
}		t_data;

typedef struct t_sem
{
	sem_t	*forks;
	sem_t	*print;
}			t_sem;

typedef struct t_philo
{
	int				id;
	pid_t			pid;
	long long		start_time;
	struct timeval	last_meal;
	t_sem			*semaphore;
	t_data			data;
}					t_philo;

int			ft_atoi(char *str);
char		*ft_itoa(int n);
void		init_philo(char **av, int ac, t_philo *f);
void		*philosophers(void *p);
void		ft_usleep(int i);
long long	calcul_time_ms(void);
void		ft_print(t_philo *f, const char *txt, int x);
void		stop_phils(t_philo *f);
void		stop_process(t_philo *f);
void		check_args(char **av, int ac);
void		child_process(char **av, t_philo *f, pthread_t	*th);

#endif
