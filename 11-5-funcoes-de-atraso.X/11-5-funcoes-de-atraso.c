/*
 * File:   11-5-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 22 de Junho de 2021, 15:47
 *
 * Ao pressionar RB0: todo o PORTD deve piscar no tempo de 1s; para gerar um 
 *atraso de 1 segundo são necessários 5.000.000 de ciclos.
 * Ao pressionar RB1: rotacionar os leds do PORTD, de RD0 à RD7(emloop), 
 *mudando de led a cada 0,8s; para gerar um atraso de 0,8 segundo são necessários
 *4.000.000 de ciclos.
 * Ao pressionar RB2: da mesma forma que a função anterior, mas deRD7 à RD0, 
 *acada 0,6s; para gerar um atraso de 0,6 segundos são necessários 3.000.000 de
 *ciclos.
 * A opressionar RB3: piscar alternadamente todos os leds pares e ímpares, 
 *em 0,5s; para gerar um atraso de 0,5 segundo são necessários 2.500.000 ciclos.
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

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00001111;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    while(1){
        if(RB0 == 1){
            PORTD = 0xff;
            _delay(5000000); //5.000.000 de ciclos gera um atraso de 1 segundo
            PORTD = 0x00;
            _delay(5000000); //5.000.000 de ciclos gera um atraso de 1 segundo
        }
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
        }
        if(RB2 == 1){
            PORTD = 0b10000000;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
            PORTD >>= 1;
            _delay(3000000); //3.000.000 de ciclos geram um atraso de 0,6 segundos
        }
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
