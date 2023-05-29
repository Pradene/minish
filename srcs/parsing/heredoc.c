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

void	free_n(t_node *node)
{
	if (node && node->type == CMD)
		dfree(node->cmd);
	if (node && (node->type == R_IN \
	|| node->type == R_OUT || node->type == R_OUT2))
		free(node->file);
	if (node && node->fd_in != -1)
		close(node->fd_in);
	if (node && node->fd_out != -1)
		close(node->fd_out);
	if (!node)
		return ;
	free(node);
	node = NULL;
}

void	lc(t_l **lst)
{
	t_l	*p;

	if (!lst)
		return ;
	while ((*lst))
	{
		p = ((*lst))->next;
		free_n((*lst)->c);
		free((*lst));
		(*lst) = p;
	}
	(*lst) = NULL;
}

void	free_d(t_data *data)
{
	if (data->tokens)
		lstclear(&data->tokens);
	if (data->fd1 != -1)
		close(data->fd1);
	if (data->fd0 != -1)
		close(data->fd0);
	dfree(data->env);
	lc(&data->tmp);
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
		if (!strcmp(limiter, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
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
	tmp->right = new_node();
	if (!tmp->right)
		return (1);
	tmp->right->type = HEREDOC;
	ladd(&data->tmp, tmp->right);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		data->fd1 = fd[1];
		signal(SIGINT, sig);
		read_heredoc(data, limiter, fd[1]);
		free_d(data);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &e, 0);
	tmp->right->fd_in = fd[0];
	return (e);
}
