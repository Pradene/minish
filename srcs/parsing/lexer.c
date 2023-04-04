/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/04 18:07:32 by tmalless         ###   ########.fr       */
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

char	*fill_new_cmd(int i, int j, char *cmds)
{
	char	*ans;
	char	*var;

	var = getenv(ft_substr(cmds, i, j - i));
	printf("subvar: %s\n", ft_substr(cmds, i, j - i));
	printf("var: %s\n", var);
	//if (!lex)
	//{
		ans = ft_strjoin(ft_substr(cmds, 0, i - 1), var);
		ans = ft_strjoin(ans, ft_substr(cmds, j, ft_strlen(cmds) - j));
	//}
	/* else
	{
		ans = ft_strjoin(ft_substr(lex, 0, i - 1), var);
		ans = ft_strjoin(ans, ft_substr(cmds, j, ft_strlen(cmds) - j));
		//free(lex);
	} */
	printf("cd: %s\n", ans);
	return (ans);
}

char	*lexer(char *command)
{
	int		i;
	int		j;
	int		quotes;
	char	*lexed_cmds;

	i = 0;
	lexed_cmds = NULL;
	quotes = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
			quote_status(command[i], &quotes);
		if (command[i] == '$')
		{
			j = i + 1;
			if (!ft_strchr(" ?", command[j]) && quotes != 1)
			{
				while (!ft_strchr(" \'\"", command[j]))
					j++;
				lexed_cmds = fill_new_cmd(i + 1, j, command);
				command = lexed_cmds;
				free(lexed_cmds);
			}
		}
		i++;
	}
	//free(lexed_cmds);
	return (command);
}
