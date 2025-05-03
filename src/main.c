
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




// #include <dirent.h>
// #include "libft.h"
// #include "ft_printf.h"
// #include <string.h>
// #include <errno.h>
// #include <sys/stat.h>

// #define MAX_PATH 4096
// #define ERROR -1

// enum e_boolean
// {
// 	false,
// 	true,
// };

// enum e_flags
// {
// 	long_format = 'l',
// 	rec = 'R',
// 	all = 'a',
// 	reverse = 'r',
// 	time = 't',
// };

// typedef struct s_file
// {
// 	char	*name;
// 	int		type;
// }	t_file;

// "-l, -R, -a, -r and -t."

// typedef struct s_flags
// {
// 	short	long_format;
// 	short	recursive;
// 	short	all;
// 	short	reverse;
// 	short	time;
// }	t_flags;

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

// void has_flags(int num_args, char **args)
// {
// 	t_flags flags;
// 	int iter;

// 	iter = 0;
// 	while (iter < num_args)
// 	{
// 		if (args[iter][0] && args[iter][0] == '-')
// 		{	
// 		}
// 	}
	
// }

// short current_directory(int num_args, char **args)
// {
// 	if (has_flags(num_args, args))
// 	{
// 		printf("Tengo flags\n");
// 		// proccess_flags(num_args, args);
// 	}
// 	return (true);
// }

// short handle_parameters(int num_args, char **args)
// {
// 	current_directory(num_args, args);
// 	return (EXIT_SUCCESS);
// }

// int main(int ac, char **av)
// {
// 	return (handle_parameters(ac, av));
// }