/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_values.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:48 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/21 11:29:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "arguments.h"
#include "libft.h"
#include "global.h"
#include "ft_printf.h"

#include <dirent.h>

/*	print_values.c	*/
char	*bool_to_text(unsigned int bool);
void	printf_value_flag(t_flags *flag);
short	print_array_files(char **files);
char	*get_type_dir(int type);
