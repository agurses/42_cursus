#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

# endif
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>


char *ft_read(int fd, char* buffer);
char *ft_strchr(const char *str, char str2);
char *get_next_line(int fd);
char *ft_strjoin(char *str1, char *str2);
size_t ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
