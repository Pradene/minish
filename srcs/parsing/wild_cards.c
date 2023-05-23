/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:58 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/23 16:01:14 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #include <dirent.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>

// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strnstr(const char *big, const char *little, size_t len);
// int	ft_strlen(const char *str);
// void	*ft_calloc(size_t nmemb, size_t size);
// int	ft_strncmp(const char *s1, const char *s2, int n);

// static void	quote_status(char c, int *quote)
// {
// 	if ((*quote == 1 && c == '\'')
// 		|| (*quote == 2 && c == '\"'))
// 		*quote = 0;
// 	else if (*quote == 0 && c == '\'')
// 		*quote = 1;
// 	else if (*quote == 0 && c == '\"')
// 		*quote = 2;
// 	else
// 		return ;
// }
//  */

// int	looking_for_a_star(char *s)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (i < ft_strlen(s))
// 	{
// 		if (s[i] == '*')
// 			count++;
// 		i++;
// 	}
	// printf("d\n");
// 	return (count);
// }

// char	**add_dir(char *s, char **tab, int d_number)
// {
// 	int	i;

// 	i = 0;
// 	d_number++;
// 	while (tab[i])
// 		i++;
// 	tab[i] = ft_strdup(s);
// 	return (tab);
// }

// char	**fill_motif(char *cmd, char **motif, int m_count)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (cmd[i] == '*')
// 		i++;
// 	while (k < m_count)
// 	{
// 		j = i;
// 		while (cmd[i] && cmd[i] != '*')
// 			i++;
// 		motif[k] = ft_substr(cmd, j, i - j);
// 		k++;
// 		while (cmd[i] == '*')
// 			i++;
// 	}
// 	return (motif);
// }

// char	**create_motif(char *cmd, char **motif)
// {
// 	int	i;
// 	int	m_count;

// 	i = 0;
// 	m_count = 0;
// 	while (cmd[i])
// 	{
// 		while (cmd[i] == '*')
// 			i++;
// 		if (cmd[i] && !ft_strchr(" \'\"", cmd[i]))
// 			m_count++;
// 		else
// 			break ;
// 		while (cmd[i] && cmd[i] != '*')
// 			i++;
// 	}
// 	motif = ft_calloc(sizeof(char *), m_count + 1);
// 	return (fill_motif(cmd, motif, m_count));
// }

// int	motif_size(char **motif)
// {
// 	int	i;

// 	i = 0;
// 	if (!motif)
// 		return (0);
// 	while (motif[i])
// 		i++;
// 	return (i);
// }

// int	corresponding_dir(char *dir, char **motif, int stars)
// {
// 	int		i;
// 	int		j;
// 	char	*k;

// 	i = 0;
// 	j = 0;
// 	if (!motif)
// 		return (1);
// 	if ((stars == 0 || stars == 2) && motif[0])
// 	{
// 		if (ft_strncmp(motif[0], dir, ft_strlen(motif[0])) != 0)
// 			return (0);
// 		else
// 		{
// 			i = ft_strlen(motif[0]) - 1;
// 			j = 1;
// 		}
// 	}
// 	while (j < motif_size(motif))
// 	{
// 		if (j == motif_size(motif) - 1 && (stars == 0 || stars == 1))
// 		{
// 			if (ft_strncmp(motif[motif_size(motif) - 1], &dir[ft_strlen(dir)
// 						- ft_strlen(motif[motif_size(motif) - 1])],
// 					ft_strlen(motif[motif_size(motif) - 1])) != 0)
// 				return (0);
// 			else
// 				return (1);
// 		}
// 		else
// 		{
// 			k = ft_strnstr(&dir[i], motif[j], ft_strlen(dir) - i);
// 			if (!k)
// 				return (0);
// 			else
// 			{
// 				dir = k + ft_strlen(motif[j]);
// 				j++;
// 				i = 0;
// 			}
// 		}
// 	}
// 	return (1);
// }

