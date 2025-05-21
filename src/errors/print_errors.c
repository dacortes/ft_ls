/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:01 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/18 16:03:07 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	error_msg(int error, int code_exit, char *input, char *er_no)
{
	int	e;

	(void)e;
	e = error & MALLOC && fd_printf(2, ERR_MALLOC, FT_LS, input);
	e = error & INVALID && fd_printf(2, ERR_INVALID, FT_LS, input);
	e = error & OPEN_DIR && fd_printf(2, ERR_OPEN, FT_LS, input, er_no);
	if (error == PERROR)
	{
		fd_printf(2, "%s%s: ", FT_LS, input);
		perror("");
	}
	return (code_exit);
}
