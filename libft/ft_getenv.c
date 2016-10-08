/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 09:55:43 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 10:09:51 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*ft_getenv(char **env, const char *name)
{
	int						i;
	size_t					len_name;

	if (env == NULL || *env == NULL || name == NULL)
		return NULL;
	if ((len_name = ft_strlen(name)) <= 0)
		return NULL;
	i = 0;
	while (env[i] != NULL)
		if (ft_strncmp(env[i++], name, len_name) == 0)
			return env[i - 1] + len_name + 1;
	return NULL;
}
