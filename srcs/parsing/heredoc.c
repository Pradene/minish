/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:40:48 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:08:00 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_d(t_data *data)
{
	if (data->tokens)
		lstclear(&data->tokens);
	if (data->fd1 != -1)
		close(data->fd1);
	if (data->fd0 != -1)
		close(data->fd0);
	data->fd0 = -1;
	data->fd1 = -1;
	dfree(data->env);
	tmp_clear(&data->tmp);
	data->tmp = NULL;
}

void	sig(int s)
{
	t_data	*data;

	(void)s;
	data = singleton(NULL);
	if (!data)
		exit(1);
	free_d(data);
	exit(1);
}

void	read_heredoc(t_data *data, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free_d(data);
			exit(0);
		}
		if (!ft_strcmp(limiter, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

void	heredoc_child(t_data *data, char *limiter, int fd[2])
{
	close(fd[0]);
	data->fd1 = fd[1];
	signal(SIGINT, sig);
	read_heredoc(data, limiter, fd[1]);
	free_d(data);
	exit(0);
}

int	heredoc(t_data *data, t_node *node, char *limiter)
{
	int		fd[2];
	int		e;
	pid_t	pid;
	t_node	*tmp;

	tmp = node;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new_node(data, HEREDOC);
	if (!tmp->right)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		heredoc_child(data, limiter, fd);
	close(fd[1]);
	waitpid(pid, &e, 0);
	tmp->right->fd_in = fd[0];
	return (e);
}
