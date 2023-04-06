/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:29:28 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:29:29 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_token(char **s)
{
	t_list	*lst;
	char	*tmp;

	tmp = next_token(s);
	if (!tmp)
		return (NULL);
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->s = tmp;
	lst->next = NULL;
	return (lst);
}

t_list	*tokens(char **s)
{
	t_list	*lst;
	t_list	*new;
	char	*tmp;

	tmp = *s;
	lst = NULL;
	new = get_token(&tmp);
	if (!new)
		return (NULL);
	while (new)
	{
		ft_lstadd(&lst, new);
		new = get_token(&tmp);
	}
	return (lst);
}

static t_node	*new_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->s = NULL;
	node->redir_type = NONE;
	node->redir_file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_list	*find(t_list *lst, char *token, int *pos, int size)
{
	t_list	*e;
	int		brackets;
	int		current;

	e = lst;
	current = 0;
	brackets = 0;
	while (e && size--)
	{
		if (!strcmp(e->s, "("))
			brackets++;
		else if (!strcmp(e->s, ")"))
			brackets--;
		else if (!brackets && !strcmp(e->s, token))
		{
			*pos = current;
			return (e);
		}
		e = e->next;
		current++;
	}
	return (NULL);
}

t_list	*find_sep(t_list *lst, int *pos, int size)
{
	t_list	*token;

	token = find(lst, ";", pos, size);
	if (token)
		return (token);
	token = find(lst, "||", pos, size);
	if (token)
		return (token);
	token = find(lst, "&&", pos, size);
	if (token)
		return (token);
	token = find(lst, "|", pos, size);
	if (token)
		return (token);
	token = find(lst, "&", pos, size);
	if (token)
		return (token);
	return (NULL);
}

t_list	*go(t_list *lst, int index)
{
	t_list	*e;

	e = lst;
	while (e && index--)
		e = e->next;
	return (e);
}

t_list	*find_brackets(t_list *lst, int first, int last)
{
	t_list	*e;

	e = go(lst, first);
	while (e && first < last)
	{
		if (!strcmp(e->s, "("))
			return (e);
		e = e->next;
		first++;
	}
	return (NULL);
}

int	search_openbrackets(t_list *lst, int first, int last)
{
	t_list	*current;

	current = go(lst, first);
	while (first < last)
	{
		if (!strcmp(current->s, "("))
			return (first);
		current = current->next;
		first += 1;
	}
	return (-1);
}

int	search_closebrackets(t_list *lst, int first, int last)
{
	t_list	*current;
	int		status;

	status = 0;
	current = go(lst, first);
	while (first < last)
	{
		if (!strcmp(current->s, ")") && status > 0)
			status -= 1;
		if (!strcmp(current->s, ")") && status == 0)
			return (first);
		else if (!strcmp(current->s, "("))
			status += 1;
		current = current->next;
		first += 1;
	}
	return (-1);
}

void	free_node(t_node *node)
{
	free(node->s);
	free(node);
}

t_node	*create_node(t_list *lst, int first, int last)
{
	t_list	*token;
	t_list	*current;
	t_node	*new;
	int		pos;

	pos = -1;
	current = go(lst, first);
	token = find_sep(current, &pos, last - first);
	if (!token || pos <= 0 || pos >= last - first - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	new->s = strdup(token->s);
	if (!new->s)
		return (free(new), NULL);
	new->left = create_tree(lst, first, first + pos);
	if (!new->left)
		return (free_node(new), NULL);
	new->right = create_tree(lst, first + pos + 1, last);
	if (!new->right)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_leaf(t_list *lst, int first, int last)
{
	t_node	*new;
	t_list	*current;

	if (last - first <= 0)
		return (NULL);
	current = go(lst, first);
	new = new_node();
	if (!new)
		return (NULL);
	while (current && first < last)
	{
		new->s = ft_stradd(new->s, strcat(current->s, " "));
		if (!new->s)
			return (NULL);
		current = current->next;
		++first;
	}
	return (new);
}

t_node	*create_child(t_list *lst, int first, int last)
{
	t_node	*new;

	if (search_openbrackets(lst, first, last) != first
		|| search_closebrackets(lst, first, last) != last - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	new->s = strdup("(");
	new->right = new_node();
	if (!new->right)
		return (free_node(new), NULL);
	new->right->s = strdup(")");
	new->left = create_tree(lst, first + 1, last - 1);
	if (!new->left)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_tree(t_list *lst, int first, int last)
{
	t_list	*current;
	t_node	*new;
	int		pos;

	pos = -1;
	new = NULL;
	current = go(lst, first);
	if (find_sep(current, &pos, last - first))
		new = create_node(lst, first, last);
	else if (search_openbrackets(lst, first, last) != -1
		|| search_closebrackets(lst, first, last) != -1)
		new = create_child(lst, first, last);
	else
		new = create_leaf(lst, first, last);
	return (new);
}

void	parse(t_node **root, char **s)
{
	t_list	*lst;

	lst = tokens(s);
	if (!lst)
		return ;
	*root = create_tree(lst, 0, ft_lstsize(lst));
	if (!(*root))
	{
		ft_lstclear(&lst);
		printf("Error\n");
	}
	ft_lstclear(&lst);
	print_tree(*root);
}
