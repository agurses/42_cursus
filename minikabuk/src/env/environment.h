#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}		t_env;

#endif