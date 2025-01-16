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

void otuzhexgonder()
{
    SysCtlDelay(100000);
    // rs=0
    GPIOPinWrite(LCDPORT, RS, 0);
    //ayar yazıldı
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, 0X30);
    // en ac kapa
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);
    // 3 kez 30h gönder
}

void lcdkomut(unsigned char c) //0x47
{
    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0xf0));
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0x0f)<<4);
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

}

void LCDilkayarlar()
{
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


void lcdkarakteryaz(unsigned char d)
{
    GPIOPinWrite(LCDPORT, RS, 1); // Karakter yazma modu
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xF0));
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

    GPIOPinWrite(LCDPORT, RS, 1); // Karakter yazma modu
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0F) << 4);
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

}


void LCDgit(unsigned char x, unsigned char y){
    unsigned char address;
    if (x == 0) {
        address = y;
    } else {
        address = 0x40 + y;
    }
    lcdkomut(0x80 | address);

}

void LCDTemizle(){
    GPIOPinWrite(LCDPORT, RS, 0);
    SysCtlDelay(2000);
    lcdkomut(0x01);
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
void lcdyaz(const char *str) {
    while (*str) {
        lcdkarakteryaz(*str++);
    }}
