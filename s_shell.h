#ifndef S_SHELL_H
#define S_SHELL_H

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

#define PATH_ENV "setenv=\n"
#define PATH_CURRENT "cd=\n"
#define BUFFER_SIZE 1024
#define UNUSED __attribute__((unused))
#define P_MSG "tee@tony$ "
#define PATH_CURRENT "cd=\n"
#define Q "exit=\n"
#define HELP1 "help=\n"
#define UNEN_PATH "unsetenv=\n"
#define PATH_TEE "env=\n"

typedef struct info
{
    char *p_name;
    char *cur;
    char *cmd_name;
    int count;
    int file_info;
    char **tok;
    char **env;
    char **tee;
} list;

typedef struct choicess
{
    char *choices;
    int (*function)(list *val);
} choicess;

int main(int argc, char *argv[], char *env[]);
void init_val(list *val, int argc, char *argv[], char **env);
void err(char *prompt, list *val);
void ctrl_c(int signal_number __attribute__((unused)));

int get_line(list *val);
int logic_ops(char *coms[], int x, char ops[]);
int exc(list *val);
int char_count(char *str, char *c);
int find_process(list *val);
char **locate(list *val);
int inspect_file(char *c);
void free_repeat(list *val);
void free_val(list *val);
void free_pointer(char **array);
int predef(list *val);
int escape(list *val);
int current(list *val);
int sw_dir(list *val, char *ch);
int for_you(list *val);
int jina(list *val);
void replace(list *val);
void processvar(list *val);
int buf_ext(char *buf, char *strconc);

char *stok(char *line, char *delim);
void strtoken(list *val);
char *env_key(char *ind, list *val);
int key(char *ind, char *id, list *val);
int rm_env(char *ind, list *val);
void printenv(list *val);
int env(list *val);
int env_set(list *val);
int env_unset(list *val);
int str_len(char *str);
char *str_dup(char *str);
int str_cmp(char *str1, char *str2, int num);
char *str_con(char *str1, char *str2);
void str_rev(char *str);
int _atoi(char *s);
int print_alias(list *val, char *jina);
char *gel(list *val, char *jina);
int set_gel(char *c, list *val);
int _print(char *str);
int printarr(char *str);
int print_err(int err_code, list *val);
void str_long(long num, char *str, int base);

#endif /* simple shell*/