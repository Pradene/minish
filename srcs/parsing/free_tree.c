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
	if (node && node->type == CMD)
		dfree(node->cmd);
	if (node && (node->type == R_IN \
	|| node->type == R_OUT || node->type == R_OUT2))
		free(node->file);
	if (node && node->fd_in != -1)
		close(node->fd_in);
	if (node && node->fd_out != -1)
		close(node->fd_out);
	if (node && node->right)
		free_node(node->right);
	if (node && node->left)
		free_node(node->left);
	if (!node)
		return ;
	free(node);
	node = NULL;
}

int	size_tree(t_node *node)
{
	if (!node || node->type == R_IN \
	|| node->type == R_OUT || node->type == R_OUT2)
		return (0);
	return (size_tree(node->left) + 1 + size_tree(node->right));
}
