/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:14:46 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 16:55:44 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
