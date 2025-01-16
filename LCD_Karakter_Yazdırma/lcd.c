#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"

#include "lcd.h"

void otuzhexgonder() {
    SysCtlDelay(100000);
    GPIOPinWrite(LCDPORT, RS, 0); // RS = 0 (Komut)
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, 0x30); // 0x30 gönder
    GPIOPinWrite(LCDPORT, E, E); // Enable HIGH
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0); // Enable LOW
}

void lcdkomut(unsigned char c) {
    GPIOPinWrite(LCDPORT, RS, 0); // RS = 0 (Komut)

    // Üst nibble gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, E); // Enable HIGH
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0); // Enable LOW

    // Alt nibble gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c << 4) & 0xF0);
    GPIOPinWrite(LCDPORT, E, E); // Enable HIGH
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0); // Enable LOW

    SysCtlDelay(2000); // Komut sonrası kısa gecikme
}


void lcdilkayar(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);// port b aktif , kitli pin yok
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF); //hepsi output

  //  SysCtlDelay(100000);

    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();
    lcdkomut(0x02);

    // ayarlar komut
    //lcd komut
}

void lcdfonksiyonayarla(unsigned char DL,unsigned char N,unsigned char F )
{
        unsigned char cmd = 0x20; // Fonksiyon set komutu başlangıcı

        if (DL)cmd |= 0x10; // DL: Data Length (0 = 4-bit, 1 = 8-bit)
        if (N) cmd |= 0x08;  // N: Display lines (0 = 1 satır, 1 = 2 satır)
        if (F) cmd |= 0x04;  // F: Font (0 = 5x8, 1 = 5x10)

        lcdkomut(cmd); // Fonksiyon set komutunu gönder
}

void lcdkarakteryaz(unsigned char c) {
    GPIOPinWrite(LCDPORT, RS, RS); // RS = 1 (Veri)

    // Üst nibble gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, E); // Enable HIGH
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0); // Enable LOW

    // Alt nibble gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c << 4) & 0xF0);
    GPIOPinWrite(LCDPORT, E, E); // Enable HIGH
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0); // Enable LOW

    SysCtlDelay(2000); // Veri sonrası kısa gecikme
}

void LCDTemizle() {
    lcdkomut(0x01); // Ekranı temizle komutu
    SysCtlDelay(2000);
}


void LCDgit(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0) {
        address = col;
    } else {
        address = 0x40 + col;
    }
    lcdkomut(0x80 | address);
}
