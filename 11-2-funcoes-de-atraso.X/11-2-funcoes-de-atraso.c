/*
 * File:   11-2-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 22 de Junho de 2021, 13:26
 * 
 * Ao pressionar RB1: rotacionar os leds do PORTD, de RD0 à RD7(emloop), 
 *mudando de led a cada 0,8s; para gerar um atraso de 0,8 segundo são necessários
 *4.000.000 de ciclos.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us
#define RB1 PORTBbits.RB1

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00000010;
    TRISC = 0x00;    
    TRISD = 0x00;
    TRISE = 0x00;
    
    while(1){
        if(RB1 == 1){
            PORTD = 0b00000001;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
            PORTD <<= 1;
            _delay(4000000); //4.000.000 de ciclos gera um atraso de 0,8 segundos
        }else{
            PORTD = 0x00;
        }
    }
    
    return;
}
