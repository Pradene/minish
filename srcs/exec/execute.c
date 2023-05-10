/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/10 15:30:23 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(char *limiter)
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
}

int	open_files(t_node *node)
{
	if (node->out || node->out2)
		close(node->fd_out);
	if (node->out)
		node->fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (node->out2)
		node->fd_out = open(node->out2, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if ((node->out || node->out2) && node->fd_out == -1)
		return (1);
	if (node->in || node->in2)
		close(node->fd_in);
	if (node->in)
		node->fd_in = open(node->in, O_RDONLY, 0777);
	if (node->in && node->fd_in == -1)
		return (1);
	if (node->in2)
		heredoc(node->in2);
	return (0);
}

void	execute(t_data *data, char **cmd, char **env)
{
	char	**cmd_line;
	char	*path;

	cmd_line = lex(cmd, data->env);
	cmd_line = wild_card(cmd_line, 0, 0, 0);
	cmd_line = clean_cmd_tab(cmd_line);
	if (!cmd_line)
		error(NULL);
	path = get_path(env, cmd_line[0]);
	if (!path)
	{
		write(2, cmd_line[0], strlen(cmd_line[0]));
		prerror(" : command not found\n");
		d_free(cmd_line);
		exit(127);
	}
	if (access(path, F_OK) == -1)
	{
		perror(cmd_line[0]);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		perror(cmd_line[0]);
		exit(126);
	}
	if (opendir(path))
	{
		write(2, path, strlen(path));
		prerror(" : Is a directory\n");
		exit(126);
	}
	if (execve(path, cmd_line, env) == -1)
		error(cmd_line[0]);
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
		if (node->in2)
			node->fd_in = open(".heredoc", O_RDONLY, 0777);
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
		printf("Error\n");
	else if (node->type == DBL_AMP)
		exec_and(data, node->left, node->right);
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		exec(data, node->left);
}
