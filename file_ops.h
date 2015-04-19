#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include "mem_ops.h"

void WriteFile(char *file,char *str);
void convert_payload(char *NameFile,char *output, char *tamper);
long FileSize(const char *file);
char *Random_linefile(char * namefile);
