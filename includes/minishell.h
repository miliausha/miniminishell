#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# define ERR_SYNTAX "minishell: syntax error near unexpected token `"

typedef struct s_all
{	
	int					fd_0;
	int					fd_1;
	int					flag_fd;
	int					flag_quot;
	int					pipefd[2];
	int					pipe_count;
	int					fd_in;
	int					redir;
	int					f_r;
	int					flag_redir;
	int					pipe_flag;
	char				*arg;
	char				*redir_file;
	char				*tmpdir;
	char				**env;
	char				**parts;
	char				**words;
	struct termios		s_term;
	struct sigaction	s_sig;
	struct stat			s_stat;
}				t_all;

int	g_exit;

/*
**	builtins
*/
void	print_cd(t_all *all);
int		print_echo(t_all *all);
void	print_env(t_all *all);
void	ft_exit(t_all *all);
void	execve_cmd(t_all *all);
void	print_export(t_all *all);
char	*cut_plus(char *words);
void	ft_unset(t_all *all);
void	sort_env(char **env_sorted);
void	get_pwd(void);

/*
**	parser
*/
char	**minishell_split(char *line, char c);
void	parser(t_all *all, char *line);
int		ft_strlen_arr(char **arr);
void	quote_parser(char *line, t_all *all, int *i, char c);
void	redirect_parser(char *line, t_all *all, int *i);
void	add_arg(t_all *all, char c);
void	add_words(t_all *all);
void	env_parser(char *line, t_all *all, int *i);
int		preparser(char *line);
int		is_quot(char c, int q_flag);
int		skip_spaces(char *s);
int		start_parsing(t_all *all, char *line);
void	run_commands(t_all *all);

/*
**	utils folder
*/
int		env_len(char *s);
void	free_arr(void **arr);
void	error(char *str1, char *str2, char *str3);
void	cmd_not_found(char *s);
int		is_file_dir_exists(t_all *all);

char	*env_path_search(char **env, char *str);
void	update_env(t_all *all, char *str, char *pwd);
char	**dup_env(char **env);
void	skip_whitespace(char *line, int *i);
int		ft_strlen_arr(char **arr);
void	add_words(t_all *all);
void	add_arg(t_all *all, char c);
char	**env_copy(char **env);
char	**env_copy_with_quotes(char **env);
int		check_match(t_all *all, char *words);
void	free_at_exit(t_all *all);
int		open_file(t_all *all);
int		check_double_redirect(char *line, int *i);
void	check_redirect(t_all *all, char *line, int *i);

/*
**	functions folder
*/
void	redirect(t_all *all, char *line, int *i);
void	set_signals(int status);
void	sigfunc(int sig);
void	sigfunc_execve(int sig);
void	run_pipe(t_all *all);

#endif
