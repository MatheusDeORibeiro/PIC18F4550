/*********************************************************************************************************
******************************************BIBLIOTECA DISPLAY LCD******************************************
**                                                                                                       *
**                    Esta biblioteca cont�m as fun��es de controle do display LCD.                      *
**                                                                                                       *    
**  Livro: Microcontroladores PIC18 - Aprenda e Programe em Linguagem C.                                 *           
**  Autor: Alberto Noboru Miyadaira                                                                      *
**  Vers�o: v0.1											 *
**  Data: 12/03/2011                                                                                     *
**  Modifica��o: 02/07/2021 - Ajuste na biblioteca para ela se adequar ao compilador xc8                 *
*********************************************************************************************************/

//#include<delays.h> //Adiciona a biblioteca de delay.; Biblioteca n�o mais necess�ria para o compilador xc8
#include <xc.h> //Adiciona a biblioteda de fun��es espec�ficas do dispositivo
/*
#ifndef Fosc
  #define Fosc 20 //Define a frequ�ncia do oscilador. Este valor deve corresponder a frequ�ncia do oscilador utilizado pelo PIC18.
#endif*/
// Os nome definidos s�o os pr�prios nomes dos pinos do display LCD.
#define B7 PORTDbits.RD2 //Define o nome B7 para a estrutra.
#define E_B7 TRISDbits.TRISD2=1;
#define S_B7 TRISDbits.TRISD2=0;
#define B6 PORTDbits.RD4 //Define o nome B6 para a estrutra.
#define E_B6 TRISDbits.TRISD4=1;
#define S_B6 TRISDbits.TRISD4=0;
#define B5 PORTDbits.RD5 //Define o nome B5 para a estrutra.
#define E_B5 TRISDbits.TRISD5=1;
#define S_B5 TRISDbits.TRISD5=0;
#define B4 PORTDbits.RD6 //Define o nome B4 para a estrutra.
#define E_B4 TRISDbits.TRISD6=1;
#define S_B4 TRISDbits.TRISD6=0;
#define E  PORTDbits.RD7  //Define o nome E para a estrutra.
#define E_E TRISDbits.TRISD7=1;
#define S_E TRISDbits.TRISD7=0;
#define RW PORTDbits.RD1//Define o nome RW para a estrutra.
#define E_RW TRISDbits.TRISD1=1;
#define S_RW TRISDbits.TRISD1=0;
#define RS PORTDbits.RD0 //Define o nome RS para a estrutra.
#define E_RS TRISDbits.TRISD0=1;
#define S_RS TRISDbits.TRISD0=0;

void gera_atraso_us(unsigned int atraso)//adaptado para Fosc de 20MHz
{
  do 
  {
    _delay(1); //Gera um delay de 1 ciclo de m�quina; Delay1TCY (); //Gera um delay de 1 ciclo de m�quina.
    _delay(1); //Gera um delay de 1 ciclo de m�quina; Delay1TCY (); //Gera um delay de 1 ciclo de m�quina.
    _delay(1); //Gera um delay de 1 ciclo de m�quina; Delay1TCY (); //Gera um delay de 1 ciclo de m�quina.
    _delay(1); //Gera um delay de 1 ciclo de m�quina; Delay1TCY (); //Gera um delay de 1 ciclo de m�quina.
    _delay(1); //Gera um delay de 1 ciclo de m�quina; Delay1TCY (); //Gera um delay de 1 ciclo de m�quina.

    atraso--;
  }while (atraso>0);
}

