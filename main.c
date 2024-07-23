/*
 * File:   main.c
 * Author: mathe
 *
 * Created on 23 de Julho de 2024, 09:15
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include "relogio.h"

#define shd RC0
#define shu RC1
#define smd RC2
#define smu RC3
#define ssd RC4
#define ssu RC5

#define dp RD7

void relogio_click()
{
    // Define a frequencia para 20MHz
    #define _XTAL_FREQ 20000000

    // Variaveis dos segmentos do display
    unsigned int segdU, segdUA, segdD, mintU, mintUA, mintD, horaU, horaUA, horaD;
    
    unsigned int segmento[]={0X3F, // 0
                            0X06, // 1
                            0X5B, // 2
                            0X4F, // 3
                            0X66, // 4
                            0X6D, // 5
                            0X7D, // 6
                            0X07, // 7
                            0X7F, // 8
                            0X67  // 9
                        };

    // Configura como saida de dados
    TRISC=0X00;
    PORTC=0X00;
    TRISD=0x00;
    PORTD=0X00;
    
    // Digitos dos Segundos
    segdU = segd % 10;
    segdUA = segd / 10;
    
    segdD = segdUA % 10;
    
    // Digitos dos Minutos
    mintU = mint % 10;
    mintUA = mint / 10;
    
    mintD = mintUA % 10;
    
    // Digito das Horas
    horaU = hora % 10;
    horaUA = hora / 10;
    
    horaD = horaUA % 10;
    
    PORTD=segmento[horaD]; shd=1; //Turn ON display 1 and print 4th digit
    __delay_ms(5); shd=0;     //Turn OFF display 1 after 5ms delay
    
    PORTD=segmento[horaU]; shu=1; dp=1; //Turn ON display 2 and print 3rd digit
    __delay_ms(5); shu=0; dp=0;     //Turn OFF display 2 after 5ms delay
    
    PORTD=segmento[mintD]; smd=1; //Turn ON display 3 and print 2nd digit
    __delay_ms(5); smd=0;     //Turn OFF display 3 after 5ms delay
    
    PORTD=segmento[mintU]; smu=1; dp=1; //Turn ON display 4 and print 1st digit
    __delay_ms(5); smu=0; dp=0;     //Turn OFF display 4 after 5ms delay
    
    PORTD=segmento[segdD]; ssd=1; //Turn ON display 4 and print 1st digit
    __delay_ms(5); ssd=0;     //Turn OFF display 4 after 5ms delay
    
    PORTD=segmento[segdU]; ssu=1; //Turn ON display 4 and print 1st digit
    __delay_ms(5); ssu=0;     //Turn OFF display 4 after 5ms delay
}

void main()
{
    int flag = 0;

    while(1)
    {
        relogio_click();

        if (flag>=33)
        {
            segd++;
            flag=0;
            
            if (segd >= 60)
            {
                mint++;
                segd = 0;
                
                if (mint >= 60)
                {
                    hora++;
                    mint = 0;
                    
                    if (hora >= 24)
                    {
                        hora = 0;
                    }
                }
            }
        }

        flag++;
    }
}