/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:36:58 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/09 13:40:16 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

volatile sig_atomic_t	g_flag = 0b00;

static void	sigusr_handler(int signum)
{
	if (signum == SIGUSR1)
		g_flag &= ~0b01;
	else
		g_flag |= 0b10;
}

static void	exit_on_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	send_byte(int pid, char c)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		g_flag |= 0b01;
		if (c & 0b000000001)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_on_error("[ERR] kill() failed.\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_on_error("[ERR] kill() failed.\n");
		}
		while (g_flag & 0b01)
			usleep(1);
		c >>= 1;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sigact;
	int					i;

	if (argc != 3)
		exit_on_error("Usage: ./client {PID} {msg}\n");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		exit_on_error("Usage: ./client {PID} {msg}\n");
	sigact.sa_handler = sigusr_handler;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		exit_on_error("[ERR] sigaction(SIGUSR1, ...) failed.\n");
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		exit_on_error("[ERR] sigaction(SIGUSR2, ...) failed.\n");
	i = 0;
	while (argv[2][i] != '\0')
		send_byte(pid, argv[2][i++]);
	send_byte(pid, '\0');
	while (!(g_flag & 0b10))
		usleep(1);
	ft_putstr_fd("Message sent successfully.\n", STDOUT_FILENO);
	return (0);
}