unsigned char lcd_envia_controle (unsigned char instrucao_dado, unsigned int escrita_leitura, unsigned char dado, unsigned int atraso_us)
{
/*
instrucao_dado = 0 //Instru��o.
instrucao_dado = 1 //Dado.
escrita_leitura = 1 //Leitura.
escrita_leitura = 0 //Escrita.
*/
unsigned char dado_entrada=0;

//Configura os pinos de dados/controle, como sa�da.
S_B7;
S_B6;
S_B5;
S_B4;
S_E;
S_RW;
S_RS;

RS = instrucao_dado; //Informa se � um comando ou dado.
RW = (unsigned char)escrita_leitura; //Informa se � escrita ou leitura.

        if(escrita_leitura == 0)
        {
                B7 = dado>>7;//B7 recebe o bit 7 da vari�vel dado.
                B6 = dado>>6;//B6 recebe o bit 6 da vari�vel dado.
                B5 = dado>>5;//B5 recebe o bit 5 da vari�vel dado.
                B4 = dado>>4;//B4 recebe o bit 4 da vari�vel dado.
                
                E = 1;//Habilita o Display LCD.
                gera_atraso_us(2); //Gera um delay de 2us.
                E = 0; //Desabilita o Display LCD.
                
                B7 = dado>>3;//B7 recebe o bit 3 da vari�vel dado.
                B6 = dado>>2;//B6 recebe o bit 2 da vari�vel dado.
                B5 = dado>>1;//B5 recebe o bit 1 da vari�vel dado.
                B4 = dado;//B4 recebe o bit 0 da vari�vel dado.
                        
                E = 1;//Habilita o Display LCD.
                gera_atraso_us(2); //Gera um delay de 2us.
                E = 0; //Desabilita o Display LCD.
                
                gera_atraso_us(atraso_us); //Gera um delay de xus. MAX 255 ciclos de m�quina
                
                return 0;
        }
        else
        {
                //Configura os pinos de dados, como entrada.
                E_B7;
                E_B6;
                E_B5;
                E_B4;
                
                E = 1;//Habilita o Display LCD.
          gera_atraso_us(2); //Gera um delay de 2us.
        
                dado_entrada = B7;
                dado_entrada = (unsigned char)(dado_entrada<<1 | B6);
                dado_entrada = (unsigned char)(dado_entrada<<1 | B5);
                dado_entrada = (unsigned char)(dado_entrada<<1 | B4);    
                
                E = 0; //Desabilita o Display LCD.
                E = 1;//Habilita o Display LCD.
                gera_atraso_us(2); //Gera um delay de 2us.
                
                dado_entrada = (unsigned char)(dado_entrada<<1 | B7);
                dado_entrada = (unsigned char)(dado_entrada<<1 | B6);
                dado_entrada = (unsigned char)(dado_entrada<<1 | B5);
                dado_entrada = (unsigned char)(dado_entrada<<1 | B4);
                        
                E = 0; //Desabilita o Display LCD.
                
                gera_atraso_us(atraso_us); //Gera um delay de xus. MAX 255 ciclos de m�quina
                
                return dado_entrada;
        }
}

//Limpa a tela e coloca o cursor na linha um e coluna um do display.
void lcd_limpa_tela ( )
{
        lcd_envia_controle (0,0,0x01,2000);
}

//Coloca o cursor na linha um e coluna um do display.
void lcd_cursor_home ( )
{
        lcd_envia_controle (0,0,0x02,2000);
}

//Desloca o cursor para a direita ou esquerda.
void lcd_desloca_cursor(unsigned char direita_esquerda)
{
/*
0 - Desloca o cursor para a direita.
1 - Desloca o cursor para a esquerda.
*/
unsigned char cursor[2] = {0x14, 0x10}; 
        lcd_envia_controle (0,0,cursor[direita_esquerda],40);
}

//Desloca a mensagem para a direita ou esquerda.
void lcd_desloca_mensagem(unsigned char direita_esquerda)
{
/*
0 - Desloca a mensagem para a direita.
1 - Desloca a mensagem para a esquerda.
*/
unsigned char cursor[2] = {0x1c, 0x18};
        lcd_envia_controle (0,0,cursor[direita_esquerda],40);
}

//Liga/Desliga o cursor/display.
void lcd_LD_cursor (unsigned char config)
{
/*
0 - Desliga o cursor.
1 - Desliga o display.
2 - Liga o cursor com altern�ncia.
3 - Liga o display e o cursor.
4 - Liga o display e o cursor piscante.
*/
unsigned char cursor [5] = {0x0c, 0x08, 0x0f, 0x0e, 0x0d}; 
        lcd_envia_controle (0,0,cursor[config],40);
}

