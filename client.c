#include "minitalk.h"
#include <stdio.h>

/*
** This function handles the signals received from the server.
** When it receives a SIGUSR2, the message was received successfully
** and the program closes.
*/

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

/*
** This functions sends the null character to finish the string.
*/

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

/*
** This function converts each character into binary using bitwise operators,
** it sends each bit as a signal to the server. SIGUSR1 represents 0, SIGUSR2
** represents 1.
**
** When it finishes sending the whole converted string, it calls the function
** finish transmission, that will pass the null character.
*/

void send_signal(char *str, int server_pid)
{
   int   i;
   int   shifter;

   i = 0;
   while (str[i])
   {
      shifter = 8;
      while (shifter-- > 0)
      {
         if (str[i] & 1UL << shifter)
         {
            if (kill(server_pid, SIGUSR2) == -1)
               exit(1);
         }
         else
         {
            if (kill(server_pid, SIGUSR1) == -1)
               exit(1);
         }
         usleep(30);
      }
      i++;
   }
  	finish_transmission(server_pid);
}

/*
** The main function handles the errors if not given a valid pid and/or 3
** arguments in the command line. If all necessary conditions are met, it
** converts the server pid to integer to be used by the program.
**
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
*/

int	main(int argc, char **argv)
{
	int	server_pid;
	struct sigaction	sa_signals;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		if (!server_pid)
		{
			ft_putstr_in_color(TEXT_COLOR_RED, "ERROR: invalid PID \n");
			return(EXIT_FAILURE);
		}
    sa_signals.sa_flags = SA_SIGINFO;
	  sa_signals.sa_sigaction = sig_handler;
    sigaction(SIGUSR1, &sa_signals, NULL);
    sigaction(SIGUSR2, &sa_signals, NULL);
		send_signal(argv[2], server_pid);
    return (0);
	}
	ft_putstr_in_color(TEXT_COLOR_RED, "WRONG ARGUMENTS\n");
	ft_putstr_in_color(TEXT_COLOR_RED, "Usage: ./client [server pid] ");
	ft_putstr_in_color(TEXT_COLOR_RED, "\"text to send\"\n");
	return (EXIT_FAILURE);
}
