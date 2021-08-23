/*
 * File:   13-teclado-matricial.c
 * Author: Matheus
 *
 * Created on 30 de Junho de 2021, 17:19
 * 
 * Alterar o atual template do Proteus (que já está com o display de 7
 *segmentos no PORTD) substituindo os botões do PORTB por um teclado matricial; 
 *Desenvolver um programa que ao pressionar uma tecla do teclado matricial 
 *(1 a 9), o seu respectivo número seja exibido no display. Por padrão o número 
 *0 deve ser exibido quando nenhuma tecla estiver sendo pressionada.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //Com uma Fosc de 20MHz temos um Tciclo de 0,2us

#define RB2 PORTBbits.RB2 //3ª linha; saída
#define RB3 PORTBbits.RB3 //2ª linha; saída
#define RB4 PORTBbits.RB4 //1ª linha; saída
#define RB5 PORTBbits.RB5 //1ª coluna; entrada;
#define RB6 PORTBbits.RB6 //2ª coluna; entrada
#define RB7 PORTBbits.RB7 //3ª coluna; entrada

//Definindo o protótipo da função le_teclado
int le_teclado(void);

void main(void) {
    
    //Configurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0b00011100; 
    TRISD = 0x00;
    TRISC = 0x00;
    TRISE = 0x00;
    
    //Habilitando os pull-ups internos do PORTB
    INTCON2bits.NOT_RBPU = 0;
    
    //Criando um vetor de caracteres contendo os segmentos do display que devem 
    //ser acesos em hexadecimal
    char cod_display[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                            0x7f, 0x6f};
    //Criando uma variável inteira para armazenar o número da tecla para 
    //selecionar o número que será exibido no display
    int tecla;
    
    while(1){
        tecla = le_teclado();        
        PORTD = cod_display[tecla];
    }
    
    return;
}

int le_teclado(void){
    //Seleciona a terceira coluna
    RB5 = 1;
    RB6 = 1;
    RB7 = 0;
    _delay(100000); //100,000 ciclos gera um atraso de 20ms para mudança de estado dos pinos
    if(!RB4) return 3; //Verifica a primeira linha
    if(!RB3) return 6; //Verifica a segunda linha
    if(!RB2) return 9; //Verifica a terceira linha
    //Seleciona a segunda coluna
    RB6 = 0;
    RB7 = 1;
    _delay(100000); //100,000 ciclos gera um atraso de 20ms para mudança de estado dos pinos
    if(!RB4) return 2; //Verifica a primeira linha
    if(!RB3) return 5; //Verifica a segunda linha
    if(!RB2) return 8; //Verifica a terceira linha
    //Saleciona a primeira coluna
    RB5 = 0;
    RB6 = 1;
    _delay(100000); //100,000 ciclos gera um atraso de 20ms para mudança de estado dos pinos
    if(!RB4) return 1; //Verifica a primeira linha
    if(!RB3) return 4; //Verifica a segunda linha
    if(!RB2) return 7; //Verifica a terceira linha
    return 0; //Se nenhuma tecla for pressionada retorna 0
    
}