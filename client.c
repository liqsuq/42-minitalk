/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:36:58 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/07 18:12:56 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

volatile sig_atomic_t	g_flag = 0;

static void	sigusr_handler(int signum)
{
	(void)signum;
}

static void	exit_with_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static void	send_byte(int pid, char c)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		if (c & 0x01)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_with_msg("[ERR] kill() failed.\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_with_msg("[ERR] kill() failed.\n");
		}
		pause();
		ft_putstr_fd(".", 1);
		c >>= 1;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sigact;
	int					i;

	if (argc != 3)
		exit_with_msg("Usage: ./client {PID} {msg}\n");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		exit_with_msg("Usage: ./client {PID} {msg}\n");
	sigact.sa_handler = sigusr_handler;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == 1)
		exit_with_msg("[ERR] sigaction() failed.\n");
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_byte(pid, argv[2][i++]);
		ft_putstr_fd("sent\n", 1);
	}
	send_byte(pid, '\0');
	return (0);
}
