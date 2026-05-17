#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(){
   char s[101];
   char k[101];
   scanf("%s", s);
   getchar();
   scanf("%s", k);
   getchar();
   int len1 = strlen(s);
   int len2 = strlen(k);

   int prefix = 0;
   int sufix = 0;
   for(int i = 0; i< len1 && i<len2; i++){
         if(s[i] == k[i]){
            prefix ++;
         }else{
            break;
         }
   }
   
   for(int i = len1-1, j = len2-1 ; i>=0 && j>=0; i--, j-- ){
         if(s[i] == k[j]){
            sufix ++;
         }
         else{
            break;
         }
   }

   if(prefix == 0 && sufix == 0){
      printf("No Output\n");
      return 0;
   }
   char result[201];
   int index = 0;
   for (int i = 0; i< prefix; i++){
      result[index] = s[i];
      index ++;
   }

   for(int i = len1 - sufix; i< len1; i++){
      result[index] = s[i];
      index ++;
   }

   
   for(int i = 0; i<index; i++){
      if(result[i]>='A' && result[i]<='Z'){
         result[i] = tolower(result[i]);
      }else if(result[i]>='a' && result[i]<='z'){
         result[i] = toupper(result[i]);
      }
      printf("%c", result[i]);
   }   
   puts("");

      
   

   return 0;
}