/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                          ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:02:38 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 19:14:03 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		smart_free(char **ptr1, char **ptr2, int ret)
{
	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (ret);
}

ssize_t	ft_strchr(const char *s, char c)
{
	ssize_t len;

	len = 0;
	while(*s)
	{
		if (*s == c)
			return (len);
		s++;
		++len;
	}
	if(c == *s)
		return (len);
	return (-1);
}

char	*ft_strappend(char *l, char *r, size_t len_l, size_t len_r)
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

int		update_line_save(char **line, char **save, long long endl_pos)
{
	char	*tmp;
	*line = ft_strappend(NULL, *save, 0, endl_pos);
	if (!*line)
		return (smart_free(save,NULL, -1));
	if ((*save)[endl_pos + 1])
	{
		tmp = ft_strappend(&((*save)[endl_pos + 1]), NULL, ft_strchr(&((*save)[endl_pos + 1]), 0), 0);
		(void)(smart_free(save,NULL, 0));
		*save = tmp;
	}
	else
		(void)(smart_free(save,NULL, 0));
	return (1);
}

ssize_t	update_save_by_buf(char **save, char **buf, ssize_t *read_size)
{
	char	*tmp;

	if (*read_size <= 0)
		return (*read_size);
	*save = (*save) ? *save : ft_strappend("", NULL, 1,0);
	tmp = ft_strappend(*save, *buf, ft_strchr(*save, 0), *read_size);
	if (!tmp)
		return (smart_free(save, buf, -1));
	(void)(smart_free(save, buf, -1));
	*save = tmp;
	return (1);
}
