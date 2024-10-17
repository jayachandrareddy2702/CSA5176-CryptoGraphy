#include <stdio.h>
#include<ctype.h>

void casear_cipher(char *text, int k)
{
    char ch;
    for(int i=0;text[i]!='\0';++i)
    {
        ch=text[i];
        if(isupper(ch))
        {
            text[i]=((ch -'A' + k)%26 ) +'A';
        }
        else if(islower(ch))
        {
            text[i]=((ch -'a' + k)%26)+'a';
        }
    }
}
int main()
{
    char text[100];
    int k;
    printf("enter the string: ");
    fgets(text, sizeof(text), stdin);
    do{
        printf("enter the (k) value from 1 to 25 :");
        scanf("%d",&k);
    } while (k<1 ||k>25);
    casear_cipher(text, k);
    printf("encrypted message is: %s",text);
    
}