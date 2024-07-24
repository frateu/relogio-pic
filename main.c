/*
 * File:   main.c
 * Author: mathe
 *
 * Created on 23 de Julho de 2024, 09:15
 */

#include <xc.h>
#include "relogio.h"

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
    
    // Liga e desliga o display de decimal das Horas
    PORTD=segmento[horaD]; SET_PIN_HIGH(PORTC, shd); __delay_ms(5); SET_PIN_LOW(PORTC, shd);
    
    // Liga e desliga o display de unidade das Horas
    PORTD=segmento[horaU]; SET_PIN_HIGH(PORTC, shu); SET_PIN_HIGH(PORTD, dp); __delay_ms(5); SET_PIN_LOW(PORTC, shu); SET_PIN_LOW(PORTD, dp);
    
    // Liga e desliga o display de decimal dos Minutos
    PORTD=segmento[mintD]; SET_PIN_HIGH(PORTC, smd); __delay_ms(5); SET_PIN_LOW(PORTC, smd);
    
    // Liga e desliga o display de unidade dos Minutos
    PORTD=segmento[mintU]; SET_PIN_HIGH(PORTC, smu); SET_PIN_HIGH(PORTD, dp); __delay_ms(5); SET_PIN_LOW(PORTC, smu); SET_PIN_LOW(PORTD, dp);
    
    // Liga e desliga o display de decimal dos Segundos
    PORTD=segmento[segdD]; SET_PIN_HIGH(PORTC, ssd); __delay_ms(5); SET_PIN_LOW(PORTC, ssd);
    
    // Liga e desliga o display de unidade dos Segundos
    PORTD=segmento[segdU]; SET_PIN_HIGH(PORTC, ssu); __delay_ms(5); SET_PIN_LOW(PORTC, ssu);
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