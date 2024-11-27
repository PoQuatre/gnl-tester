/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:04:22 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/27 21:07:56 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "utils.h"

#include "get_next_line.h"

static int g_test_id = 1;

void	handle_segv(int sig)
{
	(void) sig;
	printf(" %s[%d.SEGV]%s", CLR_SEGV, g_test_id++, CLR_RESET);
	exit(1);
}

void	check(bool ok)
{
	if (ok)
		printf(" %s[%d.OK]%s", CLR_OK, g_test_id++, CLR_RESET);
	else
		printf(" %s[%d.KO]%s", CLR_KO, g_test_id++, CLR_RESET);
}

void	gnl_check(int fd, char *expected)
{
	char	*res;
	void	*ptr;

	res = get_next_line(fd);
	if (expected)
	{
		check(res && !strcmp(res, expected));
		fflush(stdout);
		ptr = malloc(strlen(expected) + 1);
		if (res != NULL && malloc_usable_size(res) == malloc_usable_size(ptr))
			printf(" %s[%d.mOK]%s", CLR_OK, g_test_id - 1, CLR_RESET);
		else
			printf(" %s[%d.mKO]%s", CLR_KO, g_test_id - 1, CLR_RESET);
		free(ptr);
	}
	else
		check(!res);
	free(res);
	fflush(stdout);
}

void	mcheck(void *ptr, size_t target_size)
{
	void	*ptr2;

	ptr2 = malloc(target_size);
	if (ptr != NULL && malloc_usable_size(ptr) == malloc_usable_size(ptr2))
		printf(" %s[%d.mOK]%s", CLR_OK, g_test_id++, CLR_RESET);
	else
		printf(" %s[%d.mKO]%s", CLR_KO, g_test_id++, CLR_RESET);
	free(ptr2);
}

void	title(char *title)
{
	g_test_id = 1;
	printf("%s%s%s", CLR_TITLE, title, CLR_RESET);
}
