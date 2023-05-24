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
	size = strlen(s);
	if (pattern[0] != '*')
		size = strlen(ss[0]);
	index = 0;
	i = -1;
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
	tmp = strdup(lst->s);
	last = strchr(tmp + (int)(strchr(tmp, '*') - tmp), '/');
	subdir = get_subdir(tmp);
	current = readdir(dir);
	while (current)
	{
		if (strcmp(current->d_name, ".") && strcmp(current->d_name, ".."))
		{
			if (match(subdir, current->d_name))
			{
				if (strcmp(path, "."))
					new = ft_strjoin(path, current->d_name);
				else
					new = strdup(current->d_name);
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
		while (count && strchr(e->s, '*') && \
		!strchr(e->s, '\'') && !strchr(e->s, '\"'))
		{
			tmp = e->next;
			e->next = NULL;
			path = find_path(e->s);
			if (!path)
				break ;
			dir = opendir(path);
			if (dir)
			{
				count = read_dir(dir, NULL, e, path);
				closedir(dir);
			}
			free(path);
			lstlast(e)->next = tmp;
		}
		e = e->next;
	}
}

// void	get_dir(t_list *lst)
// {
// 	struct dirent	*current;
// 	t_list			*e;
// 	DIR				*dir;
// 	char			*path;
// 	char			*s;
// 	char			*new;
// 	t_list			*tmp;
// 	int				count;
// 	char			*last;
// 	int				index;
// 	DIR				*dirlo;

// 	e = lst;
// 	while (e)
// 	{
// 		count = 1;
// 		while (count && strchr(e->s, '*') &&
// 		!strchr(e->s, '\'') && !strchr(e->s, '\"'))
// 		{
// 			index = strchr(e->s, '*') - e->s;
// 			last = strchr(e->s + index, '/');
// 			tmp = e->next;
// 			e->next = NULL;
// 			path = find_path(e->s);
// 			if (!path)
// 				break ;
// 			dir = opendir(path);
// 			if (dir)
// 			{
// 				count = 0;
// 				s = get_subdir(e->s);
// 				current = readdir(dir);
// 				while (current)
// 				{
// 					if (strcmp(current->d_name, ".")
// 					&& strcmp(current->d_name, ".."))
// 					{
// 						if (match(s, current->d_name))
// 						{
// 							if (strcmp(path, "."))
// 								new = ft_strjoin(path, current->d_name);
// 							else
// 								new = strdup(current->d_name);
// 							dirlo = opendir(new);
// 							if (last && dirlo)
// 								new = ft_stradd(new, last);
// 							if (dirlo)
// 								closedir(dirlo);
// 							if (!count)
// 							{
// 								free(e->s);
// 								e->s = new;
// 							}
// 							else
// 								lstadd(&e, lstnew(new));
// 							count += 1;
// 						}
// 					}
// 					current = readdir(dir);
// 				}
// 				free(s);
// 				closedir(dir);
// 			}
// 			free(path);
// 			lstlast(e)->next = tmp;
// 		}
// 		e = e->next;
// 	}
// }

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
}
