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
int b =0;
int tmp =0;
scanf("%d", &a);
scanf("%d", &b);
if ((a>b)) { 
tmp=a;
a=b;
b=tmp;
}
while (((a!=1)||(a!=0))) { 
while ((b>a)) { 
b=(b-a);
}
if ((b<0)) { 
b=(b+a);
}
tmp=a;
a=b;
b=tmp;
}
printf("%s", "GCD IS ");
if ((a==1)) { 
printf("%d", 1);
}
else { 
printf("%d", b);
}
printf("%s", "\n");
return 0; 
 } 
