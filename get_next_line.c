/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:14:46 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 19:05:03 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_read(ssize_t ret, char **line, char **save, char **buf)
{
	if (ret <= 0)
	{
		(void)(smart_free(buf, NULL, 0));
		if (*save)
		{
			*line = *save;
			*save = NULL;
		}
		else if(ret == 0)
			*line = ft_strappend("", NULL, 1, 0);
		else
			*line = NULL;
	}
	return (int)(ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*save;
	ssize_t		endl_pos;
	char		*buf;
	ssize_t		ret;

	if (BUFFER_SIZE == 0 || line == NULL)
		return (smart_free(&save, NULL, -1));
	if (save && (endl_pos = ft_strchr(save, '\n')) != -1)
		return (update_line_save(line, &save, endl_pos));
	while (1)
	{
		if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		{
			*line = NULL;
			return (smart_free(&save, NULL, -1));
		}
		ret = check_read(read(fd, buf, BUFFER_SIZE), line, &save, &buf);
		if (update_save_by_buf(&save, &buf, &ret) <= 0)
			return (int)(ret);
		if ((endl_pos = ft_strchr(save, '\n')) != -1)
			return (update_line_save(line, &save, endl_pos));
	}
	return (0);
}
