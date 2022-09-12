/*
 * Nome do arquivo:    adc.h
 * Data:               28/08/2022
 * Versão:             2.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de Oliveira Ribeiro
 */

#ifndef __ADC_H
#define	__ADC_H

#include <xc.h>


//******************************************************************************
//definições de macros para configuração dos registradores ADCON0, ADCON1 e ADCON2
//******************************************************************************

//*************************** macros para o ADCON0 *****************************

//bit ADCON0<0> habilita ou desabilita o módulo A/D

//bit ADCON0<1> mostra o status da conversão

//bits de seleção do canal analógico ADCON0<5:2> serão macro<3:0>

#define ADC_CH0  0b11110000 //seleciona o canal analógico 0
#define ADC_CH1  0b11110001 //seleciona o canal analógico 1
#define ADC_CH2  0b11110010 //seleciona o canal analógico 2
#define ADC_CH3  0b11110011 //seleciona o canal analógico 3
#define ADC_CH4  0b11110100 //seleciona o canal analógico 4
#define ADC_CH5  0b11110101 //seleciona o canal analógico 5
#define ADC_CH6  0b11110110 //seleciona o canal analógico 6
#define ADC_CH7  0b11110111 //seleciona o canal analógico 7
#define ADC_CH8  0b11111000 //seleciona o canal analógico 8
#define ADC_CH9  0b11111001 //seleciona o canal analógico 9
#define ADC_CH10 0b11111010 //seleciona o canal analógico 10
#define ADC_CH11 0b11111011 //seleciona o canal analógico 11
#define ADC_CH12 0b11111100 //seleciona o canal analógico 12

//bits ADCON0<7:6> são lidos como 0

//bit macro<7> habilita ou desabilita a interrupção

#define ADC_INT_ON  0b11111111 //habilita a interrupção do conversor A/D
#define ADC_INT_OFF 0b01111111 //desabilita a interrupção conversor A/D

//*************************** macros para o ADCON1 *****************************

//bits de configuração da porta A/D ADCON1<3:0>

#define ADC_13AN 0b11110010 //de AN0 até AN12 é configurado como entrada analógica
#define ADC_12AN 0b11110011 //de AN0 até AN11 é configurado como entrada analógica
#define ADC_11AN 0b11110100 //de AN0 até AN10 é configurado como entrada analógica
#define ADC_10AN 0b11110101 //de AN0 até AN09 é configurado como entrada analógica
#define ADC_9AN  0b11110110 //de AN0 até AN08 é configurado como entrada analógica
#define ADC_8AN  0b11110111 //de AN0 até AN07 é configurado como entrada analógica
#define ADC_7AN  0b11111000 //de AN0 até AN06 é configurado como entrada analógica
#define ADC_6AN  0b11111001 //de AN0 até AN05 é configurado como entrada analógica
#define ADC_5AN  0b11111010 //de AN0 até AN04 é configurado como entrada analógica
#define ADC_4AN  0b11111011 //de AN0 até AN03 é configurado como entrada analógica
#define ADC_3AN  0b11111100 //de AN0 até AN02 é configurado como entrada analógica
#define ADC_2AN  0b11111101 //de AN0 até AN01 é configurado como entrada analógica
#define ADC_1AN  0b11111110 //AN0 é configurado como entrada analógica
#define ADC_0AN  0b11111111 //todo o canal analógico é configurado como I/O digital

//bit da tensão de referência positiva (Vref+) ADCON1<4>

#define ADC_VREFPLUS_AN3 0b11011111 //utiliza a tensão do canal AN3 como fonte de tensão de referência positiva
#define ADC_VREFPLUS_VDD 0b11001111 //utiliza a tensão positiva da fonte como fonte de tensão de referência positiva

//bit da tensão de referência negativa (Vref-) ADCON1<5>

#define ADC_VREFMINUS_AN2 0b11111111 //utiliza a tensão do canal AN2 como fonte de tensão de referência negativa
#define ADC_VREFMINUS_VSS 0b11011111 //utiliza a tensão negativa da fonte como fonte tensão de referência negativa

//bits ADCON1<7:6> são lidos como 0

//*************************** macros para o ADCON2 *****************************

//bits de seleção do clock de conversão ADCON2<2:0>

#define ADC_FOSC_2    0b11111000 //clock para FOSC até 2,50MHz
#define ADC_FOSC_8    0b11111001 //clock para FOSC até 10,00MHz
#define ADC_FOSC_32   0b11111010 //clock para FOSC até 40,00MHz
#define ADC_FOSC_FRC  0b11111011 //clock derivado do oscilador RC, para até 1,00MHz
#define ADC_FOSC_4    0b11111100 //clock para FOSC até 5,00MHz
#define ADC_FOSC_16   0b11111101 //clock para FOSC até 20,00MHz
#define ADC_FOSC_64   0b11111110 //clock para FOSC até 48,00MHz

//bits de seleção do tempo de aquisição ADCON2<5:3>

#define ADC_0_TAD  0b11000111 //tempo de aquisição manual, para FRC, osciador interno
#define ADC_2_TAD  0b11001111 //tempo de aquisição de 2 * Tad
#define ADC_4_TAD  0b11010111 //tempo de aquisição de 4 * Tad
#define ADC_6_TAD  0b11011111 //tempo de aquisição de 6 * Tad
#define ADC_8_TAD  0b11100111 //tempo de aquisição de 8 * Tad
#define ADC_12_TAD 0b11101111 //tempo de aquisição de 12 * Tad
#define ADC_16_TAD 0b11110111 //tempo de aquisição de 16 * Tad
#define ADC_20_TAD 0b11111111 //tempo de aquisição de 20 * Tad

//ADCON2<6> é lido como 0

//bit de seleção do formato do resultado ADCON2<7>

#define ADC_RIGTH_JUST 0b11111111 //resultado justificado à direita
#define ADC_LEFT_JUST  0b01111111 //resultado justificado à esquerda

//******************************************************************************
//definições de macros para leitura ou escrita em bits dos registradores do converdor A/C
//******************************************************************************

/* 
 * Esta macro verifica se o módulo conversor A/D está em um processo de conversão
 * ou não, e retorna '1' se o periférico estiver ocupado, ou '0' se o pefiférico
 * estiver livre 
 */
#define status_ADC() (ADCON0bits.DONE)

/* Esta macro habilita o conversor A/D                                        */
#define habilita_ADC() (ADCON0bits.ADON = 1)

/* Esta macro desabilita o conversor A/D                                      */
#define desabilita_ADC() (ADCON0bits.ADON = 0)

/* Esta macro inicia o processo de conversão do sinal analógico               */
#define inicia_conversao_ADC() (ADCON0bits.GO = 1)

//******************************************************************************
//protótipos de funções
//******************************************************************************

void inicializa_ADC(unsigned char configuracao_1, unsigned char configuracao_2, unsigned char configuracao_porta);
unsigned int leitura_ADC(void);
void seleciona_canal_ADC(unsigned char canal);

#endif	/* __ADC_H */

