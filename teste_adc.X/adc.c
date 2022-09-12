/*
 * Nome do arquivo:    adc.c
 * Data:               28/08/2022
 * Vers�o:             2.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de Oliveira Ribeiro
 */

/*
 * Esta biblioteca cont�m um conjunto de fun��es que permitem configurar e utilizar
 * o conversor anal�gico digital. 
 */

#include <xc.h>  
#include "adc.h" 


/*
 * Esta fun��o habilita e configura o m�dulo conversor A/D:
 * - configuracao_1: formato do resultado, fonte de clock e tempo de aquisi��o autom�tico
 * - configuracao_2: sele��o do canal, interrup��o, configura��o da Vref
 * - configuracao_porta: configura��o das portas do conversor A/D
 *  
 * Para tempo de aquisi��o manual: consultar se��o 21.1 do datashee
 * Para tempo de aquisi��o autom�tico: Taq = Tad / Tciclo = 3,2u / Tciclo, onde: Tciclo = 4 / FOSC 
 */
void inicializa_ADC(unsigned char configuracao_1, unsigned char configuracao_2, unsigned char configuracao_porta)
{
    ADCON0 = 0x00;
    ADCON1 = 0x00;
    ADCON2 = 0x00;
    //configura��o dos registradores ADCON0, ADCON1 e ADCON2
    //sele��o do canal
    ADCON0 |= ((configuracao_2 << 2) & 0b00111100); 
    //configura��o da Vref e configura��o das portas do conversor A/D
    ADCON1 |= ((configuracao_2 & 0b00110000) | (configuracao_porta & 0b00001111)); 
    //formato do resultado, fonte de clock e tempo de aquisi��o autom�tico
    ADCON2 |= (configuracao_1 & 0b10111111);     
    //habilitando o m�dulo A/D
    habilita_ADC();
    //configura��o da interrup��o
    if(configuracao_2 & 0b10000000)
    {
        PIR1bits.ADIF = 0; //limpa o flag bit da interrup��o do ADC
        IPR1bits.ADIP = 0; //configura interrup��o de baixa prioridade
        PIE1bits.ADIE = 1; //habilita a interrup��o do ADC
    }
}

/* Esta fun��o retorna o resultado da convers�o A/D                           */                            
unsigned int leitura_ADC(void)
{
    return (unsigned int)((ADRESH << 8) + ADRESL); //retorna o resultado da convers�o
}

/*
 * Esta fun��o seleciona que ser� canal usado como entrada para o conversor A/D:
 * - canal: seleciona canal de entrada do converdor A/D 
 */
void seleciona_canal_ADC(unsigned char canal)
{
    ADCON0 |= (canal << 2); //seleciona um canal anal�gico
}
