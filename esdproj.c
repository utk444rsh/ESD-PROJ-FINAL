#include <lpc17xx.h>
#include <stdio.h>
unsigned char temp, msg1;
unsigned int k;
char str[10];
unsigned int i = 0, flag1, j, cflag = 0;
int n, count = 0;
char msg[16] = "Obstacledetected";
char msg3[16] = "nostacledetectno";
unsigned char init_command[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x01, 0x06, 0x80};
void delayMS(unsigned int k) {
    for (i = 0; i < k * 10; i++);
}
void delay(unsigned int k) {
    for (j = 0; j < k; j++);
}
void port_write();
void lcd_write();
void buzz_init();
void lcd_port() {
    LPC_GPIO0->FIOPIN = msg1 << 23;
    if (flag1 == 0) {
        LPC_GPIO0->FIOCLR = 1 << 27;
    } else {
        LPC_GPIO0->FIOSET = 1 << 27;
    }
    LPC_GPIO0->FIOSET = 1 << 28;
    delay(50);
    LPC_GPIO0->FIOCLR = 1 << 28;
    delay(100000);
}
void lcd_wr() {
    msg1 = temp & 0xF0;
    msg1 = msg1 >> 4;
    lcd_port();
    if ((i > 3) | (flag1 == 1)) {
        msg1 = temp & 0x0F;
        lcd_port();
    }
}
void buzz_init() {
    LPC_PINCON->PINSEL0 &= 0xFF3FFFFF; //for buzzer
    LPC_GPIO0->FIODIR |= 1 << 11;
}
int main() {
    SystemInit();
    SystemCoreClockUpdate();
    buzz_init();
    LPC_PINCON->PINSEL3 = 0x00000000; //for sensor
    LPC_GPIO1->FIODIR = 0x00000000;
    LPC_PINCON->PINSEL1 |= 0;
    LPC_PINCON->PINSEL4 &= 0xFCFFFFFF;
    LPC_GPIO2->FIODIR |= 0x0 << 12;
    LPC_GPIO0->FIODIR |= 0XF << 23 | 1 << 27 | 1 << 28;
    flag1 = 0;
    for (i = 0; i < 9; i++) {
        temp = init_command[i];
        lcd_wr();
    }
    flag1 = 1;
    i = 0;
    LPC_PINCON->PINSEL0 &= 0xFFFFFCFF;
    LPC_GPIO0->FIODIR |= (0 << 4);
    while (1) {
        LPC_GPIO0->FIOSET = 1 << 11;
        delay(100000);
        LPC_GPIO0->FIOCLR = 1 << 11;
        if (((LPC_GPIO1->FIOPIN & (1 << 23)) == 0) || ((LPC_GPIO1->FIOPIN & (1 << 25)) == 0)) {
            i = 0;
            if (cflag == 0) {
                cflag = 1;
                flag1 = 0;
                for (i = 0; i < 9; i++) {
                    temp = init_command[i];
                    lcd_wr();
                }
                flag1 = 1;
                i = 0;
                while (msg[i] != '\0') {
                    temp = msg[i];
                    lcd_wr();
                    i++;
                }
            }
        } else {
            cflag = 0;
					 for (i = 0; i < 9; i++) {
                    temp = init_command[i];
                    lcd_wr();
                }
                flag1 = 1;
                i = 0;
                while (msg3[i] != '\0') {
                    temp = msg3[i];
                    lcd_wr();
                    i++;
                }
        }
        flag1 = 1;
        delayMS(150);
        if (!(LPC_GPIO2->FIOPIN & 1 << 12)) {
            LPC_GPIO0->FIOCLR = 1 << 11;
            break;
        }
    }
}
