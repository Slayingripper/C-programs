#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int pyramid(int rows)
{   int coeficient = 1, space, i, j;
    rows=rows-1;
    for(i=rows; i>=0; i--)
    {
        for(space=1; space <= rows-i; space++)
            printf("   ");

        for(j=0; j <= i; j++)
        {
            if (j==0 || i==0)
                coeficient = 1;
            else
                coeficient = coeficient*(i-j+1)/j;

            printf("%7d", coeficient);
        }
        printf("\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{

   int getvalue;
   char *tester;


  // getvalue=getvalue-1;
   if (argc !=2){  //checks if the valus is an int
    printf("You did not enter a valid number\n");
    return 1;
   }
   getvalue=strtol(argv[1],&tester,10);
    if ((getvalue<1)||(getvalue>20)){  //range check
    printf("VALUE OUT OF RANGE\n!"); //calls the pyramid function6
    return 1;
    }
    else
    pyramid(getvalue);
    //while (rows != 1) {
        // Tell the user that the entry was invalid
     //   printf("You did not enter a valid number\n");
     //   break;
   // }
    //algo();
    return 0;
}
