//main.c


#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"    // Sistemle ilgili kütüphaneler
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"   // GPIO_PIN_x tanımlamaları için
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "lcd.h"                 // LCD başlık dosyası"



int main()
 {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

   lcdilkayar();
   lcdfonksiyonayarla(0,1,0) ; // 4-bit mod, 2 satır, 5x8 karakter
   LCDTemizle();

   // İlk satıra 'A' karakteri yazdırma
    LCDgit(0,0); // 1. Satır, 1. Sütun
    lcdkarakteryaz('M');
    LCDgit(0,1); // 1. Satır, 1. Sütun
    lcdkarakteryaz('C');
    LCDgit(0,2); // 1. Satır, 1. Sütun
    lcdkarakteryaz('P');


    while (1) {} // Sonsuz döngü


}
