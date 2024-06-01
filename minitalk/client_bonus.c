/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlanca-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:45:45 by mlanca-c          #+#    #+#             */
/*   Updated: 2024/01/21 20:30:21 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_error_client(char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("Client: ERROR!\n", 2);
	exit(EXIT_FAILURE);
}

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			send_error_client(str);
		return (0);
	}
	return (1);
}

int	send_bit(int pid, char *str)
{
	static int	bit_counter = -1;
	static char	*message = 0;
	static int	server_pid = 0;

	if (str)
		message = ft_strdup(str);
	if (!message)
		send_error_client(0);
	if (pid)
		server_pid = pid;
	if (message[++bit_counter / 8])
	{
		if (message[bit_counter / 8] & (0x80 >> (bit_counter % 8)))
		{
			if (kill(server_pid, SIGUSR2) == -1)
				send_error_client(message);
		}
		else if (kill(server_pid, SIGUSR1) == -1)
			send_error_client(message);
		return (0);
	}
	if (!send_null(server_pid, message))
		return (0);
	free(message);
	return (1);
}

void	handler_sigusr_client(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_bit(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("Client: ERROR!\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_str_is_numeric(argv[1]))
	{
		ft_putstr_fd("ERROR: Please use this format: ./client PID message\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler_sigusr_client);
	signal(SIGUSR2, handler_sigusr_client);
	send_bit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
