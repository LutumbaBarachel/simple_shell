#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Customises error message for permission denied failures.
 * @args: Array of args that is passed to the command.
 *
 * Return: The error string.
 */

char *error_126(char **args)
{
char *error, *hist_str;
int len;
hist_str = _itoa(hist);
if (!hist_str)
return (NULL);
len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}
_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, hist_str);
_strcat(error, ": ");
_strcat(error, args[0]);
_strcat(error, ": Permission denied\n");
free(hist_str);
return (error);
}

/**
 * error_127 - func that creates an error msg for 'command not found' failures.
 * @args: Array of args which is passed to the command.
 *
 * Return: The error string.
 */

char *error_127(char **args)
{
char *error, *hist_str;
int len;
hist_str = _itoa(hist);
if (!hist_str)
return (NULL);
len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}
_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, hist_str);
_strcat(error, ": ");
_strcat(error, args[0]);
_strcat(error, ": not found\n");
free(hist_str);
return (error);
}
