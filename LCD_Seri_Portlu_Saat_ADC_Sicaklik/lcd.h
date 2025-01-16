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
void lcdkarakteryaz(unsigned char c);
//rs=1
//d4-d7 arasında veri yaz
//en enable aç kapa
void LCDilkayarlar();
//giriş kipini seç
//ekran aç/kapa
//kürsor kaydır
void lcdfonksiyonayarla( unsigned char e);
// dl,N,F sadece fonskiyon ayarı için
// dl= 0 1
// n=  0 1
// f=  0 1
void LCDTemizle();
//rs=0
//d4-d7 arasında veri yaz
//en enable aç kapa
void LCDgit(unsigned char row, unsigned char col);
//satır ve sütüna git
//1satır, 1 sutüna git
void LCDSaatYaz(int sa, int dk, int sn);
void lcdyaz(const char *str);

#define DURATION_IN_SECONDS 86400  // Change this value as needed
extern int totalSeconds;



#endif /* LCD_H_ */
