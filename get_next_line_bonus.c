/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:23:55 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 19:16:53 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int		each_gnl(int fd, char **save, char **line)
{
	ssize_t		endl_pos;
	char		*buf;
	ssize_t		ret;

	if (BUFFER_SIZE == 0 || line == NULL)
		return (smart_free(save, NULL, -1));
	if (*save && (endl_pos = ft_strchr(*save, '\n')) != -1)
		return (update_line_save(line, save, endl_pos));
	while (1)
	{
		if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		{
			*line = NULL;
			return (smart_free(save, NULL, -1));
		}
		ret = check_read(read(fd, buf, BUFFER_SIZE), line, save, &buf);
		if (update_save_by_buf(save, &buf, &ret) <= 0)
			return (int)(ret);
		if ((endl_pos = ft_strchr(*save, '\n')) != -1)
			return (update_line_save(line, save, endl_pos));
	}
	return (0);
}

static t_fdList	*ft_listnew(int fd)
{
	t_fdList	*fd_list;

	if ((fd_list = malloc(sizeof(t_fdList))) == NULL)
		return (NULL);
	fd_list->next = NULL;
	fd_list->save = NULL;
	fd_list->fd = fd;
	return (fd_list);
}

static void		ft_clearlst(t_fdList **del, t_fdList **from)
{
	t_fdList	*head;

	head = *from;
	free((*del)->save);
	(*del)->save = NULL;
	if ((*from)->fd == (*del)->fd)
		*from = (*del)->next;
	else
		while(head->next)
		{
			if (head->next->fd != (*del)->fd)
			{
				head->next = (*del)->next;
				*del = NULL;
				break ;
			}
			head = head->next;
		}
	(*del)->next = NULL;
	free(*del);
	*del = NULL;
}

int			get_next_line(int fd, char **line)
{
	static t_fdList	*fd_list;
	t_fdList		*head;
	int				ret;;

	head = fd_list;
	while (head && head->fd != fd)
	{
		head = head->next;
	}
	if (!head)
	{
		head = ft_listnew(fd);
		head->next = fd_list;
		fd_list = head;
	}
	ret = each_gnl(head->fd, &head->save, line);
	if (ret <= 0)
		ft_clearlst(&head, &fd_list);
	return (ret);
}
