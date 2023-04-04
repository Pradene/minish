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

# define BUFFER_SIZE 4096

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}	t_list;

typedef enum e_redir
{
	NONE = 0,
	IN,
	DBL_IN,
	OUT,
	DBL_OUT
}	t_redir;

typedef struct s_cmd
{
	t_list			*arg;
	t_redir			redir;
	char			*rfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_node
{
	char			*s;
	t_redir			redir_type;
	char			*redir_file;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_data
{
	char	**env;
	int		exit;
	t_cmd	*cmds;
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
void	ft_lstadd(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void	ft_lstprint(t_list *lst);

// MINISHELL
void	error(char *msg);
int		cmp_env(char *env, char *key);
char	*get_env(char **env, char *s);
int		last_index(char *s, int c);
char	*get_prompt(void);
void	sig_handler(int sig);
void	set_attribute(void);
void	d_free(char **ss);

// PARSER
void	parse(t_node **root, char *s);

// TOKENS
char	*next_token(char **s);

// LEXER
char	*lexer(char *command);

// EXEC
void	execute(char *command, char **envp);
char	*get_path(char **env, char *cmd);
void	get_cmd(t_data *data);

// BUILT-IN
void	builtin(char ***env, char *s);
void	cd(char **env, char *path);
void	echo(char *s, bool nl);
char	**env(char **envp);
void	print_env(char **env);
void	ex(void);
char	**export(char **env, char *new);
void	pwd(void);
char	**unset(char **env, char *key);

#endif
