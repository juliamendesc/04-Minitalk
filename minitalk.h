
#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "./libft/includes/libft.h"

/*
** Colors
*/
# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_BLUE	"\x1b[34m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_RESET	"\x1b[0m"

void	put_menu_server(pid_t	pid);

#endif
