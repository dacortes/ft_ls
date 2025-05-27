/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merory_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:46:33 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/27 09:50:35 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	*protected_memory(void *memory, char *func_err)
{
	if (!memory)
		exit(error_msg(MALLOC, 1, func_err, ""));
	return (memory);
}
