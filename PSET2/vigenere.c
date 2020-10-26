#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c); // tek bir karakterin donusumunu yapan fonk
string transform(string entry, int* num, int k); // string'in donusumunu yapan fonk
int check_kwrd(string kwrd); //keyword'un sadece harflerden olustugunu dogrulayan program

int main(int argc, string argv[])
{
    if(argc==1)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    int cntr = check_kwrd(argv[1]);
    // iki kelime girilmediyse veya ikincisi sadece harflerden olusmuyorsa 
    if(argc!=2 || cntr>0)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
        
        // anahtar üst seviyede tanımlanmak zorunda
        int key[strlen(argv[1])];
        int c=0;

        // keyword'un butun harflerini teker teker donustur
        for(int j=0,n=strlen(argv[1]);j<n;j++) 
        {
            key[j]=shift(argv[1][j]); 
        }
    
        // sifrelenecek string'i al
        string s = get_string("plaintext: ");
        
        // transform fonksiyonunun uygulanmasında sorun var. key'i nasıl baglamak lazım? (!!)
        string exit = transform(s, key, strlen(argv[1])); 
        printf("ciphertext: %s\n",exit);
}

int shift(char c)
{
    int num =(int) toupper(c)-65;
    return num;  
}


// sifrelenecek string, donusturulmus keyword ve keyword'un eleman sayısı giriliyor
// num ile ilgili sorun mu var(?)
string transform(string entry, int* num, int k)
{
    int j = 0;
    for (int i=0, n=strlen(entry); i<n; i++)    
    {
        if(65<=entry[i] && entry[i]<=90)
        {
            if(entry[i]+num[j%k] > 90)
            {
                entry[i] = ((entry[i]-65+num[j%k])%26) +65;
                j++;
            } 
            else 
            {
                entry[i] = entry[i]+num[j%k];
                j++;
            }               
        } 
        else if (97<=entry[i] && entry[i]<=122)
            {
                if((entry[i]+num[j%k])>122)
                {
                    entry[i] = ((entry[i]-97+num[j%k])%26) +97; 
                    j++;               
                } 
                else 
                {
                    entry[i] = entry[i]+num[j%k];
                    j++;
                }
            }
        
    }    
    return entry;
}

int check_kwrd(string kwrd)
{
    int cnt = 0;
    for (int i=0, n=strlen(kwrd); i<n; i++)
    {
        if(!isalpha(kwrd[i]))
        {
            cnt++;
        }
    }
    return cnt;
}
