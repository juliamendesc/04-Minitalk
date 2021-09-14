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

void	handler_sigusr(int signum)
{
   static unsigned char	c = 255;
   static int	bits = 8;

	if (signum == SIGUSR1)
	{
	printf("0");
	fflush(stdout);
	c ^= 1UL >> bits;
	}
	else if (signum == SIGUSR2)
	{
	printf("1");
	fflush(stdout);
	c |= 1UL >> bits;
	}
	bits--;
	if (bits == 0)
	{
		printf("-> %c\n", c);
		bits = 7;
		c = 255;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	put_menu_server(pid);
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	while (1)
	{
		pause();
	}
}
