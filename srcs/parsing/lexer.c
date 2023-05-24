/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/11 10:07:49 by tmalless         ###   ########.fr       */
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

int	get_index(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"' || s[i] == ' ')
			break ;
	}
	return (i);
}

char	*handle_dollar(t_data *data, char *cmd, int *c)
{
	int		i;
	int		size;
	char	*value;
	char	*key;

	i = 0;
	key = NULL;
	value = NULL;
	while (cmd[++i])
	{
		if (cmd[i] != '\'' && cmd[i] != '\"' && cmd[i] != ' ')
		{
			size = get_index(&cmd[i]);
			key = strndup(&cmd[i], size);
			value = get_env(data->env, key);
			free(key);
			(*c) += size;
			return (value);
		}
	}
	return (NULL);
}

char	*addchar(char *s, char c)
{
	int		size;
	char	*new;

	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 1 + 1));
	if (!new)
		return (s);
	memcpy(new, s, size);
	new[size] = c;
	new[size + 1] = '\0';
	if (s)
		free(s);
	return (new);
}

char	*expansion(t_data *data, char *cmd)
{
	char	*new;
	char	*tmp;
	int		quotes;
	int		i;

	if (!cmd)
		return (cmd);
	i = -1;
	quotes = 0;
	new = NULL;
	tmp = NULL;
	while (cmd[++i])
	{
		quote_status(cmd[i], &quotes);
		if (quotes != 1 && cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit);
			if (!tmp)
				continue ;
			new = ft_stradd(new, tmp);
			free(tmp);
			i += 1;
		}
		else if (quotes != 1 && cmd[i] == '$' && cmd[i + 1] \
		&& cmd[i + 1] != '\'' && cmd[i + 1] != '\"' && cmd[i + 1] != ' ')
		{
			tmp = handle_dollar(data, &cmd[i], &i);
			if (!tmp)
				continue ;
			new = ft_stradd(new, tmp);
		}
		else
			new = addchar(new, cmd[i]);
	}
	return (free(cmd), new);
}

char	**expand(t_data *data, char **cmds)
{
	int	i;
	int	j;

	if (!data->env || !cmds)
		return (cmds);
	i = -1;
	j = -1;
	while (cmds[++i])
	{
		cmds[++j] = expansion(data, cmds[i]);
		if (!cmds[j])
			j -= 1;
	}
	cmds[++j] = NULL;
	return (cmds);
}
