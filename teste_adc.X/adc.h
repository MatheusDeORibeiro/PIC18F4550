/*
 * Nome do arquivo:    adc.h
 * Data:               28/08/2022
 * Vers�o:             2.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de Oliveira Ribeiro
 */

#ifndef __ADC_H
#define	__ADC_H

#include <xc.h>


//******************************************************************************
//defini��es de macros para configura��o dos registradores ADCON0, ADCON1 e ADCON2
//******************************************************************************

//*************************** macros para o ADCON0 *****************************

//bit ADCON0<0> habilita ou desabilita o m�dulo A/D

//bit ADCON0<1> mostra o status da convers�o

//bits de sele��o do canal anal�gico ADCON0<5:2> ser�o macro<3:0>

#define ADC_CH0  0b11110000 //seleciona o canal anal�gico 0
#define ADC_CH1  0b11110001 //seleciona o canal anal�gico 1
#define ADC_CH2  0b11110010 //seleciona o canal anal�gico 2
#define ADC_CH3  0b11110011 //seleciona o canal anal�gico 3
#define ADC_CH4  0b11110100 //seleciona o canal anal�gico 4
#define ADC_CH5  0b11110101 //seleciona o canal anal�gico 5
#define ADC_CH6  0b11110110 //seleciona o canal anal�gico 6
#define ADC_CH7  0b11110111 //seleciona o canal anal�gico 7
#define ADC_CH8  0b11111000 //seleciona o canal anal�gico 8
#define ADC_CH9  0b11111001 //seleciona o canal anal�gico 9
#define ADC_CH10 0b11111010 //seleciona o canal anal�gico 10
#define ADC_CH11 0b11111011 //seleciona o canal anal�gico 11
#define ADC_CH12 0b11111100 //seleciona o canal anal�gico 12

//bits ADCON0<7:6> s�o lidos como 0

//bit macro<7> habilita ou desabilita a interrup��o

#define ADC_INT_ON  0b11111111 //habilita a interrup��o do conversor A/D
#define ADC_INT_OFF 0b01111111 //desabilita a interrup��o conversor A/D

//*************************** macros para o ADCON1 *****************************

//bits de configura��o da porta A/D ADCON1<3:0>

#define ADC_13AN 0b11110010 //de AN0 at� AN12 � configurado como entrada anal�gica
#define ADC_12AN 0b11110011 //de AN0 at� AN11 � configurado como entrada anal�gica
#define ADC_11AN 0b11110100 //de AN0 at� AN10 � configurado como entrada anal�gica
#define ADC_10AN 0b11110101 //de AN0 at� AN09 � configurado como entrada anal�gica
#define ADC_9AN  0b11110110 //de AN0 at� AN08 � configurado como entrada anal�gica
#define ADC_8AN  0b11110111 //de AN0 at� AN07 � configurado como entrada anal�gica
#define ADC_7AN  0b11111000 //de AN0 at� AN06 � configurado como entrada anal�gica
#define ADC_6AN  0b11111001 //de AN0 at� AN05 � configurado como entrada anal�gica
#define ADC_5AN  0b11111010 //de AN0 at� AN04 � configurado como entrada anal�gica
#define ADC_4AN  0b11111011 //de AN0 at� AN03 � configurado como entrada anal�gica
#define ADC_3AN  0b11111100 //de AN0 at� AN02 � configurado como entrada anal�gica
#define ADC_2AN  0b11111101 //de AN0 at� AN01 � configurado como entrada anal�gica
#define ADC_1AN  0b11111110 //AN0 � configurado como entrada anal�gica
#define ADC_0AN  0b11111111 //todo o canal anal�gico � configurado como I/O digital

//bit da tens�o de refer�ncia positiva (Vref+) ADCON1<4>

#define ADC_VREFPLUS_AN3 0b11011111 //utiliza a tens�o do canal AN3 como fonte de tens�o de refer�ncia positiva
#define ADC_VREFPLUS_VDD 0b11001111 //utiliza a tens�o positiva da fonte como fonte de tens�o de refer�ncia positiva

//bit da tens�o de refer�ncia negativa (Vref-) ADCON1<5>

#define ADC_VREFMINUS_AN2 0b11111111 //utiliza a tens�o do canal AN2 como fonte de tens�o de refer�ncia negativa
#define ADC_VREFMINUS_VSS 0b11011111 //utiliza a tens�o negativa da fonte como fonte tens�o de refer�ncia negativa

//bits ADCON1<7:6> s�o lidos como 0

//*************************** macros para o ADCON2 *****************************

//bits de sele��o do clock de convers�o ADCON2<2:0>

#define ADC_FOSC_2    0b11111000 //clock para FOSC at� 2,50MHz
#define ADC_FOSC_8    0b11111001 //clock para FOSC at� 10,00MHz
#define ADC_FOSC_32   0b11111010 //clock para FOSC at� 40,00MHz
#define ADC_FOSC_FRC  0b11111011 //clock derivado do oscilador RC, para at� 1,00MHz
#define ADC_FOSC_4    0b11111100 //clock para FOSC at� 5,00MHz
#define ADC_FOSC_16   0b11111101 //clock para FOSC at� 20,00MHz
#define ADC_FOSC_64   0b11111110 //clock para FOSC at� 48,00MHz

//bits de sele��o do tempo de aquisi��o ADCON2<5:3>

#define ADC_0_TAD  0b11000111 //tempo de aquisi��o manual, para FRC, osciador interno
#define ADC_2_TAD  0b11001111 //tempo de aquisi��o de 2 * Tad
#define ADC_4_TAD  0b11010111 //tempo de aquisi��o de 4 * Tad
#define ADC_6_TAD  0b11011111 //tempo de aquisi��o de 6 * Tad
#define ADC_8_TAD  0b11100111 //tempo de aquisi��o de 8 * Tad
#define ADC_12_TAD 0b11101111 //tempo de aquisi��o de 12 * Tad
#define ADC_16_TAD 0b11110111 //tempo de aquisi��o de 16 * Tad
#define ADC_20_TAD 0b11111111 //tempo de aquisi��o de 20 * Tad

//ADCON2<6> � lido como 0

//bit de sele��o do formato do resultado ADCON2<7>

#define ADC_RIGTH_JUST 0b11111111 //resultado justificado � direita
#define ADC_LEFT_JUST  0b01111111 //resultado justificado � esquerda

//******************************************************************************
//defini��es de macros para leitura ou escrita em bits dos registradores do converdor A/C
//******************************************************************************

/* 
 * Esta macro verifica se o m�dulo conversor A/D est� em um processo de convers�o
 * ou n�o, e retorna '1' se o perif�rico estiver ocupado, ou '0' se o pefif�rico
 * estiver livre 
 */
#define status_ADC() (ADCON0bits.DONE)

/* Esta macro habilita o conversor A/D                                        */
#define habilita_ADC() (ADCON0bits.ADON = 1)

/* Esta macro desabilita o conversor A/D                                      */
#define desabilita_ADC() (ADCON0bits.ADON = 0)

/* Esta macro inicia o processo de convers�o do sinal anal�gico               */
#define inicia_conversao_ADC() (ADCON0bits.GO = 1)

//******************************************************************************
//prot�tipos de fun��es
//******************************************************************************

void inicializa_ADC(unsigned char configuracao_1, unsigned char configuracao_2, unsigned char configuracao_porta);
unsigned int leitura_ADC(void);
void seleciona_canal_ADC(unsigned char canal);

#endif	/* __ADC_H */

