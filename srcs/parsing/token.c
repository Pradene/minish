/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:29:45 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:30:00 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	quote_status(char c, int *quote)
{
	if ((*quote == 1 && c == '\'')
		|| (*quote == 2 && c == '\"'))
		*quote = 0;
	else if (*quote == 0 && c == '\'')
		*quote = 1;
	else if (*quote == 0 && c == '\"')
		*quote = 2;
	else
		return ;
}

static char	*handle_other(char **s)
{
	int		quote;
	int		tmp;
	char	*str;

	if (!(**s))
		return (NULL);
	quote = 0;
	str = calloc(4096, sizeof(char));
	if (!str)
		return (NULL);
	while (**s)
	{
		tmp = quote;
		quote_status(**s, &quote);
		if ((!quote && strchr("\t\n\v\f\r <>|&();", **s)))
			break ;
		if (tmp == quote)
			strncat(str, *s, 1);
		*s += 1;
	}
	return (str);
}

char	*next_token(char **s)
{
	while (**s && strchr("\t\n\v\f\r ", **s))
		*s += 1;
	if (!strncmp(*s, "||", 2))
		return (*s += 2, strdup("||"));
	else if (!strncmp(*s, "&&", 2))
		return (*s += 2, strdup("&&"));
	else if (!strncmp(*s, ">>", 2))
		return (*s += 2, strdup(">>"));
	else if (!strncmp(*s, "<<", 2))
		return (*s += 2, strdup("<<"));
	else if (**s == '|')
		return (*s += 1, strdup("|"));
	else if (**s == '&')
		return (*s += 1, strdup("&"));
	else if (**s == '>')
		return (*s += 1, strdup(">"));
	else if (**s == '<')
		return (*s += 1, strdup("<"));
	else if (**s == '(')
		return (*s += 1, strdup("("));
	else if (**s == ')')
		return (*s += 1, strdup(")"));
	else if (**s == ';')
		return (*s += 1, strdup(";"));
	else
		return (handle_other(s));
}
