/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:48:48 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/09 10:14:46 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void *routine()
{
	int i = 0;
	while (i < 100000)
	{
		// pthread_mutex_lock(&mutex);
		count++;
		// pthread_mutex_unlock(&mutex);
		i++;
	}
}

int main()
{
	pthread_t th[4];
	int i = 0;
	// int total = 0;

	pthread_mutex_init(&mutex, NULL);
	while(i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return 1;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("count total = %d\n", count);
	return 0;
}
