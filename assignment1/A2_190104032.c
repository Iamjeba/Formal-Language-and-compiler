#include<stdio.h>
#include<string.h>
#include <ctype.h>

int isNumericConstant(char *lex)
{
    int i, l,s;
    i =0;

    if(isdigit(lex[i]))
    {
        s = 1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s = 2;
        i++;
    }
    else
    {
        s =0;
    }

    l = strlen(lex);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
            {
                s = 1;
            }
            else if(lex[i]=='.')
            {
                s = 2;
                i++;
                break;
            }
            else
            {
                s = 0;
                break;
            }
        }
    }

    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s = 3;
            i++;
        }
        else
        {
            s = 0;
        }
    }

    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
            {
                s = 3;
            }

            else
            {
                s = 0;
                break;
            }
        }
    }

    if(s == 3)
    {
        s = 1;
        return 1;
    }

    return s;
}

int isSeparator(char *arr)
{
    int c = 0;
    if(strlen(arr) == 1 && arr[0] == ',' || arr[0] == ';')
    {
        c = 1;
    }
    return c;
}

int isParenthesis( char *arr)
{
    int c = 0;
    if(strlen(arr) == 1 && arr[0] == '(' || arr[0] ==')' || arr[0] =='{' || arr[0] == '}' || arr[0] == '\'' || arr[0] == '\"')
    {
        c = 1;
    }
    return c;
}

int isOperator( char *arr)
{
    int c = 0;
    if( strlen(arr) == 1 && arr[0] == '<' || arr[0]=='>' || arr[0]=='=' || arr[0] == '/' || arr[0] =='%' || arr[0] == '+' || arr[0] == '-' || arr[0] == '*')
    {
        c = 1;
    }
    else if( strlen(arr) == 2 && arr[0] == '<' || arr[0]=='>' || arr[0]=='=')
    {
        if(arr[1]=='=' || arr[1] == '/' || arr[1] =='%' || arr[1] == '+' || arr[1] == '-' || arr[1] == '*')
        {
            c = 1;
        }
    }
    return c;
}

int isKeyword(char *arr)
{
    int c = 0;
    char Keyword[32][10]= {"auto","break","case","char","const","continue","default","do","double",	"else",	"enum",	"extern","float","for",	"goto",	"if","int",	"long",	"register",	"return","short","signed","sizeof","static",
                           "struct","switch","typedef","union","unsigned","void","volatile","while"};

    for(int i =0; i<32; i++)
    {
        if(strcmp(Keyword[i],arr)==0)
        {
            c =1;
        }
    }
    return c;
}

int isIdentifier(char *arr)
{
    int c = 0, i =0, l;

    if((isalpha(arr[i])) || (arr[i] =='_'))
    {
        c = 1;
    }

    else
    {
        c = 0;
    }

    l=strlen(arr);

    if(c == 1)
    {
        for(; i<l; i++)
        {
            if(isalpha(arr[i]) || arr[i]=='_' || isdigit(arr[i]))
            {
                c = 2;
            }
            else
            {
                c = 0;
                break;
            }
        }
    }

    return c;
}



