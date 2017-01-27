/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:31:10 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/27 21:31:11 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

#define TYPE t_bin
#define NEXT n_dico

static TYPE					*separer_lst(TYPE *liste)
{
	TYPE					*aux;

	if (liste == NULL)
		return (NULL);
	else if (liste->NEXT == NULL)
		return (NULL);
	else
	{
		aux = liste->NEXT;
		liste->NEXT = aux->NEXT;
		aux->NEXT = separer_lst(aux->NEXT);
		return (aux);
	}
}

static TYPE					*fusion_lst(TYPE **lg, TYPE **ld,
		int (fonc_tri)(void *, void*))
{
	if ((*lg) == NULL)
		return (*ld);
	else if ((*ld) == NULL)
		return ((*lg));
	else if (fonc_tri(lg, ld))
	{
		(*lg)->NEXT = fusion_lst(&(*lg)->NEXT, ld, fonc_tri);
		return ((*lg));
	}
	else
	{
		(*ld)->NEXT = fusion_lst(lg, &(*ld)->NEXT, fonc_tri);
		return ((*ld));
	}
}

void						sort_list(TYPE **liste,
		int (fonc_tri)(void *, void *))
{
	TYPE					*aux;

	if (liste != NULL && (*liste) != NULL)
	{
		if ((*liste)->NEXT != NULL)
		{
			aux = separer_lst(*liste);
			sort_list(liste, fonc_tri);
			sort_list(&aux, fonc_tri);
			(*liste) = fusion_lst(liste, &aux, fonc_tri);
		}
	}
}
