/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:52:54 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/25 18:03:36 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.h"

#include <dirent.h>
#include <stdlib.h>

short	clear_array(char **ptr);
short	clear_entries(struct dirent **entries, int size, short is_loop);