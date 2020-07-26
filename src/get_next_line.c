/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 20:10:25 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/04 18:50:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

void	ft_linkchr(const int fd, t_list **s_list, t_list **s_explor)
{
	t_list		*s_previous;

	while (((*s_list)->cnt != NULL) && (*s_explor != NULL))
	{
		s_previous = *s_explor;
		if ((*s_explor)->file_d == fd)
			break ;
		if ((*s_explor)->file_d != fd)
			*s_explor = (*s_explor)->next;
	}
	if (*s_explor == NULL)
	{
		ft_lstadd(&s_previous->next, ft_lstnew(NULL, 404));
		*s_explor = s_previous->next;
		(*s_explor)->file_d = fd;
	}
}

int		ft_resize_cnt(void **cnt, int len)
{
	char			*temp;

	if (!(temp = ft_strdup((char*)(*cnt) + len + 1)))
		return (-1);
	ft_memdel(cnt);
	if (!(*cnt = ft_strdup(temp)))
	{
		ft_strdel(&temp);
		return (-1);
	}
	ft_strdel(&temp);
	return (1);
}

int		ft_fill_line(char **line, void **cnt)
{
	size_t			len;

	len = 0;
	if (!(*cnt))
		return (-1);
	if (ft_strchr((char*)(*cnt), '\n') == NULL && ft_strlen((char*)(*cnt)) > 0)
	{
		*line = ft_strdup((char*)(*cnt));
		ft_memdel(cnt);
		return (*line == NULL ? -1 : 1);
	}
	len = ft_strchr((char*)(*cnt), '\n') - (char*)(*cnt);
	if (!(*line = ft_strsub((char*)(*cnt), 0, len)))
		return (-1);
	if (ft_resize_cnt(cnt, len) == -1)
	{
		ft_strdel(line);
		return (-1);
	}
	return (1);
}

void	ft_fill_link(const int fd, void **cnt, char *buff, int *stat)
{
	char	*tmp;

	while ((*stat = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[*stat] = '\0';
		if (*cnt == NULL)
		{
			if (!(*cnt = ft_strdup((char*)buff)))
				*stat = -1;
		}
		else if (*cnt != NULL)
		{
			if (!(tmp = ft_strjoin(*cnt, buff)))
				*stat = -1;
			ft_strdel((char**)cnt);
			if (!(*cnt = ft_strdup(tmp)))
			{
				ft_strdel(&tmp);
				*stat = -1;
			}
			ft_strdel(&tmp);
		}
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list		*s_list;
	t_list				*s_explor;
	char				buff[BUFF_SIZE + 1];
	int					stat;

	stat = 1;
	if (fd < 0)
		return (-1);
	if (s_list == NULL)
	{
		s_list = ft_lstnew(NULL, 404);
		s_list->file_d = fd;
	}
	s_explor = s_list;
	ft_linkchr(fd, &s_list, &s_explor);
	ft_fill_link(fd, &(s_explor->cnt), buff, &stat);
	stat = (s_explor->cnt != NULL && stat == 0)
		? ft_strlen((char*)(s_explor->cnt)) : stat;
	if (stat == -1 || stat == 0)
		return (stat);
	stat = ft_fill_line(line, &(s_explor->cnt));
	if (stat == 0 || stat == -1)
		return (stat);
	return (1);
}
