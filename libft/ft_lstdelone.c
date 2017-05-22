/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:52:01 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:52:02 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*mem;
	t_list		*cpy_alst;

	if ((cpy_alst = *alst) != NULL)
	{
		mem = cpy_alst->next;
		del(cpy_alst->content, cpy_alst->content_size);
		free(cpy_alst);
		cpy_alst = NULL;
		*alst = mem;
	}
}
