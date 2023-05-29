/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:36:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/29 17:36:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	connect_cmd(t_node *left, t_node *right, int fd[2])
{
	t_node	*c;

	c = left;
	while (c->type != CMD)
		c = c->right;
	c->fd_out = fd[1];
	c = right;
	while (c->type != CMD)
		c = c->left;
	c->fd_in = fd[0];
}

void	sig_child(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton(NULL);
	if (!data)
		exit(130);
	free_data(data);
	exit(130);
}

static void	open_file(int *fd, char *file, int option)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(file, option, 0777);
}

int	open_files(t_data *data, t_node *node)
{
	t_node	*tmp;

	tmp = node->right;
	while (tmp)
	{
		tmp->file = expansion(data, tmp->file);
		if (tmp->type != HEREDOC && !tmp->file)
			return (prerror("Ambiguous redirect\n"), 1);
		if (tmp->type != HEREDOC && strchr(tmp->file, '*'))
			return (prerror("Ambiguous redirect\n"), 1);
		if (tmp->file)
			tmp->file = clean_cmd(tmp->file);
		if (tmp->type != HEREDOC && !tmp->file)
			return (1);
		if (tmp->type == R_OUT)
			open_file(&node->fd_out, tmp->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (tmp->type == R_OUT2)
			open_file(&node->fd_out, tmp->file, O_WRONLY | O_CREAT | O_APPEND);
		if ((tmp->type == R_OUT || tmp->type == R_OUT2) && node->fd_out == -1)
			return (perror(tmp->file), 1);
		if (tmp->type == HEREDOC)
		{
			if (node->fd_in)
				close(node->fd_in);
			node->fd_in = tmp->fd_in;
		}
		if (tmp->type == R_IN)
			open_file(&node->fd_in, tmp->file, O_RDONLY);
		if (tmp->type == R_IN && node->fd_in == -1)
			return (perror(tmp->file), 1);
		tmp = tmp->right;
	}
	return (0);
}
