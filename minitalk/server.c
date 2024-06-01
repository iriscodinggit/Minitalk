/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlanca-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:45:36 by mlanca-c          #+#    #+#             */
/*   Updated: 2024/01/21 21:10:27 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_error_server(int pid, char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("Server: ERROR!\n", 2);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

char	*print_message(char *message)
{
	ft_putstr_fd(message, 1);
	free(message);
	return (NULL);
}

void	handler_sigusr_server(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bit_counter = 0;
	static int	client_pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bit_counter;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bit_counter;
	if (++bit_counter == 8)
	{
		if (c)
			message = ft_add_char(message, c);
		else
			message = print_message(message);
		bit_counter = 0;
		c = 0xFF;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		send_error_server(client_pid, message);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			ignore_signals;

	sigemptyset(&ignore_signals);
	sigaddset(&ignore_signals, SIGINT);
	sigaddset(&ignore_signals, SIGQUIT);
	sa_signal.sa_mask = ignore_signals;
	sa_signal.sa_sigaction = handler_sigusr_server;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
