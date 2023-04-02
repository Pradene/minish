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

static char	*handle_other(char *s, int *i)
{
	int		quote;
	int		tmp;
	char	*str;

	quote = 0;
	str = calloc(4096, sizeof(char));
	if (!str)
		return (NULL);
	while (s[*i])
	{
		tmp = quote;
		quote_status(s[*i], &quote);
		if (tmp == quote)
			strncat(str, &s[*i], 1);
		if ((!quote && strchr(" <>|", s[*i + 1])) || !s[*i + 1])
			break ;
		*i += 1;
	}
	return (str);
}

static char	*next_token(char *s, int *i)
{
	if (!strncmp(&s[*i], ">>", 2))
		return (*i += 1, strdup(">>"));
	else if (!strncmp(&s[*i], "<<", 2))
		return (*i += 1, strdup("<<"));
	else if (s[*i] == '|')
		return (strdup("|"));
	else if (s[*i] == '>')
		return (strdup(">"));
	else if (s[*i] == '<')
		return (strdup("<"));
	else
		return (handle_other(s, i));
	return (NULL);
}

void	get_tokens(t_list **tokens, char *s)
{
	int		i;
	t_list	*arg;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ' ')
			continue ;
		arg = malloc(sizeof(t_list));
		if (!arg)
			return ;
		arg->s = next_token(s, &i);
		arg->next = NULL;
		ft_lstadd(tokens, arg);
	}
}
