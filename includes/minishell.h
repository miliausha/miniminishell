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
#include <sys/time.h> //del

# include "libft.h"

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
	int					g_r;
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
	struct timeval		tv; //del
	long	start;	//del
}				t_all;

int	g_exit;

/*
**	builtins
*/
void	print_cd(t_all *all);		//cd.c
int		print_echo(t_all *all); //echo.c
void	print_env(t_all *all);	//env.c
void	ft_exit(t_all *all); //exit.c
void	execve_cmd(t_all *all);	//ft_execve
void	print_export(t_all *all); //export.c
char	*cut_plus(char *words); //export.c
void	ft_unset(t_all *all); // unset.c
void	sort_env(char **env_sorted); // env.c
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
int		is_quot(char c, int q_flag);	//utils_parser.c
int		skip_spaces(char *s);			//utils_parser.c
int		start_parsing(t_all *all, char *line);
void	run_commands(t_all *all);

/*
**	utils.c
*/
int		env_len(char *s);	//env_utils
void	free_arr(void **arr); //free.c
void	error(char *str1, char *str2, char *str3);
void	cmd_not_found(char *s);
int		is_file_dir_exists(t_all *all);

char	*env_path_search(char **env, char *str); //env_utils
void	update_env(t_all *all, char *str, char *pwd); //env_utils
char	**dup_env(char **env);	//env_utils
void	skip_whitespace(char *line, int *i); //utils.c
int		ft_strlen_arr(char **arr); //utils.c
void	add_words(t_all *all);
void	add_arg(t_all *all, char c);
char	**env_copy(char **env); //env_utils.c
char	**env_copy_with_quotes(char **env); //export_utils.c
int		check_match(t_all *all, char *words); //export_utils.c

/*
**	functions
*/
void	redirect(t_all *all, char *line, int *i);
void	set_signals(int status);
void	sigfunc(int sig);
void	sigfunc_execve(int sig);
void	run_pipe(t_all *all);

#endif