//Coloca o cursor em uma determinada posi��o do LCD.
void lcd_posicao(unsigned char linha, unsigned char coluna)
{
        switch (linha)
        {
                case 1:
                        lcd_envia_controle (0,0,0x80+coluna-1,40);
                        break;
                case 2:
                        lcd_envia_controle (0,0,0xc0+coluna-1,40);
                        break;
                case 3:
                        lcd_envia_controle (0,0,0x94+coluna-1,40);
                        break;
                case 4:
                        lcd_envia_controle (0,0,0xd4+coluna-1,40);
                        break;
        }       
}

//Escreve um caractere ou s�mbolo no display.
void lcd_escreve_dado(unsigned char dado)
{
        lcd_envia_controle (1,0,dado,45);
}

//Retorna o caractere presente na posi��o do cursor.
unsigned char lcd_le_dado( )
{
        return lcd_envia_controle (1,1,0,45);
}

//Retorna o valor do status + contador de endere�o.
unsigned char lcd_status ( )
{
        return lcd_envia_controle (0,1,0,40);
}

//Envia String para o Display LCD.
void imprime_string_lcd(const char *s_caracteres) //remove-se rom de const rom char *s_caracteres
{
        while (*s_caracteres!=0)
        {
                lcd_escreve_dado(*s_caracteres);
                s_caracteres++;
        }
}

//Envia uma matriz de dados para o Display LCD.
void imprime_buffer_lcd( char *s_caracteres, unsigned char tamanho_buffer)
{
        while (tamanho_buffer--)
        {
                lcd_escreve_dado(*s_caracteres);
                s_caracteres++;
        }
}

//Inicializa o display LCD alfanum�rico.
void lcd_inicia( unsigned char conf1, unsigned char conf2, unsigned char conf3)
{
/*
Configura��o do display LCD:

(0x28)
- Comunica��o 4 vias
- Display com 2 linhas
- Matriz 8x5

(0x0f)
- Liga display
- Cursor piscante

(0x06)
- Desloca o cursor para a direita quando um caractere for inserido.
*/
unsigned char config_LCD[6] = {0x03, 0x02, 0x00, 0x00, 0x00};
unsigned char repeticao;

config_LCD[2] = conf1;
config_LCD[3] = conf2;
config_LCD[4] = conf3;

//Configura os pinos de dados/controle, como sa�da.
S_B7;
S_B6;
S_B5;
S_B4;
S_E;
S_RW;
S_RS;
        
RS = 0; //Instru��o.
RW = 0; //Escrita.
E = 0; //Desabilita LCD.

        gera_atraso_us(20000); //Gera um atraso de 20ms. 

        for( repeticao = 0 ; repeticao < 3 ; repeticao++ )
        {
                B7 = config_LCD[0]>>3; //B7 recebe o bit 3 do elemento presente na posi��o 0 da matriz config_LCD.
                B6 = config_LCD[0]>>2; //B6 recebe o bit 2 do elemento presente na posi��o 0 da matriz config_LCD.
                B5 = config_LCD[0]>>1; //B5 recebe o bit 1 do elemento presente na posi��o 0 da matriz config_LCD.
                B4 = config_LCD[0];    //B4 recebe o bit 0 do elemento presente na posi��o 0 da matriz config_LCD.
                
                E = 1;//Habilita o Display LCD.
                gera_atraso_us(2); //Gera um delay de 2us.
                E = 0; //Desabilita o Display LCD.
                
                gera_atraso_us(5000); //Gera um delay de 5ms.
        }

B7 = config_LCD[1]>>3; //B7 recebe o bit 3 do elemento presente na posi��o 1 da matriz config_LCD.
B6 = config_LCD[1]>>2; //B6 recebe o bit 2 do elemento presente na posi��o 1 da matriz config_LCD.
B5 = config_LCD[1]>>1; //B5 recebe o bit 1 do elemento presente na posi��o 1 da matriz config_LCD.
B4 = config_LCD[1];    //B4 recebe o bit 0 do elemento presente na posi��o 1 da matriz config_LCD.
        
E = 1;//Habilita o Display LCD.
gera_atraso_us(2); //Gera um delay de 2us.
E = 0; //Desabilita o Display LCD.

gera_atraso_us(40); //Gera um delay de 40us.

lcd_envia_controle (0,0,config_LCD[2],40);
lcd_envia_controle (0,0,config_LCD[3],40);
lcd_envia_controle (0,0,config_LCD[4],40);

lcd_limpa_tela ( );

}

