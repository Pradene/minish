/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:41:58 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/22 15:46:29 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "env"))
		return (1);
	else if (!ft_strcmp(s, "exit"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	return (0);
}

void	builtin(t_data *data, t_node *node)
{
	if (!ft_strcmp(node->cmd[0], "cd"))
		cd(data, node);
	else if (!ft_strcmp(node->cmd[0], "echo"))
		echo(node);
	else if (!ft_strcmp(node->cmd[0], "env"))
		env(data, node);
	else if (!ft_strcmp(node->cmd[0], "exit"))
		ex(data, node);
	else if (!ft_strcmp(node->cmd[0], "export"))
		data->env = export(data, node);
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		pwd(data, node);
	else if (!ft_strcmp(node->cmd[0], "unset"))
		data->env = unset(data, node);
	return ;
}
