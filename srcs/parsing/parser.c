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

t_list	*find_token(t_list *lst, char *token, int *pos, int size)
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

	token = find_token(lst, ";", pos, size);
	if (token)
		return (token);
	token = find_token(lst, "||", pos, size);
	if (token)
		return (token);
	token = find_token(lst, "&&", pos, size);
	if (token)
		return (token);
	token = find_token(lst, "|", pos, size);
	if (token)
		return (token);
	token = find_token(lst, "&", pos, size);
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

t_node	*tree(t_list *lst, int first, int last)
{
	t_list	*token;
	t_list	*e;
	t_node	*new;
	int		pos;

	e = go(lst, first);
	new = new_node();
	if (!new)
		return (NULL);
	pos = -1;
	token = find_sep(e, &pos, last - first);
	if (token)
	{
		if (pos == 0 || pos == last - first - 1)
			return (NULL);
		new->s = strdup(token->s);
		new->left = tree(lst, first, first + pos);
		new->right = tree(lst, first + pos + 1, last);
		if (!new->right || !new->left)
			return (NULL);
	}
	else
	{
		while (first < last)
		{
			new->s = ft_stradd(new->s, strcat(e->s, " "));
			e = e->next;
			first++;
		}
	}
	return (new);
}

void	parse(t_node **root, char **s)
{
	t_list	*lst;

	lst = tokens(s);
	if (!lst)
		return ;
	*root = tree(lst, 0, ft_lstsize(lst));
	if (!(*root))
	{
		ft_lstclear(&lst);
		printf("Error\n");
	}
	ft_lstclear(&lst);
	print_tree(*root);
}
