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
int a =10;
float b=9.9;
bool x=true;
if (true) { 
tmpi = &a;
int a =*tmpi;
printf("%d", a);
tmpf = &b;
float b=*tmpf;
printf("%f", b);
printf("%s", "\n");
tmpb = &x;
bool x=*tmpb;
if (x)printf("true"); 
else printf("false");
printf("%s", "\n");
float c=0.0;
c=c;
printf("%f", c);
printf("%s", "\n");
if (true) { 
tmpi = &a;
int a =*tmpi;
printf("%d", a);
}
}
return 0; 
 } 
