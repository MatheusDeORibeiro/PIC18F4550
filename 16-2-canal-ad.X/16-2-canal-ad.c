/*
 * File:   16-2-canal-ad.c
 * 
 * Autor: Alberto Noboru Miyadara                                              
 * Modificação: 08/07/2021 - Modificação do projeto para se adequar ao compila-
 * -dor xc8.                                                                   
 */


//inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//inserindo definições
#define _XTAL_FREQ 20000000 //com uma Fosc de 20MHz temos um Tciclo de 0,2us
#define LED LATCbits.LATC0

//declarando protótipos de funções
void ADC_inicializa(void);
unsigned int ADC_resultado(void);

void main(void) {
    //configurando os periféricos do dispositivo
    TRISA = 0xFF; //configura todos os pinos da porta A, inclusive AN0, como entrada
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //inicializa o estado do LED
    LED = 0;
    
    //criando variável para armazenar o resultado da conversão
    unsigned int resultado_conv;
    
    //1 - configuração do módulo A/D
    ADC_inicializa();
    
    while(1){
        resultado_conv = ADC_resultado(); //armazena o resultado da conversão
        //Vcc =5V
        //Vref+ = Vdd e Vref- = Vss
        //V_1bit = 4,447586mV
        //resultado_conv = 410 -> V_sinal_analogico = 2,003776V
        //Se o resultado_conv for maior ou igual do que 410, o LED é lligado
        if(resultado_conv >= 410){
            LED = 1; //liga o LED
        }else{
            LED = 0; //desliga o LED
        }
    }
    
    return;
}

void ADC_inicializa(){
    //configurando os controles de operação
    ADCON0 = 0b00000001;//00-lidos como '0'; 0000-seleciona o canal AN0; 0-status da conversão; 1-habilita o módulo A/D
    //configurando as funções dos pinos da porta
    ADCON1 = 0b0000000; //00-lidos como '0'; 0-tensão de referência Vss(terra da fonte); 0-tensão de referência Vdd(positivo da fonte); 0000-configura todo o canal A/D como entrada analógica
    //configurando a fonte de clock, tempo de aquisição programada e a justificação
    ADCON2 = 0b10010101; //1-formatação a direita do resultado; 0-lido como '0'; 010-selecionando tempo de aquisição de 4Tad; 101-selecionando clock de conversão de Fos/16
}

unsigned int ADC_resultado(void){
    _delay(80000); //um delay de 80.000 ciclos gera um atraso de 16ms para carga do capacitor Chold
    ADCON0bits.GO = 1; //inicia a conversão depois da aquisição automática
    while(ADCON0bits.DONE); //espera a conversão ser concluída
    return (unsigned int)((ADRESH<<8)+ADRESL); //o resultado da conversão é armazenado em ADRESH e ADRESL
}