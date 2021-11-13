/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:47:03 by julcarva          #+#    #+#             */
/*   Updated: 2021/11/13 16:47:42 by julcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** This function puts a nice menu on server start
*/

void	put_menu_server(pid_t pid)
{
	char	*str_pid;

	str_pid = ft_itoa(pid);
	ft_putstr_in_color(TEXT_COLOR_GREEN, "\t\t\tWelcome in Minitalk\n");
	ft_putstr_in_color(TEXT_COLOR_GREEN, "To start the chat,");
	ft_putstr_in_color(TEXT_COLOR_GREEN, "share this code to the client: ");
	ft_putstr_in_color(TEXT_COLOR_GREEN, str_pid);
	ft_putstr_in_color(TEXT_COLOR_GREEN, "\nThe chat will start from here. ");
	ft_putstr_in_color(TEXT_COLOR_GREEN, "Have fun!\n");
	ft_putstr_in_color(TEXT_COLOR_GREEN, "=================================");
	ft_putstr_in_color(TEXT_COLOR_GREEN, "=================================\n");
	free(str_pid);
}

/*
** When the message is ready to print, this function is called to print it and
** free the memory allocated to it.
*/

char	*print_string(char *message)
{
	ft_putstr(message);
	free(message);
	return (NULL);
}

/*
** This function handles the signals coming from the client program.
**
** SIGUSR1 represents the bit 0, while SIGUSR2 represents the bit 1.
** This allows us to receive messages from the client bit by bit.
**
** info->si_pid retrieves the PID from the client, which will allow to
** send signals back to it.
**
** The binary received are converted into characters using bitwise operators
** again and stored in the message. When there is no char, such as the null
** character, it will call the print message function and send a signal to the
** client to inform it has received the whole string.
**
** When the full string is received, we receive a NULL (0) char, which
** means we can send a signal to the client to confirm the string
** reached its destination.
*/

void	handler_sigusr_handler(char **message, unsigned char c, int client_pid)
{
	if (c)
		*message = ft_straddchar(*message, c);
	else
	{
		*message = print_string(*message);
		ft_putchar('\n');
		kill(client_pid, SIGUSR2);
	}
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bits = 7;
	static int				client_pid = 0;
	static char				*message = 0;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c |= (1UL << bits);
	bits--;
	if (bits == -1)
	{
		handler_sigusr_handler(&message, c, client_pid);
		bits = 7;
		c = 0;
	}
}

/*
** The Sigaction structure is used to change the normal behaviour of the
** system when receiving signals. In this case, instead of finishing the
** program as soon as it receives the signal (normal behavior), it will
** call the sig_handles function.
**
** sa_flags: Allows changing the behavior of the handling process.
** To use the sa_sigaction handler, you must put SA_SIGINFO here.
** SA_SIGINFO stores information about the signal. It has 3 parameters
** (the signal, the pointer to the info about the signal and the context)
**
** The pid is retrieved and put in the menu for the client.
**
** The server waits for the signals from the client to come.
*/

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa_signal;

	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	pid = getpid();
	put_menu_server(pid);
	while (1)
		pause();
}
