/*
 * File:   12-2-display-7-segmentos.c
 * Author: Matheus
 *
 * Created on 29 de Junho de 2021, 15:00
 * 
 * 3ª tarefa do dia: visualizar o número 5 no display utilizando um vetor.
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

void main(void) {
    
    //Condigurando os periféricos do dispositivo
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //vetor de caracteres armazenando os segmentos que devem ser acesos em hexadecimal
    char cod_display[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                            0x7f, 0x6f};
    
    while(1){
        PORTD = cod_display[5];
    } 
    
    return;
}
