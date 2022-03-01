#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct Liste{
	int baglam;
	int baglamA, baglamB;
	bool durum;
	struct Liste *sonraki;
}liste;

liste *yeni, *ilk = NULL,*son = NULL, *gecici;

FILE *input, *output, *table;

int baglamSayisi=0;
int baglam=0,baglamA=0,baglamB=0;
bool durum=false;

void Ekle();
void Listele();
void Menu();
void Giris();
void Temizle();
void KelimeBulma();

int main(){
	input = fopen("INPUT.txt","w");
	fclose(input);
	output = fopen("OUTPUT.txt","w");
	fclose(output);
	table = fopen("GECISTABLOSU.txt","w");
	fclose(table);
	Giris();
	Menu();
	return 0;
}

void Temizle(){
	getchar();
	getchar();
	system("CLS");
}

void Giris(){
	
	input = fopen("INPUT.txt","w");
	fprintf(input,"Q={q1");
	printf("Kac Adet Q elemani olacak?\n");
	scanf("%d",&baglamSayisi);
		for(int i=0;i<baglamSayisi;i++){
			baglam = i+1;
			printf("%d. eleman A durumunda hangi elemana bagli olacak?\n",(i+1));
			scanf("%d",&baglamA);
			printf("%d. eleman B durumunda hangi elemana bagli olacak?\n",(i+1));
			scanf("%d",&baglamB);
			printf("%d. eleman durumu ne olacak?\n",(i+1));
			scanf("%i",&durum);
			fprintf(input,",q%d",baglam+1);
			Ekle();
		}
		fprintf(input,"}\n");
		fprintf(input,"Alphabet:{a,b}\n");
		fprintf(input,"Output:{0,1}\n");
	Temizle();
	fclose(input);
}

void Ekle(){
	yeni = (liste *)malloc(sizeof(liste));
	yeni->baglam = baglam;
	yeni->baglamA = baglamA;
	yeni->baglamB = baglamB;
	yeni->durum = durum;
	yeni->sonraki = NULL;
		if(ilk ==NULL){
			ilk = yeni;
			son = ilk;	
		}else{
			son->sonraki = yeni;
			son = son->sonraki;
		}
}

void Listele(){
	table = fopen("GECISTABLOSU.txt","w");
	fprintf(table,"Old State | After input A | After Input B | Character Printed\n");
	fprintf(table,"-------------------------------------------------------------\n");
	printf("Old State\tAfter input A\tAfter Input B\tCharacter Printed\n");
	gecici = ilk;
	while(gecici != NULL){
		fprintf(table,"q%d\t  |\tq%d\t  |\tq%d\t  |\t%i\n"
		,gecici->baglam,gecici->baglamA,gecici->baglamB,gecici->durum);
		printf("q%d\t\t\tq%d\t\tq%d\t\t%i\n"
		,gecici->baglam,gecici->baglamA,gecici->baglamB,gecici->durum);
		gecici = gecici->sonraki;
	}
	Temizle();
	fclose(table);
}

void KelimeBulma(){
	
	output = fopen("OUTPUT.txt","a");
	
	int geciciBaglam=1;
	bool ilkArama=true;
	char kelime[50];
	int matris[30];
	
	printf("Kelimeyi Giriniz:");
	scanf("%s",kelime);
		for(int i=0;kelime[i]=='a'|| kelime[i]=='b';i++){
			gecici = ilk;
			while(gecici != NULL){
				if(ilkArama == true){
					fprintf(output,"State:q%d",geciciBaglam);
					printf("State:q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					if(kelime[i]=='a'){
					geciciBaglam = gecici->baglamA;
					}else{
					geciciBaglam = gecici->baglamB;
					}
					fprintf(output,"->q%d",geciciBaglam);
					printf("->q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					ilkArama=false;
					break;
				}else{
					if(kelime[i]=='a' && geciciBaglam == gecici->baglam){
					geciciBaglam = gecici->baglamA;
					fprintf(output,"->q%d",geciciBaglam);
					printf("->q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					break;
				}else if(kelime[i]=='b' && geciciBaglam == gecici->baglam){
					geciciBaglam = gecici->baglamB;
					fprintf(output,"->q%d",geciciBaglam);
					printf("->q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					break;
				}	
			}
			gecici= gecici->sonraki;	
		} 
	}
	gecici=ilk;
	fprintf(output,"\nOutput:%i  ",gecici->durum);
	printf("\nOutput:%i  ",gecici->durum);
	for(int i=0;matris[i]!=NULL;i++){
			gecici = ilk;
			while(gecici != NULL){
				if(gecici->baglam == matris[i]){
					fprintf(output,"%i   ",gecici->durum);
					printf("%i   ",gecici->durum);	
				}
			gecici= gecici->sonraki;	
		} 
	}
	fprintf(output,"\n");
	Temizle();
	fclose(output);
}

void Menu(){
	int secim=0;
	printf(	"Secim Yapiniz:\n"
			"1-Kelime Calistirma\n"
			"2-Listele\n"
			"3-Cikis\n"
			"Secim:");
	scanf("%d",&secim);
		switch(secim){
			case 1:{
				KelimeBulma();
				break;
			}
			case 2:{
				Listele();
				break;
			}
			case 3:{
				printf("Programdan Cikiliyor...");
				exit(0);
				break;
			}
			default:{
				printf("Hatali Deger!!!");
				break;
			}
		}
	Temizle();
	Menu();
}
