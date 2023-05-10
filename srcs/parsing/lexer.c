/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/10 15:30:38 by tmalless         ###   ########.fr       */
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

char	*fill_var2(char *v_decl, int i, int j, int size)
{
	char	*var;
	int		k;

	k = 0;
	var = ft_calloc(size + 1, sizeof(char));
	if (!var)
		return (NULL);
	while (j < i)
	{
		var[k] = v_decl[j];
		k++;
		j++;
	}
	return (var);
}

char	*fill_var(char *v_decl)
{
	int		i;
	int		j;
	int		size;
	char	*var;

	i = 0;
	size = 0;
	while (v_decl[i] && v_decl[i] != '=')
		i++;
	i++;
	if (v_decl[i] && ft_strchr("\"\'", v_decl[i]))
		i++;
	j = i;
	while (v_decl[i] && !ft_strchr("\"\'", v_decl[i]))
	{
		size++;
		i++;
	}
	var = fill_var2(v_decl, i, j, size);
	return (var);
}

char	*find_var(char **env, char *tmp)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	var = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], tmp, j))
			var = fill_var(env[i]);
		i++;
	}
	return (var);
}

char	*fill_new_cmd(int i, int j, char *cmds, char **env)
{
	char	*ans1;
	char	*ans2;
	char	*var;
	char	*tmp;

	tmp = ft_substr(cmds, i, j - i);
	var = find_var(env, tmp);
	free(tmp);
	tmp = ft_substr(cmds, 0, i - 1);
	ans1 = ft_strjoin(tmp, var);
	free(tmp);
	tmp = ft_substr(cmds, j, ft_strlen(cmds) - j);
	ans2 = ft_strjoin(ans1, tmp);
	free(tmp);
	if (ans1)
		free(ans1);
	free(cmds);
	return (ans2);
}

char	*put_ret(char *cmd, int start, int end, int i, int j)
{
	char	*ret;
	char	*new_cmd;

	ret = ft_itoa(g_exit);
	new_cmd = ft_calloc(ft_strlen(cmd) + ft_strlen(ret) + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (++i < start)
		new_cmd[i] = cmd[i];
	while (ret[++j])
	{
		new_cmd[i] = ret[j];
		i++;
	}
	while (cmd[end++])
	{
		new_cmd[i] = cmd[end];
		i++;
	}
	free(cmd);
	free(ret);
	return (new_cmd);
}

char	*lexer(char *command, char **env, int i, int j)
{
	int		quotes;

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
			if (command[j] == '?' && quotes != 1)
				command = put_ret(command, i, j, -1, -1);
			else if (!ft_strchr(" \"\'?", command[j]) && quotes != 1)
			{
				while (command[j] && !ft_strchr("$ \'\"", command[j]))
					j++;
				command = fill_new_cmd(i + 1, j, command, env);
			}
		}
		i++;
	}
	return (command);
}

char	**lex(char **cmds, char **env)
{
	int	i;

	i = -1;
	while (cmds[++i])
		cmds[i] = lexer(cmds[i], env, 0, 0);
	return (cmds);
}
