#include "flag.h"
#include "node.h"
#include "errors.h"
#include "print_values.h"
#include "sort.h"

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
// #include <string.h>
// #include <errno.h>
// #include <sys/stat.h>

// #define MAX_PATH 4096
// #define ERROR -1


// char *get_type(int type)
// {
// 	if (type == DT_DIR)
// 		return ("directory");
// 	else if (type == DT_REG)
// 		return ("regular file");
// 	else if (type == DT_LNK)
// 		return ("symbolic link");
// 	else if (type == DT_FIFO)
// 		return ("FIFO/pipe");
// 	else if (type == DT_SOCK)
// 		return ("socket");
// 	else if (type == DT_CHR)
// 		return ("character device");
// 	else if (type == DT_BLK)
// 		return ("block device");
// 	else
// 		return ("unknown type");
// }

// void print_content(void *content)
// {
// 	t_file *file;

// 	file = (t_file *)content;
// 	fd_printf(1, "%s ", file->name);
// 	fd_printf(1, "%s\n", get_type(file->type));
// }

// t_file *new_file(char *name, int type)
// {
// 	t_file *file;

// 	file = ft_calloc(sizeof(t_file), 1);
// 	if (!file)
// 		exit(1);
// 	file->name = name;
// 	file->type = type;
// 	return (file);
// }

// void free_file(void *content)
// {
// 	t_file *file;

// 	file = (t_file *)content;
// 	if (file->name)
// 		free(file->name);
// 	free(file);
// }

// int main(void)
// {
// 	struct dirent	*entry;
// 	DIR				*dir;
// 	t_list			*files;

// 	char  *path = "test";
// 	dir  = opendir(path);
// 	if (dir == NULL)
// 	{
// 		fd_printf(2, "cannot access: '%s': %s\n", path, strerror(errno));
// 		return (2);
// 	}
// 	files = NULL;
// 	int num_dirs = 0;
// 	while (true)
// 	{
// 		entry = readdir(dir);
// 		if (entry->d_type == DT_DIR && (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0))
// 			num_dirs++;
// 		if (entry == NULL)
// 			break;
// 		ft_lstadd_back(&files, ft_lstnew(new_file(ft_strdup(entry->d_name), entry->d_type)));
// 	}
// 	ft_lstiter(files, print_content);
// 	ft_lstclear(&files, free_file);
// 	fd_printf(1, "\n");
// 	closedir(dir);
//     return (0);
// }
// short is_directory(char *arg)
// {
// 	struct stat sb;

// 	if (stat(arg, &sb) == -1)
// 	{
// 		fd_printf(2, "cannot access: '%s': %s\n", arg, strerror(errno));
// 		return (false);
// 	}
// 	if (S_ISDIR(sb.st_mode))
// 		return (true);
// 	return (false);
// }

int	get_size_files(char **args)
{
	int	iter;
	int	sizes;

	if (!args)
		return (-1);
	iter = 0;
	sizes = 0;
	while (args[iter])
	{
		if (is_flag(args[iter]) == false)
			sizes++;
		iter++;
	}
	return (sizes);
}

short	add_array_files(char **src, char **dst)
{
	int		iter;
	int		add;

	if (!src || !dst)
		return (EXIT_FAILURE);
	add = 0;
	iter = 0;
	while (src[iter])
	{
		if (is_flag(src[iter]) == false)
		{
			dst[add] = src[iter];
			add++;
		}
		iter++;
	}
	return (EXIT_SUCCESS);
}

char **is_file(char **args)
{
	char	**files;
	int		sizes;

	if (!args)
		return (NULL);
	sizes = get_size_files(args);
	files = ft_calloc(sizes + 1, sizeof(char *));
	if (!files)
		exit(error_msg(MALLOC, 1, "func: isfile() -> var: files"));
	if (add_array_files(args, files) == EXIT_FAILURE)
		return (NULL);
	sort_files(files, sizes);
	return (files);
}

int main(int ac, char **av)
{
	t_flags flags;
	
	char **files = NULL;
	if (has_flags(&flags, ac, &av[1]) == false && ac == 1)
		ft_printf("enlisto sin flags\n");
	else
		files = is_file(av);
	if (!files)
		return (0);
	int iter = 0;
	while (files[iter])
	{
		ft_printf("*%s*\n", files[iter]);
		iter++;
	}
	// ft_printf("%s\n", bool_to_text(is_flag("src")));
	// printf_value_flag(&flags);
	// int i = 0;

	// t_stack stack;

	// ft_bzero(&stack, sizeof(t_stack));
	// while (i < 10)
	// {
	// 	t_node *new = ft_calloc(1, sizeof(t_node));
	// 	new->data = i + 1;
	// 	push_stack(&stack, new);
	// 	i++;
	// }
	
	// t_node *iter = stack.top;
	// while (iter)
	// {
	// 	if (iter->prev)
	// 		ft_printf("soy la data del prev = %d\n", iter->prev->data);
	// 	ft_printf("data = %d\n", iter->data);
	// 	iter = iter->next;
	// }
	// i = stack.size;
	// while (i)
	// {
	// 	pop_stack(&stack);
	// 	i--;
	// }
	
	return (EXIT_SUCCESS);
}