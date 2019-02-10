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

int main() {
int a =0;
scanf("%d", &a);
printf("%d", a);
int b =123;
float c=123;
int z =(-5);
char *s="gfjhkfdhgjh";
char *t="";
scanf("%s", &t);
printf("%s", s);
scanf("%s", &s);
int x =(-9);
if (strcmp(s, t)==0) { 
printf("%s", s);
}
return 0; 
 } 
