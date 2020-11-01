/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                                ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:03:25 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 18:03:31 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

typedef struct		s_fdList
{
	int				fd;
	char			*save;
	struct s_fdList	*next;
}					t_fdList;

ssize_t	ft_strchr(const char *s, char c);
char	*ft_strappend(char *l, char *r, size_t len_l, size_t len_r);
int update_line_save(char **line, char **save, long long endl_pos);
int update_save_by_buf(char **save, char **buf, ssize_t read_size);
int check_read(ssize_t ret, char **line, char **save, char **buf);
int		get_next_line(int fd, char **line);
#endif
