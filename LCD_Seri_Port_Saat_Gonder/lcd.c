#include "inc/tm4c123gh6pm.h"
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
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

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

void LCDilkayarlar() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // PortB etkinleştir
    GPIOPinTypeGPIOOutput(LCDPORT, RS | E | D4 | D5 | D6 | D7); // Pinleri çıkış yap

    // Önceki verilerden kalan olası artıkları temizlemek için tüm pinleri sıfırla
    GPIOPinWrite(LCDPORT, RS | E | D4 | D5 | D6 | D7, 0x00); // Tüm pinleri LOW yap
    SysCtlDelay(50000);  // LCD’nin başlatılması için gecikme

    // 4-bit mod başlatmak için üç kez 0x30 komutu gönder
    otuzhexgonder();
    SysCtlDelay(50000);
    otuzhexgonder();
    SysCtlDelay(50000);
    otuzhexgonder();
    SysCtlDelay(50000);

    // 4-bit moda geçiş komutu
    lcdkomut(0x02); // LCD'yi 4-bit modda başlat
    SysCtlDelay(50000);

    // LCD ayar komutları
    lcdkomut(0x28); // 2 satır, 5x7 karakter
    SysCtlDelay(50000);
    lcdkomut(0x0C); // Ekran açık, imleç kapalı
    SysCtlDelay(50000);
    lcdkomut(0x06); // İmleci sağa kaydır
    SysCtlDelay(50000);

    // Ekranı temizle
    LCDTemizle();
    SysCtlDelay(50000);
}

void lcdfonksiyonayarla( unsigned char e)
{
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (e & 0xf0));
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(2000);

    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (e & 0x0f)<<4);
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(2000);

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


void LCDgit(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0) {
        address = col;
    } else {
        address = 0x40 + col;
    }
    lcdkomut(0x80 | address);
}

void LCDTemizle() {
    lcdkomut(0x01); // Ekranı temizle komutu
    SysCtlDelay(2000);
}

void LCDSaatYaz(int sa, int dk, int sn) {
    char sao;
    char sab;
    char dko;
    char dkb;
    char sno;
    char snb;

    sao = sa / 10 ;
    sab = sa % 10 ;
    dko = dk / 10 ;
    dkb = dk % 10 ;
    sno = sn / 10 ;
    snb = sn % 10 ;

    // Display on LCD, limited to 8 characters
    lcdkarakteryaz(sao + '0');
    lcdkarakteryaz(sab + '0');
    lcdkarakteryaz(':');
    lcdkarakteryaz(dko + '0');
    lcdkarakteryaz(dkb + '0');
    lcdkarakteryaz(':');
    lcdkarakteryaz(sno + '0');
    lcdkarakteryaz(snb + '0');
}
