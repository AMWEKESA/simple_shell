#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define PROMPT_MSG "$$< "
#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1024
#define HELP_CD_MSG "cd=\n"\
#define HELP_EXIT_MSG "exit=\n"\
#define HELP_SETTING_MSG "setting=\n"\
#define HELP_GETSETTING_MSG "getsetting=\n"\
#define HELP_REMSETTING_MSG "remsetting=\n"\
#define HELP_MSG "help=\n"\

typedef struct info
{
    char *process;
    char *input_line;
    char *cmd;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **setting;
    char **a_list;
} list;

typedef struct builtins
{
    char *builtin;
    int (*function)(list *val);
} builtins;

void initial(list *val, int arc, char *argv[], char **setting);
void show_prompt(char *prompt, list *val);
void _ctrl_c(int opr UNUSED);
int get_line(list *val);
int logic_operation(char *arr_commands[], int i, char arr_operators[]);
void process_variables(list *val);
void process_more(list *val);
int append(char *buffer, char *src_str);
void separate_String(list *val);
char *str_tok(char *line, char *sep);
int execute(list *val);
int check_predefined(list *val);
char **route(list *val);
int find_program(list *val);
void free_pointer(char **directories);
void free_repeat(list *val);
void free_space(list *val);
int terminate(list *val);
int current_dir(list *val);
int set_working_dir(list *val, char *new_dir);
int alias_toolkit(list *val);
int show_setting(list *val);
int get_setting(list *val);
int rem_setting(list *val);
char *get_variable(char *name, list *val);
int set_variable(char *ind, char *value, list *val);
int rem_variable(char *ind, list *val);
void print_variable(list *val);
int _print(char *string);
int print_out(char *string);
int print_err(int errorcode, list *val);
int str_len(char *string);
char *str_dup(char *string);
int str_cmp(char *str1, char *str2, int num);
char *str_con(char *str1, char *str2);
void str_rev(char *string);
void int_str(long num, char *string, int ch);
int _atoi(char *s);
int char_count(char *string, char *ch);
int add_alias(list *val, char *alias);
char *show_alias(list *val, char *alias);
int rem_alias(char *a_str, list *val);

#endif /* SHELL_H */
