#ifndef LCD_H_
#define LCD_H_

// LCD Pin Tanımları
#define LCDPORT    GPIO_PORTB_BASE
#define RS         GPIO_PIN_0
#define E          GPIO_PIN_1
#define D4         GPIO_PIN_4
#define D5         GPIO_PIN_5
#define D6         GPIO_PIN_6
#define D7         GPIO_PIN_7

void lcdkomut(unsigned char c);
// 0 la 255 arsında veri
//rs =0
//d4-d7 arasında veri yaz
//en enable aç kapa
void lcdilkayar();
//giriş kipini seç
//ekran aç/kapa
//kürsor kaydır

void lcdkarakteryaz(unsigned char  );
//rs=1
//d4-d7 arasında veri yaz
//en enable aç kapa
void lcdfonksiyonayarla(unsigned char DL, unsigned char N,unsigned char F);// DL,N,F
//b=0 is e4 bit ayralarsın
//b=1 ise 8 bit ayarlansın  şeklinde fonskiyon oluşturduk. fonksiyo seçtik
// 4 bit  bit ayarla
//rs=1
//d4-d7 arasında veri yaz
//en enable aç kapa
void LCDTemizle();
//rs=0
//d4-d7 arasında veri yaz
//en enable aç kapa

void LCDgit(unsigned char,unsigned char);
//satır ve sütüna git
//1satır, 1 sutüna git


#endif //lcd_h/
