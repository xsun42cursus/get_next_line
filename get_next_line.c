/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:45:25 by xsun              #+#    #+#             */
/*   Updated: 2020/10/31 13:13:41 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_save(char **save, char **line, int fd)
{
	long long	ret;
	char		*tmp;
	char		*buf;
	long long	endl_pos;

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
