/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:22:05 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:13:32 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_fd(int *old, int new)
{
	if (*old != -1)
		close(*old);
	*old = new;
}

static int	check_file_error(t_node *node)
{
	if (node->type != HEREDOC && !node->file)
		return (prerror("Ambiguous redirect\n"), 1);
	if (node->type != HEREDOC && ft_strchr(node->file, '*'))
		return (prerror("Ambiguous redirect\n"), 1);
	return (0);
}

static void	open_file(int *fd, char *file, int option)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(file, option, 0777);
}

int	open_rfile(t_node *node, t_node *tmp)
{
	if (tmp->type == R_OUT)
		open_file(&node->fd_out, tmp->file, O_WRONLY | O_CREAT | O_TRUNC);
	if (tmp->type == R_OUT2)
		open_file(&node->fd_out, tmp->file, O_WRONLY | O_CREAT | O_APPEND);
	if ((tmp->type == R_OUT || tmp->type == R_OUT2) && node->fd_out == -1)
		return (perror(tmp->file), 1);
	if (tmp->type == HEREDOC)
		replace_fd(&node->fd_in, tmp->fd_in);
	if (tmp->type == R_IN)
		open_file(&node->fd_in, tmp->file, O_RDONLY);
	if (tmp->type == R_IN && node->fd_in == -1)
		return (perror(tmp->file), 1);
	return (0);
}

int	open_files(t_data *data, t_node *node)
{
	t_node	*tmp;

	tmp = node->right;
	while (tmp)
	{
		tmp->file = expansion(data, tmp->file);
		if (check_file_error(tmp))
			return (1);
		tmp->file = clean_cmd(tmp->file);
		if (tmp->type != HEREDOC && !tmp->file)
			return (1);
		if (open_rfile(node, tmp))
			return (1);
		tmp = tmp->right;
	}
	return (0);
}
