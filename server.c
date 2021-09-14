#include "minitalk.h"
#include <stdio.h>

void	put_menu_server(pid_t	pid)
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

char	*print_string(char *message)
{
	ft_putstr(message);
	free(message);
	return (NULL);
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
  static unsigned char	c = 0;
  static int	bits = 7;
	static	int	client_pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c |= (1UL << bits);
	bits--;
	if (bits == -1)
	{
		if (c)
			message = ft_straddc(message, c);
		else
			message = print_string(message);
		bits = 7;
		c = 0;
	}
}

int	main(void)
{
	pid_t	pid;
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
