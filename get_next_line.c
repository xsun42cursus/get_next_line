/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:45:25 by xsun              #+#    #+#             */
/*   Updated: 2020/10/31 01:31:46 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

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

size_t ft_strchr(const char *s, char c)
{
	size_t i;
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
	size_t endl_pos;
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

int check_save(char **save, char **line, int fd)
{
	long long	ret;
	char		*tmp;
	char		*buf;
	size_t		endl_pos;

	if (*save && (endl_pos = ft_strchr(*save, '\n')) != -1)
	{
		*line = ft_strappend(NULL, *save, 0, endl_pos);
		if (ft_strlen(*save) > endl_pos + 1)
			tmp = ft_strdup(&(*save)[endl_pos+1]);//&(*save)[endl_pos+1] == ""
		else
			tmp = NULL;
		free(*save);
		*save = tmp;
		return (1);
	}
	if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
	{
		free(*save);
		return (-1);
	}
	if ((ret = read(fd, buf, BUFFER_SIZE)) < 0)
	{
		free(buf);
		return (-1);
	}
	if (ret == 0 && !*save)
	{
		free(buf);
		return (0);
	}
	*save = (*save) ? *save : ft_strdup("");
	if (is_finish(&buf, save, line, ret))
		return (1);
	return (2);
}

int check_error(long long ret, char **buf, char **save, char **line)
{
	if (ret < 0)
	{
		free(*buf);
		free(*save);
		return (-1);
	}
	(*buf)[ret] = '\0';
	if (ret == 0)
	{
		*line = *save;
		*save = NULL;
		free(*buf);
		return (0);
	}
	return (2);
}

int		get_next_line(int fd, char **line)
{
	long long ret;
	int err;
	static char *save;
	char *buf;

	if (BUFFER_SIZE <= 0)
	{
		free(save);
		return (-1);
	}
	if((ret = (long long)(check_save(&save, line, fd))) != 2)
		return (ret);
	while(1)
	{
		if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
			return (-1);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			if ((err = check_error(ret, &buf, &save, line)) != 2)
				return (err);
		buf[ret] = '\0';
		if(is_finish(&buf, &save, line, ret))
			return (1);
	}
	return (0);
}

int main(void)
{
	int fd;

	fd = open("./hello.txt", O_RDONLY);
	//fd = open("./a.txt", O_RDONLY);
	if (fd < 0)
		return (-1);

	char *line;

	while (1)
	{
		if (get_next_line(fd, &line) <= 0)
		//if (get_next_line(0, &line) == 0)
		{
			printf("line: %s\n", line);
			break;
		}
		printf("line: %s\n", line);
	}
	close(fd);

	return (0);
}
