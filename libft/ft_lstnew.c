/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 20:08:26 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/02 12:11:46 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*nwlist;

	if (!(nwlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		nwlist->cnt = NULL;
		nwlist->cnt_s = 0;
	}
	else
	{
		if (!(nwlist->cnt = (void*)malloc(sizeof(content))))
		{
			free(nwlist);
			return (NULL);
		}
		ft_memcpy(nwlist->cnt, content, content_size);
		nwlist->cnt_s = content_size;
	}
	nwlist->next = NULL;
	return (nwlist);
}
