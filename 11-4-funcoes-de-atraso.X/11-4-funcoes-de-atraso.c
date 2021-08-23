/*
 * File:   11-4-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 22 de Junho de 2021, 15:33
 * 
 * A opressionar RB3: piscar alternadamente todos os leds pares e ímpares, 
 *em 0,5s; para gerar um atraso de 0,5 segundo são necessários 2.500.000 ciclos.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us
#define RB3 PORTBbits.RB3

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00001000;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    while(1){
        if(RB3 == 1){
            PORTD = 0b01010101; //Acendendo os leds pares e apagando os leds ímpares
            _delay(2500000); //2.500.000 ciclos geram um atraso de 0,5 segundo
            PORTD = 0b10101010; //Acendendo os leds ímpares e apagando os leds pares
            _delay(2500000); //2.500.000 ciclos geram um atraso de 0,5 segundo
        }else{
            PORTD = 0x00;
        }
    }
    return;
}
