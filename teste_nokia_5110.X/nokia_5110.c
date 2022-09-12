/*
 * Nome do arquivo:    nokia_5110.c
 * Data:               31/08/2022
 * Versão:             1.0
 * MPLAB X IDE:        v5.45
 * Autor:              Matheus de Oliveira Ribeiro
 */

/*
 * Esta biblioteca contém funções para utilização do display Nokia 5110. 
 */

#include <xc.h>
#include "nokia_5110.h"
#include "spi.h"

/* Esta função envia uma instrução para o display */
void Envia_Instrucao(unsigned char comando)
{
    _CE = 0;
    _DC = 0;              //escreve instrução
    Escrita_SPI(comando); //envia instrução
    _CE = 1;
}

/* Esta função envia um byte para o display */
void Envia_Dado(unsigned char byte)
{
    _CE = 0;
    _DC = 1;           //escreve dado
    Escrita_SPI(byte); //envia dado
    _CE = 1;
}

/* Esta função inicializa o lcd controller PCD8544U do display Nokia 5110 */
void Inicializa_5110(void)
{
    //define direção dos pinos do mC ligados ao display
    DIR_RST = 0; //define pino de reset como saída
    DIR_CE = 0;  //define pino CE como saída
    DIR_DC = 0;  //define pino DC como saída
    DIR_BL = 0;  //define o pino BL como saída
    _BL = 0;     //desliga o led
    //pulso de reset
    _RST = 0;
    _delay(500000); //um atraso de 500.000 gera um delay de 100ms
    _RST = 1;
    //inicializa display
    Envia_Instrucao(0x21); //conjunto de instruções extendidas - chip ativo e endereçamento horizontal
    Envia_Instrucao(0x07); //controle de temperatura - coeficiente 3
    Envia_Instrucao(0x13); //sistema de bias - 1:48
    Envia_Instrucao(0xC0); //configuração Vop - Vlcd = 3,06 + 16 * 0,06 = 4,02V
    Envia_Instrucao(0x20); //conjunto de instruções básicas - chip ativo e endereçamento horizontal
    Envia_Instrucao(0x0C); //controle do display - modo normal
}

/* Esta função desloca o cursor em X */
void coordenada_x(unsigned char x)
{
    if(x < 84) Envia_Instrucao(0x80 | x);
}

/* Esta função desloca o cursor em Y */
void coordenada_y(unsigned char y)
{
    if(y < 6) Envia_Instrucao(0x40 | y);
}

/* Esta função liga todos os segmentos do display */
void testa_display(void)
{
    coordenada_xy(0x00, 0x00);
    for(unsigned char y = 0; y < 6; y++)
    {
        for(unsigned char x = 0; x < 84; x++)
        {
            Envia_Dado(0xFF);
        }
    } 
}

/* Esta função imprime alguns dos caracteres do vetor tabela_ascii no display */
void testa_caracteres(void)
{
    coordenada_xy(0x00, 0x00);
    for(unsigned char c = 0x30; c <= 'z'; c++) 
    {
        if(c == 0x3A) c = 0x41;
        if(c == 0x5B) c = 0x61;
        escreve_caractere(c);
    }
}

/* Esta função escreve um caractere */
void escreve_caractere(unsigned char caractere)
{    
    for(unsigned char i = 0; i < 5; i++)
    {
        Envia_Dado(tabela_ascii[caractere - 0x20][i]); //imprime um  caractere do vetor "tabela_ascii"
    }
    Envia_Dado(0x00);    
}

/* Esta função escreve uma string */
void escreve_string(char *string)
{
    while(*string)                    //enquanto *string != '\0', envia caractere
    {
        escreve_caractere(*string++); //escreve caractere da string
    }
}

/* Esta função escreve uma string na cor selecionada pelo usuário */
void escreve_string_cor(char *string, unsigned char cor)
{
    char caractere;                                      //declaração de variável
    while(*string)                                       //enquanto *string != '\0', envia caractere
    {
        for(unsigned int i = 0; i < 5; i++)
        {
            caractere = tabela_ascii[*string - 0x20][i]; //armazena o segmento do caractere
            if(!cor) caractere = ~(caractere & 0xFF);    //inverte pixels se desejado
            Envia_Dado(caractere);                       //escreve o trecho de caracere
        }
        string++;                                        //incrementa o endereço do caractere
        if(!cor) Envia_Dado(0xFF);
        else Envia_Dado(0x00);
    }
}

/* Esta função imprime uma imagem */
void imprime_imagem(const unsigned char *imagem)
{
    coordenada_xy(0x00, 0x00);
    _CE = 0;
    _DC = 1;
    for(unsigned int x = 0; x < 504; x++)
    {
        Escrita_SPI(imagem[x]);    
    }
    _CE = 1;
}

/* Esta função limpa a tela do display */
void limpa_display(void)
{
    for(unsigned char y = 0; y < 6; y++)
    {
        for(unsigned char x = 0; x < 84; x++)
        {
            Envia_Dado(0x00);
        }
    } 
}

void desenha_linha_horizontal(unsigned char posicao_x, unsigned char posicao_y)
{
    unsigned char linha = 84;
    coordenada_xy(posicao_x, posicao_y);
    while(linha > 0)
    {
        Envia_Dado(0x10);
        linha--;
    }
}

void desenha_linha_vertical(unsigned char posicao_x, unsigned char posicao_y)
{
    unsigned char linha = 6;
    coordenada_xy(posicao_x, posicao_y);
    Envia_Instrucao(0x22);
    while(linha > 0)
    {
        Envia_Dado(0xFF);        
        linha--;
    }
    Envia_Instrucao(0x20);
}
