/* 
 * Nome do arquivo:    spi.h
 * Data:               24/08/2022
 * Versão:             1.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de O. Ribeiro 
 */
  
/*
 * Esta biblioteca contém um conjunto de funções que permitem configurar e utilizar
 * o módulo MSSP no modo SPI. 
 */

#include <xc.h>  
#include "spi.h"


/*
 * A função OpenSPI configura e habililta o módulo MSSP modo SPI
 * - modo:       define o modo de operação do modo SP
 * - modo_clock: define o modo de operação do sinal de cloc
 * - f_amostra:  define a fase de leitura do dado
 */
void Inicializa_SPI(unsigned char modo, unsigned char modo_clock, unsigned char f_amostra)
{    
    //programando os bits de controle SSPCON1<5:0> e SSPSTAT<7:6>)
    SSPCON1 = 0x00;
    SSPSTAT &= 0x3F;
    SSPCON1 |= modo;      //configura o modo de operação do MSSP
    SSPSTAT |= f_amostra; //configura a amostragem do dado de entrada     
    switch(modo_clock)
    {
        case 1:
            SSPSTATbits.CKE = 1; //transmissão ocorre na borda de descida
            break;
        case 2:
            SSPCON1bits.CKP = 1; //transmissão ocorre na borda de descida
            SSPSTATbits.CKE = 1; 
            break;
        case 3:
            SSPCON1bits.CKP = 1; //transmissão ocorre na borda de subida
            break;
        default:                 //transmissão ocorre na borda de subida 
            break;
    }    
    //configurando a direção dos pinos do módulo MSSP modo SPI
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
            DIR_SCK = 0; //no modo mestre, configura clock serial como saída
            break;
    }    
    DIR_SDI = 1;        //configura entrada de dados serial como entrada digital
    DIR_SDO = 0;        //configura saída de dados serial como saída digital    
    ADCON1 = 0x0F;      //configura pinos do canal analógico como I/O's digitais 
    Habilita_SPI();     //habilita o módulo MSSP no modo SPI
}

/* Esta função retorna um byte de dado durante o ciclo de leitura             */
unsigned char Leitura_SPI(void)
{
    unsigned char descarte;
    descarte = SSPBUF;      //leitura antes da transmissão
    PIR1bits.SSPIF = 0;     //limpa o flag da interrupção
    SSPBUF = (0x00);
    //while(!SSPSTATbits.BF); //aguarda o buffer estar cheio 
    while(!PIR1bits.SSPIF); //aguarda completar a recepção
    return SSPBUF;          //retorna byte
}

/* Esta função lê uma string de dados de tamanho prefixado                    */
void Leitura_S_SPI(unsigned char *buffer, unsigned char tamanho)
{
    while(tamanho)                 //enquanto tamanho > 0, lê recebe dados
    {
        *buffer++ = Leitura_SPI(); //lê um byte e armazena um byte no endereço apontado e incrementa o endereço
        tamanho--;                 //decrementa tamanho
    }
}

/* 
 * Esta função envia um único byte para o barrramento SPI, retornando '0' para
 * indicar sucesso na transmissão ou '-1' para indicar que houve colisão de escrita 
 */
signed char Escrita_SPI(unsigned char dado)
{
    unsigned char descarte;
    PIR1bits.SSPIF = 0;
    descarte = SSPBUF;
    SSPBUF = dado;                         //transmite um byte
    //while(Status_buffer_SPI());
    while(!PIR1bits.SSPIF);
    if(SSPCON1bits.WCOL == 1) return (-1); //se ocorreu colisão, retorna -1
    else return 0;                         //se não ocorreu colisão, retorna 0
}

/* Envia uma string de dados para o barramento SPI até que seja encontrado um caractere nulo */
void Escrita_S_SPI(unsigned char *string)
{
    while(*string)              //enquanto *string != '\0', envia dado
    {
        SSPBUF = *string++;     //envia byte do endereço apontado e incrementa o endereço
        while(!SSPSTATbits.BF); //aguarda o buffer estar cheio
    }
}