// int	handle_star(char *cmd)
// {
// 	if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] != '*')
// 		return (0);
// 	else if (cmd[0] == '*' && cmd[ft_strlen(cmd) - 1] != '*')
// 		return (1);
// 	else if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] == '*')
// 		return (2);
// 	else
// 		return (3);
// }

// char	**wild_carder(char *cmd)
// {
// 	struct dirent	*lecture;
// 	DIR				*rep;
// 	char			**ans;
// 	char			**motif;
// 	static int		d_number = 0;

// 	motif = NULL;
// 	rep = NULL;
// 	motif = create_motif(cmd, motif);
// 	rep = opendir(".");
// 	ans = ft_calloc(sizeof(char *), 4096);
// 	if (!ans)
// 		return (NULL);
// 	lecture = readdir(rep);
// 	while (lecture)
// 	{
// 		if (d_number > 4095)
// 			break ;
// 		if (corresponding_dir(lecture->d_name, motif, handle_star(cmd)))
// 			add_dir(lecture->d_name, ans, d_number++);
// 		lecture = readdir(rep);
// 	}
// 	closedir(rep);
// 	dfree(motif);
// 	return (ans);
// }

// int	tab_size(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 		i++;
// 	return (i);
// }

// int	cmd_nbrs(char **cmds)
// {
// 	int i;

// 	i = 0;
// 	while (cmds[i])
// 		i++;
// 	return (i);
// }

// char **wild_card2(char **old_cmd, char **dirs, int i, int j, int k)
// {
// 	char	**new_cmd;
// 	int		n;

// 	new_cmd = ft_calloc(tab_size(dirs) + tab_size(old_cmd) + 1, sizeof(char *));
// 	while (j < i)
// 	{
// 		new_cmd[j] = old_cmd[j];
// 		j++;
// 	}
// 	while (dirs[k])
// 	{
// 		new_cmd[j] = dirs[k];
// 		k++;
// 		j++;
// 	}
// 	free(dirs);
// 	n = i + 1;
// 	i = j - 1;
// 	while (old_cmd[n])
// 	{
// 		new_cmd[j] = old_cmd[n];
// 		j++;
// 		n++;
// 	}
// 	return (new_cmd);
// }

// char	**wild_card(char **cmds, int i)
// {
// 	char	**new_cmd;
// 	char	**old_cmd;
// 	char	**dirs;

// 	if (!cmds)
// 		return (cmds);
// 	old_cmd = cmds;
// 	while (old_cmd[i])
// 	{
// 		if (old_cmd[i] && ft_strchr(old_cmd[i], '*')
// 			&& (!ft_strchr(old_cmd[i], '\'') && !ft_strchr(old_cmd[i], '\"')))
// 		{
// 			dirs = wild_carder(old_cmd[i]);
// 			if (dirs[0])
// 			{
// 				new_cmd = wild_card2(old_cmd, dirs, i, 0, 0);
// 				free(old_cmd);
// 				old_cmd = new_cmd;
// 			}
// 			else
// 				free(dirs);
// 		}
// 		i++;
// 	}
// 	return (old_cmd);
// }

int	get_slash(char *path)
{
	int		index;
	int		slash;
	int		tmp;

	index = (int)(strchr(path, '*') - path);
	slash = (int)(strchr(path, '/') - path);
	if (slash < 0 || slash > index)
		return (-1);
	while (1)
	{
		tmp = (int)(strchr(path + slash + 1, '/') - path);
		if (tmp > 0 && tmp < index)
			slash = tmp;
		else
			break ;
	}
	return (slash);
}

char	*substr(char *s, int n)
{
	char	*new;

	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	new[n] = '\0';
	memcpy(new, s, n);
	return (new);
}

char	*find_path(char *path)
{
	char	*new;
	int		index;

	index = get_slash(path);
	if (index == -1)
	{
		new = strdup(".");
		if (!new)
			return (NULL);
		return (new);
	}
	new = substr(path, index + 1);
	if (!new)
		return (path);
	return (new);
}

