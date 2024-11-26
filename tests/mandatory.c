/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:05:00 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/26 15:24:25 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

int	main(void)
{
	int fd;

	signal(SIGSEGV, handle_segv);

	TEST("Invalid fd", {
		/* 1 */ gnl_check(1000, NULL);
		/* 2 */ gnl_check(-1, NULL);
		fd = open("testdata/alt_no_nl", O_RDONLY);
		close(fd);
		/* 3 */ gnl_check(fd, NULL);
	});

	TESTF("empty", {
		/* 1 */ gnl_check(fd, NULL);
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("nl", {
		/* 1 */ gnl_check(fd, "\n");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("nl_x5", {
		/* 1 */ gnl_check(fd, "\n");
		/* 2 */ gnl_check(fd, "\n");
		/* 3 */ gnl_check(fd, "\n");
		/* 4 */ gnl_check(fd, "\n");
		/* 5 */ gnl_check(fd, "\n");
		/* 6 */ gnl_check(fd, NULL);
	});
}
