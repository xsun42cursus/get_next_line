/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                      ::    ##    #==#    */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:43:38 by xsun              #+#    #+#             */
/*   Updated: 2020/10/31 16:33:43 by s.son             ####     ::::  .SUM    */
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

size_t	ft_strlen(const char *s);
ssize_t	ft_strchr(const char *s, char c);
char	*ft_strappend(char *l, char *r, size_t len_l, size_t len_r);
char	*ft_strdup(const char *s);
int		get_next_line(int fd, char **line);
#endif
