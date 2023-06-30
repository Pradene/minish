/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:36:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:11:28 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_fd(int *old, int new)
{
	dup2(*old, new);
	close(*old);
	*old = -1;
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

void	sig_child(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton(NULL);
	if (!data)
		exit(130);
	free_data(data);
	exit(130);
}
