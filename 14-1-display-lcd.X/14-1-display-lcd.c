/*
 * File:   14-1-dispay-lcd.c
 * Author: Matheus
 *
 * Created on 2 de Julho de 2021, 16:29
 * 
 * Crie um novo projeto no MPLabX e utilize o código abaixo para uma primeira
 *utilização do Display LCD:
 */

//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"
#include "biblioteca_lcd_2x16.h"

//Inserindo definições
#define _XTAL_FOSC 20000000; //Com uma Fosc de 20MHz temos um Tciclo de 0,2us

void main(void) {
    
    //Configurando os periféricos do dispositovo
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
    TRISE=0x00;
    
    lcd_inicia(0x28,0x0F,0x06); //lcd_inicializa(0x28,0x0F,0x03); //Inicializa o display de lcd alfanumérico
    //Display: 0x28 - comunicação de 4 vias, display de 2 linhas e matriz 8x5
    //Cursor: 0x0F - liga o cursor com alternância
    //Cursor: 0x06 - desloca o cursor para a direita quando um caractere é inserido, mas não desloca a mensagem
    lcd_limpa_tela(); //limpa a tela do display lcd
    lcd_posicao(1,1); //coloca o cursor do display na linha 1 e na coluna 1
    lcd_LD_cursor(0); //desliga o cursor
    lcd_posicao(1,6); //coloca o cursor do display na linha 1 e na coluna 6
    imprime_string_lcd("Teste display"); //envia uma string para o display de lcd
    lcd_posicao(2,4); //coloca o cursor do display  na lina 2 e na coluna 4
    imprime_string_lcd("Teste display"); //envia uma string para o display de lcd
    while(1){
        _delay(300000); //Delay10KTCYx(30);
        lcd_desloca_mensagem(1); //desloca a mensagem para a direita
    }
   return;
}
