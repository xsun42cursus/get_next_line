/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:23:55 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 17:52:28 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int		gnl(int fd, char **save, char **line)
{
	ssize_t		endl_pos;
	char		*buf;
	ssize_t		ret;

	if (BUFFER_SIZE == 0 || line == NULL)
	{
		free(*save);
		return (-1);
	}
	if (*save && (endl_pos = ft_strchr(*save, '\n')) != -1)
		return (update_line_save(line, save, endl_pos));
	while (1)
	{
		if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		{
			free(*save);
			*line = NULL;
			return (-1);
		}
		if ((ret = check_read(read(fd, buf, BUFFER_SIZE), line, save, &buf)) <= 0)
			return (ret);
		if (update_save_by_buf(save, &buf, ret) == -1)
			return (-1);
		if ((endl_pos = ft_strchr(*save, '\n')) != -1)
			return (update_line_save(line, save, endl_pos));
	}
	return (0);
}

t_fdList *ft_listnew(int fd)
{
	t_fdList *fd_list;

	if ((fd_list = malloc(sizeof(t_fdList))) == NULL)
		return (NULL);
	fd_list->next = NULL;
	fd_list->save = NULL;
	fd_list->fd = fd;
	return (fd_list);
}

//t_fdList *find_list(t_fdList *list, int fd)
//{
//	t_fdList *head;
//
//	head = list;
//	while (head)
//	{
//		if (head->fd == fd)
//		{
//			return (head);
//		}
//		head = head->next;
//	}
//	return (NULL);
//}

void ft_clearlst(t_fdList **del, t_fdList **from)
{
	t_fdList *head;

	head = *from;
	free((*del)->save);
	printf("freed save\n");
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
	printf("freed lst\n");
	*del = NULL;
	printf("deleted lst\n");
}
	//head = *lst;
	//if (!lst)
	//	return ;
	//while (head)
	//{
	//	tmp = head->next;
	//	head->next = NULL;
	//	free(head);
	//	head = tmp;
	//}
	//*lst = NULL;
//}

int		get_next_line(int fd, char **line)
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
	ret = gnl(head->fd, &head->save, line);
	//if (ret == -1)
	//	ft_clearlst(&head, &fd_list);

	//if (!fd_list)
	//{
	//	if ((fd_list = ft_listnew(fd)) == NULL)
	//		return (-1);
	//	ret = gnl(fd_list->fd, &fd_list->save, line);
	//}
	//else
	//{
	//	if((tmp = find_list(fd_list, fd)) == NULL)
	//	{
	//		tmp = ft_listnew(fd);
	//		tmp->next = fd_list;
	//		fd_list = tmp;
	//	}
	//	ret = gnl(tmp->fd, &tmp->save, line);
	//}
	if (ret <= 0)
		ft_clearlst(&head, &fd_list);
	return (ret);
}
