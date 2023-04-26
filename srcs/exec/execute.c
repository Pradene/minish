/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/20 13:57:58 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_files(t_data *data, t_node *node)
{
	(void)data;
	if (node->out || node->out2)
		close(node->fd_out);
	if (node->out)
		node->fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (node->out2)
		node->fd_out = open(node->out2, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (node->in)
		close(node->fd_in);
	if (node->in)
		node->fd_in = open(node->in, O_RDONLY, 0777);
}

void	execute(t_data *data, char **cmd, char **env)
{
	// char	*cmd_line;
	// char	**cmds;
	char	*path;

	(void)data;
	// cmd_line = lexer(cmd);
	// if (!cmds)
	// 	error(NULL);
	path = get_path(env, cmd[0]);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		d_free(cmd);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
		error(cmd[0]);
}

void	exec_cmd(t_data *data, t_node *node)
{
	pid_t	pid;
	int		exit;

	if (is_builtin(node->cmd[0]))
		return (builtin(&data->env, node->cmd));
	exit = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		open_files(data, node);
		if (node->fd_in != -1)
			dup2(node->fd_in, STDIN_FILENO);
		if (node->fd_out != -1)
			dup2(node->fd_out, STDOUT_FILENO);
		execute(data, node->cmd, data->env);
	}
	waitpid(pid, &exit, 0);
	data->exit = WEXITSTATUS(exit);
}

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

void	exec_pipe(t_data *data, t_node *left, t_node *right)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	connect_cmd(left, right, fd);
	exec(data, left);
	close(fd[1]);
	exec(data, right);
	close(fd[0]);
}

void	exec_semicol(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	exec(data, right);
}

void	exec_or(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	if (data->exit)
		exec(data, right);
}

void	exec_and(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	if (!data->exit)
		exec(data, right);
}

void	exec(t_data *data, t_node *node)
{
	if (!node)
		return ;
	if (node->type == CMD)
		exec_cmd(data, node);
	else if (node->type == PIPE)
		exec_pipe(data, node->left, node->right);
	else if (node->type == DBL_PIPE)
		exec_or(data, node->left, node->right);
	else if (node->type == AMP)
		printf("Implementation to do\n");
	else if (node->type == DBL_AMP)
		exec_and(data, node->left, node->right);
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		exec(data, node->left);
}
