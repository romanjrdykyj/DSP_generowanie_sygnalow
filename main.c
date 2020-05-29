#include <dsplib.h>

const long d = ((long)100*22368)>>14;
#define rozmiar 5000
int probki[rozmiar];
int dsplib[rozmiar];
//unsigned int fs = 48000;
//unsigned int f = 100;



void saw(int* wsk_tablicy, unsigned int l_el_tablicy, int krok){  //sygnal piloksztaltny
	static int amplituda = 0;		//akumulator
	int i;
	int y;
	for(i = 0; i<l_el_tablicy; i++){
		y = amplituda;
		wsk_tablicy[i]=y;
		amplituda = amplituda + krok;		//nastepuje przepelnienie zakresu
	}
}

void rect(int* wsk_tablicy, unsigned int l_el_tablicy, int krok, int progowa){ //sygnal prostokatny
		static int amplituda = 0;
		int i;
		int y;
		for(i = 0; i<l_el_tablicy; i++){
			y = amplituda;
			if(y>=progowa)
			{
				wsk_tablicy[i]=32767;
			}
			if(y<progowa)
			{
				wsk_tablicy[i]=-32768;
			}
			amplituda = amplituda + krok;
		}
}



void tri(int* wsk_tablicy, unsigned int l_el_tablicy, int krok){		//sygnal trojkatny
		static int amplituda = 0;
		int i;
		int y;

		for(i = 0; i<l_el_tablicy; i++){
			y = ((amplituda < 0 ? -amplituda : amplituda)-16384-1)<<1;
			wsk_tablicy[i]=y;
			amplituda = amplituda + krok;
		}
}

void sint(int* wsk_tablicy, unsigned int l_el_tablicy, int krok){ //sygnal sinus
		const long a7 = -2455;
		const long a5 = 10445;
		const long a3 = -21167;
		const long a1 = 12868;
		static int amplituda = 0;
		static int amplituda_prim = 0;
		static int abs = 0;
		int i;
		long y;
		int x;
		int x2;
		int x3;
		int x5;
		int x7;
		for(i = 0; i<l_el_tablicy; i++){
			amplituda_prim = amplituda;
			abs = (amplituda < 0 ? -amplituda : amplituda);
			if( abs > 16384 ){
				abs = 32767 - abs;
			}
			x = abs;
			x2 = _smpy(x,x);
			x3 = _smpy(x2,x);
			x5 = _smpy(x2,x3);
			x7 = _smpy(x2,x5);
			y = (a1*x) + (a3*x3) + (a5*x5) + (a7*x7);
			if(amplituda_prim < 0){
				y = y*(-1);
			}
			y = y + (1 << 11);
			y = y >> 12;
			wsk_tablicy[i] = (int)y;
			amplituda = amplituda + krok;
		}
}


void main(void) {


	saw(probki, rozmiar, d);
	//rect(probki, rozmiar, d, 0);
	//tri(probki, rozmiar, d);
	//sine((DATA*)probki, (DATA*)dsplib, rozmiar);		 //funkcja generujaca sinusa z bilbioteki DSPlib
	//rand16init();										//funckja generujaca liczby losowe
	//rand16((DATA*)dsplib, rozmiar); 					//funkcja generujaca szum z bilbioteki DSPlib

	//sint(probki, rozmiar, d);

	while (1); // do not exit
}
