#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int x,w,a,b,c,e;
char metin1[9999];
char alfabe[]={"abcdefghijklmnoprstuvywxqz"};

float distances [2];
//float calculated_frequencies[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//brigram dizisi
const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
//trigram dizisi
const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
//Ingilizce dilinin frekans degerleri
 const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
 //Almanca dilinin frekans degerleri
 const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };

const char languages[2][8]={"english", "german"};
float calculated_frequencies[20];
float liste1[20];

void filter_str(){

for(w=0; w<strlen(metin1); w++)//metin boyutu kadar donme saglaniyor..
    {
        metin1[w]=tolower(metin1[w]);//tum karakterler kucuk harfe cevriliyor...
        int control;
        for(x=0; x<strlen(alfabe); x++)
        {
            if(metin1[w] == alfabe[x])
            {
                control = 0;
                break;
            }
            else
                control = 1;
        }
        if(control != 0)
            metin1[w] = ' ';//yabanci karakterler bosluk karakteri ile degistiriliyor.
    }
}

void calculate_frequencies_bi(char x[],char y[],int cx){
    int i,j;
    float adet=0;

    for(i=0;i<strlen(x)-strlen(y)+1;i++){

        for(j=0;j<strlen(y);j++){

            if(x[i+j]!=y[j])
                break;

            }

        if(j==strlen(y))//aranan metin bulundu.
            adet++;//metinde kac tane brigram ve trigram oldugunu belirlememize yaramasi icin eklendi.

    }
calculated_frequencies[cx]=adet;//lokal veriler global diziye aktarýlýyor.

printf("%s: %f\n",y,adet);

}

void calculate_frequencies_tri(char x[],char y[],int cx){
    int i,j;
    float adet=0;

    for(i=0;i<strlen(x)-strlen(y)+1;i++){

        for(j=0;j<strlen(y);j++){

            if(x[i+j]!=y[j])
                break;

            }

        if(j==strlen(y))//aranan metin bulundu.
            adet++;//metinde kac tane brigram ve trigram oldugunu belirlememize yaramasi icin eklendi.

    }
calculated_frequencies[cx]=adet;

printf("%s: %f\n",y,adet);

}

void calculate_distances(float x[],float enger[],int gh,float distances1[]){ //almanca ve ingilizce dillerinin frekansindan metnin frekansinin cikarilmasi
    float toplam=0.0;
    int i,j,k;
    for(i=0;i<20;i++){
        if(gh==0){
            toplam=toplam+enger[i]*x[i];

            distances1[1]=toplam;}
        else{
            toplam=toplam+enger[i]*x[i];

            distances1[0]=toplam;}

    }

}
void detect_lang(float asd[]){
float dis1,dis2;
dis1=asd[0];
dis2=asd[1];

    if(dis1<dis2)
        printf("Girilen metin '%s' dilinde yazilmistir.\n",languages[0]);
    else if(dis1>dis2)
        printf("Girilen metin '%s' dilinde yazilmistir.\n",languages[1]);
    else
        printf("Girilen metnin dili tespit edilememistir.\n");
}

void sus(){
printf("***********************************************\n");
}
int main()
{
    printf("Metni giriniz\n");
    gets(metin1);
    filter_str();
    puts(metin1);
    sus();

    for(a=0;a<10;a++){
    calculate_frequencies_bi(metin1,matrix_bigram_strings[a],a);//metindeki brigramlar kontrol ediliyor.
    }
    for(b=0;b<10;b++){
    calculate_frequencies_tri(metin1,matrix_trigram_strings[b],b+10);//metindeki trigramlar kontrol ediliyor.
    }

    sus();
    calculate_distances(calculated_frequencies,frequency_eng,0,distances);
    calculate_distances(calculated_frequencies, frequency_germ,1,distances);

    for(e=0;e<2;e++){
    printf("%f\n",distances[e]);}
    sus();
    detect_lang(distances);
    sus();


    return 0;
}
