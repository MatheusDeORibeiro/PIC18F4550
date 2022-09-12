/*
 * Nome do arquivo:    adc.c
 * Data:               28/08/2022
 * Versão:             2.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de Oliveira Ribeiro
 */

/*
 * Esta biblioteca contém um conjunto de funções que permitem configurar e utilizar
 * o conversor analógico digital. 
 */

#include <xc.h>  
#include "adc.h" 


/*
 * Esta função habilita e configura o módulo conversor A/D:
 * - configuracao_1: formato do resultado, fonte de clock e tempo de aquisição automático
 * - configuracao_2: seleção do canal, interrupção, configuração da Vref
 * - configuracao_porta: configuração das portas do conversor A/D
 *  
 * Para tempo de aquisição manual: consultar seção 21.1 do datashee
 * Para tempo de aquisição automático: Taq = Tad / Tciclo = 3,2u / Tciclo, onde: Tciclo = 4 / FOSC 
 */
void inicializa_ADC(unsigned char configuracao_1, unsigned char configuracao_2, unsigned char configuracao_porta)
{
    ADCON0 = 0x00;
    ADCON1 = 0x00;
    ADCON2 = 0x00;
    //configuração dos registradores ADCON0, ADCON1 e ADCON2
    //seleção do canal
    ADCON0 |= ((configuracao_2 << 2) & 0b00111100); 
    //configuração da Vref e configuração das portas do conversor A/D
    ADCON1 |= ((configuracao_2 & 0b00110000) | (configuracao_porta & 0b00001111)); 
    //formato do resultado, fonte de clock e tempo de aquisição automático
    ADCON2 |= (configuracao_1 & 0b10111111);     
    //habilitando o módulo A/D
    habilita_ADC();
    //configuração da interrupção
    if(configuracao_2 & 0b10000000)
    {
        PIR1bits.ADIF = 0; //limpa o flag bit da interrupção do ADC
        IPR1bits.ADIP = 0; //configura interrupção de baixa prioridade
        PIE1bits.ADIE = 1; //habilita a interrupção do ADC
    }
}

/* Esta função retorna o resultado da conversão A/D                           */                            
unsigned int leitura_ADC(void)
{
    return (unsigned int)((ADRESH << 8) + ADRESL); //retorna o resultado da conversão
}

/*
 * Esta função seleciona que será canal usado como entrada para o conversor A/D:
 * - canal: seleciona canal de entrada do converdor A/D 
 */
void seleciona_canal_ADC(unsigned char canal)
{
    ADCON0 |= (canal << 2); //seleciona um canal analógico
}
