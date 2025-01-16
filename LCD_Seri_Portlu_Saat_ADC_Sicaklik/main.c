#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "lcd.h"

void SetInitSettings();
void timerkesmefonksiyonu();
void uart_ayari();
void diger_ayar();
void serikesme();
void adc_ayari();
void adc_veri_gonder();

// Zaman değişkenleri (kesme fonksiyonu için volatile)
int saat;
int dakika;
int saniye;

int main(void)
{
    LCDilkayarlar();  // LCD'yi başlat
    SetInitSettings(); // Timer ve kesmeleri ayarla
    uart_ayari();
    adc_ayari();
    diger_ayar();

    while (1)
    {
        adc_veri_gonder();
        SysCtlDelay(SysCtlClockGet() / 3); // 1 saniye gecikme
    }
}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 40 MHz

    // GPIO ayarları
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // PF1, PF2, PF3 çıkış

    // Timer ayarları
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); // Periyodik mod
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()); // 40 MHz -> 1 saniye

    // Kesme ayarları
    IntMasterEnable();                             // Genel kesmeleri aç
    IntEnable(INT_TIMER0A);                        // Timer0A kesmesini etkinleştir
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Kesme kaynağını seç
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmefonksiyonu); // Kesme işleyicisini kaydet
}

// Kesme işleyicisi
void timerkesmefonksiyonu()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Kesme bayrağını temizle

    // Zamanı güncelle
    saniye++;
    if (saniye == 60) {
        saniye = 0;
        dakika++;
    }
    if (dakika == 60) {
        dakika = 0;
        saat++;
    }
    if (saat == 24) {
        saat = 0;
    }

    // Zamanı LCD'ye yazdır
    LCDgit(1, 8);          // LCD'nin 1. satırına git
    LCDSaatYaz(saat, dakika, saniye); // Zamanı LCD'ye yaz
}

void uart_ayari()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Pin ayarları
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // UART0 yapılandır
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600, // Baud rate: 9600
                        (UART_CONFIG_WLEN_8 |               // 8-bit veri uzunluğu
                         UART_CONFIG_STOP_ONE |             // 1 stop biti
                         UART_CONFIG_PAR_NONE));
}

void diger_ayar()
{
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(UART0_BASE, serikesme);
}

void serikesme()
{
    char buffer[9];  // "HH:MM:SS" için 8 karakter + null terminator
    int i = 0;

    // UART üzerinden 8 karakter oku
    while (i < 8) {
        buffer[i] = UARTCharGet(UART0_BASE);
        i++;
    }
    buffer[8] = '\0'; // String'i sonlandır

    // "HH:MM:SS" formatındaki string'i parçala
    saat   = (buffer[0] - '0') * 10 + (buffer[1] - '0');
    dakika = (buffer[3] - '0') * 10 + (buffer[4] - '0');
    saniye = (buffer[6] - '0') * 10 + (buffer[7] - '0');

    TimerEnable(TIMER0_BASE, TIMER_A);
}
void adc_ayari()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
}
void adc_veri_gonder()
{
    uint32_t adc_degeri;
    char adc_mesaji[16];
    int i = 0;
    int u = 0;

    ADCProcessorTrigger(ADC0_BASE, 3); // ADC'yi tetikle
    while (!ADCIntStatus(ADC0_BASE, 3, false)); // Dönüşüm tamamlanana kadar bekle
    ADCIntClear(ADC0_BASE, 3); // Kesme bayrağını temizle
    ADCSequenceDataGet(ADC0_BASE, 3, &adc_degeri); // ADC değerini al
    LCDgit(0, 0); // LCD'nin 2. satırına git
    lcdyaz("                "); // 16 boşluk yaz (LCD'nin bir satırını temizler)
    // ADC değerini LCD'ye yazdır
    LCDgit(0, 0); // LCD'nin 2. satırına git
    sprintf(adc_mesaji, "ADC: %d", adc_degeri);
    lcdyaz(adc_mesaji);

    // ADC değerini UART üzerinden gönder
    sprintf(adc_mesaji, "ADC: %d\n", adc_degeri);
    for (i = 0; adc_mesaji[i] != '\0'; i++) {
        UARTCharPut(UART0_BASE, adc_mesaji[i]);
    }
}
