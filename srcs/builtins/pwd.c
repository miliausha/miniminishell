#include "minishell.h"

void	get_pwd(void)
{
	char	dir[1024];

	getcwd(dir, 1024);
	ft_putendl_fd(dir, 1);
	g_exit = 0;
}
