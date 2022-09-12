/*
 * File:   16-2-canal-ad.c
 * 
 * Autor: Alberto Noboru Miyadara                                              
 * Modifica��o: 08/07/2021 - Modifica��o do projeto para se adequar ao compila-
 * -dor xc8.                                                                   
 */


//inserindo bibliotecas
#include <xc.h>
#include "configuracao_pic18f4550.h"

//inserindo defini��es
#define _XTAL_FREQ 20000000 //com uma Fosc de 20MHz temos um Tciclo de 0,2us
#define LED LATCbits.LATC0

//declarando prot�tipos de fun��es
void ADC_inicializa(void);
unsigned int ADC_resultado(void);

void main(void) {
    //configurando os perif�ricos do dispositivo
    TRISA = 0xFF; //configura todos os pinos da porta A, inclusive AN0, como entrada
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //inicializa o estado do LED
    LED = 0;
    
    //criando vari�vel para armazenar o resultado da convers�o
    unsigned int resultado_conv;
    
    //1 - configura��o do m�dulo A/D
    ADC_inicializa();
    
    while(1){
        resultado_conv = ADC_resultado(); //armazena o resultado da convers�o
        //Vcc =5V
        //Vref+ = Vdd e Vref- = Vss
        //V_1bit = 4,447586mV
        //resultado_conv = 410 -> V_sinal_analogico = 2,003776V
        //Se o resultado_conv for maior ou igual do que 410, o LED � lligado
        if(resultado_conv >= 410){
            LED = 1; //liga o LED
        }else{
            LED = 0; //desliga o LED
        }
    }
    
    return;
}

void ADC_inicializa(){
    //configurando os controles de opera��o
    ADCON0 = 0b00000001;//00-lidos como '0'; 0000-seleciona o canal AN0; 0-status da convers�o; 1-habilita o m�dulo A/D
    //configurando as fun��es dos pinos da porta
    ADCON1 = 0b0000000; //00-lidos como '0'; 0-tens�o de refer�ncia Vss(terra da fonte); 0-tens�o de refer�ncia Vdd(positivo da fonte); 0000-configura todo o canal A/D como entrada anal�gica
    //configurando a fonte de clock, tempo de aquisi��o programada e a justifica��o
    ADCON2 = 0b10010101; //1-formata��o a direita do resultado; 0-lido como '0'; 010-selecionando tempo de aquisi��o de 4Tad; 101-selecionando clock de convers�o de Fos/16
}

unsigned int ADC_resultado(void){
    _delay(80000); //um delay de 80.000 ciclos gera um atraso de 16ms para carga do capacitor Chold
    ADCON0bits.GO = 1; //inicia a convers�o depois da aquisi��o autom�tica
    while(ADCON0bits.DONE); //espera a convers�o ser conclu�da
    return (unsigned int)((ADRESH<<8)+ADRESL); //o resultado da convers�o � armazenado em ADRESH e ADRESL
}