#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char restaurant[100];
    char city[100];
    int costfortwo;
    char currency[100];
    int price;
    double rating;
    char ratingtext[100];
    int votes;
}Restaurant;

Restaurant r[10000];
//array global + jumlah data global
int data = 0;
Restaurant temp[10000];

void trim(char s[]){
    // hapus spasi/tab depan
    while(s[0] == ' ' || s[0] == '\t'){
        int i = 0;
        while(s[i] != '\0'){
            s[i] = s[i+1];
            i++;
        }
    }

    

    // hapus spasi/tab/\r belakang
    int len = strlen(s);
    while(len > 0 && (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\r')){
        s[len-1] = '\0';
        len--;
    }
}



void readfile(){
    FILE *fp;
    fp = fopen("restaurant.csv", "r");
    if(fp == NULL) {
        perror("ERROR");
        return;
    }
    data = 0;
    //skip header
    char h1[100], h2[100], h3[100], h4[100], h5[100], h6[100], h7[100], h8[100];
    fscanf(fp, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\r\n]%*c",
       h1, h2, h3, h4, h5, h6, h7, h8);

    ///baca data
    while(!feof(fp)){
    char ratingbuf[100];

    int ret = fscanf(fp, " %[^;];%[^;];%d;%[^;];%d;%[^;];%[^;];%d",
                     r[data].restaurant,
                     r[data].city,
                     &r[data].costfortwo,
                     r[data].currency,
                     &r[data].price,
                     ratingbuf,
                     r[data].ratingtext,
                     &r[data].votes);

    if(ret != 8){
        int ch;
        while((ch = fgetc(fp)) !='\n' && ch != EOF);
        continue;
    }

    for(int k = 0; ratingbuf[k] != '\0'; k++){
        if(ratingbuf[k] == ',') ratingbuf[k] = '.';
    }
    r[data].rating = atof(ratingbuf);

    r[data].restaurant[strcspn(r[data].restaurant, "\r")] = 0;
    r[data].city[strcspn(r[data].city, "\r")] = 0;
    r[data].currency[strcspn(r[data].currency, "\r")] = 0;
    r[data].ratingtext[strcspn(r[data].ratingtext, "\r")] = 0;

    trim(r[data].restaurant);
    trim(r[data].city);
    trim(r[data].currency);
    trim(r[data].ratingtext);



    data++;
    if(data >= 8000) break;


}


   

    fclose(fp);

}

//ini buat displaydata
void displayData(int n){

    if (data == 0){
        puts("Tidak ada data yang terbaca.");
        return;
    }
    if(n<= 0){
        puts("n must be a positive integer!");
        return;
    }
    int limit = data;
    if(n>0 && n<limit) limit = n;
    printf("\n%-25s %-20s %-12s %-20s %-12s %-8s %-12s %-6s\n",
       "Restaurant name", "City", "Cost for two", "Currency",
       "Price range", "Rating", "Rating text", "Votes");

for(int i = 0; i < limit; i++){
    printf("%-25s %-20s %-12d %-20s %-12d %-8.1lf %-12s %-6d\n",
           r[i].restaurant,
           r[i].city,
           r[i].costfortwo,
           r[i].currency,
           r[i].price,
           r[i].rating,
           r[i].ratingtext,
           r[i].votes);
    }


    printf("\n");
}


