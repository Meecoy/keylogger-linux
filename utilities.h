#ifndef UTILITIES_H
#define UTILITIES_H


extern const char *key_names[KEY_MAX + 1];
extern FILE *fptr;
extern int fd;

void emergency_exit(int sig);

const char *get_key_name(int code);

#endif
