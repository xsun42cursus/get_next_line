/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:45:25 by xsun              #+#    #+#             */
/*   Updated: 2020/10/15 13:24:53 by xsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

static char *ft_strdup(const char *s)
{
	size_t size;
	char *ret;
	char *head;

	size = 0;
	while (s[size])
		size++;
	if((ret = malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	head = ret;
	while (*s)
		*head++ = *s++;
	*head = '\0';
	return (ret);

}

static void ft_move(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int hasendl(char *line, char *buf, size_t *start)
{
	size_t i;
	size_t offset;

	i = 0;
	while (buf[i])
	{
		line[*start + i] = buf[i];
		if (buf[i++] == '\n')
		{
			ft_move(&buf[0], &buf[i]);
			*start = *start + i;
			line[*start] = '\0';
			return (1);
		}
	}
	offset = i;
	*start = *start + i;
	line[*start] = '\0';
	return (0);

}

int		get_next_line(int fd, char **line)
{
	size_t res;
	static char buf[BUFFER_SIZE + 1];
	char *tmp;
	size_t readpoint;

	if (fd < 0)
		return (-1);

	if ((tmp = malloc(sizeof(char) * (100000000))) == NULL)
		return (-1);
	readpoint = 0;
	if (hasendl(tmp, buf, &readpoint))
	{
		*line= ft_strdup(tmp);
		printf("buf: %s\n", buf);
		free(tmp);
		return (1);
	}
	while (1)
	{
		res = read(fd, buf, BUFFER_SIZE);
		if (res != 0 && hasendl(tmp, buf, &readpoint))
		{
			*line= ft_strdup(tmp);
			free(tmp);
			if (res == 0)
				return (0);
			return (1);
		}
		else if (res == 0)
		{
			*line= ft_strdup("");
			free(tmp);
			return (0);
		}
		else if (res == -1)
		{
			free(tmp);
			return (-1);
		}
	}
	free(tmp);

	return (res);
}


int main(void)
{
	int fd;

	fd = open("./hello.txt", O_RDONLY);
	if (fd < 0)
		return (-1);

	char *line;

	while (get_next_line(0, &line))
	{
		printf("line: %s", line);
	}

	return (0);
}
