/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:40:12 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/18 19:40:14 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*rmdirfrompath(char *path)
{
	char	*s;
	int		index;

	index = last_index(path, '/');
	s = malloc(sizeof(char) * (index + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, path, index);
	free(path);
	s[index] = '\0';
	return (s);
}

static char	*abs_path(char *path)
{
	char	**ss;
	char	*s;
	int		i;

	s = malloc(sizeof(char) * 1024);
	if (!s)
		return (NULL);
	getcwd(s, 1024);
	ss = ft_split(path, '/');
	i = -1;
	while (ss[++i])
	{
		if (ft_strncmp(ss[i], ".", ft_strlen(ss[i])) == 0)
			continue ;
		else if (ft_strncmp(ss[i], "..", ft_strlen(ss[i])) == 0)
			s = rmdirfrompath(s);
		else
			s = ft_stradd(ft_stradd(s, "/"), ss[i]);
	}
	dfree(ss);
	return (s);
}

static char	*cmd_path(char **env, char *command)
{
	char	**s_paths;
	char	*paths;
	char	*path;
	int		i;

	paths = get_env(env, "PATH");
	if (!paths)
		return (NULL);
	s_paths = ft_split(paths, ':');
	if (!s_paths)
		return (NULL);
	i = -1;
	while (s_paths[++i])
	{
		path = ft_stradd(ft_stradd(ft_strdup(s_paths[i]), "/"), command);
		if (access(path, F_OK | X_OK) == 0)
		{
			dfree(s_paths);
			return (path);
		}
		free(path);
	}
	dfree(s_paths);
	return (NULL);
}

char	*get_path(char **env, char *cmd)
{
	char	*path;

	if (!cmd[0])
		return (NULL);
	path = NULL;
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (NULL);
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	else if (!ft_strncmp(cmd, "./", 2))
		path = abs_path(cmd);
	else
		path = cmd_path(env, cmd);
	return (path);
}
