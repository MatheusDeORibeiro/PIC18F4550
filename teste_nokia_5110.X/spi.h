/* 
 * Nome do arquivo:    spi.h
 * Data:               24/08/2022
 * Versão:             1.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de O. Ribeiro 
 */

  
#ifndef __SPI_H
#define	__SPI_H

#include <xc.h>  


//******************************************************************************
//definições dos pinos do módulo MSSP modo SPI
//******************************************************************************

#define _SDI    PORTBbits.RB0    //define pino SDI
#define DIR_SDI TRISBbits.TRISB0 //define direção do pino SDI
#define _SDO    PORTCbits.RC7    //define pino SDO
#define DIR_SDO TRISCbits.TRISC7 //define direção do pino SDO
#define _SCK    PORTBbits.RB1    //define pino SCK
#define DIR_SCK TRISBbits.TRISB1 //define direção do pino SCK
#define _SS     PORTAbits.RA5    //define pino SS
#define DIR_SS  TRISAbits.TRISA5 //define direção do pino SS

//******************************************************************************
//definições de macros para configurar os registradores SSPCON1 e SSPSTAT
//******************************************************************************

//********************** macros de configuração do SSPCON1 *********************

#define SPI_MM_FOSC_4  0b00000000 //modo mestre, clock = FOSC/4
#define SPI_MM_FOSC_16 0b00000001 //modo mestre, clock = FOSC/16
#define SPI_MM_FOSC_64 0b00000010 //modo mestre, clock = FOSC/64
#define SPI_MM_TMR2_2  0b00000011 //modo mestre, clock = TMR2/2
#define SPI_MS_SS_ON   0b00000100 //modo escravo, clock = pino SCK e pino SS habilitado
#define SPI_MS_SS_OFF  0b00000101 //modo escravo, clock = pino SCK e pino SS desabilitado

//******************* macros de configuração de forma de onda ******************

#define MODE_00 0x00 //estado ocioso do clock é o nível baixo e transmissão ocorre na transição de ocioso para ativo
//CKP = 0 e CKE = 0

#define MODE_01 0x01 //estado ocioso do clock é o nível baixo e transmissão ocorre na transição de ativo para ocioso
//CKP = 0 e CKE = 1

#define MODE_10 0x02 //estado ocioso do clock é o nível alto e transmissão ocorre na transição de ocioso para ativo
//CKP = 1 e CKE = 0

#define MODE_11 0x03 //estado ocioso do clock é o nível alto e transmissão ocorre na transição de ativo para ocioso
//CKP = 1 e CKE = 1

//********************** macros de configuração do SSPSTAT *********************

#define SMP_MIDDLE 0b00000000 //dado de entrada é amostrado no meio do tempo do dado de saída
#define SMP_END    0b10000000 //dado de entrada é amostrado no final do tempo do dado de saída

//******************************************************************************
//definição de macros para leitura e escrita de bits do módulo MSSP
//******************************************************************************

/* Esta macro habilita o móduo MSSP para comunicação SPI                      */
#define Habilita_SPI() (SSPCON1 |= 0x20)

/* Esta macro desabilita o módulo MSSP para comunicação SPI                   */
#define Desabilita_SPI() (SSPCON1 &= 0xDF)

/* Esta macro retorna 1 se há um dado no buffer de recepção, ou 0 se não há um dado */
#define Status_buffer_SPI() (SSPSTATbits.BF)

//******************************************************************************
//protótipos de funções
//******************************************************************************

void Inicializa_SPI(unsigned char modo, unsigned char modo_clock, unsigned char f_amostra);
unsigned char Leitura_SPI(void);
void Leiturs_S_SPI(unsigned char *buffer, unsigned char tamanho);
signed char Escrita_SPI(unsigned char dado);
void Escrita_S_SPI(unsigned char *string);

#endif	/* __SPI_H */

