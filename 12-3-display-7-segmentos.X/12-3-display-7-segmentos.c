/*
 * File:   12-3-display-7-segmentos.c
 * Author: Matheus
 *
 * Created on 29 de Junho de 2021, 17:34
 * 
 * 1- Ao pressionar os botões de 0 a 7 (conectados ao PORTB), demonstrar o 
 *respectivo número no display de 7 segmentos.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us

#define RB0 PORTBbits.RB0
#define RB1 PORTBbits.RB1
#define RB2 PORTBbits.RB2
#define RB3 PORTBbits.RB3
#define RB4 PORTBbits.RB4
#define RB5 PORTBbits.RB5
#define RB6 PORTBbits.RB6
#define RB7 PORTBbits.RB7

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0xff;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //vetor de caracteres armazenando os segmentos que devem ser acesos em hexadecimal
    char cod_display[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                            0x7f, 0x6f};
    
    while(1){
        if(RB0 == 1){
            PORTD = cod_display[0];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB1 == 1){
            PORTD = cod_display[1];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB2 == 1){
            PORTD = cod_display[2];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB3 == 1){
            PORTD = cod_display[3];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB4 == 1){
            PORTD = cod_display[4];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB5 == 1){
            PORTD = cod_display[5];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB6 == 1){
            PORTD = cod_display[6];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
        if(RB7 == 1){
            PORTD = cod_display[7];
            _delay(100000);//100.000 de ciclos gera um atraso de 20ms
        }else{
            PORTD = 0x00;    
        }
    }
    
    return;
}
