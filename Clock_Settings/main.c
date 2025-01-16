
//HWREG fonksiyonun bulunduðu adres.
#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
//APISIZ

void clockinit();
int main(void)
{

    SYSCTL_RCGCGPIO_R|=0x20; // portf enerjilendirildi 20 hex tabanlýdýr. CLOCK AKTÝF ETME


    GPIO_PORTF_LOCK_R= 0x4C4F434B; //commiti aç
    GPIO_PORTF_CR_R= 0x01; //pf0 da artýk konfigrasyon yapýlabilir. 0000 0001 þeklindedir.(pf0,pf4 ve pf7 kapalýdýr bu iki kod ile açýyoruz).KÝLÝTÝ KALDIRDIK

    GPIO_PORTF_DIR_R|=0x0E; //porf xx543210 þeklindedir. Ý-R-G-B-Ý LED pin ayarlanmasýný saðlar, PÝNLERÝ I/O YAPAR. 0000 1110-
    GPIO_PORTF_DEN_R|=0x1F; //BÜTÜN PÝNLERÝN AKTÝF  EDÝLMESÝ. pin 0001 1111


    GPIO_PORTF_PUR_R =0x11; // pf0 ve pf4 pull-up aktif edildi. 0001 0001
    while(1)
    {
    unsigned  int value;
     // GPIO_PORTA_DATA_R|=0x02; kýrmýzý ledi yaktýk.
    // butonlara dokunulmamýþsa 0001 0001 þeklindedir. pf0 ve pf4 1 dir. ledler 0 dýr.
    value=GPIO_PORTF_DATA_R;

       if ((value & 0x10)==0)// pf4 týkladýysak pf4 0'a çeker.
        {

          GPIO_PORTA_DATA_R|=0x02; // PF1 pinindeki kýrmýzý ledi yak

          GPIO_PORTF_DATA_R &= ~0x02;       // PF1 pinindeki kýrmýzý LED'i söndür

        }

         if((value & 0x01)==0) // pf0' a týkladýk pf0 0'a çekti.(& andledik.)
          {

             GPIO_PORTA_DATA_R|=0x04;
          }





    }

}

void clockinit(){


//    The PLL is configured using direct register writes to the RCC/RCC2 register. If the RCC2 register
//     is being used, the USERCC2 bit must be set and the appropriate RCC2 bit/field is used. The steps
//     required to successfully change the PLL-based system clock are:
//     1. Bypass the PLL and system clock divider by setting the BYPASS bit and clearing the USESYS
//     bit in the RCC register, thereby configuring the microcontroller to run off a "raw" clock source
//     and allowing for the new PLL configuration to be validated before switching the system clock
//     to the PLL.
//     2. Select the crystal value (XTAL) and oscillator source (OSCSRC), and clear the PWRDN bit in
//     RCC/RCC2. Setting the XTAL field automatically pulls valid PLL configuration data for the
//     appropriate crystal, and clearing the PWRDN bit powers and enables the PLL and its output.
//     3. Select the desired system divider (SYSDIV) in RCC/RCC2 and set the USESYS bit in RCC. The
//     SYSDIV field determines the system frequency for the microcontroller.
//     4. Wait for the PLL to lock by polling the PLLLRIS bit in the Raw Interrupt Status (RIS) register.
//     5. Enable use of the PLL by clearing the BYPASS bit in RCC/RCC2

//0.
    //SYSCTL_RCC2_R &=7FFFFFFF;// RCC2 REGÝSTERINI 0 A ÇEKTÝK. KULLANMAYACAZ.
      SYSCTL_RCC2_R=~SYSCTL_RCC2_USERCC2;// YUKARIDAKÝ ÝLE AYNI ÞEY

//1.
      //SYSCTL_RCC_R|=0x0800;// BAYPASS YAPTIK.BU ÝLEM DAHÝLÝ OSÝLATÖRÜ HEMEN ÇALIÞMAYA BAÞLAMASINI SAÐLAR.
      SYSCTL_RCC_R|= SYSCTL_RCC_BYPASS; // YUKARIDAKÝ ÝLE YANI ÞEY. BÖYLELÝKLE PLL KULLANMAK YERÝNE SÝSTEMÝN SAATÝNÝ KULLANDIK.
      SYSCTL_RCC_R|= ~SYSCTL_RCC_USESYSDIV;

//2.XTALI AYARLAMAK ÝSTÝYORUZ MAÝN OSC 16MHZ OLDUÐUNDAN 16 MHZE GÖRE AYARLAMA YAPILACAK.
      SYSCTL_RCC_R=(SYSCTL_RCC_R+ ~SYSCTL_RCC_XTAL_M)+ SYSCTL_RCC_XTAL_16MHZ;// XTALI SIFIRLADIK VE 16 MHZ YÜKLEDÝK.
      SYSCTL_RCC_R &=~SYSCTL_RCC_OSCSRC_M; //BÖYLELÝKLE OSCRC YÝ AYARLADIK O ALANI SIFIRLADIK.
      SYSCTL_RCC_R &=~SYSCTL_RCC_PWRDN;//PWRDN YÝ SIFIRA ÇEKTÝK.
      SYSCTL_RCC2_R &=~SYSCTL_RCC2_DIV400;//DÝV400 0 YAP. ARTIK 2 YE BÖLÜNECEK.
 //3.
      SYSCTL_RCC_R &=~(SYSCTL_RCC_SYSDIV_M);//SYSDIV BÖLGESÝNÝ TEMÝZLEDÝK.
      SYSCTL_RCC_R |= (SYSCTL_RCC_USESYSDIV + (4<<22));// 16 MHZ OLARAK AYARLADIK USESYSDIV AYARLANDI.

//4.
     while(SYSCTL_RIS_R &SYSCTL_RIS_PLLLRIS==0);//PLLRIS 0 ÝSE BEKLER 1 ÝSE AKTÝF OLUR.
     SYSCTL_RCC_R= ~SYSCTL_RCC_BYPASS; //

}

