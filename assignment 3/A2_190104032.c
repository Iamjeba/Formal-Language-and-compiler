#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>

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
    else if( strlen(arr) == 2 && arr[0] == '<' || arr[0]=='>' || arr[0]=='+' || arr[0]=='/' || arr[1] == '-' || arr[1] == '*' )
    {
        if(arr[1]== '='  )
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
                           "struct","switch","typedef","union","unsigned","void","volatile","while"
                          };

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
        i++;
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

    if( c == 2)
    {
        c = 1;
    }

    return c;
}

char a[10000],b[10000],temp[10000],arr1[1000][50];
int curr = 0;

struct table
{
    char *name;
    char *id_type;
    char *data_type;
    char *scope;
    char *value;
} tab[100];

void insert(int si, char *name, char *id_type, char *data_type, char *scope, char *value)
{
    tab[si].name = name;
    tab[si].id_type=id_type;
    tab[si].data_type=data_type;
    tab[si].scope= scope;
    tab[si].value = value;
}

void display()
{
    int i =0;
    printf("SI.No\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(int i = 0; i<curr; i++)
    {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",i+1,tab[i].name,tab[i].id_type,tab[i].data_type,tab[i].scope,tab[i].value);
    }
}

int lookup(char *name,char *id_type,char *scope)
{
    int i=0;

    for(i=0; i<curr; i++)
    {
        if(strcmp(tab[i].name,name)==0 && strcmp(tab[i].id_type,id_type)==0 && strcmp(tab[i].scope,scope)==0 )
        {
            return i;
        }
    }
    return -1;
}

void set_attribute(int curr, char *value)
{
    tab[curr].value = value;
}

char* check(char *arr)
{
    if(strlen(arr) == 1)
    {
        return arr;
    }
    else if(arr[0]>='0' && arr[0]<='9' )
    {
        return arr;
    }
    else
    {
        return "";
    }
}

struct indx
{
    int id;
    char *name;

} indx[30];

void insert_index(int s, int id, char *name)
{
    indx[s].id = id;
    indx[s].name=name;
}

int id_number(char *arr)
{
    for(int i =0; i<curr; i++)
    {
        if(strcmp(arr,indx[i].name)==0)
        {
            return indx[i].id;
        }
    }

    return -1;
}

void free_space()
{
    for(int i =0; i<curr; i++)
    {
        indx[i].id='\0';
        indx[i].name='\0';
    }
    for(int j =0; j<curr; j++)
    {
        tab[j].data_type='\0';
        tab[j].id_type='\0';
        tab[j].name='\0';
        tab[j].scope='\0';
        tab[j].value='\0';
    }
}

int main(void)
{
    FILE *p1, *p2, *p3, *p4, *p5, *p6;
    char c;
    int flag = 1, i =0, j = 0, k = 0, l = 0, t = 0, a, b=0;
    char array[15];
    array[0]=' ';

    p1 = fopen("input.c","r");
    p2 = fopen("output.txt","w");

    if(!p1)
    {
        printf("\nFile Cannot be opened!");
    }
    else
    {
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
                {
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
                {
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

    p1 = fopen("input.c","r");

    printf("Input C File :\n");
    while((c = fgetc(p1)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n\n\n");

    p2 = fopen("output.txt","r");

    printf("Assignment 1's outtput:\n\n");
    while((c = fgetc(p2)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n\n\n");
    fclose(p2);


    p2 = fopen("output.txt","r");
    p3 = fopen("separated.txt", "w");

    if(!p2)
    {
        printf("\nFile Cannot be opened!");
    }
    else
    {
        int p = 0, s=0;

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
                    s = 1;
                }
                p = 0;
            }
            else if( c == '<' || c =='>' )
            {
                fputc(' ', p3);
                fputc(c,p3);
                k = 1;
            }
            else if ( c == '=' || c =='+' || c =='-' || c =='*' || c=='/' || c=='%')
            {
                if(k == 1)
                {
                    fputc(c,p3);
                    fputc(' ',p3);
                    k = 0;
                    p = 1;
                    s = 0;
                }
                if(s == 1)
                {
                    fputc(c,p3);
                    fputc(' ',p3);
                    s = 0;
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
                    p=0;
                }
                if (s== 1)
                {
                    s = 0;
                }

                fputc(c,p3);
            }
        }

        fclose(p2);
        fclose(p3);

        p3 = fopen("separated.txt", "r");


        printf("Separated Lexems :\n\n");
        while((c = fgetc(p3)) != EOF)
        {
            printf("%c",c);
        }

        printf("\n\n\n");

        p3 = fopen("separated.txt", "r");
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

                    // arr1[a][b] = ' ';


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
                    else if( isIdentifier(array))
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
            arr1[a][b]='\0';
        }
    }

    fclose(p3);
    fclose(p4);

    printf("\n\n");
    printf("Categorized Lexemes: \n\n");

    p4 = fopen("result.txt", "r");
    while((c = fgetc(p4)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n\n\n");
    fclose(p4);

    p3 = fopen("separated.txt", "r");
    p5 = fopen("identifier.txt","w");
    a = 0;

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

                if( isKeyword(array))
                {
                    arr1[a][b]='\0';
                    a++;
                    b =  0;
                    fputs("[", p5);
                    fputs(array, p5);
                    fputs("] ", p5);

                }
                else if( isIdentifier(array))
                {
                    fputs("[Identifier ", p5);
                    fputs(array, p5);
                    fputs("] ", p5);
                    arr1[a][b]='\0';
                    a++;
                    arr1[a][0]='i';
                    arr1[a][1]='d';
                    arr1[a][2]='\0';
                    a++;
                    b = 0;
                }
                else
                {
                    arr1[a][b]='\0';
                    a++;
                    b =  0;
                    fputs("[", p5);
                    fputs(array, p5);
                    fputs("] ", p5);
                }
            }
            else
            {
                array[i] = c;
                arr1[a][b]= c;
                b++;
                i++;
            }
        }
    }
    fclose(p3);
    fclose(p5);

    printf("Categorized Indentifiers: \n\n");

    p5 = fopen("identifier.txt", "r");
    while((c = fgetc(p5)) != EOF)
    {
        printf("%c",c);
    }

    printf("\n\n\n");
    fclose(p5);

    char *scope="global";
    int h, s=0;
    for(h =0; h<a; h++)
    {
        if(strcmp(arr1[h],"id")==0)
        {

            if(strcmp(arr1[h+1],"(")==0)
            {
                if(strcmp(arr1[h-2],"int")==0 || strcmp(arr1[h-2],"float")==0 || strcmp(arr1[h-2],"double")==0 || strcmp(arr1[h-2],"void")==0 || strcmp(arr1[h-2],"char")==0)
                {
                    insert(curr,arr1[h-1],"func",arr1[h-2],scope," ");
                    insert_index(s++,curr,arr1[h-1]);
                    curr++;
                    scope = arr1[h-1];
                    h = h+1;
                }
                else
                {
                    int val = lookup(arr1[h-1],"func","global");
                    if(val == -1)
                    {
                        printf("%c is not declared",arr1[h-1]);
                    }
                    h = h+1;
                }
            }
            else if(strcmp(arr1[h+1],"=")==0)
            {
                if(strcmp(arr1[h-2],"int")==0 || strcmp(arr1[h-2],"float")==0 || strcmp(arr1[h-2],"double")==0 || strcmp(arr1[h-2],"void")==0 || strcmp(arr1[h-2],"char")==0)
                {
                    insert(curr,arr1[h-1],"var",arr1[h-2],scope,check(arr1[h+2]));
                    insert_index(s++,curr,arr1[h-1]);
                    curr++;
                    h +=2;
                }
                else
                {
                    int val = lookup(arr1[h-1],"var",scope);
                    if(val != -1)
                    {
                        set_attribute(val,check(arr1[h+2]));
                        insert_index(s++,val,arr1[h-1]);
                    }
                }
            }
            else if(strcmp(arr1[h+1],";")==0 || strcmp(arr1[h+1],",")==0 || strcmp(arr1[h+1],")")==0)
            {
                if(strcmp(arr1[h-2],"int")==0 || strcmp(arr1[h-2],"float")==0 || strcmp(arr1[h-2],"double")==0  || strcmp(arr1[h-2],"char")==0 )
                {
                    int val = lookup(arr1[h-1],"var",scope);
                    if(val == -1)
                    {
                        insert(curr,arr1[h-1],"var",arr1[h-2],scope," ");
                        insert_index(s++,curr,arr1[h-1]);
                        curr++;
                        h +=2;
                    }
                    else
                    {
                        printf("%c is already declared",arr1[h-1]);
                    }
                }
            }
        }

        else if(strcmp(arr1[h],"}")==0)
        {
            scope = "global";
        }

    }
    printf("\n\nSymbol Table\n\n");
    display();

    p3 = fopen("separated.txt", "r");
    p6 = fopen("output.txt","w");

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

                if(isKeyword(array))
                {
                    fputs("[", p6);
                    fputs(array, p6);
                    fputs("] ", p6);

                }
                else if(isIdentifier(array))
                {
                        int id = id_number(array);
                        fputs("[Identifier ", p6);
                        fputc(id+1+48, p6);
                        fputs("] ", p6);
                        fputs(" ",p6);

                }
                    else
                    {
                        fputs("[", p6);
                        fputs(array, p6);
                        fputs("] ", p6);
                    }
                }
                else
                {
                    array[i] = c;
                    i++;
                }
            }
        }

        fclose(p3);
        fclose(p6);

        printf("\n\nModified token stream: \n\n");

        p6 = fopen("output.txt", "r");
        while((c = fgetc(p6)) != EOF)
        {
            printf("%c",c);
        }

        printf("\n\n\n");
        fclose(p6);

        free_space();

        return 0;
    }
