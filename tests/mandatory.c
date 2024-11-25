/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:05:00 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/25 19:57:22 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"

#include "get_next_line.h"

int	main(void)
{
	signal(SIGSEGV, handle_segv);

	int fd;
	char *res;

	TEST("Invalid fd:", {
		/* 1 */ check(!get_next_line(1000));
		/* 2 */ check(!get_next_line(-1));
		fd = open("testdata/alt_no_nl", O_RDONLY);
		close(fd);
		/* 3 */ check(!get_next_line(fd));
	});

	TEST("empty:", {
		fd = open("testdata/empty", O_RDONLY);
		res = get_next_line(fd);
		/* 1 */ check(res && strcmp(res, ""));
		free(res);
		res = get_next_line(fd);
		/* 2 */ check(!res);
		close(fd);
	});
}
