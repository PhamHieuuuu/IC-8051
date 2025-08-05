void Uart_Init();
void Uart_Write_Char(char c);
void Uart_Write_String(char * str);// xuong dong " \r "
char Uart_Data_Ready();
char Uart_Read();
void Uart_Write_Number(int num) ;