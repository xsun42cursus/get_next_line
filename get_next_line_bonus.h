#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

typedef struct		s_fdList
{
	int				fd;
	char			*save;
	struct s_fdList	*next;
}					t_fdList;

size_t ft_strlen(const char *s);
ssize_t ft_strchr(const char *s, char c);
char *ft_strappend(char *l, char *r, size_t len_l, size_t len_r);
char *ft_strdup(const char *s);
int		get_next_line(int fd, char **line);
#endif
