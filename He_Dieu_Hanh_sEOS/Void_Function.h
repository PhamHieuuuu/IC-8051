#ifndef Void_Function_H
#define Void_Function_H

//Khai bao chan cho ADC0808
#define CL P2_0  
#define ST P2_1  // Muc 1 de chuyen doi
#define EOC P2_2 // Xuat muc 1 khi chuyen doi ADC xong
#define OE P2_3 // Muc 1 de doc gia tri Digital
#define ALE P2_4 // chot cong IN0-7
#define A P2_5 
#define B P2_6 
#define C P2_7 
#define Data_ADC P0

// khai báo chan Cho Cam bien
#define GAS P1_0
#define LIGHT P1_1

// Khai bao chan relay
#define Relay1 P1_5
#define Relay2 P1_6
#define Relay3 P1_7

// Hàm Function
void readnhietdo();
void readGas();
void CambienAS();
void Button();
void Comunication_Uart();







#endif
