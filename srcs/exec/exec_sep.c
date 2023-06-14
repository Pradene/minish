/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:36:13 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/29 17:36:14 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_pipe(t_data *data, t_node *left, t_node *right)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return ;
	connect_cmd(left, right, fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		close(fd[0]);
		exec(data, left);
		close(fd[1]);
		free_data(data);
		exit(g_exit);
	}
	close(fd[1]);
	exec(data, right);
	close(fd[0]);
	wait(&status);
}

static void	exec_semicol(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	exec(data, right);
}

static void	exec_or(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	if (g_exit)
		exec(data, right);
}

static void	exec_and(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	if (!g_exit)
		exec(data, right);
}

void	exec(t_data *data, t_node *node)
{
	if (!node)
		return ;
	if (node->type == CMD)
		exec_node(data, node);
	else if (node->type == PIPE)
		exec_pipe(data, node->left, node->right);
	else if (node->type == DBL_PIPE)
		exec_or(data, node->left, node->right);
	else if (node->type == AMP)
		exec_semicol(data, node->left, node->right);
	else if (node->type == DBL_AMP)
		exec_and(data, node->left, node->right);
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		exec(data, node->left);
}
