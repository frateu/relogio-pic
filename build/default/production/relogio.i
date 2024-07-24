# 1 "relogio.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "relogio.c" 2








# 1 "./relogio.h" 1





#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
# 29 "./relogio.h"
extern unsigned int hora;
extern unsigned int mint;
extern unsigned int segd;
# 9 "relogio.c" 2


unsigned int hora = 0;
unsigned int mint = 0;
unsigned int segd = 0;
