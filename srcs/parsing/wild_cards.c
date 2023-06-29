/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:58 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/29 17:56:04 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	get_slash(char *path)
{
	int		index;
	int		slash;
	int		tmp;

	index = (int)(ft_strchr(path, '*') - path);
	slash = (int)(ft_strchr(path, '/') - path);
	if (slash < 0 || slash > index)
		return (-1);
	while (1)
	{
		tmp = (int)(ft_strchr(path + slash + 1, '/') - path);
		if (tmp > 0 && tmp < index)
			slash = tmp;
		else
			break ;
	}
	return (slash);
}

char	*ssubstr(char *s, int n)
{
	char	*new;

	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	new[n] = '\0';
	ft_memcpy(new, s, n);
	return (new);
}

char	*find_path(char *path)
{
	char	*new;
	int		index;

	index = get_slash(path);
	if (index == -1)
	{
		new = ft_strdup(".");
		if (!new)
			return (NULL);
		return (new);
	}
	new = ssubstr(path, index + 1);
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
	new = ssubstr(path + start, end - start);
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
	index = 0;
	size = ft_strlen(s);
	if (pattern[ft_strlen(pattern) - 1] != '*' \
	&& pattern[0] == '*' && dsize(ss) == 1)
		index = ft_strlen(s) - ft_strlen(ss[0]);
	else if (pattern[0] != '*')
		size = ft_strlen(ss[0]);
	i = -1;
	while (ss[++i])
	{
		tmp = ft_strnstr(s + index, ss[i], size);
		if (!tmp)
			return (dfree(ss), 0);
		index = tmp - s + 1;
		size = ft_strlen(s) - index;
		if (i + 1 == dsize(ss) - 1 && pattern[ft_strlen(pattern) - 1] != '*')
		{
			index = ft_strlen(s) - ft_strlen(ss[i + 1]);
			size = ft_strlen(ss[i + 1]);
		}
	}
	dfree(ss);
	return (1);
}

int	check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	read_dir(DIR *dir, struct dirent *current, t_list *lst, char *path)
{
	char			*subdir;
	char			*last;
	char			*new;
	char			*tmp;
	int				count;

	count = 0;
	new = NULL;
	tmp = ft_strdup(lst->s);
	last = ft_strchr(tmp + (int)(ft_strchr(tmp, '*') - tmp), '/');
	subdir = get_subdir(tmp);
	current = readdir(dir);
	while (current)
	{
		if (ft_strcmp(current->d_name, ".") && ft_strcmp(current->d_name, ".."))
		{
			if (match(subdir, current->d_name))
			{
				if (ft_strcmp(path, "."))
					new = ft_strjoin(path, current->d_name);
				else
					new = ft_strdup(current->d_name);
				if (last && check_dir(new))
					new = ft_stradd(new, last);
				if (!count)
				{
					free(lst->s);
					lst->s = new;
				}
				else
					lstadd(&lst, lstnew(new));
				count += 1;
			}
		}
		current = readdir(dir);
	}
	free(subdir);
	free(tmp);
	return (count);
}

int	wc_in_quotes(char *s)
{
	int	quotes;
	int	i;

	i = -1;
	quotes = 0;
	while (s[++i])
	{
		quote_status(s[i], &quotes);
		if (!quotes && s[i] == '*')
			return (1);
	}
	return (0);
}