char	*get_subdir(char *path)
{
	int		start;
	int		end;
	char	*new;

	start = get_slash(path) + 1;
	end = start;
	while (path[end] && path[end] != '/')
		end += 1;
	new = substr(path + start, end - start);
	if (!new)
		return (NULL);
	return (new);
}

int	match(char *pattern, char *s)
{
	int		i;
	char	**ss;
	int		index;
	char	*tmp;
	int		size;

	ss = ft_split(pattern, '*');
	if (!ss)
		return (0);
	i = -1;
	size = strlen(s);
	if (pattern[0] != '*')
		size = strlen(ss[0]);
	index = 0;
	while (ss[++i])
	{
		tmp = ft_strnstr(s + index, ss[i], size);
		if (!tmp)
			return (dfree(ss), 0);
		index = tmp - s + 1;
		size = strlen(s) - index;
		if (i + 1 == dsize(ss) - 1 && pattern[strlen(pattern) - 1] != '*')
		{
			index = strlen(s) - strlen(ss[i + 1]);
			size = strlen(ss[i + 1]);
		}
	}
	dfree(ss);
	return (1);
}

void	get_dir(t_list *lst)
{
	struct dirent	*current;
	t_list			*e;
	DIR				*dir;
	char			*path;
	char			*s;
	char			*new;
	t_list			*tmp;
	int				count;
	char			*last;
	int				index;
	DIR				*dirlo;

	e = lst;
	while (e)
	{
		count = 1;
		while (count && strchr(e->s, '*') && \
		!strchr(e->s, '\'') && !strchr(e->s, '\"'))
		{
			index = strchr(e->s, '*') - e->s;
			last = strchr(e->s + index, '/');
			tmp = e->next;
			e->next = NULL;
			path = find_path(e->s);
			if (!path)
				break ;
			dir = opendir(path);
			if (dir)
			{
				count = 0;
				s = get_subdir(e->s);
				current = readdir(dir);
				while (current)
				{
					if (strcmp(current->d_name, ".") \
					&& strcmp(current->d_name, ".."))
					{
						if (match(s, current->d_name))
						{
							if (strcmp(path, "."))
								new = ft_strjoin(path, current->d_name);
							else
								new = strdup(current->d_name);
							dirlo = opendir(new);
							if (last && dirlo)
								new = ft_stradd(new, last);
							if (dirlo)
								closedir(dirlo);
							if (!count)
							{
								free(e->s);
								e->s = new;
							}
							else
								lstadd(&e, lstnew(new));
							count += 1;
						}
					}
					current = readdir(dir);
				}
				free(s);
				closedir(dir);
			}
			free(path);
			lstlast(e)->next = tmp;
		}
		e = e->next;
	}
}

t_list	*arrtolst(char **ss)
{
	int		i;
	t_list	*lst;
	t_list	*new;

	i = -1;
	lst = NULL;
	while (ss[++i])
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (lstclear(&lst), NULL);
		new->s = strdup(ss[i]);
		new->next = NULL;
		lstadd(&lst, new);
	}
	dfree(ss);
	return (lst);
}

char	**lsttoarr(t_list **lst)
{
	t_list	*e;
	char	**cmds;
	int		i;
	int		size;

	e = *lst;
	size = lstsize(e);
	cmds = malloc(sizeof(char *) * (size + 1));
	if (!cmds)
		return (lstclear(lst), NULL);
	cmds[size] = NULL;
	i = -1;
	while (e)
	{
		cmds[++i] = strdup(e->s);
		e = e->next;
	}
	lstclear(lst);
	return (cmds);
}

char	**wild_card(t_data *data, char **cmds)
{
	char	**new;
	t_list	*lst;

	(void)data;
	if (!cmds)
		return (NULL);
	new = NULL;
	lst = arrtolst(cmds);
	if (!lst)
		return (NULL);
	get_dir(lst);
	new = lsttoarr(&lst);
	free(lst);
	return (new);
}