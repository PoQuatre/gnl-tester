/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:05:00 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/25 19:28:53 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

#include "get_next_line.h"

int	main(void)
{
	signal(SIGSEGV, handle_segv);

	int fd;

	title("Invalid fd:");
	/* 1 */ check(get_next_line(1000) == NULL);
	/* 2 */ check(get_next_line(-1) == NULL);
	fd = open("testdata/alt_no_nl", O_RDONLY);
	close(fd);
	/* 3 */ check(get_next_line(fd) == NULL);

	fflush(stdout);
	write(1, "\n", 1);
}
