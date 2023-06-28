/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:29:45 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/27 15:46:42 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_other(char **s)
{
	int		quote;
	char	*str;

	if (!(**s))
		return (NULL);
	quote = 0;
	str = ft_calloc(4096, sizeof(char));
	if (!str)
		return (NULL);
	while (**s)
	{
		if ((!quote && ft_strchr("\t\n\v\f\r <>|&();", **s)))
			break ;
		ft_strncat(str, *s, 1);
		quote_status(**s, &quote);
		*s += 1;
	}
	return (str);
}

char	*next_token(char **s)
{
	while (**s && ft_strchr("\t\n\v\f\r ", **s))
		*s += 1;
	if (!ft_strncmp(*s, "||", 2))
		return (*s += 2, ft_strdup("||"));
	else if (!ft_strncmp(*s, "&&", 2))
		return (*s += 2, ft_strdup("&&"));
	else if (!ft_strncmp(*s, ">>", 2))
		return (*s += 2, ft_strdup(">>"));
	else if (!ft_strncmp(*s, "<<", 2))
		return (*s += 2, ft_strdup("<<"));
	else if (**s == '|')
		return (*s += 1, ft_strdup("|"));
	else if (**s == '&')
		return (*s += 1, ft_strdup("&"));
	else if (**s == '>')
		return (*s += 1, ft_strdup(">"));
	else if (**s == '<')
		return (*s += 1, ft_strdup("<"));
	else if (**s == '(')
		return (*s += 1, ft_strdup("("));
	else if (**s == ')')
		return (*s += 1, ft_strdup(")"));
	else if (**s == ';')
		return (*s += 1, ft_strdup(";"));
	return (handle_other(s));
}

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

	if (!(*s))
		return (NULL);
	tmp = *s;
	lst = NULL;
	new = get_token(&tmp);
	if (!new)
		return (NULL);
	while (new)
	{
		lstadd(&lst, new);
		new = get_token(&tmp);
	}
	return (lst);
}
