#include "minishell.h"

char    *get_prompt()
{
    char    *cwd;
    char    *prompt;
    char    *merge;

    cwd = getcwd(NULL, 0);
    prompt = ft_strjoin("minishell@", cwd);
    merge = ft_strjoin(prompt, "$");
    return (merge);
}

int main(void)
{
	char *input;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	input = readline(get_prompt());

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
