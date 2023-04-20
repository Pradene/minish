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

void	execute(char *command, char **env)
{
	char	*cmd_line;
	char	**cmds;
	char	*path;
	int		i;

	cmd_line = lexer(command);
	cmds = ft_split(cmd_line, ' ');
	if (!cmds)
		error(NULL);
	path = get_path(env, cmds[0]);
	if (!path)
	{
		printf("%s: command not found\n", cmds[0]);
		i = -1;
		while (cmds[++i])
			free(cmds[i]);
		free(cmds);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmds, env) == -1)
		error(cmds[0]);
}

void	exec_cmd(t_data *data, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execute(node->s, data->env);
	else
		wait(NULL);
}

void	exec_pipe(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	exec(data, right);
}

void	exec_semicol(t_data *data, t_node *left, t_node *right)
{
	exec(data, left);
	exec(data, right);
}

void	exec(t_data *data, t_node *node)
{
	if (node->type == CMD)
		exec_cmd(data, node);
	else if (node->type == PIPE)
		exec_pipe(data, node->left, node->right);
	else if (node->type == DBL_PIPE)
		printf("Implementation to do\n");
	else if (node->type == AMP)
		printf("Implementation to do\n");
	else if (node->type == DBL_AMP)
		printf("Implementation to do\n");
	else if (node->type == SEMICOL)
		exec_semicol(data, node->left, node->right);
	else if (node->type == OPEN_BRACKET)
		printf("Implementation to do\n");
	else if (node->type == CLOSE_BRACKET)
		printf("Implementation to do\n");
}
