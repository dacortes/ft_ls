/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:01 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/14 14:40:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	error_msg(int error, int code_exit, char *input)
{
	int	e;

	(void)e;
	e = error & MALLOC && fd_printf(2, ERR_MALLOC, FT_LS, input);
	e = error & INVALID && fd_printf(2, ERR_INVALID, FT_LS, input);
	if (error == PERROR)
	{
		fd_printf(2, "%s%s: ", FT_LS, input);
		perror("");
	}
	return (code_exit);
}
