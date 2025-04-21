#include "minishell.h"

int main(void)
{
	char *input;

	while ((input = readline("minishell$")) != NULL)
	{
		if (*input)
			add_history(input);
		free(input);
	}
	return (1);
}
