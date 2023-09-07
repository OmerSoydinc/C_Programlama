#include<stdio.h>
#include<locale.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <time.h>
struct Ogrenci{
char ad[50];
char soyad[50];
char tc[12];
char telefon[12];   //sonunda /0 olduðu için 1 fazla tanýmlandý
int no;
};

void ekle(){

struct Ogrenci ogrenci;

	printf("\n Öðrenci Adýný Giriniz: ");
    scanf("%s",ogrenci.ad);
   
    printf("\n Öðrenci Soyadý Giriniz: ");
    scanf("%s",ogrenci.soyad);
   
    printf("\n Öðrenci TC Kimlik No Giriniz: ");
    scanf("%s",ogrenci.tc);
   
    printf("\n Öðrenci Telefonu Giriniz: ");
    scanf("%s", ogrenci.telefon);
   

    //--------------------------telefon kontrol--------------------------
   
    int telefonUzunluk = strlen(ogrenci.telefon);
   
    while(telefonUzunluk !=11){
    printf("\n Öðrenci Telefonu Hatalý Tekrar Giriniz: ");
    scanf("%s",ogrenci.telefon);
    telefonUzunluk=strlen(ogrenci.telefon);
	}

	//--------------------------tc kontrol--------------------------

	int tcUzunluk=strlen(ogrenci.tc);

	int sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';

	int ilkBasamak =ogrenci.tc[0] - '0';
	
	do{  
		if(tcUzunluk !=11){

			printf("\n Girilen TC 11 Basamaklý Deðil ");
			printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
    		scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    		ilkBasamak =ogrenci.tc[0] - '0';
		}
		
		if(sonBasamak %2){
			printf("\n Girilen TC nin Son Basamaðý 0-2-4-6-8 deðerinde olmalý");
			printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
    		scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    		ilkBasamak =ogrenci.tc[0] - '0';
		}
		
		if(ilkBasamak == 0){
			printf("\n Girilen TC nin Ýlk Basamaðý 0 Olamaz");
			printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
			scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
			ilkBasamak = ogrenci.tc[0] - '0';
		}

		
		// Baþka kayýtlarla karþýlaþtýrma 
		
		struct Ogrenci yedek;
		char aranan_tc[12]; 
		strcpy(aranan_tc,ogrenci.tc);
		int var = 0;
	
		do{
		
			FILE *dosya1 = fopen("ogrenciKayitlari.txt", "r");
		
			while (fscanf(dosya1, "%s %s %s %s %d", yedek.ad, yedek.soyad, yedek.tc, yedek.telefon, &yedek.no) != EOF) {
   
        		if (strcmp(yedek.tc, aranan_tc) == 0) { //eþitse 0 deðerini döndürür
        
        			var =1;
        	
        			printf("\n Girilen TC Baþka Öðrenciye Ait");
					printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
    				strcpy(aranan_tc,ogrenci.tc);	
    			}else{
    				var=0;
				}
    		}
    		
    		strcpy(ogrenci.tc,aranan_tc);
    		fclose(dosya1);
		}while(var);    
	
	
	}while(tcUzunluk !=11 || sonBasamak %2|| ilkBasamak==0);

	
	//--------------------------öðrenci no atama--------------------------

	ogrenci.no = numara();

	//-----------öðrenci bilgilerini dosyaya kayýt iþlmleri -----------------	   
	FILE *dosya;

	dosya = fopen("ogrenciKayitlari.txt","a"); //ekleme modunda açar
	
	if(dosya == NULL) //dosya boþsa oluþtur ve baþtan yaz
	{
		dosya = fopen("ogrenciKayitlari.txt","w");

		fprintf(dosya, "%s %s %s %s %d \n"
		,ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
		
	}else{ //eðer dosya varsa sonuna ekleme yazp

		fprintf(dosya, "%s %s %s %s %d \n",
		ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
	}
	
	fclose(dosya);
	
	//--------------------------Bilgilendirme--------------------------

	printf("\n---------- Kayýt Edilen Öðrencinin Bilgileri---------- ");

	printf("\n Öðrenci Adý: %s" , ogrenci.ad);
   
    printf("\n Öðrenci Soyadý: %s", ogrenci.soyad);
   
    printf("\n Öðrenci TC Kimlik No: %s", ogrenci.tc);
   
	printf("\n Öðrenci Telefon Numarasý: %s", ogrenci.telefon);

    printf("\n Öðrenci Numarasý : %d", ogrenci.no);
}

int numara(){

    return rand() % 100000;
}

void sil(){
	
	FILE *dosya = fopen("ogrenciKayitlari.txt", "r");
    FILE *gecici_dosya = fopen("geciciDosya.txt", "w");
   
	int bulundu=0;
	struct Ogrenci ogrenci;

	char aranan_tc[12];
	char secim;

	printf("\nKaydýný Silmek Ýstediðiniz Öðrencinin TC Numarasýný Giriniz: ");
    scanf("%s", aranan_tc);
	
	while (fscanf(dosya, "%s %s %s %s %d", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, &ogrenci.no) != EOF) {
	
		if (strcmp(ogrenci.tc, aranan_tc) == 0) { //eþitse 0 deðerini döndürür

			printf("\n---------- Kaydý Bulunan Öðrencinin Bilgileri---------- ");

			printf("\n Öðrenci Adý: %s" , ogrenci.ad);
   
    		printf("\n Öðrenci Soyadý: %s", ogrenci.soyad);
   
    		printf("\n Öðrenci TC Kimlik No: %s", ogrenci.tc);
   
			printf("\n Öðrenci Telefon Numarasý: %s", ogrenci.telefon);

			printf("\n *******************************************************");
    		
			printf("\n Kaydý Silmek Ýstediðinizden Eminseniz E veya e'yi Tuþlayýnýz? ");
   
			getchar();
			scanf("%c",&secim);
   
   			if(secim=='e'|| secim=='E'){
			   bulundu = 1;  // silmek istiyorsa gecici dosyaya bu kaydý kaydetmeyecek diðer kayýtlarý oraya kopyalayacak
			   printf("\n Öðrencinin Kaydý Silinmiþtir....");
			}
			
		}else{
        	fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
			}
    }
   	
	fclose(dosya);
    fclose(gecici_dosya);  //dosyalar kapatýlýyor.

    if (bulundu==1) {
        remove("ogrenciKayitlari.txt");  //dosyayý sil
        rename("geciciDosya.txt", "ogrenciKayitlari.txt");   //geciciyi ->  ogrenciKayitlari olarak isim deðiþtir
    } else {
        printf("\n Aradýðýnýz TC kimlik numarasýna sahip öðrenci bulunamadý.\n");
        remove("geciciDosya.txt");
    }
}

void guncelle(){

    FILE *dosya = fopen("ogrenciKayitlari.txt", "r");
    FILE *gecici_dosya = fopen("geciciDosya.txt", "w");
   
    int bulundu = 0;
    struct Ogrenci ogrenci;
   
    char aranan_tc[12];
   
    printf("\nKaydýný Güncellemek Ýstediðiniz Öðrencinin TC Numarasýný Giriniz: ");
    scanf("%s", aranan_tc);
   

    while (fscanf(dosya, "%s %s %s %s %d", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, &ogrenci.no) != EOF) {
   
        if (strcmp(ogrenci.tc, aranan_tc) == 0) { //eþitse 0 deðerini döndürür

			bulundu = 1;
       
        	printf("\n---------- Kaydý Bulunan  Öðrencinin Bilgileri---------- ");

			printf("\n Öðrenci Adý: %s" , ogrenci.ad);
   
    		printf("\n Öðrenci Soyadý: %s", ogrenci.soyad);
   
    		printf("\n Öðrenci TC Kimlik No: %s", ogrenci.tc);
   
			printf("\n Öðrenci Telefon Numarasý: %s", ogrenci.telefon);

    		printf("\n Öðrenci Numarasý : %d", ogrenci.no);
       
	//-----------------------------------------------------------------
       
			printf("\n :.....Öðrencinin Yeni Bilgilerini Giriniz...... \n");
           
        	printf("\n Öðrenci Adýný Giriniz: ");
    		scanf("%s",&ogrenci.ad);
   
    		printf("\n Öðrenci Soyadý Giriniz: ");
    		scanf("%s",&ogrenci.soyad);
   
    		printf("\n Öðrenci TC Kimlik No Giriniz: ");
    		scanf("%s",&ogrenci.tc);
   
    		printf("\n Öðrenci Telefonu Giriniz: ");
    		scanf("%s",&ogrenci.telefon);

    //--------------------------telefon kontrol--------------------------
   
    		int telefonUzunluk=strlen(ogrenci.telefon);
   
    		while(telefonUzunluk !=11){
    			printf("\n Öðrenci Telefonu Hatalý Tekrar Giriniz: ");
    			scanf("%s",&ogrenci.telefon);
    			telefonUzunluk=strlen(ogrenci.telefon);
			}

	//--------------------------tc kontrol--------------------------

			int tcUzunluk=strlen(ogrenci.tc);

			int sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';

			int ilkBasamak =ogrenci.tc[0] - '0';
			
			do{  
				
				if(tcUzunluk !=11){

					printf("\n Girilen TC 11 Basamaklý Deðil ");
					printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
   
				}
				
				if(sonBasamak %2){

					printf("\n Girilen TC nin Son Basamaðý 0-2-4-6-8 deðerinde olmalý");
					printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
				}
				
				if(ilkBasamak == 0){

					printf("\n Girilen TC nin Ýlk Basamaðý 0 Olamaz");
					printf("\n Öðrenci TC Kimlik No Tekrar Giriniz: ");
					scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
					ilkBasamak =ogrenci.tc[0] - '0';
				}  

			}while(tcUzunluk !=11 || sonBasamak %2  ||ilkBasamak!=0);

//--------------------------öðrenci no atama--------------------------

			// ogrenci.no = numara();   kayýt güncellemede numara deðiþmeyecek ayný kalacak


			printf("\n---------- Kayýt Edilen Öðrencinin Bilgileri---------- ");

			printf("\n Öðrenci Adý: %s" , &ogrenci.ad);
   
    		printf("\n Öðrenci Soyadý: %s", &ogrenci.soyad);
   
    		printf("\n Öðrenci TC Kimlik No: %s", &ogrenci.tc);
   
			printf("\n Öðrenci Telefon Numarasý: %s", &ogrenci.telefon);

    		printf("\n Öðrenci Numarasý : %d", &ogrenci.no);
   
    		fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
       
    	} else {
    		
				fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
            //burayý tc bulununcaya kadar olan kayýtlarý ve bulunduktan sonrasýný gecici dosyaya kayýt etmek için yazdým
        }
    }

    fclose(dosya);
    fclose(gecici_dosya);

    if (bulundu) {
        remove("ogrenciKayitlari.txt");  //dosyayý sil
        rename("geciciDosya.txt", "ogrenciKayitlari.txt");   //geciciyi ->  ogrenciKayitlari olarak isim deðiþtir
    } else {
        printf("Aradýðýnýz TC kimlik numarasýna sahip öðrenci bulunamadý.\n");
        remove("geciciDosya.txt");
    }
}



void listele(){

	FILE *dosya = fopen("ogrenciKayitlari.txt", "r"); // okuma modunda açýlýr
   
    int i, sayac=0;

    char satir[100]; // Okunan satýrý tutmak için bir tampon olþturuldu
    
	while (fgets(satir, sizeof(satir), dosya) != NULL) {
        // Satýrý boþluða göre bölelim
        char *kelime = strtok(satir, " \t\n");

        // Bölünmüþ kelimeleri yazdýralým
        while (kelime != NULL) {
        	printf("---------- %d . Öðrencinin Bilgileri ----------------\n", sayac+1);
        	for(i=0;i<5;i++){
        		if(i==0){
        			printf("Adý: %s\n", kelime);
        			kelime = strtok(NULL, " \t\n");
				}else if(i==1){
					printf("Soyadý: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==2){
					printf("TC: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==3){
					printf("Telefon: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==4){
					printf("Numara: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");							
				}
			}
        	sayac++;
    	}
    }    
    
	printf("\n-----------------------------------------------------\n Sistemde %d Öðrenci Kaydý Bulunmaktadýr... \n-----------------------------------------------------\n",sayac);
	
	fclose(dosya);
}

void menu(){

printf("\n!!!!!! Türkçe Karakter Kullanmayýnýz !!!!!!");
printf("\n*------------------Menü-------------------*");
printf("\n| Öðrenci Eklemek     Ýçin 1              |");
printf("\n| Öðrenci Silmek      Ýçin 2              |");
printf("\n| Öðrenci Güncellemek Ýçin 3              |");
printf("\n| Öðrenci Listesi     için 4'ü tuþlayýnýz |");
printf("\n*-----------------------------------------*");
}

int main()
{
	setlocale(LC_ALL, "Turkish");
	srand(time(NULL));

	char secim;
	int islem;

	do{
		menu();
		printf("\n Yapmak Ýstediðiniz Ýþlemi Seçiniz:");
    	scanf("%d",&islem);
       
		switch(islem){
        	case 1:
        		ekle();
         	   	break;
       		case 2:
     			sil();
     			break;
        	case 3:
            	guncelle();
        	    break;
        	case 4:
            	listele();
            	break;
        	default:
            	printf("Hatalý Giriþ Yaptýnýz");
    	}
    
		printf("\n------------------------------------\n");

		printf("\nMenü  Ýçin E \nÇýkýþ Ýçin H: ");
		getchar();
		scanf("%c",&secim);
	}while(secim == 'e' || secim == 'E');
	return 0;
}
