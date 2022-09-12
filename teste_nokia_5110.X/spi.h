/* 
 * Nome do arquivo:    spi.h
 * Data:               24/08/2022
 * Vers�o:             1.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de O. Ribeiro 
 */

  
#ifndef __SPI_H
#define	__SPI_H

#include <xc.h>  


//******************************************************************************
//defini��es dos pinos do m�dulo MSSP modo SPI
//******************************************************************************

#define _SDI    PORTBbits.RB0    //define pino SDI
#define DIR_SDI TRISBbits.TRISB0 //define dire��o do pino SDI
#define _SDO    PORTCbits.RC7    //define pino SDO
#define DIR_SDO TRISCbits.TRISC7 //define dire��o do pino SDO
#define _SCK    PORTBbits.RB1    //define pino SCK
#define DIR_SCK TRISBbits.TRISB1 //define dire��o do pino SCK
#define _SS     PORTAbits.RA5    //define pino SS
#define DIR_SS  TRISAbits.TRISA5 //define dire��o do pino SS

//******************************************************************************
//defini��es de macros para configurar os registradores SSPCON1 e SSPSTAT
//******************************************************************************

//********************** macros de configura��o do SSPCON1 *********************

#define SPI_MM_FOSC_4  0b00000000 //modo mestre, clock = FOSC/4
#define SPI_MM_FOSC_16 0b00000001 //modo mestre, clock = FOSC/16
#define SPI_MM_FOSC_64 0b00000010 //modo mestre, clock = FOSC/64
#define SPI_MM_TMR2_2  0b00000011 //modo mestre, clock = TMR2/2
#define SPI_MS_SS_ON   0b00000100 //modo escravo, clock = pino SCK e pino SS habilitado
#define SPI_MS_SS_OFF  0b00000101 //modo escravo, clock = pino SCK e pino SS desabilitado

//******************* macros de configura��o de forma de onda ******************

#define MODE_00 0x00 //estado ocioso do clock � o n�vel baixo e transmiss�o ocorre na transi��o de ocioso para ativo
//CKP = 0 e CKE = 0

#define MODE_01 0x01 //estado ocioso do clock � o n�vel baixo e transmiss�o ocorre na transi��o de ativo para ocioso
//CKP = 0 e CKE = 1

#define MODE_10 0x02 //estado ocioso do clock � o n�vel alto e transmiss�o ocorre na transi��o de ocioso para ativo
//CKP = 1 e CKE = 0

#define MODE_11 0x03 //estado ocioso do clock � o n�vel alto e transmiss�o ocorre na transi��o de ativo para ocioso
//CKP = 1 e CKE = 1

//********************** macros de configura��o do SSPSTAT *********************

#define SMP_MIDDLE 0b00000000 //dado de entrada � amostrado no meio do tempo do dado de sa�da
#define SMP_END    0b10000000 //dado de entrada � amostrado no final do tempo do dado de sa�da

//******************************************************************************
//defini��o de macros para leitura e escrita de bits do m�dulo MSSP
//******************************************************************************

/* Esta macro habilita o m�duo MSSP para comunica��o SPI                      */
#define Habilita_SPI() (SSPCON1 |= 0x20)

/* Esta macro desabilita o m�dulo MSSP para comunica��o SPI                   */
#define Desabilita_SPI() (SSPCON1 &= 0xDF)

/* Esta macro retorna 1 se h� um dado no buffer de recep��o, ou 0 se n�o h� um dado */
#define Status_buffer_SPI() (SSPSTATbits.BF)

//******************************************************************************
//prot�tipos de fun��es
//******************************************************************************

void Inicializa_SPI(unsigned char modo, unsigned char modo_clock, unsigned char f_amostra);
unsigned char Leitura_SPI(void);
void Leiturs_S_SPI(unsigned char *buffer, unsigned char tamanho);
signed char Escrita_SPI(unsigned char dado);
void Escrita_S_SPI(unsigned char *string);

#endif	/* __SPI_H */

