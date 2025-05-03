/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:24:59 by dacortes          #+#    #+#             */
/*   Updated: 2025/04/29 16:20:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "flag.h"

static short put_flags(t_flags *flags, char *arg)
{
	int iter;
	int status;

	iter = 0;
	status = false;
	while (arg[iter])
	{
		if (arg[iter] == long_format)
			flags->long_format = true;
		else if (arg[iter] == recursive)
			flags->recursive = true;
		else if (arg[iter] == all)
			flags->all = true;
		else if (arg[iter] == reverse)
			flags->reverse = true;
		else if (arg[iter] == time)
			flags->time = true;
		status = true;
		iter++;
	}
	return (status);
}

static short analyze_args(t_flags *flags, int num_args, char **args)
{
	int iter;
	int status;

	iter = 0;
	status = false;
	while (iter < num_args)
	{
		if (args[iter][0] && args[iter][0] == '-')
			status = put_flags(flags, args[iter]);
		iter++;
	}
	return	 (status);
}

short has_flags(t_flags *flags, int num_args, char **args)
{
	if (!num_args)
	{
		ft_bzero(flags, sizeof(t_flags));
		return (false);
	}
	
}