//ini buat searchfile 
void searchfile(){
    if(data == 0){
        puts("Data not Found!");
        return;
    }
    char col[1001];
    char query[1001];

    while(1){
        printf("Choose column: ");
        scanf(" %1000[^\n]", col);
        getchar();
        trim(col);

        if(strcmp(col, "Restaurant name") == 0) break;
        if(strcmp(col, "Restaurant Name") == 0) break;

        if(strcmp(col, "City") == 0) break;

        if(strcmp(col, "Cost for two") == 0) break;
        if(strcmp(col, "Currency") == 0) break;
        if(strcmp(col, "Price range") == 0) break;
        if(strcmp(col, "Rating") == 0) break;
        if(strcmp(col, "Rating text") == 0) break;
        if(strcmp(col, "Votes") == 0) break;
    }
    printf("What data do you want to find?");
    scanf(" %1000[^\n]", query);
    getchar();
    trim(query);

    int found = 0;

    //siapin query numeric kalo dibutuhkan 
    int qint = 0;
    double qdouble = 0.0;

    //kalau rating kalo user ngetik 4, 2 ubah jadi 4.2

    char queryRating[1001];
    strcpy(queryRating, query);
    for(int k = 0; queryRating[k]!= '\0'; k++){
        if(queryRating[k] == ',') queryRating[k] = '.';
    }
    qint = atoi(query);
    qdouble = atof(queryRating);
    

    printf("\n%-25s %-20s %-12s %-20s %-12s %-8s %-12s %-6s\n",
           "Restaurant Name", "City", "Cost for two", "Currency",
           "Price range", "Rating", "Rating text", "Votes");
    for(int i = 0; i<data; i++){
        int ok = 0;
           

    if(strcmp(col, "Restaurant name") == 0 || strcmp(col, "Restaurant Name") == 0){
        if(strcmp(r[i].restaurant, query) == 0) ok =1;
    }
    else if(strcmp(col, "City") == 0){
            if(strcmp(r[i].city, query)==0) ok =1;
        
    }

    else if(strcmp(col, "Currency") == 0){
        if(strcmp(r[i].currency, query) == 0) ok =1;
    }
    else if(strcmp(col, "Rating text") == 0){
        if(strcmp(r[i].ratingtext, query) == 0) ok =1;
    }

    //column integer
    else if(strcmp(col, "Cost for two") == 0){
        if(r[i].costfortwo == qint) ok =1;
    }

    else if(strcmp (col, "Price range") == 0){
        if(r[i].price == qint) ok =1;
    }
    else if(strcmp(col, "Votes")==0){
        if(r[i].votes == qint) ok =1;
    }

    //double column
    else if(strcmp(col, "Rating") == 0){
        double diff = r[i].rating -qdouble;
        if(diff<0) diff = -diff;
        if(diff<0.000001) ok =1;
    }
    if(ok){
        found =1;
        printf("%-25s %-20s %-12d %-20s %-12d %-8.1lf %-12s %-6d\n",
                   r[i].restaurant,
                   r[i].city,
                   r[i].costfortwo,
                   r[i].currency,
                   r[i].price,
                   r[i].rating,
                   r[i].ratingtext,
                   r[i].votes);
    }

}
if(!found){
    printf("\nData not found!\n\n");
}
    

}


int compare(Restaurant a, Restaurant b, char col[]){
    //string
    if(strcmp(col, "Restaurant name") == 0 || strcmp(col, "Restaurant Name") == 0) return strcmp(a.restaurant, b.restaurant);
    if(strcmp(col, "City") == 0)return strcmp(a.city, b.city);
    if(strcmp(col, "Currency") == 0)return strcmp(a.currency, b.currency);
    if(strcmp(col, "Rating text") == 0)return strcmp(a.ratingtext, b.ratingtext);

    //integer
    if(strcmp(col, "Cost for two") == 0){
        if(a.costfortwo<b.costfortwo) return -1;
        if(a.costfortwo>b.costfortwo) return 1;
        return 0;
    }
    if(strcmp(col, "Price range") == 0){
        if(a.price<b.price) return -1;
        if(a.price>b.price) return 1;
        return 0;
    }
    if(strcmp(col, "Votes") == 0){
        if(a.votes<b.votes) return -1;
        if(a.votes>b.votes) return 1;
        return 0;
    }

    //double
    if(strcmp(col, "Rating") == 0){
        if(a.rating <b.rating) return -1;
        if(a.rating >b.rating) return -1;
        return 0;

    }
    return 0;

}

void merge(int l, int m, int rgt, char col[], int asc){
    int i = l;
    int j = m+1;
    int k = l;
    while(i<= m && j<= rgt){
        int cmp = compare(r[i], r[j], col);

        if((asc && cmp <= 0)||(!asc &&cmp>=0)){
            temp[k]= r[i];
            i++;
        }else{
            temp[k] = r[j];
            j++;
        }
        k++;
    }
    while(i<= m){
        temp[k] = r[i];
        i++; k++;
    }
    while(j<= rgt){
        temp[k] = r[j];
        j++; k++;
    }
    for(int x = l; x<= rgt; x++){
        r[x] = temp[x];
    }
}
void mergesort(int l, int rgt, char col[], int asc){
    if(l>=rgt) return;
    int m = (l+rgt)/2;
    mergesort(l, m, col, asc);
    mergesort(m+1, rgt, col, asc);
    merge(l, m, rgt, col, asc);
    
    
}


