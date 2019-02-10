#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

char *str_add(char *s1, char *s2) {
    char *s3 = (char *)malloc((strlen(s1) + strlen(s2)) * sizeof(char));
    return strcat(strcat(s3, s1), s2);
}

int bool_inp() {
    char *boolean = (char *)malloc(sizeof(char) * 5);

    scanf("%s", boolean);

    if(!strcmp(boolean, "true"))
        return 1;
    if(!strcmp(boolean, "false"))
        return 0;
    return -1;
}

int *tmpi;
float *tmpf;
char **tmps;
bool *tmpb;

int main() {
int a =0;
while (true) { 
tmpi = &a;
int a =*tmpi;
}
int b =0;
bool c=false;
char *z=str_add(str_add("jdhg", "shjfhg"), "dkhjgh");
z="Aks";
char *s="";
s=str_add(str_add(str_add("Akshay", "Gopalakrishnan"), "Student"), "COMP520");
return 0; 
 } 
