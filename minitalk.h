/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:26:17 by julcarva          #+#    #+#             */
/*   Updated: 2021/11/13 15:26:37 by julcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "./libft/includes/libft.h"

/*
** Server
*/

void	put_menu_server(pid_t pid);
char	*print_string(char *message);
void	handler_sigusr_handler(char **message, unsigned char c, int client_pid);
void	handler_sigusr(int signum, siginfo_t *info, void *context);

/*
** Client
*/

void	sig_handler(int signum, siginfo_t *info, void *context);
void	finish_transmission(int pid);
void	send_signal(char *str, int server_pid);

#endif
