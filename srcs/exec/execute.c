/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/23 16:01:38 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_child(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton(NULL);
	free_node(data->root);
	data->root = NULL;
	dfree(data->env);
	exit(130);
}

void	sig_child2(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton(NULL);
	free_node(data->root);
	data->root = NULL;
	dfree(data->env);
	exit(131);
}

void	heredoc(t_data *data, t_node *node, char *limiter)
{
	char	*line;
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
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd[1]);
				free_node(data->root);
				dfree(data->env);
				exit(0);
			}
			if (!strcmp(limiter, line))
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		free(line);
		close(fd[1]);
		free_node(data->root);
		dfree(data->env);
		exit(0);
	}
	waitpid(pid, &e, 0);
	close(fd[1]);
	node->fd_in = fd[0];
}

int	open_files(t_data *data, t_node *node)
{
	t_node	*tmp;

	tmp = node->right;
	while (tmp)
	{
		tmp->file = expansion(data, tmp->file);
		if (!tmp->file)
			return (1);
		tmp->file = clean_cmd(tmp->file);
		if (node->fd_out != -1 && (tmp->type == R_OUT || tmp->type == R_OUT2))
		{
			close(node->fd_out);
			node->fd_out = -1;
		}
		if (tmp->type == R_OUT)
			node->fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp->type == R_OUT2)
			node->fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if ((tmp->type == R_OUT || tmp->type == R_OUT2) && node->fd_out == -1)
		{
			perror(tmp->file);
			return (1);
		}
		if (node->fd_in != -1 && tmp->type == R_IN)
		{
			close(node->fd_in);
			node->fd_in = -1;
		}
		if (tmp->type == R_IN)
			node->fd_in = open(tmp->file, O_RDONLY, 0777);
		if (tmp->type == R_IN && node->fd_in == -1)
		{
			perror(tmp->file);
			return (1);
		}
		if (tmp->type == HEREDOC)
			heredoc(data, node, tmp->file);
		tmp = tmp->right;
	}
	return (0);
}

void	execute(t_data *data, t_node *node, char **env)
{
	char	*path;
	DIR		*dir;

	if (!node->cmd)
		return ;
	path = get_path(env, node->cmd[0]);
	if (!path)
	{
		write(2, node->cmd[0], ft_strlen(node->cmd[0]));
		prerror(" : command not found\n");
		free_node(data->root);
		data->root = NULL;
		dfree(env);
		exit(127);
	}
	else if (access(path, F_OK) == -1)
	{
		perror(node->cmd[0]);
		free_node(data->root);
		data->root = NULL;
		dfree(env);
		free(path);
		exit(127);
	}
	else if (access(path, X_OK) == -1)
	{
		perror(node->cmd[0]);
		free_node(data->root);
		data->root = NULL;
		dfree(env);
		free(path);
		exit(126);
	}
	dir = opendir(path);
	if (dir)
	{
		write(2, path, ft_strlen(path));
		prerror(" : Is a directory\n");
		free_node(data->root);
		closedir(dir);
		data->root = NULL;
		dfree(env);
		free(path);
		exit(126);
	}
	if (execve(path, node->cmd, env) == -1)
		error(node->cmd[0]);
}

void	exec_cmd(t_data *data, t_node *node)
{
	pid_t	pid;
	int		e;
	int		error;

	if (is_builtin(node->cmd[0]))
		return (builtin(data, node));
	e = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, sig_child);
		signal(SIGQUIT, sig_child2);
		if (open_files(data, node))
		{
			// write(2, "No such file or directory\n", 27);
			free_node(data->root);
			data->root = NULL;
			dfree(data->env);
			exit(1);
		}
		if (node->fd_in != -1)
			dup2(node->fd_in, STDIN_FILENO);
		if (node->fd_out != -1)
			dup2(node->fd_out, STDOUT_FILENO);
		execute(data, node, data->env);
	}
	error = waitpid(pid, &e, 0);
	g_exit = WEXITSTATUS(e);
}

void	exec_builtin(t_data *data, t_node *node)
{
	int	sstdin;
	int	sstdout;

	sstdin = dup(STDIN_FILENO);
	sstdout = dup(STDOUT_FILENO);
	dup2(STDOUT_FILENO, sstdout);
	dup2(STDIN_FILENO, sstdin);
	if (open_files(data, node))
	{
		// write(2, "No such file or directory\n", 27);
		close(sstdout);
		close(sstdin);
		g_exit = 1;
		return ;
	}
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
	node->cmd = expand(data, node->cmd);
	node->cmd = wild_card(node->cmd, 0);
	node->cmd = clean_cmds(node->cmd);
	if (!node->cmd || !node->cmd[0])
		return ;
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
		exec_semicol(data, node->left, node->right);
	else if (node->type == DBL_AMP)
		exec_and(data, node->left, node->right);
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		exec(data, node->left);
}
