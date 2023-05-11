/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/10 16:17:59 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_node *node, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (1)
	{
		line = readline("> ");
		if (!line)
			continue ;
		if (!strcmp(limiter, line))
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	node->fd_in = open(".heredoc", O_RDONLY, 0777);
}

int	open_files(t_node *node)
{
	t_node	*tmp;

	tmp = node->right;
	while (tmp)
	{
		if (node->fd_out != -1)
			close(node->fd_out);
		if (tmp->type == R_OUT)
			node->fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp->type == R_OUT2)
			node->fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if ((tmp->type == R_OUT || node->type == R_OUT2) && node->fd_out == -1)
			return (1);
		if (node->fd_in != -1)
			close(node->fd_in);
		if (tmp->type == R_IN)
			node->fd_in = open(tmp->file, O_RDONLY, 0777);
		if (tmp->type == R_IN && node->fd_in == -1)
			return (1);
		if (tmp->type == HEREDOC)
			heredoc(node, tmp->file);
		tmp = tmp->right;
	}
	return (0);
}

void	execute(t_data *data, char **cmd, char **env)
{
	char	*path;

	cmd = lex(cmd, data->env);
	cmd = wild_card(cmd, 0, 0, 0);
	cmd = clean_cmd_tab(cmd);
	if (!cmd)
		error(NULL);
	path = get_path(env, cmd[0]);
	if (!path)
	{
		write(2, cmd[0], strlen(cmd[0]));
		prerror(" : command not found\n");
		d_free(cmd);
		exit(127);
	}
	if (access(path, F_OK) == -1)
	{
		perror(cmd[0]);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		perror(cmd[0]);
		exit(126);
	}
	if (opendir(path))
	{
		write(2, path, strlen(path));
		prerror(" : Is a directory\n");
		exit(126);
	}
	if (execve(path, cmd, env) == -1)
		error(cmd[0]);
}

void	exec_cmd(t_data *data, t_node *node)
{
	pid_t	pid;
	int		e;

	if (is_builtin(node->cmd[0]))
		return (builtin(data, node));
	e = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (open_files(node))
			exit(1);
		if (node->fd_in != -1)
			dup2(node->fd_in, STDIN_FILENO);
		if (node->fd_out != -1)
			dup2(node->fd_out, STDOUT_FILENO);
		execute(data, node->cmd, data->env);
	}
	waitpid(pid, &e, 0);
	g_exit = WEXITSTATUS(e);
	unlink(".heredoc");
}

void	exec_builtin(t_data *data, t_node *node)
{
	int	sstdin;
	int	sstdout;

	sstdin = dup(STDIN_FILENO);
	sstdout = dup(STDOUT_FILENO);
	dup2(STDOUT_FILENO, sstdout);
	dup2(STDIN_FILENO, sstdin);
	open_files(node);
	if (node->fd_in != -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
		dup2(node->fd_out, STDOUT_FILENO);
	builtin(data, node);
	dup2(sstdin, STDIN_FILENO);
	dup2(sstdout, STDOUT_FILENO);
	close(sstdin);
	close(sstdout);
}

void	exec2(t_data *data, t_node *node)
{
	if (is_builtin(node->cmd[0]))
		exec_builtin(data, node);
	else
		exec_cmd(data, node);
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
	if (g_exit)
		exec(data, right);
}

void	exec_and(t_data *data, t_node *left, t_node *right)
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
		exec2(data, node);
	else if (node->type == PIPE)
		exec_pipe(data, node->left, node->right);
	else if (node->type == DBL_PIPE)
		exec_or(data, node->left, node->right);
	else if (node->type == AMP)
		return ;
	else if (node->type == DBL_AMP)
		exec_and(data, node->left, node->right);
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		exec(data, node->left);
}