void	get_dir(t_list *lst)
{
	t_list			*e;
	DIR				*dir;
	char			*path;
	t_list			*tmp;
	int				count;

	e = lst;
	while (e)
	{
		count = 1;
		while (count && wc_in_quotes(e->s))
		{
			tmp = e->next;
			e->next = NULL;
			path = find_path(e->s);
			if (!path)
				break ;
			dir = opendir(path);
			if (dir)
				(count = read_dir(dir, NULL, e, path), closedir(dir));
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
		new->s = ft_strdup(ss[i]);
		new->next = NULL;
		lstadd(&lst, new);
	}
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
	while (e && i < size)
	{
		cmds[++i] = ft_strdup(e->s);
		e = e->next;
	}
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
		return (cmds);
	dfree(cmds);
	get_dir(lst);
	new = lsttoarr(&lst);
	lstclear(&lst);
	return (new);
} */

char	**wild_card(t_data *data, char **cmds)
{
	(void)data;
	return (cmds);
}

/*

int	looking_for_a_star(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '*')
			count++;
		i++;
	}
	printf("d\n");
	return (count);
}

char	**add_dir(char *s, char **tab, int d_number)
{
	int	i;

	i = 0;
	d_number++;
	while (tab[i])
		i++;
	tab[i] = ft_strdup(s);
	return (tab);
}

char	**fill_motif(char *cmd, char **motif, int m_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i] == '*')
		i++;
	while (k < m_count)
	{
		j = i;
		while (cmd[i] && cmd[i] != '*')
			i++;
		motif[k] = ft_substr(cmd, j, i - j);
		k++;
		while (cmd[i] == '*')
			i++;
	}
	return (motif);
}

char	**create_motif(char *cmd, char **motif)
{
	int	i;
	int	m_count;

	i = 0;
	m_count = 0;
	while (cmd[i])
	{
		while (cmd[i] == '*')
			i++;
		if (cmd[i] && !ft_strchr(" \'\"", cmd[i]))
			m_count++;
		else
			break ;
		while (cmd[i] && cmd[i] != '*')
			i++;
	}
	motif = ft_calloc(sizeof(char *), m_count + 1);
	return (fill_motif(cmd, motif, m_count));
}

int	motif_size(char **motif)
{
	int	i;

	i = 0;
	if (!motif)
		return (0);
	while (motif[i])
		i++;
	return (i);
}

int zeubi(char *dir, char **motif, int stars, int *z)
{
	z[1]--;
	while (++z[1] < motif_size(motif))
	{
		if (z[1] == motif_size(motif) - 1 && (stars == 0 || stars == 1))
		{
			if (ft_strncmp(motif[motif_size(motif) - 1], &dir[ft_strlen(dir)
						- ft_strlen(motif[motif_size(motif) - 1])],
					ft_strlen(motif[motif_size(motif) - 1])) != 0)
				return (0);
			else
				return (1);
		}
		else
		{
			if (!ft_strnstr(&dir[z[0]], motif[z[1]], ft_strlen(dir) - z[0]))
				return (0);
			else
			{
				dir = ft_strnstr(&dir[z[0]], motif[z[1]],
						ft_strlen(dir) - z[0]) + ft_strlen(motif[z[1]]);
				z[0] = 0;
			}
		}
	}
	return (1);
}

int	corresponding_dir(char *dir, char **motif, int stars)
{
	int	z[2];
	int	ret;

	z[0] = 0;
	z[1] = 0;
	if (!motif)
		return (1);
	if ((stars == 0 || stars == 2) && motif[0])
	{
		if (ft_strncmp(motif[0], dir, ft_strlen(motif[0])) != 0)
			return (0);
		else
		{
			z[0] = ft_strlen(motif[0]) - 1;
			z[1] = 1;
		}
	}
	ret = zeubi(dir, motif, stars, z);
	if (ret == 0)
		return (0);
	else
		return (1);
}

int	handle_star(char *cmd)
{
	if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (0);
	else if (cmd[0] == '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (1);
	else if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] == '*')
		return (2);
	else
		return (3);
}

char	**wild_carder(char *cmd)
{
	struct dirent	*lecture;
	DIR				*rep;
	char			**ans;
	char			**motif;
	static int		d_number = 0;

	motif = NULL;
	rep = NULL;
	motif = create_motif(cmd, motif);
	rep = opendir(".");
	ans = ft_calloc(sizeof(char *), 4096);
	if (!ans)
		return (NULL);
	lecture = readdir(rep);
	while (lecture)
	{
		if (d_number > 4095)
			break ;
		if (corresponding_dir(lecture->d_name, motif, handle_star(cmd)))
			add_dir(lecture->d_name, ans, d_number++);
		lecture = readdir(rep);
	}
	closedir(rep);
	dfree(motif);
	return (ans);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	cmd_nbrs(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void wild_card3(char **new_cmd, char **old_cmd, int i, int j)
{
	int	n;

	n = i + 1;
	i = j - 1;
	while (old_cmd[n])
	{
		new_cmd[j] = old_cmd[n];
		j++;
		n++;
	}
}

char **wild_card2(char **old_cmd, char **dirs, int i, int j)
{
	char	**new_cmd;
	int		k;

	k = 0;
	new_cmd = ft_calloc(tab_size(dirs) + tab_size(old_cmd) + 1, sizeof(char *));
	while (j < i)
	{
		new_cmd[j] = old_cmd[j];
		j++;
	}
	while (dirs[k])
	{
		new_cmd[j] = dirs[k];
		k++;
		j++;
	}
	free(dirs);
	wild_card3(new_cmd, old_cmd, i, j);
	return (new_cmd);
}

char	**wild_card(char **cmds, int i)
{
	char	**new_cmd;
	char	**old_cmd;
	char	**dirs;

	if (!cmds)
		return (cmds);
	old_cmd = cmds;
	while (old_cmd[i])
	{
		if (old_cmd[i] && ft_strchr(old_cmd[i], '*')
			&& (!ft_strchr(old_cmd[i], '\'') && !ft_strchr(old_cmd[i], '\"')))
		{
			dirs = wild_carder(old_cmd[i]);
			if (dirs[0])
			{
				new_cmd = wild_card2(old_cmd, dirs, i, 0);
				free(old_cmd);
				old_cmd = new_cmd;
			}
			else
				free(dirs);
		}
		i++;
	}
	return (old_cmd);
}


*/


