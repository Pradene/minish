/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:27:04 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 15:27:07 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		change_fd(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
		change_fd(node->fd_out, STDOUT_FILENO);
	builtin(data, node);
	dup2(data->fd0, STDIN_FILENO);
	dup2(data->fd1, STDOUT_FILENO);
	close(data->fd0);
	close(data->fd1);
}