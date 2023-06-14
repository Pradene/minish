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
		return (free_data(data));
	path = get_path(env, node->cmd[0]);
	if (!path)
		command_nfound(data, node->cmd[0]);
	else if (access(path, F_OK) == -1)
		access_error(data, path, node->cmd[0], 127);
	else if (access(path, X_OK) == -1)
		access_error(data, path, node->cmd[0], 126);
	dir = opendir(path);
	if (dir)
		path_isdir(data, path, dir);
	if (execve(path, node->cmd, env) == -1)
		error(node->cmd[0]);
}

void	exec_cmd_child(t_data *data, t_node *node)
{
	signal(SIGINT, sig_child);
	if (open_files(data, node))
	{
		free_data(data);
		exit(1);
	}
	if (node->fd_in != -1)
		change_fd(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
		change_fd(node->fd_out, STDOUT_FILENO);
	if (node->cmd && is_builtin(node->cmd[0]))
	{
		builtin(data, node);
		free_data(data);
		exit(g_exit);
	}
	execute(data, node, data->env);
	exit(EXIT_SUCCESS);
}

void	exec_cmd(t_data *data, t_node *node)
{
	pid_t	pid;
	int		status;
	int		error;

	status = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_cmd_child(data, node);
	error = waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
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
