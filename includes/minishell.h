/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:15:22 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 04:29:10 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****************************************************************************
-----------------------------------INCLUDES-----------------------------------
* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ****************************************************************************
------------------------------------TYPEDEF----------------------------------
* ************************************************************************** */

typedef struct s_execution  t_exec;
typedef struct s_parsing    t_parse;
typedef struct s_btin		t_btin;
typedef struct s_builtin	t_builtin;

extern int g_status;

/* ****************************************************************************
------------------------------------DEFINE-----------------------------------
* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define REDIR_IN_FLAG 1

# define REDIR_OUT_FLAG 2

# define HERE_DOC_FLAG 3

# define REDIR_OUT_ADD_FLAG 4

# define CMD_FLAG 5

# define ARGS_FLAG 6

# define PIPE_FLAG 7

# define EMPTY_LINE 8

# define SIMPLE_QUOTE 10

# define DOUBLE_QUOTE 11

# define PARSE_ERROR 12

# define PIPE_ERROR 13

# define FILE_NAME 14

# define DELIM_NAME 15

# define BUILTIN_FLAG 16

# define LAST_PIPE_STATUS 17


/* ****************************************************************************
-------------------------------------ENUM-------------------------------------
* ************************************************************************** */

typedef enum s_bool
{
	false,
	true
}			t_bool;

/* ****************************************************************************
------------------------------------STRUCT------------------------------------
* ************************************************************************** */

typedef struct s_instance
{
	char		**envp;
	char		*line;
	t_builtin	*builtin;
}		t_instance;

typedef struct s_var
{
	char			*varname;
	char			*value;
	struct s_var	*start;
	struct s_var	*next;
}				t_var;

struct s_execution
{
	char	    *cmd[100];
	char	    *in[100];
	char	    *out[100];
    char        *limiter;
    char	    is_append[100];
	t_bool	    is_here_doc;
	t_bool		is_builtin;
	t_exec		*next;
	t_exec		*prev;
};	

struct s_parsing
{
	char	*elem;
	int		flag;
	size_t	pos_dol;
	t_parse	*next;
};

typedef struct s_control_parse
{
	t_parse	*first;
	t_parse	*iter;
	size_t	*size;
}	t_control_parse;

typedef struct s_control_exec
{
	t_exec	*first;
	t_exec	*iter;
	size_t	*size;
}	t_control_exec;

struct s_builtin
{
	t_btin	*first;
	t_btin	*iter;
	size_t	size;
};

struct s_btin
{
	char	*name;
	int		(*fun)(char **arg, t_instance *instance);
	t_btin	*next;
};

typedef struct s_fthenorm
{
	int		i;
	short	in;
	short	out;
}	t_fthenorm;

/* ****************************************************************************
-----------------------------PROTOTYPES FUNCTIONS-----------------------------
* ************************************************************************** */

/* ----- main -------------------------------------------------------------- */

int					free_instance(t_instance *instance, int i);

/* ----- signal ------------------------------------------------------------ */

void			    sig_int_child_handler(int signum);
void			    sig_quit_handler(int signum);
void			    sig_int_handler(int signum);

/* ----- structurization --------------------------------------------------- */

char			    *get_path(char *cmd, char **envp, size_t j);
t_control_exec		*structy(t_control_parse *parse, int nb_pipe, char **envp);

/* ----- redirect ---------------------------------------------------------- */

int					redirect_out(t_exec *cmd);
void				redir_in_error(t_exec *cmd);
int					line_counter(char **aos);
int					here_doc(t_exec *cmd, t_instance *instance);

/* ----- execution --------------------------------------------------------- */

int					execuction(t_exec *cmd, t_instance *instance);
int                 allocator_counter(t_control_parse *parse_list,
						t_exec *node, short in, short out);
char	            **exec_split(char const *s, char c);
int					forklift(t_exec *cmd, t_instance *instance, int fd);
int					chose_exec(t_control_exec *exes, t_instance *instance);

/* ----- utils ------------------------------------------------------------- */

