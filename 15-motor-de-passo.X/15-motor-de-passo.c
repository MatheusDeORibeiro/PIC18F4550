/*
 * File:   15-motor-de-passo.c
 * Author: Matheus
 *
 * Created on 5 de Julho de 2021, 16:31
 * 
 * Desenvolver uma programação que faça o motor de passo girar no sentido
 *horário quando pressionado um botão conectado em RB0, e no sentido
 *anti-horário se pressionado um botão conectado em RB1.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FOSC 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us

#define sent_horario  PORTBbits.RB0
#define sent_ahorario PORTBbits.RB1

#define bob1 PORTDbits.RD0
#define bob2 PORTDbits.RD1
#define bob3 PORTDbits.RD2
#define bob4 PORTDbits.RD3

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00000011;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
        
    while(1){
        if(sent_horario == 1){//sentido horário
            PORTD = 0b00000001;//primeiro passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD <<= 1;//segundo passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD <<= 1;//terceiro passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD <<= 1;//quarto passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
        
        }else{
            PORTD = 0x0F;//motor travado
        }
        if(sent_ahorario == 1){//sentido anti-horário
            PORTD = 0b00001000;//primeiro passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD >>= 1;//segundo passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD >>= 1;//terceiro passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
            PORTD >>= 1;//quarto passo
            _delay(500000);//500.000 ciclos gera um atraso de 10ms para garantir uma mudança de estado segura da porta D
        
        }else{
            PORTD = 0x0F;//motor travado
        }
    }
    
    return;
}
