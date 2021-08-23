/*
 * File:   08-portas-digitais.c
 * Author: Matheus
 *
 * Created on 12 de Junho de 2021, 14:30
 * 
 *Na aula passada, você utilizou o firmware do professor que ao ligar RB0 
 *através de um botão, o led de RD0 era acionado, assim como RB1 e RD1, e 
 *assim por diante. 
 *Sua tarefa agora consiste em criar uma programação que faça o acionamento
 *inverso: Ao acionar RB0, acionar RD7, acionando RB1, acionar RD6, e assim 
 *por diante. 
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h" //Inserindo a configuração do dispositivo

//Inserindo definições
#define botao_0 PORTBbits.RB0
#define botao_1 PORTBbits.RB1
#define botao_2 PORTBbits.RB2
#define botao_3 PORTBbits.RB3
#define botao_4 PORTBbits.RB4
#define botao_5 PORTBbits.RB5
#define botao_6 PORTBbits.RB6
#define botao_7 PORTBbits.RB7

#define led_0 PORTDbits.RD0
#define led_1 PORTDbits.RD1
#define led_2 PORTDbits.RD2
#define led_3 PORTDbits.RD3
#define led_4 PORTDbits.RD4
#define led_5 PORTDbits.RD5
#define led_6 PORTDbits.RD6
#define led_7 PORTDbits.RD7

void main(void){

    //Configuração dos periféricos do dispositivo
    ADCON1 = 0b00001111; //Configurando os canais analógicos como I/Os
    TRISA = 0x00;
    TRISB = 0xff;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    if(botao_0 == 1){
        led_7 = 1;
    }else{
        led_7 = 0;
    }
    if(botao_1 == 1){
        led_6 = 1;
    }else{
        led_6 = 0;
    }
    if(botao_2 == 1){
        led_5 = 1;
    }else{
        led_5 = 0;
    }
    if(botao_3 == 1){
        led_4 = 1;
    }else{
        led_4 = 0;
    }
    if(botao_4 == 1){
        led_3 = 1;
    }else{
        led_3 = 0;
    }
    if(botao_5 == 1){
        led_2 = 1;
    }else{
        led_2 = 0;
    }
    if(botao_6 == 1){
        led_1 = 1;
    }else{
        led_1 = 0;
    }
    if(botao_7 == 1){
        led_0 = 1;
    }else{
        led_0 = 0;
    }

    return;
}
