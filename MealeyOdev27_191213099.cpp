#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct Liste{
	int baglam;
	int baglam0, baglam1;
	bool durum0,durum1;
	struct Liste *sonraki;
}liste;

liste *yeni, *ilk = NULL,*son = NULL, *gecici;

FILE *input, *output, *table;

int baglamSayisi=0;
int baglam=0,baglam0=0,baglam1=0;
bool durum0=false,durum1=false;

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
			printf("%d. eleman 0 girisinde hangi elemana bagli olacak?\n",(i+1));
			scanf("%d",&baglam0);
			printf("%d. eleman 1 girisinde hangi elemana bagli olacak?\n",(i+1));
			scanf("%d",&baglam1);
			printf("%d. eleman 0 girisinde cikis ne olacak?\n",(i+1));
			scanf("%i",&durum0);
			printf("%d. eleman 1 girisinde cikis ne olacak?\n",(i+1));
			scanf("%i",&durum1);
				if(baglam <baglamSayisi){
					fprintf(input,",q%d",baglam+1);
				}
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
	yeni->baglam0 = baglam0;
	yeni->baglam1 = baglam1;
	yeni->durum0 = durum0;
	yeni->durum1 = durum1;
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
	fprintf(table,"Old State | After input 0 | After Input 1 | Character Printed 0 | Character Printed 1\n");
	fprintf(table,"-------------------------------------------------------------------------------------\n");
	printf("Old State\tAfter input 0\tAfter Input 1\tCharacter Printed 0\tCharacter Printed 1\n");
	gecici = ilk;
	while(gecici != NULL){
		fprintf(table,"q%d\t  |\tq%d\t  |\tq%d\t  |\t%i\t  |\t%i\n"
		,gecici->baglam,gecici->baglam0,gecici->baglam1,gecici->durum0,gecici->durum1);
		printf("q%d\t\t\tq%d\t\tq%d\t\t%i\t\t%i\n"
		,gecici->baglam,gecici->baglam0,gecici->baglam1,gecici->durum0,gecici->durum1);
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
		for(int i=0;kelime[i]=='0'|| kelime[i]=='1';i++){
			gecici = ilk;
			while(gecici != NULL){
				if(ilkArama == true){
					fprintf(output,"State:q%d",geciciBaglam);
					printf("State:q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					if(kelime[i]=='0'){
					geciciBaglam = gecici->baglam0;
					}else{
					geciciBaglam = gecici->baglam1;
					}
					fprintf(output,"->q%d",geciciBaglam);
					printf("->q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					ilkArama=false;
					break;
				}else{
					if(kelime[i]=='0' && geciciBaglam == gecici->baglam){
					geciciBaglam = gecici->baglam0;
					fprintf(output,"->q%d",geciciBaglam);
					printf("->q%d",geciciBaglam);
					matris[i]=geciciBaglam;
					break;
				}else if(kelime[i]=='1' && geciciBaglam == gecici->baglam){
					geciciBaglam = gecici->baglam1;
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
	fprintf(output,"\nOutput:");
	printf("\nOutput:");
	for(int i=0;matris[i]!=NULL;i++){
			gecici = ilk;
			while(gecici != NULL){
				if(gecici->baglam == matris[i]){
						if(kelime[i] == '0'){
							fprintf(output,"%i   ",gecici->durum0);
							printf("%i   ",gecici->durum0);	
						}else if(kelime[i] == '1'){
							fprintf(output,"%i   ",gecici->durum1);
							printf("%i   ",gecici->durum1);	
						}
					break;
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
