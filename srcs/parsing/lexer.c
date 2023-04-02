/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/03/28 01:54:25 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_new_cmd(int i, int j, char *lex, char *cmds)
{
	char	*ans;
	char	*var;

	var = getenv(ft_substr(cmds, i, j - i));
	printf("subvar: %s\n", ft_substr(cmds, i, j - i));
	printf("var: %s\n", var);
	if (!lex)
	{
		ans = ft_strjoin(ft_substr(cmds, 0, i - 1), var);
		ans = ft_strjoin(ans, ft_substr(cmds, j, ft_strlen(cmds - j)));
	}
	else
	{
		ans = ft_strjoin(ft_substr(lex, 0, i - 1), var);
		ans = ft_strjoin(ans, ft_substr(cmds, j, ft_strlen(cmds - j)));
	}
	printf("cd: %s\n", ans);
	return (ans);
}

char	*lexer(char *command)
{
	int		i;
	int		j;
	char	*lexed_cmds;

	i = 0;
	lexed_cmds = NULL;
	while (command[i])
	{
		if (command[i] == '$')
		{
			j = i + 1;
			if (ft_strchr(" ?", command[j]))
				i++;
			else
			{
				while (!ft_strchr(" ", command[j]))
					j++;
				lexed_cmds = fill_new_cmd(i + 1, j, lexed_cmds, command);
			}
		}
		i++;
	}
	if (lexed_cmds)
		return (lexed_cmds);
	else
		return (command);
}
