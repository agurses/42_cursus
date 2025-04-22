#include "minishell.h"


int main(void)
{
	char *input;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while ((input = readline("minishell$")) != NULL)
	{
		if (*input)
			add_history(input);
		free(input);
	}
	return (1);
}
