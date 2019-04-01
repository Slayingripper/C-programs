#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
  register unsigned int getvalue,getvalue2,getvalue3;
char *tester;
getvalue=0;
getvalue2=0;
getvalue3=0;
if (argc !=4){
     printf("too many values\n");
     return 1;
 }

getvalue=strtol(argv[1],&tester,10);
getvalue2=strtol(argv[2],&tester,10);
getvalue3=strtol(argv[3],&tester,10);

int a,b,c;
a=getvalue;
b=getvalue2;
c=getvalue3;
if(*tester != '\0'){
printf("hey scotty...jesus man!");
return 1;
}
if(c>255 || c<=0){
  printf("value out of range\n");
  return 1;
}
if(a<=0 ||b<=0 ){
  printf("value out of range\n");
  return 1;
}

if(*tester != '\0'){
printf("hey scotty...jesus man!\n");
return 1;
}


int i;
i=a+b+c;
printf("%d\n",i );
  return 0;
}
