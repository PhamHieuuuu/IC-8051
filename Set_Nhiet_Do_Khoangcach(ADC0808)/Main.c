#include<REGX51.H>
#include <Thu_Vien_LCD.h>

#define CL P2_0  
#define ST P2_1  // Muc 1 de chuyen doi
#define EOC P2_2 // Xuat muc 1 khi chuyen doi ADC xong
#define OE P2_3 // Muc 1 de doc gia tri Digital
#define ALE P2_4 // chot cong IN0-7
#define A P2_5 
#define B P2_6 
#define C P2_7 

// khai báo Cho SRF04
#define TRIG P1_0
#define ECHO P1_1

// khai bao nut nhan
#define UP P1_2
#define DOWN P1_3
#define Select_Mode P1_4


// các bien tinh nhiet do
int kq; 
int Set_Nhiet_Do=25;
int i;

// cac bien cho SRF
int khoangcach, time, dem, convert_us;

void delay(int ms){
  for(i=0;i<ms;i++){
	TMOD=0x01;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
  while(TF0==0);
  TR0=1;
  TF0=0;		
	}
}


void Clock(){
  CL=0;
	CL=1;
}

void IN_x(unsigned char ad){

	A = ad & 0x01;
	B = ad & 0x02;
	C = ad & 0x04;
}

unsigned char ADC_Read(unsigned char diachi){
 unsigned char ketqua;

	ST=1; //kich 1 xung 1 ve 0
	Clock();
	IN_x(diachi);// truyen dia chi chon IN
	ALE=1;//kich 1 xung 1 ve 0
	Clock();
	ALE=0;
	Clock();
	ST=0;

	while(EOC==0) Clock();
	OE=1;
	ketqua=P0;
	OE=0;
	
	return ketqua;
}
void readnhietdo(){
	  LCD_Gotoxy(0,0);
		LCD_Puts(" Nhiet Do: ");		
		kq = ADC_Read(0);
    kq = (kq * 500) / 256;  // 500 = 5V * 100 (100°C = 1V)
		LCD_PutNumber(kq);
		LCD_Puts("'C  ");
}

int chonmode=0;

void main() {
	
    LCD_Init();
    LCD_Clear();
	  LCD_Gotoxy(3, 0);
    LCD_Puts("Chon Che Do");
    LCD_Gotoxy(4, 1);
    LCD_Puts("PhamHieuu");
	
	  TMOD = 0x01;
    TH0=0x00;
    TL0=0x00;  
	
    while (1) {
			
			// CHON CHE DO 1 OR 2
			if(Select_Mode==0){
			 chonmode=chonmode+1;
			  delay(400);
				 if(chonmode==3)
					 chonmode=1;
			}
			
			// CHE DO 1
			if(chonmode==1){
					readnhietdo();
					
					 if(UP==0){
						LCD_Gotoxy(0, 1);
						LCD_Puts(" Cai Dat: ");	 
						Set_Nhiet_Do=Set_Nhiet_Do+1;
						LCD_PutNumber(Set_Nhiet_Do);
						LCD_Puts(" 'C");	 
						delay(200);
					 }
					 else if(DOWN==0){
						LCD_Gotoxy(0, 1);
						LCD_Puts(" Cai Dat: ");	 
						Set_Nhiet_Do=Set_Nhiet_Do-1;
						LCD_PutNumber(Set_Nhiet_Do);
						LCD_Puts(" 'C");	 
						delay(200);}
							
					 if(kq>=Set_Nhiet_Do){
						P1_5=0;
						}
					 else {
						P1_5=1;
					}
			}
			
			// CHE DO 2
			else if(chonmode==2)
				{
					  P1_5=1;// tat het trang thai cua che do 1
					
						TRIG = 1;
						delay(10);
						TRIG = 0;
						
						// tranh bi treo chuong trinh doi khi echo=1 thi moi thoat
						if (ECHO==0){
						 TR0=0;
						 TH0=0x00;
						 TL0=0x00;
						 dem++;
						 while(ECHO==0){
							if(dem<8)
								break;
						 }
						}
						
						if (ECHO==1){
						 TH0=TL0=0x00;
						 TR0=1;
						 while(ECHO==1);
						 TR0=0;
						}
						
						time= TH0*256+TL0; //Chuyen TH0 và TL0 tu he hexa sang decimal
						convert_us= time*1.058;// chuyen time sang don vi us
						khoangcach= convert_us/58; // khoangcach= (Tocdo*convert_us)/2 
						
						// sai so trong thuc te
						if(khoangcach>=3 && khoangcach<=5) khoangcach++;
						if(khoangcach>=24 && khoangcach<=41) khoangcach--;
						if(khoangcach>=42 && khoangcach<=59) khoangcach =  khoangcach - 2;
						if(khoangcach>=60 && khoangcach<=77) khoangcach =  khoangcach - 3;
						
						LCD_Gotoxy(0,0);
						LCD_Puts("  DO DAI: ");
						LCD_PutNumber(khoangcach);
						LCD_Puts("CM    ");
						LCD_Gotoxy(0, 1);
            LCD_Puts("    PhamHieuu   ");
				}
	   	}
     }













