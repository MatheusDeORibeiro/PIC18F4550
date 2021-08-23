/*
 * File:   11-3-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 22 de Junho de 2021, 14:44
 * 
 * Ao pressionar RB2: da mesma forma que a função anterior, mas deRD7 à RD0, 
 *acada 0,6s; para gerar um atraso de 0,6 segundos são necessários 3.000.000 de
 *ciclos.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us
#define RB2 PORTBbits.RB2

void main(void) {
    
    //Configurando periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00000100;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    while(1){
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
        }else{
            PORTD = 0x00;
        }
    }
    
    return;
}
