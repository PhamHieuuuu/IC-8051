#include <REGX51.H>
#include <Thu_Vien_LCD.h>

#define INA1 P2_0
#define INA2 P2_1
#define INB1 P2_2
#define INB2 P2_3

#define N P2_4
#define P P2_5
#define ON_OFF P2_6

int i;
bit on_off = 0;   
unsigned char flag = 0;

void delay(int ms){
	for(i=0;i<ms;i++){
	TMOD = 0x01;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
		}
	}

void thuan(){
  INA1=0;
	INA2=0;
	
	INB1=1;
	INB2=1;
}

void nghich(){
  INA1=1;
	INA2=1;
	
	INB1=0;
	INB2=0;
}

void off(){
	INA1=0;
	INA2=0;
	
	INB1=0;
	INB2=0;
	
}

int main(){
	 LCD_Init();
	 LCD_Clear();
	 LCD_Gotoxy(0,0);
	 LCD_Puts("  Chon Chieu DC");
	 LCD_Gotoxy(0,1);
	 LCD_Puts("    Chon Mode");
   while(1){
		 
		  if(ON_OFF==0)	{
				on_off=!on_off;
					if(on_off==1){ 
					thuan();
					LCD_Gotoxy(0,1);
					LCD_Puts("     DC: ON       ");
					flag=1;
				}
			  else {
					off();
					LCD_Gotoxy(0,1);
					LCD_Puts("     DC: OFF      ");
					flag=0;
				}
			  delay(300);
		 }

		if(N==0 & flag==1){
				thuan();
				LCD_Gotoxy(0,1);
				LCD_Puts("  Chieu: Thuan        ");
				delay(300); }
		 else if (P==0 & flag==1){
				nghich();
				LCD_Gotoxy(0,1);
				LCD_Puts("  Chieu: Nghich        ");
				delay(300);		 
		 }		 
		 
	 }
 }