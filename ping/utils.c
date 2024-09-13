#include "includes/ping.h"


bool puterr(char *error){
    write(2, error, strlen(error));
    return FALSE;
}

void puterr_and_exit(char *error, int exit_code){
    write(2, error, strlen(error));
    exit(exit_code);
}