#include "minitalk.h"
#include <stdio.h>

void	finish_transmission(int pid)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(30);
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_putstr_fd("Message successfully sent ✅\n", 1);
		exit(0);
	}
}

static void send_signal(char *str, int server_pid)
{
   int   i;
   int   shifter;

   i = 0;
   shifter = 8;
   while (str[i])
   {
      while (shifter-- > 0)
      {
         if (str[i] & (1UL << shifter))
         {
            if (kill(server_pid, SIGUSR1) == -1)
               exit(1);
            write(1, "1", 1);
         }
         else
         {
            if (kill(server_pid, SIGUSR2) == -1)
               exit(1);
            write(1, "0", 1);
         }
         usleep(30);
      }
      write(1, "\n", 1);
      i++;
   }
   //finish_transmission(server_pid);
}

int	main(int argc, char **argv)
{
	int	server_pid;
   struct sigaction	sa_signals;

	sa_signals.sa_flags = SA_SIGINFO;
	sa_signals.sa_sigaction = sig_handler;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
      printf("PID %d\n:", server_pid);
		if (!server_pid)
		{
			ft_putstr_in_color(TEXT_COLOR_RED, "ERROR: invalid PID \n");
			return(EXIT_FAILURE);
		}
      sigaction(SIGUSR2, &sa_signals, NULL);
		send_signal(argv[2], server_pid);
      return (0);
	}
	ft_putstr_in_color(TEXT_COLOR_RED, "WRONG ARGUMENTS\n");
	ft_putstr_in_color(TEXT_COLOR_RED, "Usage: ./client [server pid] ");
	ft_putstr_in_color(TEXT_COLOR_RED, "\"text to send\"\n");
	return (EXIT_FAILURE);
}
