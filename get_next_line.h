/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:43:38 by xsun              #+#    #+#             */
/*   Updated: 2020/10/31 01:56:13 by s.son             ####     ::::  .SUM    */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

int		get_next_line(int fd, char **line);
long long	ft_strlen(const char *s);
char	*ft_strappend(char *l, char *r, size_t len_l, size_t len_r);
long long	ft_strchr(const char *s, char c);
char	*ft_strdup(const char *s);
int		is_finish(char **buf, char **save, char **line, size_t ret);
#endif
