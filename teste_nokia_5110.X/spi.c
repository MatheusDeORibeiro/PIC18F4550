/* 
 * Nome do arquivo:    spi.h
 * Data:               24/08/2022
 * Vers�o:             1.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de O. Ribeiro 
 */
  
/*
 * Esta biblioteca cont�m um conjunto de fun��es que permitem configurar e utilizar
 * o m�dulo MSSP no modo SPI. 
 */

#include <xc.h>  
#include "spi.h"


/*
 * A fun��o OpenSPI configura e habililta o m�dulo MSSP modo SPI
 * - modo:       define o modo de opera��o do modo SP
 * - modo_clock: define o modo de opera��o do sinal de cloc
 * - f_amostra:  define a fase de leitura do dado
 */
void Inicializa_SPI(unsigned char modo, unsigned char modo_clock, unsigned char f_amostra)
{    
    //programando os bits de controle SSPCON1<5:0> e SSPSTAT<7:6>)
    SSPCON1 = 0x00;
    SSPSTAT &= 0x3F;
    SSPCON1 |= modo;      //configura o modo de opera��o do MSSP
    SSPSTAT |= f_amostra; //configura a amostragem do dado de entrada     
    switch(modo_clock)
    {
        case 1:
            SSPSTATbits.CKE = 1; //transmiss�o ocorre na borda de descida
            break;
        case 2:
            SSPCON1bits.CKP = 1; //transmiss�o ocorre na borda de descida
            SSPSTATbits.CKE = 1; 
            break;
        case 3:
            SSPCON1bits.CKP = 1; //transmiss�o ocorre na borda de subida
            break;
        default:                 //transmiss�o ocorre na borda de subida 
            break;
    }    
    //configurando a dire��o dos pinos do m�dulo MSSP modo SPI
    switch(modo)
    {
        case 4:
            DIR_SCK = 1; //no modo escravo, configura clock serial como entrada
            DIR_SS  = 1; //habilita seletor
            SSPSTATbits.SMP = 0;
            break;
        case 5:
            DIR_SCK = 1; //no modo escravo, configura clock serial como entrada            
            SSPSTATbits.SMP = 0;
            break; 
        default:   
            DIR_SCK = 0; //no modo mestre, configura clock serial como sa�da
            break;
    }    
    DIR_SDI = 1;        //configura entrada de dados serial como entrada digital
    DIR_SDO = 0;        //configura sa�da de dados serial como sa�da digital    
    ADCON1 = 0x0F;      //configura pinos do canal anal�gico como I/O's digitais 
    Habilita_SPI();     //habilita o m�dulo MSSP no modo SPI
}

/* Esta fun��o retorna um byte de dado durante o ciclo de leitura             */
unsigned char Leitura_SPI(void)
{
    unsigned char descarte;
    descarte = SSPBUF;      //leitura antes da transmiss�o
    PIR1bits.SSPIF = 0;     //limpa o flag da interrup��o
    SSPBUF = (0x00);
    //while(!SSPSTATbits.BF); //aguarda o buffer estar cheio 
    while(!PIR1bits.SSPIF); //aguarda completar a recep��o
    return SSPBUF;          //retorna byte
}

/* Esta fun��o l� uma string de dados de tamanho prefixado                    */
void Leitura_S_SPI(unsigned char *buffer, unsigned char tamanho)
{
    while(tamanho)                 //enquanto tamanho > 0, l� recebe dados
    {
        *buffer++ = Leitura_SPI(); //l� um byte e armazena um byte no endere�o apontado e incrementa o endere�o
        tamanho--;                 //decrementa tamanho
    }
}

/* 
 * Esta fun��o envia um �nico byte para o barrramento SPI, retornando '0' para
 * indicar sucesso na transmiss�o ou '-1' para indicar que houve colis�o de escrita 
 */
signed char Escrita_SPI(unsigned char dado)
{
    unsigned char descarte;
    PIR1bits.SSPIF = 0;
    descarte = SSPBUF;
    SSPBUF = dado;                         //transmite um byte
    //while(Status_buffer_SPI());
    while(!PIR1bits.SSPIF);
    if(SSPCON1bits.WCOL == 1) return (-1); //se ocorreu colis�o, retorna -1
    else return 0;                         //se n�o ocorreu colis�o, retorna 0
}

/* Envia uma string de dados para o barramento SPI at� que seja encontrado um caractere nulo */
void Escrita_S_SPI(unsigned char *string)
{
    while(*string)              //enquanto *string != '\0', envia dado
    {
        SSPBUF = *string++;     //envia byte do endere�o apontado e incrementa o endere�o
        while(!SSPSTATbits.BF); //aguarda o buffer estar cheio
    }
}