int					control_parse(t_control_parse *truct);
void				exec_cleaner(t_control_exec *exec);
int					test_free(t_control_exec *exec, int nb_pipe);
void			    cmd_free(char **cmd);
size_t			    ft_size(char **array);
char        	    *ft_strnstr(const char *s1, char *s2, size_t n);
char	            *ft_strfreejoin( char *s1,  char *s2);
size_t      	    ft_strlcpy(char *dst,  char *src, size_t dstsize);
int	                ft_memcmp(void *s1, void *s2, size_t n);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_itoa(int n);
size_t				ft_strlen(char *s);
char				**ft_split_it(char *line, char c, size_t i, int q);
int					pipe_counter(t_control_parse *parse);
int					free_exe(t_exec *exec);
int					ft_atoi(char *s);

/* ----- list -------------------------------------------------------------- */

t_exec			    *exec_last(t_control_exec *lst);
t_parse	            *parse_last(t_control_parse *lst);
void        	    parse_add_back(t_control_parse *lst, t_parse *add);
void	            parse_add_just_back(t_control_parse *lst, t_parse *add);
int					exec_add_back(t_control_exec *lst, t_exec *add);
t_exec			    *init_exe(void);
size_t			    exec_size(t_control_exec *lst);
size_t			    parse_size(t_control_parse *lst);
t_control_exec		*init_exe_list(void);
t_parse				*init_parse(char *elem, float flag);
t_control_parse		*init_control_parse(void);

t_control_parse		*set_pars(t_control_parse *pars, char **line_tab, char **envp);
void				cleaner(t_control_parse *parsing);
t_var				*ft_lstnew(char *line);
void				var_clear(t_var *var);
void				var_clear(t_var *var);
t_control_parse		*parse(t_control_parse *parsing, size_t x, char **env);

/* ----- builtins ---------------------------------------------------------- */

int					built_in_pwd(char **arg, t_instance *instance);
int					exit_builtin(char **arg, t_instance *instance);
int					built_in_env(char **arg, t_instance *instance);
int					builtin_echo(char **arg, t_instance *instance);
int					builtin_cd(char **arg, t_instance *instance);
int					builtin_export(char **arg, t_instance *instance);
int					builtin_unset(char **arg, t_instance *instance);
char				**init_envp(char **envp);
char				**add_envp(char **envp, char *new);
char				*get_varname(char *new);
char				**del_envp(char **envp, int index);
void				addshlv(t_instance *instance);

/* ----- parsing ----------------------------------------------------------- */

t_control_parse		*parsing(char *line, char **envp);
int					parsing_printer(t_control_parse *parse_list);
t_bool				first_check(char *line);
t_bool				check_empty_line(char *line);
t_bool				check_last_pipe(char *line);
t_bool				check_last_chev(char *line);
t_bool				check_first_pipe(char *line);
t_bool				check_quote(char *line);
int					tote(char c, int q);
t_bool				check_consec_pipe(char *line);
t_control_parse		*split_block(char *elem, int x);
void				splitter(t_control_parse *parsing, t_control_parse *rep);
void				tab_cleaner(char **tab);
void				flaggeur_redir(t_control_parse *parsing);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				flaggeur_file_name(t_control_parse *parsing);
void				cut_redir(t_control_parse *parsing);
void				universal_flaggeur(t_control_parse *parsing);
void				check_multi_chev(t_control_parse *parsing);
int					check_multi_node_chev(t_control_parse *parsing);
int					check_no_file_name(t_control_parse *parsing);
t_bool				printer_error(t_control_parse *parsing);
t_var				*set_var(char **env);
t_var				*fill_var(t_var *var, char **env);
int					dollar(t_control_parse *parsing, char **env);
int					quote_supp(t_control_parse *parsing);
int					supp_empty_node(t_control_parse *parsing);
void				re_flaggeur(t_control_parse *parsing);
int					ident_cmd(char *s);
size_t				cpy_value(char *s, t_var *var, size_t dellen, char *dst);
char				*find_name(char *s, size_t dellen, size_t i, size_t j);
t_bool				in_charset(char c);
t_var				*dispatch_var(t_var *var);
void				sub_it(char *final_s, t_parse *node, t_var *var, size_t	dellen);
size_t				ft_find_value(char *varname, t_var *var);

#endif
