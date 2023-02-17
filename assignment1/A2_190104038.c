#include<stdio.h>
int main(void)
{
    FILE *p1, *p2;
    char c;
    int flag = 1, i =0, j = 0;

    p1 = fopen("input1.c","r");
    p2 = fopen("output.txt","w");

    if(!p1)
    {
        printf("\nFile Cannot be opened!");
    }
    else
    {
//conditions
        while((c=fgetc(p1)) != EOF)
        {

            if( c == '/' && i ==0)
            {
                flag = 0;
                i = 1;
            }
            else if(i==1 && c=='/')
            {
                flag = 0;
                i =2;
            }

            else if( i ==2 && c=='\n')
            {

                flag = 1;
                i = 0;
                continue;
            }
            else if( i==1 && c=='*')
            {
                flag = 0;
                i =3;
            }
            else if( i ==3 && c =='/')
            {
                flag = 1;
                i = 0;
                continue;
            }
            else if(c == '\n')
            {
                continue;
            }


            if ( c == ' ')
            {
                if( j == 1)
                {
                     j = 2;
                    continue;
                }
                else if (j == 2)
                {
                    j = 3;
                    continue;
                }
                else if ( j == 3)
                {
                    j = 0;
                    continue;
                }
                else
                {
                    j = 1;
                }
            }


            if(flag == 1)
            {
                fputc(c,p2);
            }

        }
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("input1.c","r");
    p2 = fopen("output.txt", "r");

    while((c = fgetc(p1)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n");

    while((c=fgetc(p2)) != EOF)
    {
        printf("%c",c);
    }

    fclose(p1);
    fclose(p2);

    printf("\n");

    return 0;
}
