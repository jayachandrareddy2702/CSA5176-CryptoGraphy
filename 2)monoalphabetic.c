#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
void mono(char PT[], char key[])
{
    int k = strlen(key);
    for(int i=0;PT[i]!='\0';++i)
    {
        if(isalpha(PT[i]))
        {
            if(isupper(PT[i]))
            {
                PT[i] = toupper(key[(PT[i] -'A') % k]);
            }
            else{
                PT[i] = tolower(key[(PT[i]-'a') % k]);
            }
        }
    }
}
int main()
{
    char PT[100];
    char *key;
    int k;
    printf("enter the plaintext: \n");
    fgets(PT, sizeof(PT),stdin);
    PT[strcspn(PT, "\n")] = '\0';
    printf("Enter the size of the key: ");
    scanf("%d", &k);
    key = (char *)malloc((k + 1) * sizeof(char));
    printf("Enter the key (at least %d characters): ", k);
    scanf("%s", key);
    mono(PT, key);
    printf("Encrypted text: %s\n",PT);
    free(key);
}