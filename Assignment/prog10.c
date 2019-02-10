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
char *a="";
scanf("%s", &a);
printf("%s", a);
char *b=a;
if ((strcmp(a, b)&&strcmp(b, a))) { 
printf("%s", a);
}
a=str_add(str_add(str_add(str_add(a, b), a), b), a);
float x=0.0;
return 0; 
 } 
