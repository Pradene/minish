/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:41:58 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/18 19:42:06 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *s)
{
	if (!strncmp(s, "cd", 2))
		return (1);
	else if (!strncmp(s, "echo", 4))
		return (1);
	else if (!strncmp(s, "env", 3))
		return (1);
	else if (!strncmp(s, "exit", 4))
		return (1);
	else if (!strncmp(s, "export", 6))
		return (1);
	else if (!strncmp(s, "unset", 5))
		return (1);
	return (0);
}

void	builtin(char ***env, char **cmd)
{
	if (!strncmp(cmd[0], "cd", 2))
		cd(*env, "./srcs");
	else if (!strncmp(cmd[0], "echo", 4))
		echo("echo\n", 0);
	else if (!strncmp(cmd[0], "env", 3))
		print_env(*env);
	else if (!strncmp(cmd[0], "exit", 4))
		ex();
	else if (!strncmp(cmd[0], "export", 6))
		*env = export(*env, "COOL=COOL");
	else if (!strncmp(cmd[0], "unset", 5))
		*env = unset(*env, "COOLe");
	return ;
}
