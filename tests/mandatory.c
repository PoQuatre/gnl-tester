/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:05:00 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/26 15:40:56 by mle-flem         ###   ########.fr       */
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
	signal(SIGSEGV, handle_segv);

	TEST("Invalid fd", {
		/* 1 */ gnl_check(1000, NULL);
		/* 2 */ gnl_check(-1, NULL);
		int fd = open("testdata/alt_no_nl", O_RDONLY);
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

	TESTF("41_no_nl", {
		/* 1 */ gnl_check(fd, "01234567890123456789012345678901234567890");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("41_with_nl", {
		/* 1 */ gnl_check(fd, "01234567890123456789012345678901234567890\n");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("42_no_nl", {
		/* 1 */ gnl_check(fd, "012345678901234567890123456789012345678901");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("42_with_nl", {
		/* 1 */ gnl_check(fd, "012345678901234567890123456789012345678901\n");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("43_no_nl", {
		/* 1 */ gnl_check(fd, "0123456789012345678901234567890123456789012");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("43_with_nl", {
		/* 1 */ gnl_check(fd, "0123456789012345678901234567890123456789012\n");
		/* 2 */ gnl_check(fd, NULL);
	});

	TESTF("mul_no_nl", {
		/* 1 */ gnl_check(fd, "01234567890123456789012345678901234567890\n");
		/* 2 */ gnl_check(fd, "123456789012345678901234567890123456789012\n");
		/* 3 */ gnl_check(fd, "3456789012345678901234567890123456789012345\n");
		/* 4 */ gnl_check(fd, "678901234567890123456789012345678901234567\n");
		/* 5 */ gnl_check(fd, "89012345678901234567890123456789012345678");
		/* 6 */ gnl_check(fd, NULL);
	});

	TESTF("mul_with_nl", {
		/* 1 */ gnl_check(fd, "01234567890123456789012345678901234567890\n");
		/* 2 */ gnl_check(fd, "123456789012345678901234567890123456789012\n");
		/* 3 */ gnl_check(fd, "3456789012345678901234567890123456789012345\n");
		/* 4 */ gnl_check(fd, "678901234567890123456789012345678901234567\n");
		/* 5 */ gnl_check(fd, "89012345678901234567890123456789012345678\n");
		/* 6 */ gnl_check(fd, NULL);
	});

	TESTF("alt_no_nl", {
		/* 1  */ gnl_check(fd, "01234567890123456789012345678901234567890\n");
		/* 2  */ gnl_check(fd, "\n");
		/* 3  */ gnl_check(fd, "123456789012345678901234567890123456789012\n");
		/* 4  */ gnl_check(fd, "\n");
		/* 5  */ gnl_check(fd, "3456789012345678901234567890123456789012345\n");
		/* 6  */ gnl_check(fd, "\n");
		/* 7  */ gnl_check(fd, "678901234567890123456789012345678901234567\n");
		/* 8  */ gnl_check(fd, "\n");
		/* 9  */ gnl_check(fd, "89012345678901234567890123456789012345678");
		/* 10 */ gnl_check(fd, NULL);
	});
}
