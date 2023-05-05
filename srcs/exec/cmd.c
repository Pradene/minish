/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:11:08 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 22:11:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *s)
{
	int	i;
	int	status;

	if (!s)
		return (0);
	i = -1;
	status = 0;
	while (s[++i])
	{
		if (!status && s[i] == '\"')
			status = 2;
		else if (!status && s[i] == '\'')
			status = 1;
		else if ((status == 1 && s[i] == '\'')
			|| (status == 2 && s[i] == '\"'))
			status = 0;
	}
	return (status);
}

void	get_cmd(t_data *data)
{
	char	*prompt;
	char	*s;

	prompt = get_prompt();
	if (!prompt)
		error(NULL);
	s = readline(prompt);
	free(prompt);
	if (!s)
		exit(g_exit);
	add_history(s);
	if (check_quotes(s))
		return (printf("Error\n"), free(s));
	parse(&data->root, &s);
	// print_tree(data->root);
	exec(data, data->root);
	free_node(data->root);
	data->root = NULL;
	free(s);
}
