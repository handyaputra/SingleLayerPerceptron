#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

int main(){
	//public var
	int i, j, n, pil;
	double bobot[8], awalBobot[8]; //bobot before
	double rataBobot[8]; //bobot after
	long twk[52],tiu[52],tkp[52],psi[52],tba[52],wcr[52]; //nilai cabang
	double nilai[52]; //nilai akhir
	
	//main menu
	printf("Ujian Tengah Semester\n");
	printf("Jaringan Syaraf Tiruan\n");
	printf("Perceptron with\n");
	printf("10 - Fold Cross Validation\n");
	printf("----------------------------\n");
	printf("Masukan Pengaturan Bobot : \n");
	printf("1) Default Rata\n");
	printf("2) Random\n");
	printf("3) Manual Input\n");
	printf("Pilihan : "); scanf("%d",&pil);
	
	//cek menu
	if(pil==1){
		printf("\nDefault Rata dipilih\n");
		
		//init bobot awal
		for(i=0;i<6;i++){
			bobot[i] = 100.0/6.0/100;
			awalBobot[i] = bobot[i];
			printf("Bobot %d : %f\n",i+1,bobot[i]);
		}
		
		printf("\n");
	} else if(pil==2) {
		printf("\nRandom dipilih\n");
		
		//init bobot awal
		long total;
		srand(time(NULL)); //func state random
		for(i=0;i<6;i++){
			if(i==5){
				bobot[i] = 100 - total;
			} else {
				bobot[i] = (rand() % (95+i-total)) + 1;	//func random
			}
			total += bobot[i];
			bobot[i] /= 100.0;
			awalBobot[i] = bobot[i];
			printf("Bobot %d : %f\n",i+1,bobot[i]);
		}
		printf("\n");
	} else if(pil==3){
		printf("\nManual Input dipilih\n");
		printf("Masukan antara 1-100\n");
		printf("Pastikan Total Bobot = 100\n");
		
		//init bobot awal
		long total = 0;
		for(i=0;i<6;i++){
			printf("Masukan Bobot ke-%d : ",i+1); scanf("%lf",&bobot[i]);
			total += bobot[i];
			bobot[i] /= 100.0;
			awalBobot[i] = bobot[i];
			printf("Bobot %d : %f\n",i+1,bobot[i]);
		}
		
		//cek total
		if(total!=100){
			printf("\nTotal Tidak Sesuai!!\nRestart Program :v");
			exit(0);
		}
		
		printf("\n");
	} else {
		printf("\nPilihan Salah!!\nRestart Program :v");
		exit(0);
	}
	
	//input data//
	//init jml data
	printf("Masukan Jumlah Data : "); scanf("%d",&n);
	
	//init nilai
	printf("Masukan Nilai : (pisahkan dengan spasi ' ')\n");
	for(i=0;i<n;i++){
		scanf("%ld %ld %ld %ld %ld %ld",&twk[i],&tiu[i],&tkp[i],&psi[i],&tba[i],&wcr[i]);
		scanf("%lf",&nilai[i]);
	}
	
	//training process//
	//init var
	double e, count, comp;
	long epoch, ba, bb, cek;
	bool stop;
	
	printf("\n~ Training Process ~\n");
	
	//10 fold-cross validation
	for(j=1;j<=10;j++){
		bb = (j-1)*5; //batas bawah
		ba = (j*5)-1; //batas atas
		epoch = 1; //init epoch
		stop = false; //init cond 
		
		printf("\nSet ke- %ld\n",j);
		printf("--------------------\n");
		
		//init bobot tiap set
		for(i=0;i<6;i++){
			bobot[i] = awalBobot[i];
		}
		
		//iteration training
		while (stop == false){
			stop = true;
			cek = 0;
			
//			printf("Epoch ke- %ld\n",epoch);
			
			for(i=0;i<n;i++){
				
				//jika set testing
				if((i >= bb) && (i <= ba)){
					continue;
				}
				
				//init comp tiap nilai
				comp = 0;
				comp += twk[i] * bobot[0];
				comp += tiu[i] * bobot[1];
				comp += tkp[i] * bobot[2];
				comp += psi[i] * bobot[3];
				comp += tba[i] * bobot[4];
				comp += wcr[i] * bobot[5];
				e = (nilai[i] - comp) * 0.00001;
	
				//update bobot
				bobot[0] += (0.00001 * twk[i] * e);
				bobot[1] += (0.00001 * tiu[i] * e);
				bobot[2] += (0.00001 * tkp[i] * e);
				bobot[3] += (0.00001 * psi[i] * e);
				bobot[4] += (0.00001 * tba[i] * e);
				bobot[5] += (0.00001 * wcr[i] * e);
				e = abs(nilai[i] - comp);
				
				//cek selisih
				if(e>0.0001){
					cek++;		
				}
			}
			
			//cek error
			if(cek>0){
				++epoch;
				stop = false;
			} else {
				printf("Epoch ke- %ld\n",epoch);
				printf("done.\n");
				stop = true;
			}
		}
		
		//output bobot baru
		printf("\nBobot Nilai Baru\n");
		for(i=0;i<6;i++){
			printf("Bobot ke- %ld: %.11f\n",i+1,bobot[i]);
			rataBobot[i] += bobot[i];
		}
		
		//testing//
		//output result
		printf("\nNo\tHasil\t\tTarget\t\n");
		for(i=bb;i<=ba;i++){
			count = 0;
			count += twk[i] * bobot[0];
			count += tiu[i] * bobot[1];
			count += tkp[i] * bobot[2];
			count += psi[i] * bobot[3];
			count += tba[i] * bobot[4];
			count += wcr[i] * bobot[5];
				
			printf("%d\t%.7f\t%.7f\n",i+1,count,nilai[i]);
		}
	}
	
	//after 10 iteration
	printf("\n====== Setelah 10 Fold-Cross Validation ======\n");
	
	//output bobot baru
	printf("\nBobot Nilai Baru\n");
	for(i=0;i<6;i++){
		rataBobot[i] /= 10;
		printf("Bobot ke- %ld: %.11f\n",i+1,rataBobot[i]);
	}
	
	//output result
	printf("\nNo\tHasil\t\tTarget\t\n");
	for(i=0;i<n;i++){
		count = 0;
		count += twk[i] * rataBobot[0];
		count += tiu[i] * rataBobot[1];
		count += tkp[i] * rataBobot[2];
		count += psi[i] * rataBobot[3];
		count += tba[i] * rataBobot[4];
		count += wcr[i] * rataBobot[5];
				
		printf("%d\t%.7f\t%.7f\n",i+1,count,nilai[i]);
	}
	
	return 0;
}
