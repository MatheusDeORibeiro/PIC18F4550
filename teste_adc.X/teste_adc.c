/*
 * File: teste_adc.c
 * Author: Matheus de Oliveira Ribeiro
 *
 * Created on April 12, 2022, 5:27 PM
 */


//Inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"
#include "adc.h"

//Inserindo definições
#define _XTAL_FREQ 20000000 //com uma Fosc de 20MHz temos um Tciclo de 0,2us

void main(void)
{    
    //Declaração de variável local
    unsigned int resultado;
    
    //Configurando pefiféricos
    TRISA = 0x01; //definindo AN0(RA1) como entrada
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //Configurando o estado inicial dos periféricos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    inicializa_ADC(ADC_LEFT_JUST&ADC_FOSC_16&ADC_4_TAD, 
                   ADC_INT_OFF&ADC_VREFPLUS_VDD&ADC_VREFMINUS_VSS&ADC_CH0, 
                   ADC_1AN);
    
    do
    {
        inicia_conversao_ADC();
        while(status_ADC());
        resultado = leitura_ADC();
    
        PORTC = (unsigned char)resultado;        //RC7 e RC6 recebem os dois bits menos significativos dos registradores ADRESH e ADRESL
        PORTD = (unsigned char)(resultado >> 8); //PORTD recebe os oito bits mais significativos dos registradores ADRESH e ADRESL   
    
        //desabilita_ADC();
        _delay(80000);    
    }
    while(1);    
    return;    
}
