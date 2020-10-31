#include "get_next_line_bonus.h"

size_t ft_strlen(const char *s)
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

ssize_t ft_strchr(const char *s, char c)
{
	ssize_t i;
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
