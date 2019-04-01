#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
int main(int argc, char const *argv[])
{
  //char buffer[999983];
  
    register unsigned int getvalue,getvalue2;
char *tester;
  getvalue=0;
  getvalue2=0;
  if (argc !=3){
      printf("too many values\n");
      return 1;
  }
   getvalue=strtol(argv[1],&tester,10);
   getvalue2=strtol(argv[2],&tester,10);
   
   register unsigned int min, max, i, flag;
    min=getvalue;
    max=getvalue2;
    //printf("Enter two numbers(intervals): ");
    //scanf("%d %d", &low, &high);
//if(max>=10000000   && min>=10000000){
  //  printf("wow boy the numbers is outaa range");
  //  return 1;
//}

if(max>1000000   && min<=1){
    printf("wow boy the numbers is outaa range");
    return 1;
}
if(*tester != '\0'){
printf("hey scotty...jesus man!");
return 1; 

}

    if(min==1){
    printf("wrong\n");
    return 1;
    }
    if(max>1000000){
    printf("wrong\n");
    return 1;
}
    //fprintf(stderr, "%d\n",min );
    if(max<=1000000   && min>=1)
    {
        
        while (min <=max)
    {
        flag = 0;
        
        for(i =2; i <= sqrt(min); i++)
        {
            if(min % i == 0)
            {
                flag = 4;
                break;
            }
        }

        if (flag == 0)
            fprintf(stderr, "%d\n",min );
            //sprintf(tester[a],"%d\n",min);
            //sprintf(buffer, "%d\n",low);
            //printf("%s\n",buffer );
             min++;

    }
    }
    return 0;
}
