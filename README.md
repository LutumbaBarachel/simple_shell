$ echo "echo 'hello' ; echo 'world'" | ./hsh 'hello' 'world' && - AND logical operator command1 && command2: command2 is executed if, and only if, command1 returns an exit status of zero.

Example:

$ echo "error! && echo 'julien'" | ./hsh ./shellby: 1: error!: not found $ echo "echo 'my name is' && echo 'julien'" | ./hsh 'my name is' 'julien' || - OR logical operator command1 || command2: command2 is executed if, and only if, command1 returns a non-zero exit status.

Example:

$ echo "error! || echo 'wait for it'" | ./hsh ./hsh: 1: error!: not found 'wait for it' The operators && and || have equal precedence, followed by ;.

Builtin Commands cd Usage: cd [DIRECTORY] Changes the current directory of the process to DIRECTORY. If no argument is given, the command is interpreted as cd $HOME. If the argument - is given, the command is interpreted as cd $OLDPWD and the pathname of the new working directory is printed to standad output. If the argument, -- is given, the command is interpreted as cd $OLDPWD but the pathname of the new working directory is not printed. The environment variables PWD and OLDPWD are updated after a change of directory. Example:

$ ./hsh ^-^ pwd /home/vagrant/julien/simple_shell $ cd ../ ^-^ pwd /home/vagrant/julien ^-^ cd - ^-^ pwd /home/vagrant/julien/simple_shell exit Usage: exit [STATUS] Exits the shell. The STATUS argument is the integer used to exit the shell. If no argument is given, the command is interpreted as exit 0. Example:

$ ./hsh $ exit env Usage: env Prints the current environment. Example:

$ ./hsh $ env NVM_DIR=/home/vagrant/.nvm ... setenv Usage: setenv [VARIABLE] [VALUE] Initializes a new environment variable, or modifies an existing one. Upon failure, prints a message to stderr. Example:

$ ./sodash $ setenv NAME julien $ echo $NAME julien unsetenv Usage: unsetenv [VARIABLE] Removes an environmental variable. Upon failure, prints a message to stderr. Example:

$ ./hsh $ setenv NAME julien $ unsetenv NAME $ echo $NAME

$ Authors & Copyrights Lutumba Barachel || Ndineze Emmanuel.C
