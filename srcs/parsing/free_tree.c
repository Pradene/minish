/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:33:19 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/22 16:33:21 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *node)
{
	if (!node || node->type == ERR)
		return ;
	else if (node->type == CMD)
		dfree(node->cmd);
	else if (node->type == R_IN || node->type == HEREDOC \
	|| node->type == R_OUT || node->type == R_OUT2)
		free(node->file);
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	if (node->right)
		free_node(node->right);
	if (node->left)
		free_node(node->left);
	free(node);
}

int	size_tree(t_node *node)
{
	if (!node || node->type == R_IN || node->type == HEREDOC \
	|| node->type == R_OUT || node->type == R_OUT2)
		return (0);
	return (size_tree(node->left) + 1 + size_tree(node->right));
}