int main(void)
{
    FILE *p1, *p2, *p3, *p4;
    char c;
    int flag = 1, i =0, j = 0, k = 0, l = 0, t = 0, a=0;
    char array[15];
    array[0]=' ';

    p1 = fopen("input1.c","r");
    p2 = fopen("output5.txt","w");



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
                if( j == 1)
                {
                    j = 0;
                }
                flag = 0;
                i = 1;
            }
            else if(i==1 && c=='/')
            {
                if( j == 1)
                    j = 0;
                }
                flag = 0;
                i =2;
            }

            else if( i ==2 && c=='\n')
            {
                if( j == 1)
                {
                    j = 0;
                }

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
                if( j == 1)
                {
                    j = 0;
                }
                flag = 1;
                i = 0;
                continue;
            }
            else if(c == '\n')
            {
                if( j == 1)
                {
                    j = 0;
                }
                continue;
            }
            else if ( c == '\t')
            {
                fputc(' ', p2);
                if( j == 1)
                {
                    j = 0;
                }
                continue;
            }
            else if ( c == ' ')
            {

                if( j == 1)
                {
                    j == 2;
                    continue;
                }
                else if(j == 2)
                {
                    j = 0;
                    continue;
                }
                else
                {
                    j = 1;
                }
            }
            else
            {
                if( j == 1)
                    j = 0;
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

    printf("Input C File :\n");
    while((c = fgetc(p1)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n\n\n");


    fclose(p1);

    p2 = fopen("output5.txt","r");
    p3 = fopen("new.txt", "w");

    if(!p2)
    {
        printf("\nFile Cannot be opened!");
    }
    else
    {
        int p = 0;

        while((c=fgetc(p2)) != EOF)
        {

            if ( c == '(' || c ==')' || c =='{' || c == '}' || c == '\'' || c == '\"' || c ==',' || c ==';' || c =='[' || c==']')
            {
                if(k == 1)
                {

                    k = 0;
                }
                if( p == 0)
                {
                    fputc(' ',p3);
                    fputc(c,p3);
                    fputc(' ',p3);
                    p = 1;
                }
                else
                {
                    fputc(c,p3);
                    fputc(' ',p3);
                    p = 1;
                }

            }

            else if( c == ' ')
            {
                if(p == 1)
                {
                    continue;
                }
                else
                {
                    fputc(c,p3);
                }



            }
            else if( c == '<' || c =='>' )
            {
                fputc(' ', p3);
                k = 1;
            else if ( c == '=' || c =='+' || c =='-' || c =='*' || c=='/' || c=='%')
            {
                if(k == 1)
                {
                    fputc(c,p3);
                    fputc(' ',p3);
                    k = 0;
                    p = 1;
                }
                else
                {
                    fputc(' ', p3);
                    fputc(c,p3);
                    fputc(' ',p3);
                    p = 1;
                }
            }
            else
            {
                if(k == 1)

                {
                    fputc(' ',p3);
                    k = 0;
                }
                if( p ==1)
                {
                    p= 0;
                }

                fputc(c,p3);
            }
        }

        fclose(p2);
        fclose(p3);

        p3 = fopen("new.txt", "r");

        printf("Separated Lexems :\n\n");
        while((c = fgetc(p3)) != EOF)
        {
            printf("%c",c);
        }

        printf("\n\n\n");

        p3 = fopen("new.txt", "r");
        p4 = fopen("result.txt","w");

        if(!p3)
        {
            printf("\nFile Cannot be opened!");
        }
        else
        {
            while( (c = fgetc(p3)) != EOF )
            {
                if(c == ' ')
                {
                    array[i] = '\0';
                    i=0;

                    if(isSeparator(array))
                    {
                        fputs("[Separator ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }
                    else if( isParenthesis(array))
                    {
                        fputs("[Parenthesis ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }
                    else if( isOperator(array))
                    {
                        fputs("[Operator ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }
                    else if( isNumericConstant(array))
                    {
                        fputs("[Numeric Constant ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }
                    else if( isKeyword(array))
                    {
                        fputs("[Keyword ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }
                    else if( isIdentifier(array) == 2)
                    {
                        fputs("[Identifier ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);

                    }
                    else
                    {
                        fputs("[Unknown ", p4);
                        fputs(array, p4);
                        fputs("] ", p4);
                    }

                }
                else
                {
                    array[i] = c;
                    i++;
                }
            }

        }
    }
    fclose(p3);
    fclose(p4);

    printf("\n\n");
    printf("Categorized Lexemes \n\n");
    p4 = fopen("result.txt", "r");

    while((c = fgetc(p4)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n");


    fclose(p4);
    return 0;
}
