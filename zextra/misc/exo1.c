/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:19:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/04/11 17:23:12 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_data
{
	int i;
	int n[4];
} t_data;

void *sum(void *args)
{
	t_data *ag = (t_data *)args;
	int *res = malloc(sizeof(int));
	if (!res)
		return NULL;
	printf("Thread %d: ag->n[%d] = %d, ag->n[%d] = %d\n", ag->i, ag->i, ag->n[ag->i], ag->i + 1, ag->n[ag->i + 1]);
	*res = ag->n[ag->i] + ag->n[ag->i + 1];
	return (void *)res;
}

int main(void)
{
	pthread_t thread[2];
	t_data *args[2];
	int *res;
	int total = 0;

	// Remplir le tableau
	int numbers[4] = {5, 9, 15, 54};

	for (int index = 0; index < 2; index++)
	{
		args[index] = malloc(sizeof(t_data));
		args[index]->i = index * 2;
		for (int j = 0; j < 4; j++)
			args[index]->n[j] = numbers[j];
		if (pthread_create(&thread[index], NULL, &sum, (void *)args[index]) != 0)
			return 1;
	}

	for (int index = 0; index < 2; index++)
	{
		if (pthread_join(thread[index], (void **)&res) != 0)
			return 1;
		total += *res;
		free(res);
		free(args[index]);
	}

	printf("total = %d\n", total);
	return 0;
}

//resultat = 84