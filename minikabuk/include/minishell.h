#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_ctrl_c(int sig);

#endif