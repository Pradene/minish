/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/26 15:37:47 by tmalless         ###   ########.fr       */
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
	char	*ans1;
	char	*ans2;
	char	*var;
	char	*tmp;

	tmp = ft_substr(cmds, i, j - i);
	var = getenv(tmp);
	free(tmp);
	//printf("subvar: %s\n", ft_substr(cmds, i, j - i));
	printf("var: %s\n", var);
	//if (!lex)
	//{
		tmp = ft_substr(cmds, 0, i - 1);
		ans1 = ft_strjoin(tmp, var);
		free(tmp);
		tmp = ft_substr(cmds, j, ft_strlen(cmds) - j);
		ans2 = ft_strjoin(ans1, tmp);
		free(tmp);
		if (ans1)
			free(ans1);
	//}
	/* else
	{
		ans = ft_strjoin(ft_substr(lex, 0, i - 1), var);
		ans = ft_strjoin(ans, ft_substr(cmds, j, ft_strlen(cmds) - j));
		//free(lex);
	} */
	free(cmds);
	printf("cd: %s\n", ans2);
	return (ans2);
}

char	*lexer(char *command)
{
	int		i;
	int		j;
	int		quotes;

	i = 0;
	quotes = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
			quote_status(command[i], &quotes);
		if (command[i] == '$')
		{
			j = i + 1;
			if (j >= ft_strlen(command))
				 break ;
			if (!ft_strchr(" ?", command[j]) && quotes != 1)
			{
				while (command[j] && !ft_strchr("$ \'\"", command[j]))
					j++;
				/* lexed_cmds = fill_new_cmd(i + 1, j, command); */
				command = fill_new_cmd(i + 1, j, command);
			}
		}
		i++;
	}
	//free(lexed_cmds);
	return (command);
}

char	**lex(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		cmds[i] = lexer(cmds[i]);
	return (cmds);
}