/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/04/03 15:18:13 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Invalid number of arguments !\n");
		return (false);
	}
	while (av[i])
	{
		if (!its_integer(av[i]))
		{
			printf("One of the arguments is invalid !\n");
			return (false);			
		}
		i++;
	}	
	if (!all_positiv_num(av))
	{
		printf("One of the arguments is invalid !\n");
		return(false);
	}
	return(true);
}	

void	all_dead(t_philosophers *philo)
{
	// int	i;

	// i = philo->number_of_philosophers;
	// printf("philoID %d\n", philo->id_philosphers);
	// printf("philo->life %d\n", philo->life);
	philo->life = 1;

	// while (i >= 0)
	// {
		// // printf("philoID %d\n", philo[i].id_philosphers);
		// philo[i].alive = false;
		// i--;
	// }
}

void	check_dead(t_philosophers *philo, int flag, long int current_time)
{
	(void) current_time;
	if (flag == 0)
	{
		if (philo->start_dead >= philo->time_to_die
			|| philo->time_to_eat >= philo->time_to_die)
		{
			all_dead(philo);
			philo->end_time = philo->time_to_die / 1000;
		}
		else
			philo->start_dead = 0;
	}
	if (flag == 1)
	{
		philo->start_dead += philo->time_to_sleep + philo->time_to_eat;
		if (philo->start_dead >= philo->time_to_die
			|| philo->time_to_sleep >= philo->time_to_die)
		{
			all_dead(philo);
			philo->end_time = philo->time_to_die / 1000 + philo->time_to_eat / 1000;
		}
	}
}

void	ft_usleep(t_philosophers *philo, long int mili_second)
{
	(void) philo;
	(void) mili_second;
	struct timeval my_time;
  	long int current_time;
  	long int i;

	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	printf("current time %lu\n", current_time);
	i = 0;
	while (i < mili_second / 1000)
	{
		usleep(170);
		gettimeofday(&my_time, NULL);
		i = ((my_time.tv_sec * 1000) + (my_time.tv_usec / 1000)) - philo->start_time;
	}
}

void	ft_eating(t_philosophers *philo)
{
	struct timeval my_time;
  	long int current_time;
	pthread_mutex_lock(&philo->my_fork);
	pthread_mutex_lock(philo->next_fork);
	pthread_mutex_lock(&philo->print);
	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);	
	check_dead(philo, 0, current_time);
	// if (philo->alive == true && (current_time - philo->start_time) < philo->time_to_die / 1000)
	if (philo->life == 0 && (current_time - philo->start_time) < philo->time_to_die / 1000)
	{
		printf("%ld\tLe philosophe %d take fork ! \n",current_time - philo->start_time,  philo->id_philosphers);
		printf("%ld\tLe philosophe %d take second fork ! \n",current_time - philo->start_time,  philo->id_philosphers);
		printf("%ld\tLe philosophe %d start eat \n",current_time - philo->start_time,  philo->id_philosphers);
		usleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(&philo->print);
	philo->number_of_times_each_philosopher_must_eat--;
		// ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(philo->next_fork);
}

void	sleeping(t_philosophers *philo)
{
	struct timeval my_time;
  	long int current_time;
	
	pthread_mutex_lock(&philo->print);
	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	// if (philo->alive == true && (current_time - philo->start_time) < philo->time_to_die / 1000)
	if (philo->life == 0 && (current_time - philo->start_time) < philo->time_to_die / 1000)
	{
		printf("%ld\tLe philosophe %d start sleep !\n",current_time - philo->start_time, philo->id_philosphers);
	    usleep(philo->time_to_sleep);
	}
	check_dead(philo, 1, current_time);
	// ft_usleep(philo, philo->time_to_sleep);
	pthread_mutex_unlock(&philo->print);
}

void	thinking(t_philosophers *philo)
{
	struct timeval my_time;
  	long int current_time;
	pthread_mutex_lock(&philo->print);
	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	printf("%ld\tLe philosophe %d think !\n",(current_time - philo->start_time),  philo->id_philosphers);
	pthread_mutex_unlock(&philo->print);
}

void	add_dead(t_philosophers *philo)
{
	int i;

	i = 0;
	while (i < (int)philo->number_of_philosophers)
	{
		if (philo[i].life == 0)
			philo[i].life = 2;
		i++;
	}
	
}

int	check_life(t_philosophers *philo)
{
	int i;
	int j;
	int	flag;

	j = 0;
	i = 0;
	flag = 1;
	(void) j;
	while (i < (int)philo->number_of_philosophers)
	{
		// if (philo[i].life == 1)
		// {
		// 	j = i;
		// 	while (i > 0)
		// 	{
		// 		philo[i - 1].life = 2;
		// 		i--;
		// 	}
		// 	i = j;
		// 	flag = 0;
		// }
		// if(flag == 0)
		// 	philo[i].life = 2;
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}
void	*round_table(void *arg)
{
	t_philosophers	*philo = (t_philosophers *) arg;
	struct timeval start;
	gettimeofday(&start, NULL);
	philo->start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	if (check_life(philo) != 0)
		pthread_exit(EXIT_SUCCESS);	
	while (philo->life == 0)
	{
		if (philo->life == 0)
			ft_eating(philo);	
		if(philo->number_of_times_each_philosopher_must_eat == 0 || philo->life != 0)
		{
			philo->life = 1;
			add_dead(philo);
			break;
		}
		if (philo->life == 0)
			sleeping(philo);
		else
		{
			philo->life = 1;
			add_dead(philo);
			break;
		}
		if (philo->life == 0)
			thinking(philo);
	}
	pthread_exit(EXIT_SUCCESS);	
}

void	get_thread(t_data *data)
{
	unsigned int	num_fork;

	num_fork = data->data_philo->number_of_philosophers;
	while (num_fork > 0)
	{
		pthread_create(&data->data_philo[num_fork -1].thread, NULL, round_table, &data->data_philo[num_fork - 1]);
		num_fork--;
	}
	while (num_fork < data->data_philo->number_of_philosophers)
	{
		pthread_join(data->data_philo[num_fork].thread, NULL);
		num_fork++;
	}
}

int	main(int ac, char **av)
{
	t_data data;
	if (!check_arg(ac, av))
		return (1);
	init_philo(&data, av);
	// print_test_init(&data);
	get_thread(&data);
	for (unsigned int i = 0; i < data.data_philo->number_of_philosophers; i++)
    {
		// printf("%ld\tLe philosophe %d est mort, arrêt du programme.\n", data.data_philo->end_time, data.data_philo[i].id_philosphers);
		printf("id%d\n", data.data_philo[i].id_philosphers);
		printf("life = %d\n", data.data_philo[i].life);
		// if (data.data_philo[i].life == 1)
        // {
            // printf("%ld\tLe philosophe %d est mort, arrêt du programme.\n", data.data_philo->end_time, data.data_philo[i].id_philosphers);
            // return (0); // Arrête le programme
        // }
    }
	// free_all(&data);
	return (0);
}