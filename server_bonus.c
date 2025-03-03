/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:37:04 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/09 17:27:30 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	sigusr_handler(int signum, siginfo_t *siginfo, void *ctx)
{
	static char	c;
	static int	i;

	(void)ctx;
	if (signum == SIGUSR1)
		c |= 0b000000001 << i;
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\nWaiting for message ...\n", 25);
			kill(siginfo->si_pid, SIGUSR2);
		}
		else
			write(STDOUT_FILENO, &c, 1);
		c = 0;
		i = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
}

static void	exit_on_error(char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	exit(1);
}

int	main(void)
{
	struct sigaction	sigact;

	ft_dprintf(STDOUT_FILENO, "Server PID: %d\n", getpid());
	sigact.sa_sigaction = sigusr_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		exit_on_error("[ERR] sigaction(SIGUSR1, ...) failed.\n");
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		exit_on_error("[ERR] sigaction(SIGUSR2, ...) failed.\n");
	ft_dprintf(STDOUT_FILENO, "Waiting for message ...\n");
	while (1)
		pause();
	return (0);
}
