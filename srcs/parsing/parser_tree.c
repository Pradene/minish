/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:33 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 17:58:34 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_redir(t_data *data, t_node *node, t_type type, char *file)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new_node();
	if (!tmp->right)
		return (1);
	tmp = tmp->right;
	tmp_add(&data->tmp, tmp);
	tmp->type = type;
	tmp->file = ft_strdup(file);
	return (0);
}

t_node	*create_leaf(t_data *data, t_list *lst, int first, int last)
{
	t_node	*new;
	t_list	*c;

	if (last - first <= 0)
		return (NULL);
	c = go(lst, first);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
	new->type = CMD;
	while (c && ++first <= last)
	{
		if (isredir(c->s))
		{
			first += 1;
			if (first > last || issep(c->next->s) || isredir(c->next->s))
				return (free_node(new), NULL);
			if (handle_redir(data, new, c->s, c->next->s))
			{
				data->c_heredoc = 1;
				return (free_node(new), NULL);
			}
			c = c->next;
		}
		else
		{
			new->cmd = add_to_cmd(new->cmd, c->s);
			if (!new->cmd)
				return (free_node(new), NULL);
		}
		c = c->next;
	}
	return (new);
}

t_node	*create_child(t_data *data, t_list *lst, int first, int last)
{
	t_node	*new;

	if (search_openbrackets(lst, first, last) != first)
		return (print_error(data, ")"), NULL);
	if (search_closebrackets(lst, first, last) != last - 1)
		return (print_error(data, "("), NULL);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
	new->type = OPEN_BRACKET;
	new->right = new_node();
	if (!new->right)
		return (free_node(new), NULL);
	new->right->type = CLOSE_BRACKET;
	new->left = create_tree(data, lst, first + 1, last - 1);
	if (!new->left)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_node(t_data *data, t_list *lst, int first, int last)
{
	t_list		*token;
	t_list		*c;
	t_node		*new;
	int			pos;

	pos = -1;
	c = go(lst, first);
	token = search_sep(c, &pos, last - first);
	if (!token || pos < 0 || pos > last - first - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
	new->type = get_type(token->s);
	new->left = create_tree(data, lst, first, first + pos);
	if (!new->left)
		return (print_error(data, token->s), free_node(new), NULL);
	new->right = create_tree(data, lst, first + pos + 1, last);
	if (!new->right)
		return (print_error(data, token->s), free_node(new), NULL);
	return (new);
}

t_node	*create_tree(t_data *data, t_list *lst, int first, int last)
{
	t_list	*c;
	t_node	*new;
	int		pos;

	pos = -1;
	new = NULL;
	c = go(lst, first);
	if (search_sep(c, &pos, last - first))
		new = create_node(data, lst, first, last);
	else if (search_openbrackets(lst, first, last) != -1
		|| search_closebrackets(lst, first, last) != -1)
		new = create_child(data, lst, first, last);
	else
		new = create_leaf(data, lst, first, last);
	return (new);
}
