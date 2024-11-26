/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:04:06 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/26 15:24:14 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>

# define CLR_RESET "\x1b[0m"
# define CLR_TITLE "\x1b[0;2;97m"
# define CLR_SEGV "\x1b[0;1;91;7m"
# define CLR_OK "\x1b[0;1;92m"
# define CLR_KO "\x1b[0;1;91m"

# define TEST(title_str, code) { \
	title(title_str ":"); \
	{code}; \
	printf(" \n");\
}

# define TESTF(title_str, code) { \
	title(title_str ":"); \
	int fd = open("testdata/" title_str, O_RDONLY); \
	if (fd < 0) \
		printf("%s [CANNOT OPEN %s]%s", CLR_KO, "testdata/" title_str, CLR_RESET); \
	else \
	{ \
		{code}; \
		close(fd); \
	} \
	printf(" \n");\
}

void	handle_segv(int sig);
void	check(bool ok);
void	gnl_check(int fd, char *expected);
void	mcheck(void *ptr, size_t target_size);
void	title(char *title);

#endif
