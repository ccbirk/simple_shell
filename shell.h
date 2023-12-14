#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- the structure for program data.
 * @program_name: name of the executables.
 * @input_line: the pointer to the input read for _getline.
 * @command_name: the pointer to the first command typed by the user.
 * @exec_counter: the number of excecuted commands.
 * @file_descriptor: fd to the input of commands.
 * @tokens: the pointer to array of tokenized input
 * @env: the copy of the environment
 * @alias_list: array of pointers with alias.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - structure for the builtins
 * @builtin: name of the builtin
 * @function: funct to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Initializes the structure with the info of the program */
void initialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Prints the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Reads one line of the standar input*/
int _getline(data_of_program *data);

/* splits each line for the logical operators if it exists */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* it expands variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* appends the str to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the str in tokens using a designed delim */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a str */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Executes a command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If it matches a builtin, executes it */
int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Frees all the field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Closes the shell */
int builtin_exit(data_of_program *data);

/* Changes the current dir */
int builtin_cd(data_of_program *data);

/* set the work dir*/
int set_work_directory(data_of_program *data, char *new_dir);

/* show help infor */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Shows the environ where the shell runs */
int builtin_env(data_of_program *data);

/* create or overrides a variable of environ */
int builtin_set_env(data_of_program *data);

/* deletes a var of environ */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* gets the value of an environ var*/
char *env_get_key(char *name, data_of_program *data);

/* Overwrites the value of the environ var */
int env_set_key(char *key, char *value, data_of_program *data);

/* Removes a key from the environ */
int env_remove_key(char *key, data_of_program *data);

/* prints the current environment */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a str in the standar output */
int _print(char *string);

/* Prints a str in the standar error */
int _printe(char *string);

/* Prints a str in the standar error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a str */
int str_length(char *string);

/* Duplicates a str */
char *str_duplicate(char *string);

/* Compares two strs */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strs */
char *str_concat(char *string1, char *string2);

/* Reverse a str */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to str */
void long_to_string(long number, char *string, int base);

/* convert an str in to a num */
int _atoi(char *s);

/* count the coincidences of character in str */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
