/*
 * File:   09-4-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 14 de Junho de 2021, 18:46
 * 
 * Desenvolver uma programação que faça os leds do PORTD serem rotacionados 
 * (piscar RD0, depois RD1, etc.). Deseja-se um atraso de 100ms e são 
 * necessários 500.000 ciclos de instrução, pode-se utilizar:
 * _delay(500000)
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h" //Inserindo a configuração do dispositivo

//Inserindo definições
#define _XTAL_FREQ_ 20000000 //com uma Fosc de 20MHz temos um Tciclo de 0.2us

void main(void) {
    
    //Configuração dos periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //Configuração inicial do estado do PORTD em nível lógico baixo
    PORTD = 0x00;
 
    while(1){        
        PORTD = 0b00000001;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        PORTD <<= 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
    } 
    return;
}
