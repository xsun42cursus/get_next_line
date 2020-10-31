/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:45:25 by xsun              #+#    #+#             */
/*   Updated: 2020/10/31 16:47:44 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int update_line_save(char **line, char **save, long long endl_pos)
{
	char * tmp;
	*line = ft_strappend(NULL, *save, 0, endl_pos);
	if (!*line)
	{
		free(*save);
		return(-1);
	}
	if ((*save)[endl_pos + 1])
	{
		tmp = ft_strdup(&((*save)[endl_pos + 1]));
		free(*save);
		*save = tmp;
	}
	else
	{
		free(*save);
		*save = NULL;
	}
	return (1);
}

int update_save_by_buf(char **save, char **buf, ssize_t read_size)
{
	char *tmp;

	*save = (*save) ? *save : ft_strdup("");
	tmp = ft_strappend(*save, *buf, ft_strlen(*save), read_size);
	if (!tmp)
	{
		free(*save);
		free(*buf);
		return (-1);
	}
	free(*save);
	free(*buf);
	*save = tmp;
	return (1);
}

int check_read(ssize_t ret, char **line, char **save, char **buf)
{
	if (ret <= 0)
	{
		free(*buf);
		if (*save)
		{
			*line = *save;
			*save = NULL;
		}
		else if(ret == 0)
			*line = ft_strdup("");
		else
			*line = NULL;
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*save;
	ssize_t		endl_pos;
	char		*buf;
	ssize_t		ret;

	if (BUFFER_SIZE == 0 || line == NULL)
	{
		free(save);
		return (-1);
	}
	if (save && (endl_pos = ft_strchr(save, '\n')) != -1)
		return (update_line_save(line, &save, endl_pos));
	while (1)
	{
		if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		{
			free(save);
			*line = NULL;
			return (-1);
		}
		if ((ret = check_read(read(fd, buf, BUFFER_SIZE), line, &save, &buf)) <= 0)
			return (ret);
		if (update_save_by_buf(&save, &buf, ret) == -1)
			return (-1);
		if ((endl_pos = ft_strchr(save, '\n')) != -1)
			return (update_line_save(line, &save, endl_pos));
	}
	return (0);
}