//ini buat sortdata dengan bantuan mergesort
void sortData(){
    if(data == 0){
        puts("Tidak ada data yang terbaca.");
        return;
    }

    char col[1001];
    char order[1001];
    while(1){
        printf("Choose column: ");
        scanf(" %1000[^\n]", col);
        getchar();

        if(strcmp(col, "Restaurant name") == 0) break;
        if(strcmp(col, "Restaurant Name") == 0) break;
        if(strcmp(col, "City") == 0) break;
        if(strcmp(col, "Cost for two") == 0) break;
        if(strcmp(col, "Currency") == 0) break;
        if(strcmp(col, "Price range") == 0) break;
        if(strcmp(col, "Rating") == 0) break;
        if(strcmp(col, "Rating text") == 0) break;
        if(strcmp(col, "Votes") == 0) break;
    }
    do{
        printf("Sort ascending(asc) or descending(desc)?");
        scanf(" %1000[^\n]", order);
        getchar();
    }while(strcmp(order, "asc") != 0 &&strcmp(order, "desc")!= 0);
    int asc=(strcmp(order, "asc") == 0);
    mergesort(0, data-1, col, asc);
    int limit =10;
    if(data<10) limit = data;

    printf("\n%-25s %-20s %-12s %-20s %-12s %-8s %-12s %-6s\n", "Restaurant Name", "City", "Cost for two", "Currency", "Price range", "Rating", "Rating text", "Votes");
    for(int i =0; i<limit; i++){
        printf("%-25s %-20s %-12d %-20s %-12d %-8.1lf %-12s %-6d\n",
               r[i].restaurant,
               r[i].city,
               r[i].costfortwo,
               r[i].currency,
               r[i].price,
               r[i].rating,
               r[i].ratingtext,
               r[i].votes);
    }
    printf("\n");
}
//ini buat fungsi export
void exportdata(){
    if(data == 0){
        puts("Tidak ada data yang terbaca");
        return;
    }

    char filename[1000];
    char fullname[1000];

    printf("File name: ");
    scanf(" %999[^\n]", filename);
    getchar();
    trim(filename);

    sprintf(fullname, "%s.csv", filename);

    FILE *out = fopen(fullname, "w");
    if(out== NULL){
        perror("Error");
        return;
    }
    fprintf(out, "Restaurant Name, City, Cost for two, Currency, Price range, Rating, Rating text, Votes\n");

    for(int i =0; i<data; i++){
        fprintf(out, "%s,%s,%d,%s,%d,%.1lf,%s,%d\n", r[i].restaurant, r[i].city, r[i].costfortwo,r[i].currency, r[i].price, r[i].rating,r[i].ratingtext,r[i].votes);
    }
    fclose(out);
    printf("Data successfully written to file %s!\n", fullname);

}

//ini buat kata-katanya supaya kek ketikan gitu
void typetext(char text[], int delayMs){
    for(int i = 0; text[i]!='\0'; i++){
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delayMs);
    }
}

int main(){
    readfile();
    while(1){
        printf("What do you want to do?\n");
        printf("1. Display data\n");
        printf("2. Search Data\n");
        printf("3. Sort Data\n");
        printf("4. Export Data\n");
        printf("5. Exit\n");
        printf("Your Choice:");
        int a;
        scanf("%d", &a);
        getchar();
        if(a<1 || a>5){
            printf("Invalid choice! Please input 1-5.\n\n");
            continue;
        }
        //Display
        if(a == 5){
            typetext("Terima kasih, Pak, atas bimbingannya.\n", 50);
            typetext("Jika terdapat kekurangan, saya mohon masukan agar bisa saya perbaiki.\n", 50);
            typetext("Saya berharap nilai saya dapat dipertimbangkan sebaik mungkin.\n", 50);
            return 0;
        }
    
        if(a == 1){
            int n;
            do{
            printf("Number of rows: ");
            scanf("%d", &n);
            getchar();

            if(n<= 0) printf("n must be a positive integer!\n");
            }while(n<= 0);

            displayData(n);
            printf("\nPress ENTER to return to menu...");
            getchar();
            system("cls");
        
            }
        else if(a == 2){
            searchfile();
            printf("\nPress ENTER to return to menu...");
            getchar();
            system("cls");

            }
        if(a == 3){
            sortData();
            printf("\nPress ENTER to return to menu...");
            getchar();
            system("cls");
        
            }
        if(a == 4){
            exportdata();
            printf("\nPress ENTER to return to menu...");
            getchar();
            system("cls");
        
            }
 
        }
    

    return 0;
}
