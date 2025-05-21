/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:51:36 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/17 11:04:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

short	clear_array(char **ptr)
{
	int	iter;

	if (!ptr || !*ptr)
		return (false);
	iter = 0;
	while (ptr[iter])
	{
		free(ptr[iter]);
		ptr[iter] = NULL;
		iter++;
	}
	free(ptr);
	return (true);
}
