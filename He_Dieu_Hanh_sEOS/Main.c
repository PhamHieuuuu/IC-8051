#include <REGX51.H>
#include <Void_Function.h>

#define MAX_TASKS 5  // So luong task toi da

// Cau truc Task
typedef struct {
    void (*taskFunc)(void);
    unsigned int delay;
} Task;

// Danh sach Task
Task taskList[MAX_TASKS];

// Bien Task hien tai
unsigned char currentTask = 0;

// Ham delay mo phong os_dly_wait()
void os_dly_wait(unsigned int time) {
    taskList[currentTask].delay = time;
}

// Task 1
void task1_readGas(void) {
    readGas();
    os_dly_wait(2); // Delay 2 tick (2 x 50ms = 100ms)
}
// Task 2
void task2_readLm35(void) {
    readnhietdo(); 
    os_dly_wait(20);  // Delay 20 tick (20 x 50ms = 1000ms)
}

// Task 3
void task3_readLight(void) {
    CambienAS(); 
    os_dly_wait(10);  // Delay 10 tick (10 x 50ms = 500ms)
}
// Task 4
void task4_readButton(void) {
    Button();
    os_dly_wait(1);  // Delay 1 tick (1 x 50ms = 50ms)
}
// Task 5
void task5_CommunicationUART(void) {
    Comunication_Uart();
    os_dly_wait(100);  // Delay 100 tick (100 x 50ms = 5000ms)
}

// Khoi tao danh sach Task
void os_task_init(void) {
    taskList[0].taskFunc = task1_readGas;
    taskList[0].delay = 0;

    taskList[1].taskFunc = task2_readLm35; 
    taskList[1].delay = 0;

    taskList[2].taskFunc = task3_readLight; 
    taskList[2].delay = 0;

    taskList[3].taskFunc = task4_readButton;
    taskList[3].delay = 0;

    taskList[4].taskFunc = task5_CommunicationUART;
    taskList[4].delay = 0;
}

// Bo dem tick moi 50ms (ISR Timer 0)
void Timer0_ISR(void) interrupt 1 {
    unsigned char i;
    for (i = 0; i < MAX_TASKS; i++) {
        if (taskList[i].delay > 0) {
            taskList[i].delay--;  // Giam bo dem delay cua task
        }
    }
    
    // Reload Timer 0 de duy tri tan so ngat 50ms
    TH0 = 0x3B;
    TL0 = 0xF9;
}

// 1 Tick se la 50ms
// Cau hinh Timer 0 de tao ngat moi 50ms
void os_init(void) {
    TMOD |= 0x01; // Che do 16-bit Timer 0
    TH0 = 0x3B; 
    TL0 = 0xF9;
    ET0 = 1;  // Bat ngat Timer 0
    EA = 1;   // Cho phep ngat toan cuc
    TR0 = 1;  // Bat Timer 0
}

// Bo lap lich voi che do ngu
void os_scheduler(void) {
    while (1) {
        unsigned char i;
        bit taskReady = 0;

        for (i = 0; i < MAX_TASKS; i++) {
            if (taskList[i].delay == 0) {
                currentTask = i;
                taskList[i].taskFunc(); // Thuc hien task
                taskReady = 1;// báo hieu co task san sang de khong vào che do sleep
            }   
        }       

        // Neu khong co Task nao san sang -> Dua vi dieu khien vao che do Idle
        if (!taskReady) {
            PCON |= 0x01;
        }
    }
}

// Ham main
void main() {
	  Uart_Init();
	  LCD_Init();
    os_init();       // Khoi tao he thong
    os_task_init();  // Khoi tao danh sach Task
    os_scheduler();  // Chay bo lap lich
}


































































/*
-------Giai thích bien TaskReady--------

        for (i = 0; i < MAX_TASKS; i++) {
            if (taskList[i].delay == 0) {
                currentTask = i;
                taskList[i].taskFunc(); // Thuc hien task
                taskReady = 1;// báo hieu co task san sang de khong vào che do sleep (CO HAY KHONG CO DEU DUOC)
            }   // TaskReady có NV neu co it nhat 1 task duoc thuc hien khi het vong for
        }       // Vi taskReady=1; 8051 se thuc hien quet 1 lan for nua de chac chan het task san sang

        // Neu khong co Task nao san sang -> Dua vi dieu khien vao che do Idle
        if (!taskReady) {
            PCON |= 0x01;
        }
    }

*/