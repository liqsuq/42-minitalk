/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:37:04 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/07 18:17:24 by kadachi          ###   ########.fr       */
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
		c |= 1 << i;
	i++;
	if (i == 8)
	{
		if (c == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd('c', 1);
		c = 0;
		i = 0;
	}
	usleep(5000);
	kill(siginfo->si_pid, SIGUSR1);
}

static void	exit_with_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(void)
{
	struct sigaction	sigact;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigact.sa_sigaction = sigusr_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		exit_with_msg("[ERR] sigaction(SIGUSR1, ...) failed.\n");
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		exit_with_msg("[ERR] sigaction(SIGUSR2, ...) failed.\n");
	while (1)
		pause();
	return (0);
}
