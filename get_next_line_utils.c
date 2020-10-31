#include "get_next_line.h"

long long ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while(*s)
	{
		s++;
		++len;
	}
	return (len);
}

char *ft_strappend(char *l, char *r, size_t len_l, size_t len_r)
{
	size_t	i;
	char	*append;

	if ((append = malloc(sizeof(char) * (len_l + len_r + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < len_l)
	{
		append[i++] = *l++;
	}
	while (i < len_l + len_r)
	{
		append[i++] = *r++;
	}
	append[i] = '\0';
	return (append);
}

long long ft_strchr(const char *s, char c)
{
	long long i;
	i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	if(c == s[i])
		return (i);
	return (-1);
}

char *ft_strdup(const char *s)
{
	size_t len;
	char *ret;
	size_t i;

	len = ft_strlen(s);
	if ((ret = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	while(s[i])
	{
		ret[i] = s[i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}

int is_finish(char **buf, char **save, char **line, size_t ret)
{
	long long endl_pos;
	char *tmp;

	if ((endl_pos = ft_strchr(*buf, '\n')) != -1)
	{
		tmp = ft_strappend(*save, *buf, ft_strlen(*save), endl_pos);
		free(*save);
		if ((*buf)[endl_pos + 1])
			*save = ft_strdup(&(*buf)[endl_pos + 1]);
		else
			*save = NULL;
			//*save = ft_strdup("");
		free(*buf);
		*line = tmp;
		return (1);
	}
	else
	{
		tmp = ft_strappend(*save, *buf, ft_strlen(*save), ret);
		free(*save);
		free(*buf);
		*save = tmp;
	}
	return (0);
}
