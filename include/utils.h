/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-flem <mle-flem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:04:06 by mle-flem          #+#    #+#             */
/*   Updated: 2024/11/25 13:04:07 by mle-flem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>

# define CLR_RESET "\x1b[0m"
# define CLR_SEGV "\x1b[0;1;91;7m"
# define CLR_OK "\x1b[0;1;92m"
# define CLR_KO "\x1b[0;1;91m"

void	handle_segv(int sig);
void	check(bool ok);
void	mcheck(void *ptr, size_t target_size);

#endif
