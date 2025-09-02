/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/11 11:44:33 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define TIME_TO_COUNT 1000000

typedef struct s_data
{
	pthread_mutex_t m1;
	pthread_mutex_t m2;
	unsigned int count;
}t_data;

void *routine_t1(void *arg)
{
	int i = 0;
	pthread_t id;
	t_data *data;

	data = (t_data *)arg;
	while(i < TIME_TO_COUNT)
	{
		pthread_mutex_lock(&data->m1);
		pthread_mutex_lock(&data->m2);
		data->count++;
		pthread_mutex_unlock(&data->m1);
		pthread_mutex_unlock(&data->m2);
		i++;
	}
	return (NULL);
}
void *routine_t2(void *arg)
{
	int i = 0;
	pthread_t id;
	t_data *data;

	data = (t_data *)arg;
	while(i < TIME_TO_COUNT)
	{
		pthread_mutex_lock(&data->m2);
		pthread_mutex_lock(&data->m1);
		data->count++;
		pthread_mutex_unlock(&data->m2);
		pthread_mutex_unlock(&data->m1);
		i++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1;
	pthread_t t2;
	t_data data;
	data.count = 0;

	pthread_mutex_init(&data.m1, NULL);
	pthread_mutex_init(&data.m2, NULL);
	pthread_create(&t1, NULL, &routine_t1, &data);
	pthread_create(&t2, NULL, &routine_t2, &data);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&data.m1);
	pthread_mutex_destroy(&data.m2);

	printf("TOTAL COUNT = %d\n", data.count);
	return (0);
}

// typedef struct s_data
// {
// 	pthread_mutex_t mutex;
// 	unsigned int count;
// }t_data;

// void *routine(void *arg)
// {
// 	int i = 0;
// 	pthread_t id;
// 	t_data *data;

// 	data = (t_data *)arg;
// 	while(i < TIME_TO_COUNT)
// 	{
// 		pthread_mutex_lock(&data->mutex);
// 		data->count++;
// 		pthread_mutex_unlock(&data->mutex);
// 		i++;
// 	}
// 	return (NULL);
// }

// int main(void)
// {
// 	pthread_t t1;
// 	pthread_t t2;
// 	t_data data;
// 	data.count = 0;

// 	pthread_mutex_init(&data.mutex, NULL);
// 	pthread_create(&t1, NULL, &routine, &data);
// 	printf("First thread created\n");
// 	pthread_create(&t2, NULL, &routine, &data);
// 	printf("Second thread created\n");

// 	pthread_join(t1, NULL);
// 	printf("First thread joined id = %ld\n", t1);
// 	pthread_join(t2, NULL);
// 	printf("Second thread joined id = %ld\n", t2);
// 	pthread_mutex_destroy(&data.mutex);

// 	printf("TOTAL COUNT = %d\n", data.count);
// 	return (0);
// }