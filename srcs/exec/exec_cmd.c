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

void	execute(t_data *data, t_node *node, char **env)
{
	char	*path;
	DIR		*dir;

	if (!node->cmd || !node->cmd[0])
		return ;
	path = get_path(env, node->cmd[0]);
	if (!path)
	{
		write(2, node->cmd[0], ft_strlen(node->cmd[0]));
		prerror(" : command not found\n");
		free_data(data);
		exit(127);
	}
	else if (access(path, F_OK) == -1)
	{
		perror(node->cmd[0]);
		free_data(data);
		free(path);
		exit(127);
	}
	else if (access(path, X_OK) == -1)
	{
		perror(node->cmd[0]);
		free_data(data);
		free(path);
		exit(126);
	}
	dir = opendir(path);
	if (dir)
	{
		write(2, path, ft_strlen(path));
		prerror(" : Is a directory\n");
		free_data(data);
		closedir(dir);
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

	e = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, sig_child);
		if (open_files(data, node))
		{
			free_data(data);
			exit(1);
		}
		if (node->fd_in != -1)
		{
			dup2(node->fd_in, STDIN_FILENO);
			close(node->fd_in);
			node->fd_in = -1;
		}
		if (node->fd_out != -1)
		{
			dup2(node->fd_out, STDOUT_FILENO);
			close(node->fd_out);
			node->fd_out = -1;
		}
		if (node->cmd && is_builtin(node->cmd[0]))
		{
			builtin(data, node);
			free_data(data);
			exit(g_exit);
		}
		execute(data, node, data->env);
	}
	error = waitpid(pid, &e, 0);
	g_exit = WEXITSTATUS(e);
}

void	exec_builtin(t_data *data, t_node *node)
{
	if (open_files(data, node))
	{
		g_exit = 1;
		return ;
	}
	data->fd0 = dup(STDIN_FILENO);
	data->fd1 = dup(STDOUT_FILENO);
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
		node->fd_in = -1;
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
		node->fd_out = -1;
	}
	builtin(data, node);
	dup2(data->fd0, STDIN_FILENO);
	dup2(data->fd1, STDOUT_FILENO);
	close(data->fd0);
	close(data->fd1);
}

void	exec_node(t_data *data, t_node *node)
{
	node->cmd = expand(data, node->cmd);
	node->cmd = wild_card(data, node->cmd);
	node->cmd = clean_cmds(node->cmd);
	if (!node)
		return ;
	if (node->cmd && node->fd_in == -1 && node->fd_out == -1 \
	&& is_builtin(node->cmd[0]))
		exec_builtin(data, node);
	else
		exec_cmd(data, node);
}
