#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int shellie_exit(char **args, char **front);
int shellie_cd(char **args, char __attribute__((__unused__)) **front);
int shellie_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - coordinates a command with a matching
 * shell by builtin function.
 * @command: Command in question.
 *
 * Return: A function pointer to the corresponding builtin.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
builtins_t funcs[] = {
{ "exit", shellie_exit },
{ "env", shellie_env },
{ "setenv", shellie_setenv },
{ "unsetenv", shellie_unsetenv },
{ "cd", shellie_cd },
{ "alias", shellie_alias },
{ "help", shellie_help },
{ NULL, NULL }
};
int i;
for (i = 0; funcs[i].name; i++)
{
if (_strcmp(funcs[i].name, command) == 0)
break;
}
return (funcs[i].f);
}

/**
 * shellie_exit - leads to normal termination of process
 * for the shellby shell.
 * @args: An array of arguments that contains the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If no arguments - -3.
 * If given exit value is invalid - 2.
 * Otherwisw - exit with the given status value.
 *
 * Description: once -3 is returned,program exits to main function.
 */
int shellie_exit(char **args, char **front)
{
int i, len_of_int = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
if (args[0])
{
if (args[0][0] == '+')
{
i = 1;
len_of_int++;
}
for (; args[0][i]; i++)
{
if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
num = (num * 10) + (args[0][i] - '0');
else
return (create_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (create_error(--args, 2));
args -= 1;
free_args(args, front);
free_env();
free_alias_list(aliases);
exit(num);
}

/**
 * shellie_cd - Changes the current working directory of the shellby process.
 * @args: An array of args.
 * @front: A double pointer to the start of arguments.
 *
 * Return: - 2 if given string is not in dir.
 * If error occurs - -1.
 * O/W - 0.
 */
int shellie_cd(char **args, char __attribute__((__unused__)) **front)
{
char **dir_info, *new_line = "\n";
char *oldpwd = NULL, *pwd = NULL;
struct stat dir;
oldpwd = getcwd(oldpwd, 0);
if (!oldpwd)
return (-1);
if (args[0])
{
if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') ||
args[0][1] == '\0')
{
if (_get_env("OLDPWD") != NULL)
(chdir(*_get_env("OLDPWD") + 7));
}
else
{
free(oldpwd);
return (create_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
&& ((dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(oldpwd);
return (create_error(args, 2));
}
}
}
else
{
if (_get_env("HOME") != NULL)
chdir(*(_get_env("HOME")) + 5);
}
pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);
dir_info = malloc(sizeof(char *) * 2);
if (!dir_info)
return (-1);
dir_info[0] = "OLDPWD";
dir_info[1] = oldpwd;
if (shellie_setenv(dir_info, dir_info) == -1)
return (-1);
dir_info[0] = "PWD";
dir_info[1] = pwd;
if (shellie_setenv(dir_info, dir_info) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(oldpwd);
free(pwd);
free(dir_info);
return (0);
}

/**
 * shellie_help - shows info about shellby builtin commands.
 * @args: An array of args.
 * @front: A pointer to the beginning of arguments.
 *
 * Return: Incase of an error - -1.
 * O/W - 0.
 */
int shellie_help(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
help_all();
else if (_strcmp(args[0], "alias") == 0)
help_alias();
else if (_strcmp(args[0], "cd") == 0)
help_cd();
else if (_strcmp(args[0], "exit") == 0)
help_exit();
else if (_strcmp(args[0], "env") == 0)
help_env();
else if (_strcmp(args[0], "setenv") == 0)
help_setenv();
else if (_strcmp(args[0], "unsetenv") == 0)
help_unsetenv();
else if (_strcmp(args[0], "help") == 0)
help_help();
else
write(STDERR_FILENO, name, _strlen(name));
return (0);
}
