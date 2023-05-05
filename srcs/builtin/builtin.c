/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:41:58 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/02 15:37:05 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *s)
{
	if (!strncmp(s, "cd", 2))
		return (1);
	/* else if (!strncmp(s, "echo", 4))
		return (1); */
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

void	builtin(t_data *data, t_node *node)
{
	if (!strncmp(node->cmd[0], "cd", 2))
		cd(data, node);
	/* else if (!strncmp(node->cmd[0], "echo", 4))
		echo(data, node); */
	else if (!strncmp(node->cmd[0], "env", 3))
		print_env(data, node);
	else if (!strncmp(node->cmd[0], "exit", 4))
		ex(data, node);
	else if (!strncmp(node->cmd[0], "export", 6))
		data->env = export(data, node);
	else if (!strncmp(node->cmd[0], "unset", 5))
		data->env = unset(data, node);
	return ;
}
