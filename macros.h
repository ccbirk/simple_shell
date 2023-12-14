#ifndef HELPERS_H
#define HELPERS_H
/* Prompt to be printed */
#define PROMPT_MSG "$" /* Needed to work with signal */

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	to change shell working directory.\n\n"\
"	If there is no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	when the arg help is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	the exit of the simple-shell.\n\n"\
"	this exits the shell with a stat of N. If N is omitted, the exit status\n"\
"	the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	the print environment.\n\n"\
"	env command will be printed to complete a list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	this will change or add an environment variable.\n\n"\
"	this will initialize a new environ variable, or modify an existing one\n"\
"	if there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	unsetenv funct removess one var from the environment.\n\n"\
"	if there are not correct numbers of args print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	this will display infor about builtin commands.\n\n"\
"	ill display a brief summary of builtin commands.  If BUILTIN_NAME is\n"\
"	if specified it gives details help on all commands matching BUILTIN_NAME,\n"\
"	if not the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
