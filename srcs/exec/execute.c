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

static void	exec(char *command, char **envp)
{
	char	*cmd_line;
	char	**cmds;
	char	*path;
	int		i;

	cmd_line = lexer(command);
	cmds = ft_split(cmd_line, ' ');
	if (!cmds)
		error(NULL);
	path = get_path(envp, cmds[0]);
	if (!path)
	{
		printf("%s: command not found\n", cmds[0]);
		i = -1;
		while (cmds[++i])
			free(cmds[i]);
		free(cmds);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmds, envp) == -1)
		error(cmds[0]);
}

void	execute(char *command, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec(command, envp);
	else
		wait(NULL);
}
