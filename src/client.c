/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:56:03 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/27 00:59:00 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <unistd.h>


void	send_bits(pid_t serverpid, char c)
{
	int	i;

	i = 128;
	while (i)
	{
		if (c & i)
		{
			if (kill(serverpid, SIGUSR2) == -1)
				unix_error("Kill error");
		}
		else
		{
			if (kill(serverpid, SIGUSR1) == -1)
				unix_error("Kill error");
		}
                usleep(300);
		i = i >> 1;
	}
}

void	send_buffer(pid_t serverpid, char *buffer)
{
	if (buffer == NULL)
		return ;
	while (*buffer)
		send_bits(serverpid, *buffer++);
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	char	*buffer;

	if (argc != 3)
		return (EXIT_FAILURE);
        // TODO: Check server pid if valid
	serverpid = atoi(argv[1]);
	buffer = argv[2];
	send_buffer(serverpid, buffer);
	return (0);
}
