/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:40:48 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/24 16:40:50 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig(int s)
{
	t_data	*data;

	(void)s;
	data = singleton(NULL);
	if (!data)
		exit(0);
	free_data(data);
	exit(0);
}

void	read_heredoc(t_data *data, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			free_data(data);
			exit(0);
		}
		if (!strcmp(limiter, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

void	heredoc(t_data *data, t_node *node, char *limiter)
{
	int		fd[2];
	int		e;
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		data->tmp = node;
		data->sstdout = fd[1];
		signal(SIGINT, sig);
		close(fd[0]);
		read_heredoc(data, limiter, fd[1]);
		close(fd[1]);
		free_data(data);
		exit(0);
	}
	waitpid(pid, &e, 0);
	close(fd[1]);
	node->fd_in = fd[0];
}
