/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:37:16 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/18 16:03:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include "global.h"
#include "ft_printf.h"

#include <errno.h>
#include <stdio.h>

/*	printf_errors.c	*/
int	error_msg(int error, int code_exit, char *input, char *er_no);