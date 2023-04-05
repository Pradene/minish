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
