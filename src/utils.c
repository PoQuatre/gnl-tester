/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:04:22 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/25 19:22:07 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "utils.h"

static int g_test_id = 1;

void	handle_segv(int sig)
{
	(void) sig;
	printf(" %s[%d.SEGV]", CLR_SEGV, g_test_id++);
	exit(1);
}

void	check(bool ok)
{
	if (ok)
		printf(" %s[%d.OK]", CLR_OK, g_test_id++);
	else
		printf(" %s[%d.KO]", CLR_KO, g_test_id++);
}

void	mcheck(void *ptr, size_t target_size)
{
	void	*ptr2;

	ptr2 = malloc(target_size);
	if (ptr != NULL && malloc_usable_size(ptr) == malloc_usable_size(ptr2))
		printf(" %s[%d.mOK]", CLR_OK, g_test_id++);
	else
		printf(" %s[%d.mKO]", CLR_KO, g_test_id++);
	free(ptr2);
}

void	title(char *title)
{
	printf("%s%s%s", CLR_TITLE, title, CLR_RESET);
}
