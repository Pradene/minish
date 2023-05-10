/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:03:13 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/10 15:05:54 by tmalless         ###   ########.fr       */
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

char **clean_cmd_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		tab[i] = clean_cmd(tab[i], -1, -1, 0);
		i++;
	}
	return (tab);
}

char	*clean_cmd(char *cmd, int i, int j , int quote)
{
	char	*new_cmd;

	new_cmd = ft_calloc(ft_strlen(cmd) - 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (cmd[++i])
	{
		if (quote == 0 && ft_strchr("\'\"", cmd[i]))
			quote_status(cmd[i], &quote);
		else if (quote == 1 && cmd[i] == '\'')
			quote_status(cmd[i], &quote);
		else if (quote == 2 && cmd[i] == '\"')
			quote_status(cmd[i], &quote);
		else
			new_cmd[++j] = cmd[i];
	}
	return (new_cmd);
}