#include "node.h"
#include "clear.h"
#include "errors.h"
#include "arguments.h"
#include "print_values.h"


/*
	◦ write
	◦ opendir
	◦ readdir
	◦ closedir
	◦ stat
	◦ lstat
	◦ getpwuid
	◦ getgrgid
	◦ listxattr
	◦ getxattr
	◦ time
	◦ ctime
	◦ readlink
	◦ malloc
	◦ free
	◦ perror
	◦ strerror
	◦ exit
*/

// #include "libft.h"
// #include "ft_printf.h"
// #include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>

// short	loop_recursive(t_flags flags, t_stack *stack)
// {
// 	t_node	*curr;
// 	t_node	*add;
// 	DIR		*dir;
// 	short	status;

// 	(void)flags;
// 	status = EXIT_SUCCESS;
// 	dir = NULL;
// 	while (stack->size > 0)
// 	{
// 		curr = copy_node(stack, true);
// 		ft_printf("file name %s\n", curr->entry->d_name);
// 		status = init_struct_dirent(&curr, dir, curr->entry->d_name);
// 		if (status == 2)
// 			stack->status = status;
// 		while (status != end_dir)
// 		{
// 			if (default_directories(curr->entry->d_name, curr->entry->d_type))
// 				continue ;
// 			if (curr->entry->d_type == DT_DIR)
// 			{
// 					add = ft_calloc(1, sizeof(t_node));
// 					if (!add)
// 						exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
// 					status = init_struct_dirent(&add, dir, add->entry->d_name);
// 					push_stack(stack, add);
// 					ft_printf("+++++++++++++++++++++++++\n");
// 			}
// 		}
// 		free(curr->entry);
// 		free(curr);
// 	}
// 	return (true);
// }

DIR	*init_dir(char *file)
{
	DIR *dir;

	dir = opendir(file);
	if (!dir)
		return (error_msg(OPEN_DIR, 2, file, strerror(errno)), NULL);
	return (dir);
}

short	is_readdir(struct dirent **entry, DIR		*dir)
{
	*entry = readdir(dir);
	if (!*entry)
		return (false);
	return (true);
}

short	loop_recursive(t_flags flags, t_stack *stack)
{
	t_node	*curr;
	t_node	*add;
	DIR		*dir;
	struct dirent *entry;

	(void)flags;
	while (stack->size > 0)
	{
		curr = copy_node(stack, true);
		ft_printf("Exploring: %s\n", curr->entry->d_name);

		dir = init_dir(curr->entry->d_name);
		if (!dir)
			continue ;

		while (is_readdir(&entry, dir))
		{
			if (default_directories(entry->d_name, entry->d_type))
				continue;

			char *tmp = ft_addend_char(curr->entry->d_name, '/');
			char *full_path = ft_strjoin(tmp, entry->d_name);
			if (tmp)
				free(tmp);
			if (entry->d_type == DT_DIR)
			{
				add = ft_calloc(1, sizeof(t_node));
				if (!add)
					exit(error_msg(MALLOC, 1, "loop_recursive", ""));
				// copy_struct_dirent(entry, &add->entry);
				add->entry = ft_calloc(1, sizeof(struct dirent) + strlen(full_path) + 1);
                ft_strcpy(add->entry->d_name, full_path);
				push_stack(stack, add);
				ft_printf("Added directory to stack: %s\n", entry->d_name);
			}
			else
			{
				ft_printf("File: %s\n", entry->d_name);
			}
			if (full_path)
				free(full_path);
		}

		closedir(dir);
		free(curr->entry);
		free(curr);
	}
	return (true);
}


short	exec_recursive_flag(t_flags flags, char *start_dir)
{
	t_stack	stack;
	t_node	*root;

	if (!start_dir)
		return (false);
	ft_bzero(&stack, sizeof(t_stack));
	root = ft_calloc(1, sizeof(t_node));
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
    root->entry = ft_calloc(1, sizeof(struct dirent) \
		+ ft_strlen(start_dir) + 1);
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
    ft_strcpy(root->entry->d_name, start_dir);
	push_stack(&stack, root);
	loop_recursive(flags, &stack);
	clear_stack(&stack);
	return (stack.status);
}

int main(int ac, char **av)
{
	t_flags flags;
	char	**files;
	
	files = NULL;
	if (has_flags(&flags, ac, &av[1]) == false && ac == 1)
		ft_printf("enlisto sin flags\n");
	else
		files = is_file(&av[1]);
	if (!files)
		return (0);

	exec_recursive_flag(flags, files[0]);
	print_array_files(files);
	clear_array(files);
	return (EXIT_SUCCESS);
}