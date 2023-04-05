/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:20:33 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/05 19:20:34 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_node **node)
{
	if (!(*node))
		return ;
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	free((*node)->s);
}

void	print_tree(t_node *node)
{
	if (!node)
		return ;
	print_tree(node->left);
	printf("%s \n", node->s);
	print_tree(node->right);
}
