#include <REGX51.H>
#include <Thu_Vien_LCD.h>

// khai báo chan keypad
#define H1 P2_0
#define H2 P2_1
#define H3 P2_2
#define H4 P2_3
#define C1 P2_4
#define C2 P2_5
#define C3 P2_6
#define C4 P2_7

// khai bao chan ADC
#define CS P1_0
#define RD P1_1
#define WR P1_2
#define INTR P1_3
#define Data P0

int kq;
int i; 

// Ma tran phim va gia tri tuong ung
char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


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

void HienthiLCD(char key) {

    LCD_Gotoxy(0, 0);
    LCD_Puts("      Key: ");
    LCD_PutChar(key);
    LCD_Puts("        ");
}


char ScanKeypad() {
    char H, C;

    for (H = 0; H < 4; H++) {
        H1 = 1; H2 = 1; H3 = 1; H4 = 1;

        if (H == 0) H1 = 0;
        if (H == 1) H2 = 0;
        if (H == 2) H3 = 0;
        if (H == 3) H4 = 0;

        // Kiem tra tung cot
        if (C1 == 0) {
            C = 0;
        } else if (C2 == 0) {
            C = 1;
        } else if (C3 == 0) {
            C = 2;
        } else if (C4 == 0) {
            C = 3;
        } else {
            continue;
        }


        return keys[H][C];
    } 

    return 0; 
}


unsigned char ADC_Read(){
	
	unsigned char ketqua;
	// chon chip 
	CS = 0;

	WR = 0;
	WR = 1;
	

	while(INTR); // chuyen doi xong 

	RD = 0;
	ketqua = Data;
	RD = 1;
	
	return ketqua;
}

void main() {
    char key;
	  char keylast;
	  int valueADC;
	
    LCD_Init();
    LCD_Clear();
    LCD_Gotoxy(0, 0);
    LCD_Puts("Nhan Phim Bat Ky"); 
    LCD_Gotoxy(4, 1);
    LCD_Puts("PhamHieuu");

    while (1) {
			
        key = ScanKeypad(); // Ðoc phím nhan
		    valueADC=ADC_Read();
			
        if (key != 0) { // Hien thi khi nhan phim moi
					  HienthiLCD(key);      // Hien thi lên LCD
			  }

				switch (valueADC){
					case 0:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(1);		
            LCD_Puts("       ");
					  break;
					case 128:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(2);		
            LCD_Puts("       ");
					  break;
					case 170:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(3);		
            LCD_Puts("       ");
					  break;
					case 191:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(4);		
            LCD_Puts("       ");
					  break;
					case 204:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(5);		
            LCD_Puts("       ");
					  break;
					case 212:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(6);		
            LCD_Puts("       ");
					  break;
					case 219:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(7);		
            LCD_Puts("       ");
					  break;
					case 223:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(8);		
            LCD_Puts("       ");
					  break;
					case 227:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(9);		
            LCD_Puts("       ");
					  break;
					case 229:
				    LCD_Gotoxy(0, 0);
            LCD_Puts("      Key: ");
            LCD_PutNumber(10);		
            LCD_Puts("       ");
					  break;

				}
        }

    }














