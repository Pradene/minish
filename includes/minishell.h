/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:31:12 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:31:14 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>

# include <sys/wait.h>

# include <signal.h>

# include <stdbool.h>

# include <termios.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 4096

extern int	g_exit;

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}	t_list;

typedef enum e_type
{
	ERR = 0,
	CMD,
	PIPE,
	DBL_PIPE,
	AMP,
	DBL_AMP,
	SEMICOL,
	OPEN_BRACKET,
	CLOSE_BRACKET,
}	t_type;

typedef struct s_node
{
	t_type			type;
	char			**cmd;
	char			*in;
	char			*in2;
	char			*out;
	char			*out2;
	int				fd_in;
	int				fd_out;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_data
{
	char	**env;
	t_node	*root;
}	t_data;

// UTILS
void	ft_bzero(char *s, int n);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *s);
void	ft_strcpy(char *s1, char *s2, int n);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, int n);
char	*ft_strcat(char *s1, char *s2);
char	*ft_stradd(char *s1, char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void	ft_lstprint(t_list *lst);

// MINISHELL
void	error(char *msg);
int		cmp_env(char *env, char *key);
char	*get_env(char **env, char *s);
char	**envcp(char **envp);
int		last_index(char *s, int c);
char	*get_prompt(void);
void	sig_handler(int sig);
void	set_attribute(void);
void	d_free(char **ss);
int		get_size(char **ss);

// PARSER
void	parse(t_node **root, char **s);

// TREE
t_node	*create_node(t_list *lst, int first, int last);
t_node	*create_tree(t_list *lst, int first, int last);
void	print_tree(t_node *node);
void	free_node(t_node *node);

// TOKENS
t_list	*tokens(char **s);

// LEXER
char	**lexer(char **command);

// EXEC
void	exec(t_data *data, t_node *node);
char	*get_path(char **env, char *cmd);
void	get_cmd(t_data *data);

// BUILT-IN
int		is_builtin(char *s);
void	builtin(t_data *data, t_node *node);
void	cd(t_data *data, t_node *node);
void	echo(t_data *data, t_node *node);
void	env(t_data *data, t_node *node);
void	ex(t_data *data, t_node *node);
char	**export(t_data *data, t_node *node);
void	pwd(t_data *data, t_node *node);
char	**unset(t_data *data, t_node *node);

#endif
