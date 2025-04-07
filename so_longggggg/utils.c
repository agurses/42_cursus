#include "so_long.h"

int	ft_strcspn(const char *s, const char *charset)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_strlen_for_int(char *str)
{
	int i;

	i = 0;
	while (str[i] || str[i] == '\n')
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	int len = ft_strlen(s);
	char *new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	int i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
