/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:45:25 by xsun              #+#    #+#             */
/*   Updated: 2020/10/14 10:27:21 by xsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

//int		get_next_line(int fd, char **line)
//{
//	size_t res;
//	static char buf[BUFFER_SIZE + 1];
//
//	if (fd < 0)
//		return (-1);
//	while (1)
//	{
//		res = read(fd, buf, BUFFER_SIZE);
//		if (res == -1)
//			return (0);
//	}
//	printf("%s\n", buf);
//
//	return (res);
//}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);

}

int append(char **dst, char *src)
{
	size_t dstsize = ft_strlen(*dst);
	size_t srcsize = ft_strlen(src);
	char *head;

	head = *dst;
	if ((*dst = malloc(sizeof(char) * (dstsize + srcsize + 1))) == NULL)
		return (-1);
	int i = 0;
	while (i < dstsize)
	{
		(*dst)[i] = head[i];
		i++;
	}
	free(head);
	while (*src)
	{
		(*dst)[i++] = *src++;
	}
	(*dst)[i] = '\0';
	return (0);
}

int main(void)
{
	char *src[10] = {"aahw", "hwllo", "good", "bad", "no", "aaaaaaaaaaaa"};
	char *dst = malloc(sizeof(char) * (ft_strlen(src[0]) + 1));
	char *s = src[0];
	int i = 0;
	int size = 3000;
	while (*s)
		dst[i++] = *s++;
	dst[i] = '\0';

	i = 0;
	int j = 0;
	while (j < size)
	{
		while (i < 6)
		{
			if (append(&dst, src[i++]))
				printf("!!!!!!!!!!!not!!!!!!!!!!!\n");
		}
		i = 0;
		j++;
	}

	printf("%s\n", dst);
	//while(1)
	//{}
	return 0;
}
