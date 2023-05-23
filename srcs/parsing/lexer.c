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

// char	*fill_var2(char *v_decl, int i, int j, int size)
// {
// 	char	*var;
// 	int		k;

// 	k = 0;
// 	var = ft_calloc(size + 1, sizeof(char));
// 	if (!var)
// 		return (NULL);
// 	while (j < i)
// 	{
// 		var[k] = v_decl[j];
// 		k++;
// 		j++;
// 	}
// 	return (var);
// }

// char	*fill_var(char *v_decl)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	*var;

// 	i = 0;
// 	size = 0;
// 	while (v_decl[i] && v_decl[i] != '=')
// 		i++;
// 	i++;
// 	if (v_decl[i] && ft_strchr("\"\'", v_decl[i]))
// 		i++;
// 	j = i;
// 	while (v_decl[i] && !ft_strchr("\"\'", v_decl[i]))
// 	{
// 		size++;
// 		i++;
// 	}
// 	var = fill_var2(v_decl, i, j, size);
// 	return (var);
// }

// char	*find_var(char **env, char *tmp)
// {
// 	int		i;
// 	int		j;
// 	char	*var;

// 	i = 0;
// 	var = NULL;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] != '=')
// 			j++;
// 		if (!ft_strncmp(env[i], tmp, j))
// 			var = fill_var(env[i]);
// 		i++;
// 	}
// 	return (var);
// }

// char	*no_var(char *cmds, int i, int j)
// {
// 	char	*new_cmds;
// 	int		t;

// 	t = 0;
// 	if (ft_strlen(cmds) - (j - i) == 0)
// 		return (NULL);
// 	new_cmds = ft_calloc(ft_strlen(cmds) - (j - i) + 1, sizeof(char));
// 	while (t < i)
// 	{
// 		new_cmds[t] = cmds[t];
// 		t++;
// 	}
// 	while (cmds[j])
// 	{
// 		new_cmds[t] = cmds[j];
// 		t++;
// 		j++;
// 	}
// 	free(cmds);
// 	return (new_cmds);
// }

// char	*fill_new_cmd(int i, int j, char *cmds, char **env)
// {
// 	char	*ans1;
// 	char	*ans2;
// 	char	*var;
// 	char	*tmp;

// 	tmp = ft_substr(cmds, i, j - i);
// 	var = find_var(env, tmp);
// 	free(tmp);
// 	if (!var)
// 		return (no_var(cmds, i - 1, j));
// 	tmp = ft_substr(cmds, 0, i - 1);
// 	ans1 = ft_strjoin(tmp, var);
// 	free(tmp);
// 	tmp = ft_substr(cmds, j, ft_strlen(cmds) - j);
// 	ans2 = ft_strjoin(ans1, tmp);
// 	free(tmp);
// 	if (ans1)
// 		free(ans1);
// 	free(cmds);
// 	return (ans2);
// }

// char	*put_ret(char *cmd, int start, int end)
// {
// 	char	*ret;
// 	char	*new_cmd;
// 	int		i;
// 	int		j;
// 	int		c;

// 	i = -1;
// 	j = -1;
// 	ret = ft_itoa(g_exit);
// 	c = ft_strlen(cmd) + ft_strlen(ret);
// 	new_cmd = ft_calloc(c + 1, sizeof(char));
// 	if (!new_cmd)
// 		return (NULL);
// 	new_cmd[c] = '\0';
// 	while (++i < start)
// 		new_cmd[i] = cmd[i];
// 	while (ret[++j])
// 		new_cmd[i++] = ret[j];
// 	while (cmd[end++])
// 		new_cmd[i++] = cmd[end];
// 	free(cmd);
// 	free(ret);
// 	return (new_cmd);
// }

// char	*lexer(char *command, char **env, int i, int j)
// {
// 	int		quotes;

// 	quotes = 0;
// 	while (command[i])
// 	{
// 		quote_status(command[i], &quotes);
// 		if (command[i] == '$')
// 		{
// 			j = i + 1;
// 			if (j >= ft_strlen(command))
// 				break ;
// 			if (command[j] == '?' && quotes != 1)
// 				command = put_ret(command, i, j);
// 			else if (!ft_strchr(" \"\'?", command[j]) && quotes != 1)
// 			{
// 				while (command[j] && !ft_strchr("$ \'\"", command[j]))
// 					j++;
// 				command = fill_new_cmd(i + 1, j, command, env);
// 			}
// 		}
// 		i++;
// 	}
// 	return (command);
// }

// char	**clean_tab(char **cmd)
// {
// 	int		i;
// 	int		j;
// 	int		empty_box;
// 	char	**new_cmd;

// 	i = 0;
// 	empty_box = 0;
// 	while (cmd[i])
// 	{
// 		if (strlen(cmd[i]) == 1 && cmd[i][0] == ' ')
// 			empty_box++;
// 		i++;
// 	}
// 	if (!empty_box)
// 		return (cmd);
// 	new_cmd = ft_calloc(tab_size(cmd) - empty_box + 1, sizeof(char *));
// 	i = 0;
// 	j = 0;
// 	while (cmd[i])
// 	{
// 		if (strlen(cmd[i]) == 1 && cmd[i][0] == ' ')
// 			i++;
// 		new_cmd[j] = cmd[i];
// 		i++;
// 		j++;
// 	}
// 	return (new_cmd);
// }

// char	**lex(char **cmds, char **env)
// {
// 	int	i;

// 	if (!cmds || !env)
// 		return (cmds);
// 	i = -1;
// 	while (cmds[++i])
// 		cmds[i] = lexer(cmds[i], env, 0, 0);
// 	//cmds = clean_tab(cmds);
// 	return (cmds);
// }

char	*handle_dollar(t_data *data, char *cmd, int *c)
{
	int		i;
	int		j;
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
			j = i;
			while (cmd[j])
			{
				if (cmd[j] == '\'' || cmd[j] == '\"' || cmd[j] == ' ')
					break ;
				j += 1;
			}
			size = j - i;
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
	int 	size;
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
		else if (quotes != 1 && cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != '\'' \
		&& cmd[i + 1] != '\"' && cmd[i + 1] != ' ')
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
