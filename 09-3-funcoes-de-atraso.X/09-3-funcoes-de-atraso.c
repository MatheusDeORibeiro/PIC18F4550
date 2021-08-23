/*
 * File:   09-3-funcoes-de-atraso.c
 * Author: Matheus
 *
 * Created on 14 de Junho de 2021, 15:53
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
#define _XTAL_FREQ_ 20000000 //com uma Fosc de 20MHz temos um Tciclo de 0,2us

#define RD0 PORTDbits.RD0
#define RD1 PORTDbits.RD1 
#define RD2 PORTDbits.RD2 
#define RD3 PORTDbits.RD3 
#define RD4 PORTDbits.RD4 
#define RD5 PORTDbits.RD5 
#define RD6 PORTDbits.RD6 
#define RD7 PORTDbits.RD7 

void main(void) {

    //Configuração dos periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //Configuração do estado inicial do PORTD em nível lógico baixo
    PORTD = 0x00;

    while(1){
        RD0 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD0 = 0;
        RD1 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD1 = 0;
        RD2 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD2 = 0;
        RD3 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD3 = 0;
        RD4 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD4 = 0;
        RD5 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD5 = 0;
        RD6 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD6 = 0;
        RD7 = 1;
        _delay(500000); //para gerar um atraso de 100ms são necessários 500.000 ciclos
        RD7 = 0;
    }

    return;
}
