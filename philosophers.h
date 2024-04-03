#ifndef		PHILOSOPHERS_H
# define	PHILOSOPHERS_H

/*printf*/
# include <stdio.h>

/*usleep*/
# include <unistd.h>

/*gettimeofday*/
# include <sys/time.h>

/*bool*/
# include <stdbool.h>

/*malloc*/
# include <stdlib.h>

/*thread*/
# include <pthread.h>

typedef struct s_philosophers
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	unsigned int	id_philosphers;
	long int		start_time;
	long int		end_time;
	long int		start_dead;
	bool			alive;
	pthread_t		thread_philo;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	print;
} t_philosophers;

typedef struct s_data
{
	int				dead_id;
	bool			alive;
	// pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*dead;
	pthread_mutex_t	print;
	t_philosophers	*data_philo;
} t_data;

/*philosophers_utils.c*/
long int		ft_atoi(const char *nptr);
bool			its_integer(char *str);
bool			all_positiv_num(char **av);

/*free.c*/
void	free_split(int	**tab);
void	free_all(t_data *data);

/*init.c*/
void	init_philo(t_data *data, char **av);
void	init_mutex(t_data *data);

/*DEL AFTER -- test.c*/
void	print_test_init(t_data *data);

#endif 
