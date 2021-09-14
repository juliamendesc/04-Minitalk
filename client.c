#include "minitalk.h"
#include <stdio.h>

void send_signal(char *str, int server_pid)
{
   int   i;
   int   shifter;

   i = 0;
   shifter = 8;
   while (str[i])
   {
      while (shifter-- > 0)
      {
         if (str[i] & 1UL << shifter)
         {
            if (kill(server_pid, SIGUSR2) == -1)
               exit(1);
            write(1, "1", 1);
         }
         else
         {
            if (kill(server_pid, SIGUSR1) == -1)
               exit(1);
            write(1, "0", 1);
         }
         usleep(30);
      }
      write(1, "\n", 1);
      i++;
   }
}

int	main(int argc, char **argv)
{
	int	server_pid;
	// struct sigaction	sa_signals;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
      printf("PID %d\n:", server_pid);
		if (!server_pid)
		{
			ft_putstr_in_color(TEXT_COLOR_RED, "ERROR: invalid PID \n");
			return(EXIT_FAILURE);
		}
/*       sa_signals.sa_flags = SA_SIGINFO;
	   sa_signals.sa_sigaction = send_signal;
      sigaction(SIGUSR1, &sa_signals, NULL);
      sigaction(SIGUSR2, &sa_signals, NULL); */
      printf("%d\n", *argv[2]);
		send_signal(argv[2], server_pid);
      return (0);
	}
	ft_putstr_in_color(TEXT_COLOR_RED, "WRONG ARGUMENTS\n");
	ft_putstr_in_color(TEXT_COLOR_RED, "Usage: ./client [server pid] ");
	ft_putstr_in_color(TEXT_COLOR_RED, "\"text to send\"\n");
	return (EXIT_FAILURE);
}
