#include "inc/tm4c123gh6pm.h"
#include "lcd.h"
#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"


volatile uint32_t saniye = 0;
volatile uint32_t dakika = 0;
volatile uint32_t saat = 0;
volatile uint8_t timerFlag = 0; // uint8_t, 8-bitlik unsigned integer türüdür

void kesme() {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    timerFlag = 1;
}
void saniyeyiArtir() {
    saniye++;

    if (saniye == 60) {
        saniye = 0;
        dakika++;
        if (dakika == 60) {
            dakika = 0;
            saat++;
            if (saat == 24) {
                saat = 0;
            }
        }
    }
}
int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 40mhz
    IntMasterEnable();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, kesme);

    TimerEnable(TIMER0_BASE, TIMER_A);

    LCDilkayarlar();
    lcdfonksiyonayarla(0x2C);
    LCDTemizle();



    while (1) {
        if (timerFlag) {
            saniyeyiArtir();

            LCDgit(1, 8);

            // Saat
            lcdkarakteryaz((saat / 10) + '0');
            lcdkarakteryaz((saat % 10) + '0');
            lcdkarakteryaz(':');

            // Dakika
            lcdkarakteryaz((dakika / 10) + '0');
            lcdkarakteryaz((dakika % 10) + '0');
            lcdkarakteryaz(':');

            // Saniye
            lcdkarakteryaz((saniye / 10) + '0');
            lcdkarakteryaz((saniye % 10) + '0');

            timerFlag = false;
        }
    }





}
