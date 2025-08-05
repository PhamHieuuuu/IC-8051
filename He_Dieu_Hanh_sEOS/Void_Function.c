#include <REGX51.H>
#include <Thu_Vien_LCD.h>
#include <UART.h>
#include <Void_Function.h>

// Khai bao chan cho ADC0808
#define CL P2_0  
#define ST P2_1  // Muc 1 de chuyen doi
#define EOC P2_2 // Xuat muc 1 khi chuyen doi ADC xong
#define OE P2_3 // Muc 1 de doc gia tri Digital
#define ALE P2_4 // chot cong IN0-7
#define A P2_5 
#define B P2_6 
#define C P2_7 
#define Data_ADC P0

// Khai báo chan Cho Cam bien
#define GAS P1_0
#define LIGHT P1_1

// Khai bao chan relay
#define Relay1 P1_5
#define Relay2 P1_6
#define Relay3 P1_7

// Set gia tri dat nguong Relay
unsigned char Set_Nhiet_Do=25;
unsigned char Set_Gas=0;
unsigned char Set_Light=0;

// Bien luu gia tri cam bien
unsigned char LM35=0;
unsigned char  MQ2=0;
unsigned char  LDR=0;

unsigned char i,j;

void delay(int ms){
 for(i=0;i<ms;i++)
   for(j=0;j<125;j++); 
}

// Các hàm Nv doc ADC
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

// Doc nhiet do & xu ly relay 1 
void readnhietdo(){	
		LM35 = ADC_Read(0);
		LM35 = LM35 / 0.512; // suy ra do C doc duoc
	
		if(LM35>=Set_Nhiet_Do){
		Relay1=0;
		}
	  else {
		Relay1=1;
    }
}

// Doc cam bien anh sang & xu ly relay 2
void CambienAS(){
    LDR = LIGHT;
		
	 if(Set_Light==LDR){
		Relay2=0;
		}
	 else {
		Relay2=1;
		}
}


// Doc MQ2 & xu ly relay 3
void readGas(){
  MQ2=GAS;

	if(Set_Gas==MQ2)
		Relay3=0;
	else 
		Relay3=1;
}

// Doc ADC nút nhan, thuc hien chuc nang dua len LCD
// ADC: (+) 0 | (-) 128 | (MODE) 170 
unsigned char  up_button=0;
unsigned char  down_button=0;
unsigned char  chon_mode=0;

void Button(){
	  switch (ADC_Read(1)){
			case 0: up_button=1; delay(100); break;
			case 128: down_button=1; delay(100); break;			
			case 170: chon_mode++; delay(100); break;		}	
		if(chon_mode==4)
			chon_mode=0;

    if(chon_mode==0){ // che do 0
	  LCD_Gotoxy(0, 0);
    LCD_Puts("     Chon Che Do    ");
	  LCD_Gotoxy(0, 1);
    LCD_Puts("     ___________     ");
	  LCD_Gotoxy(0, 2);
    LCD_Puts("                     ");
    LCD_Gotoxy(0, 3);
    LCD_Puts("   ---PhamHieuu---     ");
		}	
		
    else if(chon_mode==1){ // che do 1
    LCD_Gotoxy(0, 0);
    LCD_Puts("      Mode (1)     ");
    LCD_Gotoxy(0, 1);
		LCD_Puts("   Nhiet Do: ");   			
		LCD_PutNumber(LM35);			
		LCD_Puts("'C     ");   
	
			 LCD_Gotoxy(0, 2);
			 LCD_Puts("    Cai Dat: ");
			 LCD_PutNumber(Set_Nhiet_Do);
			 LCD_Puts("'C");	
			 if(up_button==1){ 
				Set_Nhiet_Do=Set_Nhiet_Do+1;
			  LCD_Gotoxy(13, 2);
				LCD_PutNumber(Set_Nhiet_Do);
				LCD_Puts("'C");	
				up_button=0;			 
			 }
			 else if(down_button==1){ 
				Set_Nhiet_Do=Set_Nhiet_Do-1;
			  LCD_Gotoxy(13, 2);
				LCD_PutNumber(Set_Nhiet_Do);
				LCD_Puts("'C");	
				down_button=0;
				}	
	}
		
	  else if(chon_mode==2){ // che do 2
    LCD_Gotoxy(0, 0);
    LCD_Puts("      Mode (2)     ");
    LCD_Gotoxy(0, 1);
		LCD_Puts("  Light Senser: ");   			
    if(LDR==1)
		LCD_Puts("Sang");   
    else 
		LCD_Puts("Toi ");   
		
		 if(up_button==1){ 
			Set_Light=1;
			up_button=0;			 
		 }
		 else if(down_button==1){ 
			Set_Light=0;
			down_button=0;
		}		
			 LCD_Gotoxy(0, 2);
			 LCD_Puts("    Cai Dat: ");
		   if(Set_Light==1) LCD_Puts("Sang ");
		   else LCD_Puts("Toi ");
		}
		
	  else if(chon_mode==3){ // che do 3
    LCD_Gotoxy(0, 0);
    LCD_Puts("      Mode (3)     ");
    LCD_Gotoxy(0, 1);
		LCD_Puts("      GAS: ");   			
    if(MQ2==1)
		LCD_Puts("YES      ");   
    else 
		LCD_Puts("NO       ");   
		
		 if(up_button==1){ 
			Set_Gas=1;
			up_button=0;			 
		 }
		 else if(down_button==1){ 
			Set_Gas=0;
			down_button=0;
			}
	
		LCD_Gotoxy(0, 2);
		LCD_Puts("    Cai Dat: ");		
		 if(Set_Gas==1) LCD_Puts("YES    ");
		 else LCD_Puts("NO    ");		
		}
}

// Gui du lieu UART
void Comunication_Uart(){
    Uart_Write_String("MQ2: ");
    Uart_Write_Number(MQ2); // Gui giá tri MQ2
    Uart_Write_Char('\r'); // Xuong hàng

    Uart_Write_String("LM35: ");
    Uart_Write_Number((int)LM35); // Gui giá tri nhiet do LM35
    Uart_Write_String("'C"); 
    Uart_Write_Char('\r'); 

    Uart_Write_String("LDR: ");
    Uart_Write_Number(LDR); // Gui giá tri LDR
    Uart_Write_Char('\r'); 
    Uart_Write_Char('\r');
}






