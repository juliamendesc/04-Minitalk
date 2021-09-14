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

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 255;
	static int				shifter = 0;
	static int				pid = 0;
	int								bit;

	(void)context;
	(void)info;
	if (signum == SIGUSR1)
	{
    //write(1, "0", 1);
		c ^= 1 << shifter;
		bit = (c >> shifter) & 1U;
		printf("shifter 1 %d\n", bit);
	}
	else if (signum == SIGUSR2)
	{
    //write(1, "1", 1);
		c |= 1 << shifter;
		bit = (c >> shifter) & 1U;
		printf("shifter 2 %d\n", bit);
	}
	shifter++;
	if (shifter == 8)
	{
		write(1, &c, 1);
		shifter = 0;
		if (c == 0)
		{
			ft_putstr_fd("\n", 1);
			kill(pid, SIGUSR2);
		}
		c = 255;
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
	{
		pause();
	}
}
