/*colocar um help
   PROGRAMA........: JOGO DE PACIENCIA VERSAO XPTO
   CRIADO EM.......: 1/1/2009
   ATUALIZADO EM...: 17/1/2009
   AUTORES...........: Andr� Marcelo e Luis Barbosa
   E-MAIL..........: ....... / ....
   DESCRI��O.......: 
 * Changes:
 *   constru��o (8/01/2009): Primeira release.
     BREVEMENTE
 */
//***************PRELIMINARES***************************************************
/* inclusao das livrarias, constantes necessarias, estruturas , e vectore e resgistos de estruturas tambem com
matrizes de estruturas e tambem variaveis globais que nao deixam de ser arrays globais de registos etc*/


//#####################################Inclusao de Livrarias####################

#include <stdio.h>// standard input/output
#include <stdlib.h>// standard lib
#include <time.h>// biblioteca time :>
#include<conio.h>// console input/output
#include<conio.c>// console input/output
#include <windows.h>

//#####################################Defini��o de Variaveis###################

#define MAXCARTA 52// as minhas 52 cartas
#define PRETO 0// constante 0 para a cor preta;
#define VERMELHO  1//constante 1 para a cor vermelha;
#define BRANCO 2//constante 2 para a cor branca;
#define COPAS 3//o meu simbolo de copas
#define OUROS 4// o meu simbolo de ouros
#define PAUS 5//o meu simbolo de paus
#define ESPADAS 6 // o meu simbolo de espadas
#define MAXCOLUNAS  7//colunas do tabuleiro do jogo
#define MAXLINHAS  19//linhas do tabuleiro do jogo
#define ESCONDIDA  0//Para as cartas ocultas, para a minha fun��o oculta
#define VISIVEL  1//Para as cartas VISIVEIS
#define NAIPE 13//Maximo de cartas por naipe
#define ENTRA 1
#define SAI 0
#define MAXRECORDES 5//5 jogadores no top five
#define CAMINHO "C:\Documents and Settings\Web Design AM.ACER-CBB9A4757D\My Documents\test.txt"
#define Clear system("CLS")


//variaveis globais

int nvirada;//n� de cartas viradas
int pos;//n� posi��o que nos diz onde est� oi zero
int nab;//numero actual de cartas no baralho
int nrecordes;
int pont;

//int nab;//numero actual de cartas no baralho

//n�o foi feita uma fun��o virar carta a media que o jogo corre a carta vira se nao tem nenhuma por baixo automaticamente
//atribui o valor na pontua��o por ter virado e o valor do respectivo movimento


//gerar cartas de 0 a 51 e barralhar as cartas de seguida
/*Bem criou-se um estrutura em que definimos as caracteristicas que cada carta 
iria ter , criamos uma variavel carta do tipo "cartas" pelo o qual � um vector com 52 posi��es;*/


//###############DECLARA��O DE ESTRUTURAS#######################################
// UM NOVO TIPO DE DADOS COM AS AS CARACTERISTICAS DE CADA CARTA

struct cartas
{
   int valor;//valor de cada carta
   char naipe;//o naipe de cada carta
   int cor;// a cor de cada carta
   int ocultas;//se a carta est� oculta/escondida ou se est� visivel.
   int pode_entrar;   /* diz se existe algum monte na pilha de jogo pode ou nao entrar nessa pilha */
   int pode_sair;
}carta[MAXCARTA];//vector do tipo cartas(estrutura cartas) que nos vai armazenar as 52cartas com os seus atributos
//MAXCARTA � uma constante de valor 52; MAXCARTA=52; PODERIAMOS TER DECLARADO EM BAIXO NAS AQUI TAMBEM D�


//##############################Estrutura dos recordes##########################

struct recordes
{
    char nome[50];//NOME DO VENCEDOR
    int pontuacao;//TEM DE A RECEBER DE ALGUM LADO
}top[MAXRECORDES];

//#########################ARRAYS E MATRIZES DE ESTRUTURAS######################

struct cartas novacarta[MAXCARTA];//novo vector do tipo cartas com 52 posi��es que vai receber as cartas baralhadas.
struct cartas tabuleiro[MAXLINHAS][MAXCOLUNAS];//definir a matriz para o tabuleiro do jogo;
struct cartas naipe1[NAIPE];//array de estruturas com 13 posi��es para que vai armazenar as cartas de um naipe nao sabemos qual isso depende do naipe da primeira carta de A a entrar
struct cartas naipe2[NAIPE];//array de estruturas com 13 posi��es """""""""""""""""""""""""""""""""
struct cartas naipe3[NAIPE];//array de estruturas com 13 posi��es """""""""""""""""""""""""""""""""
struct cartas naipe4[NAIPE];//array de estruturas com 13 posi��es """""""""""""""""""""""""""""""""


/*a nossa ideia foi pegar no vector das cartas ordenadas e coloca-las num novo vector de forma desordenada*/ 

//###############APRESENTA��O DAS FUN��ES/PROCEDIMENTOS#########################
//###############[FUN��ES/PROCEDIMENTOS AO LONGO DO PROGRAMA####################

/*NOTA-->A EXPLICA��O DE CADA FUN��O/PROCEDIMENTO SER� EXPLICADA ANTES DA SUA 
CONSTRU��O TAL COM AS SUAS VARIAVEIS E O QUE ELAS ARMAZENAM OU FAZEM AO LONGO DA FUN��O<-----*/
/*AO LONGO DO PROGRAMA PODER� TAMBEM ENCONTRAR CODIGO COMENTADO OU ATE FUN��ES DE 
TESTE VISTO, AOS TESTES QUE FOMOS FAZENDO NO FINAL DA CRIA��O DE CADA FUN��O*/
void cria_cartas();
void remover(int tmp,int ncartas);
void baralhar();
void teste();
void limpar_matriz();
void limpar_naipe();
void ocultar(int j, int i);
void descodifica_carta(int i,int j);
void imprime_carta(int i,int j);
void descodifica_carta_baralho();
void clear();
void imprime_baralho();
//void descodifica_carta_baralho(nvirada);
void imprime_naipes();
void impressao_texto();
void imprime_tabuleiro();
void dispor_montes();
void tabuleiros();
void sub_menu();
void move_monte_monte();
void move_naipe_monte();
void mover_baralho_monte();
void mover_baralho_naipe();
void move_monte_naipe();
void descrisao_jogo();
void descrisao_jogo();
void creditos();
void menuprincipal();
void sub_menu();
//void gravar_recorde();
//void top_five();
//void pontua��o();



//******************************1�PASSO*****************************************

//*********************procedimento cria_cartas()*******************************
/*est� fun��o cria as cartas percorremos o vector de estrturas carta de 52 posi��es,
interessa-nos colocar l� dentro as informa��es referentes a 13 cartas de cada naipe 
ou seja de desde o A at� ao R isto 4 vezes , dividindo em 4 passos e 4 ciclos for, 
em que o  primerio ciclo vai de 0 ate 12 e o segundo de 13 a 25 o terceiro de 26 a 38 e quarto de 39 a 51
de modo a que as 4 divis�es tenham 13 cartas cada, mas para que em cada ciclo fique as cartas de 1 ate 13
e a posi��o 0 entra tambem e tem de ter o valor 1, colocamos uma variavel j e esse j atribui
o valor aos varios naipes, isto � a medida que o i do ciclo for � incrementado ele coloca 1 na posi��o 0, 2 na posi��o zero
e assim sucessivamente,a  medida que o i � incrementado o j tambem � coloca l� esse valor de incremento dentro do array carta
atraves da estrutura como � uma estrutura cada posi��o tem varios atributos e caracteristo como o valor � uma deles, colocamos
dentro do valor o incremento do j isto nos 4 ciclos, aproveitando injectamos la tambem o valor do naipe directmante visto 4 ciclos
4 naipes 1 naipe em cada ciclo, declaramos as constantes acima COPAS, OUROS , PAUS, ESPADAS, como sabemos que 
o codigo do caracter de de copas � 3 bastou fazer carta[i].naipe=COPAS pois est� l� 3 e o 3 corresponde ao caracter copas, tal como 
nos restantes simbolos ou naipes, j� a cor � de um modo diferente temos 2 constanste PRETO=0 E VERMELHO=1 e colocamos esse valor l�
e mais a frente quando estivermos a imprimir o jogo decidir a cor e cada naipe atraves de uma fun��o que toma a decis�o
como sabemos que ouros e copas e vermelho atribuimos-lhe j� o valor de vermelhor e como o paus e o espadas e preto atribuimos e 
valor de preto, as linahs comentadas foram estes de imprimir directamente so mesmo teste aqui temos o nosso vector cartas ordenado
do seguinte modo de 0 a 12 com as cartas de copas, de 13 a 25 com as de ouros de 26 a 38 com as paus de 39 a 51 com as de espadas */
//FICAM AS CARTAS ORDENADAS

void cria_cartas()
{
   int i;//variavel de itera��o de 0 a 12, depois no 2ciclo de 13 a 25, no 3 de 26 a 38 e o quarto de 39 a 52
   int j;//variavel de itera��o
   j=1;
   for(i=0;i<=12;i++)
   {
       carta[i].valor=j;
       carta[i].naipe=COPAS;
       carta[i].cor=VERMELHO;
       j++;
       //printf("%d%c\n\n",carta[i].valor,carta[i].naipe);--->teste
   }
   j=1;
   for(i=13;i<=25;i++)
   {
       carta[i].valor=j;
       carta[i].naipe=OUROS;
       carta[i].cor=VERMELHO;
       j++;
        //printf("%d%c\n\n",carta[i].valor,carta[i].naipe);--->teste
   }
   j=1;
   for(i=26;i<=38;i++)
   {
       carta[i].valor=j;
       carta[i].naipe=PAUS;
       carta[i].cor=PRETO;
       j++;
        //printf("%d%c\n\n",carta[i].valor,carta[i].naipe);--->teste na cria��o
   }
   j=1;
   for(i=39;i<=51;i++)
   {
       carta[i].valor=j;
       carta[i].naipe=ESPADAS;
       carta[i].cor=PRETO;
       j++;
        //printf("%d%c\n\n",carta[i].valor,carta[i].naipe);--->teste na cria��o
   }
}

//********************* 2�passo*************************************************

/*Nesta fase o que nos queremos fazer e pegar no nosso vector carta que est� ordenado com as cartas por naipe
e queremos desordena-lo basicamente para o fazer criamos um novo vector pelo o qual demos o nome novacarta e utilizando a fun��o
remover, e as fun��es do C fornecida pela biblioteca time srandon e randon geramos cartas aleatorias de 1 a 52 atraves do novo
vector carta que esta ordenado com as cartas todas l� dentro geramos cartas e a medida que elas eram geradas eram colocadas
no vector novacarta de forma desordenada a medida que v�o saindo, mas como a fun��o srandon depende do tempo 
ou seja vai buscar informa��es a hora do computador estarmos a gerar 52 cartas seguidas no mesmo instante certamente
elas serias sempre a mesma carta dai ter a necessidade de a media que o randon era feito por exemplo
era feito o primeiro randon diminuimos a posi��o em que a carta que foi gerada se encontra no vector cartas e descrementamos 
ao proximo random rand()%(MAXCARTA - i), pois a media que iteravamos o randon vai diminuindo e a posi��o da carta gerada � eliminada
do vector cartas ai chegarmos ao final de gerar as cartas e termos a certeza que elas nao sai repetidas 
pois estamos a diminuir ao tamanho do i que � a posi��o que ele pode gerar.
*/

// A fun��o remover com como fun��o remover a posi��o da carta que � gerada e diminuir ao array carta do tipo estrutura.


//fun��o nos nos gera as cartas para serem colocadas no nosso novo vector

/*int aleatorio(int ncartas) // Gera um n�mero aleat�rio entre 0 e 51 � utilizada em conjunto com a baralhar;
{
    srand( (unsigned int) time(NULL) );
    return 0 + rand() % ncartas;
}*/


/*gera uma carta e coloca-a num novo vector, est� fun��o remove o indice do vector[rdenado], remove a posi��o
da carta gerada*/

//remove a carta do vector ordenado a carta gerada numa certa certa posi��o visto que nos na segunda passagem queremos que sejam
//menos cartas, como falamos da segunda falamos nas outras visto que nos interessa gerar as cartas sem estarem repetidas.

//procedimento remover a sua fun��o e remover cartas do vector ordenado de forma a que elas nao voltem a ser gerdas novamente.
//***************************Procedimento Remover*******************************   
void remover(int tmp,int ncartas)/*ncartas criadas � o numero actual de cartas criadas ate ao momento dai recebe como parametro
tmp que � a carta que � gerada, e o n� de cartas geradas ate ao momento*/
{
    int i;//variavel que nos ajuda a percorrer o vector e uma variavel de itera��o
    if (tmp==ncartas)//tmp � a carta gerada
    {
        ncartas--;// se a nossa carta gerada for igual a carta que est� no limite entao decrementa isto para nao haver problemas com o limite.
    }
    else
    {//if(indice<ncartas);
        for(i=tmp;i<ncartas;i++)//se o nossa carta gerada � menor ao nactualdecartas entao ele elemina a posi��o intermedia
        {
            carta[i]=carta[i+1];//isto se forem cartas intermedias para o caso de remover posi��es intermedias
        }
        ncartas--;//decremento ao ncartas
    }
}


/*entao vamos gerar as nossas 52 cartas apartir do nosso vector ordenado e colocalas no nosso novo vector de forma,desorganizada.
Atraves de uma fun��o baralhar que tem o randon que � a carta gerada e tem a uma chamada ao procedimento remover 
por nos final de gerar a carta aleatoriamente a a novacarta tomar o seu valor ir e remover ao vector carta ao antigo de forma a que 
remove  a posi��o da carta gerada para que no proximo o randon seja mais curto e nunca gera a mesma carta pois ela ja l� nao esta
foi copiada para outro vector para o novo assim nunca se corre o risco de sairam cartas repetidas*/

//***************************Procedimento Baralhar*******************************
//baralha as cartas como o referido acima....
void baralhar()
{
   int ncartas=51;
   int i;//variavel de incremento para percorrer o vector,
   int tmp;//armazena do valor da carta gerada.

  //como criamos as constantes, estamos a usa-las sempre que  necess�rio
   for(i=0;i<MAXCARTA;i++)
   {
      /* para gerar n�meros aleat�rios de 0 a 50 */
        //Para que a seed do seu random seja sempre aleat�ria tamb�m
        srand( (unsigned int) time(NULL) );
        tmp= rand()%(MAXCARTA - i);//outra ideia;
        novacarta[i]=carta[tmp];//TMP guarda temporariamente o numero gerado aleatoriamente pela fun��o srand();      
        //novo valor enviado por argumento
        remover(tmp,ncartas);//chamada e do procedimento remover
  }
}

/*Ao longo da constru��o do codigo fomos fazendo testes para ter a certeza que 
estavamos a apresentar estava correcto e este � um deles imprime o vector nova carta desordenado*/

/************************************teste*************************************/

void teste()
{
     int i;
     for(i=0;i<=51;i++)
     {
         printf("%d%c\n",novacarta[i].valor,novacarta[i].naipe);//teste
         //printf("%d%c\n\n",carta[i].valor,carta[i].naipe);---->TESTE VECTOR ANTIGO
         
     }
} //neste teste nota-se que ele coloca todas as cartas geradas noutro vector e que o vector carta antigo e destruido ou seja imprime apenas a unica posi��o com que fica;

/*******************************************************************************/
/*********************************3�PASSO***************************************/
/*Necessidade de colcar as cartas baralhadas numa matriz, 20 por 7 ou seja 20 linhas porque � o maximo que cada coluna ou seja monte
pode levar por exemplo uma carta com 7 naipes + 13 d� 20 visto que isto pode acontecer.

come�amos entao por criar um tabuleiro com uma fun��o tabuleiros para expor a nossa mesa de jogo,e come�ando por definir a sua cor,
de seguida fizemos uma chamada a fun��o cria_carta acima referida no primeiro passo
seguida do procedimento baralhar(de notar que o procedimento baralhar tem dentro de si o remover e o randon das cartas) 
que depois dentro do tabuleiro vamos chamar os procedimentos ocultar as cartas dos montes e depois o procedimento para imprimir 
o tabuleiro isto sao tudo procedimentos que sao criados e que sao chamados ai dentro

BREVE EXPLICA��O
---> criar o tabuleiro do jogo definindo a cor de fundo com o system("color 20"), chamando o cria_cartas(), o baralhar(), antes disto no inicio definir uma matriz 
tabuleiro[MAXLINHAS---> constante igual a 20][MAXCOLUNAS---> 7 colunas inicialmente pois elas durante  o jgo sao alteradas]
percorremos entao a matriz com o ciclo for atraves de duas variaveis de itera��o i e j como so queremos percorrer as 7 primeiras linhas
inicialmente e as 7 clonuas por o jogo come�a com a diagonal principal principal com as cartas visiveis
e acima da diagonal as cartas est�o ocultas ou seja com XXX posto isto, e como abaixo da diagonal o C diz-nos autom�ticamente 
que abaixo da diagonal principal que nao tem nada la e nao vamos para ja colocar nada queremos e imprimir, est�o l� zeros, percorremos 
entao a matriz dentro da principam 7X7 e dissemos que a nossa matriz do tipo carta  tabuleiro[j][i]=novacarta[a], toma o valor e nova carta,
antes disso definimos uma variavel que nos ajuda a percorrer o vector novacarta que esta desordenado com as cartas todas  la,
do inicio para o fim eu seja colomos a variavel percorre_novacarta=51 e no numero de itera��o para preencher as posi��es da matriz,depois chamamos
a fun��o ocultas(j,i) para nos dizer que as cartas est�o ocultas excpeto as da diagonal principal o que esta acima esta oculto,
abaixo est� a zero por defeito, e fomos decrementando ao nosso percorre_novacarta ate que este tive-se percorrido as posi��es que necessita
que neste caso sao as tais 28 cartas para colocar nos monte apartir e depois apartir do imprimir e que vai imprimir a casa onde se
encontra o resto do nossa carta que sao as posi��es de 0 a 23 pois como percorremos do incio para o fim, vai imprir 4 arrays de estrutura
um para cada naipe pois mais abaixo nas valida��es cada um deles � validado, imprime umas linha engra�adas, e o monte tem um nome
para que o jogador compreenda melhor nos para simplicificar no movimento de cartas vamos colocar os naipe com se fosse um monte mas 
so que com as restri��es diferentes de monte ou seja num monte as cartas tem de estar da maior para a mais pequena e as cores alternadas
ja no naipe tem de ser na mais pequena para a maior e entram la as cartas da mesma cor em cada um e s� mais para que o jogador defina
logo para onde quer jogar, --->ver<----,como ja temos a cartas na matriz resta-nos apenar que se o tabuleiro[i][j].valor==0 da uma
tabla��o e passa para o seguinte monte e continua a preencher ou seja a imprimir atraves da fun��o imprime_carta(j,i); que se �
tabuleiro[i][j].valor!=0 entao imprime a carta que se entra naquela posi��o ou seja mas estamos a jogar com a fun��o ocultar ja no
procedimento tabuleiros() inicialmente, entao para imprimir definimos uma fun��o imprime_carta que nos diz que se o valor tabuleiro[j][i].ocultas==ESCONDIDA
pois sao constantes definidas inicalmente pelo o qual na nova estrutura inicial injectamos valores l� dentro, for igual a ESCONDIDA imprime XXX a cor branca
se a carta tabuleiro[j][i].cor==VERMELHO se a cor � igual a vermelho dependende do valor da variavel na estrutura imprime a carta a vermelho
tal como para o preto, no final desta valida��o tivemos a necessidade de criar um procedimento  para descodificar as cartas especiais como
o A=1, o V=11,a D=12,e o R=13, para que eles assomisem o valor do respectivo caracter o descodifica_carta(int j,int i) recebe 2 paramentros
para percorrer a matriz e avaliar se a cartas para tomar esse valor e depois com um case vimos os casos e imprimimos de seguida imprimos
o respectivo caracter

*/

//coloca as cartas na matriz
//cria o tabuleiro do jogo inicial, mais nada pois as cartas sao movidas



//procedimento ocultar

//*****************************+LIMPARMATRIZ************************************
/*Coloca a matriz inicial a zeros a matriz total toda preenchida a zeros*/
void limpar_matriz()
{
    int i,j;
    for(i=0;i<MAXCOLUNAS;i++)
    {
        for(j=0;j<MAXLINHAS;j++)
        {
            tabuleiro[i][j].valor=0;
        }
    }
}

void limpar_naipe()
{
    int j;
    for(j=0;j<NAIPE;j++)
    {
       naipe1[j].valor=0;
       naipe2[j].valor=0;
       naipe3[j].valor=0;
       naipe4[j].valor=0;
    }
}



/*******************************Prodecimento ocultar************************************/
/*procedimento ocultar ->responsavel por ocultar as cartas da matriz que nao tem valor zero execto as da diagonal principal,
� so utilizada no incio depois vamos ter uma que nos vai virar as cartas mas isso e uma op��o e isso de virar as cartas vai ser definido
durante o jogo
*/
void ocultar(int i, int j)//recebe 2 paramentros para percorrer a matriz tabuleiro
{
  if(i!=j)//diagonal ou seja verifica os dois triandulos ou seja acima da diagonal e abixo da diagonal apenas
  {
      tabuleiro[i][j].ocultas=ESCONDIDA;//ver se a cata esta escondida ja tinha l� zero mas colocamo-lo novamente
  }
  else
  {
     tabuleiro[i][j].ocultas=VISIVEL;//ver se a cata esta escondida
  }
}

/*******************************descodifica_carta*********************************/
/*DEFINI��O DE CARTA NAIPES DESCODIFICA CARTAS ESPECIAIS.....FUN��O QUE NOS DIZ QUE O ,
--------
|A----1|
|J---11|
|Q---12|
|R---13|
--------2.....10 ---> os numeros normais de 2 ate 10*/

//unica fun��o que imprime que descodifica a carta  e imprime o valor o naipe e a cor na matriz

void descodifica_carta(int i,int j)//recebe 2 paramentros para percorrer a matriz
{
     
     if(tabuleiro[i][j].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(tabuleiro[i][j].valor)//faz as verifica��es percorrendo a matriz
     {
          case 1:
               printf("A");
               break;
          case 11:
               printf("V");
               break;
          case 12:
               printf("D");
               break;
          case 13:
               printf("R");
               break;
          default:
                  printf("%d",tabuleiro[i][j].valor);//imprime o numero de 2 ate 10
     }
    printf("%c\t",tabuleiro[i][j].naipe);//imprimir o naipe de cada carta
}


/*************************imprime_carta****************************************/
/*cores e ocultas -- decis�o--> decide as cores e ve as cartas ocultas e o que esta fun��o faz imprimir a cor das cartas e as cartas
ocultas*/
void imprime_carta(int i,int j)//2 paramentros para percorrer a matriz
{
     if(tabuleiro[i][j].ocultas==ESCONDIDA)//ver se vai ser uma carta oculta ou nao tem haver com o que esta acima
     {
         textcolor(WHITE);
         printf("XXX\t");//se esta oculta imprime XXX  a cor branca
     }
     else
     {
             descodifica_carta(i,j);
     }
} 
//*************************percorre o baralho************************************
//TEMOS DE JOGAR COM AS OCULTAS
/*void decide_cor_baralho(int i)//decidir qual a cor das cartas do baralho
{
     if(novacarta[i].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
}*///optimiza��o de codigo no descodifica carta

//unica fun��o que imprime que descodifica a carta  e imprime o valor o naipe e a cor no baralho
void descodifica_carta_baralho()//tivemos a necessidade pois estamos a proveitar as 24 posi��es iniciais do baralho
{
    if(nvirada==-1)
    {
            
            printf("B");//n�o existe cartas no baralho   
    }
    else
    {
    
    if(novacarta[nvirada].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(novacarta[nvirada].valor)
     {
        case 1:
             printf("A");
             printf("%c",novacarta[nvirada].naipe);
             break;
        case 11:
              printf("V");
              printf("%c",novacarta[nvirada].naipe);
              break;
        case 12:
             printf("D");
             printf("%c",novacarta[nvirada].naipe);
             break;
        case 13:
             printf("R");
             printf("%c",novacarta[nvirada].naipe);
             break;
        default:
             printf("%d",novacarta[nvirada].valor);
             printf("%c",novacarta[nvirada].naipe);
     }
     //
    }
     
}

//********************************Clear****************************************

void clear()
{
    system("cls");
}


//*************************Imprime Baralho*************************************
// e percorre o baralho  do inicio para o fim etc;     
void imprime_baralho()
{
     int nab,i;
    //numero actual de cartas no baralho
     //nvirada=0;//numero de actual de cartas viradas no baralho
     //printf("%d",novacarta[nvirada].valor);
     
     //printf("\n*** %d ***\n",nvirada);
     //system("pause");
     
    descodifica_carta_baralho(nvirada);
}

//sei que vamos ter de jogar com o nvirada o numero de cartas viradas ate ao momento

void imprime_naipes()
{
    int i;
    i=0;
    
    if(naipe1[i].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(naipe1[i].valor)
     {
        case 1:
             printf("A");
             break;
        case 11:
              printf("V");
              break;
        case 12:
             printf("D");
             break;
        case 13:
             printf("R");
             break;
        default:
             printf("%d",naipe1[i].valor);
     } printf("%c\t",naipe1[i].naipe);
     if(naipe2[i].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(naipe2[i].valor)
     {
        case 1:
             printf("A");
             break;
        case 11:
              printf("V");
              break;
        case 12:
             printf("D");
             break;
        case 13:
             printf("R");
             break;
        default:
             printf("%d",naipe2[i].valor);
     }printf("%c\t",naipe2[i].naipe);
     if(naipe3[i].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(naipe3[i].valor)
     {
        case 1:
             printf("A");
             break;
        case 11:
              printf("V");
              break;
        case 12:
             printf("D");
             break;
        case 13:
             printf("R");
             break;
        default:
             printf("%d",naipe3[i].valor);
     }
     printf("%c\t",naipe3[i].naipe);
     if(naipe4[i].cor==VERMELHO)
     {
           textcolor(LIGHTRED);
     }
     else
     {
          textcolor(BLACK);
     }
     switch(naipe4[i].valor)
     {
        case 1:
             printf("A");
             break;
        case 11:
              printf("V");
              break;
        case 12:
             printf("D");
             break;
        case 13:
             printf("R");
             break;
        default:
             printf("%d",naipe4[i].valor);
     }
     printf("%c",naipe4[i].naipe);
    printf("\n");
}


//contador de segundos

//nao sabemos implementar isso e onde o colocar com como � interativo e dificil aplicar
int contador(void)
{  
  int hora,min,seg; 
  int i;
  int u = 0;
  hora = 0, min = 0, seg = 0; 
  Sleep(2000);
  Clear;     

  while (hora < 24)
  { 
    while (min < 60)
    {           
      while (seg < 60)
      {       
        printf("\n%38.2d:%.2d:%.2d",hora,min,seg);             	
        Sleep(1000);
        seg = seg + 1;           
        system("CLS");
      }
      seg = 0; /* tirar 1 segundo*/
      min = min + 1; /* Incrementando minuto */
    }
    min = 0; 
    hora = hora + 1; /* Incrementando  hora */
    
    /* tirar a hora para o lopp ser continuo */
    if (hora > 23)
    {
      hora = 0; 
    }         
  } 
  return(0);
}

void imprime_pontuacao()
{
    printf("Pontuacao = ");
    if(top[pont].pontuacao<0)
    {
        printf("0");
    }
    else
    {
       printf("%d",top[pont].pontuacao);
    }
}



void impressao_texto()
{
    printf("--------------------------------------------------------------------\n");
    printf("\n\n");
    textcolor(WHITE);
    printf("\t\t\tNAIPES, 1-COPAS 2-OUROS 3-PAUS 4-ESPADAS\n ");
    textcolor(LIGHTGRAY);
    printf("Baralho\t\t\t");//texto barralho
    printf("1-C\t2-O\t3-P\t4-E\n");//imprir os 4 naipes.. 4 arrays
    textcolor(YELLOW);
    printf("--------------------------------------------------------------------\n");
    textcolor(BLACK);
    imprime_baralho();//imprimir o baralho;
    printf("\t\t\t\t");
    //primeira posi��o do vector --->temos de o percorrer modificar
    imprime_naipes();
    textcolor(YELLOW);
    printf("--------------------------------------------------------------------\n");//linha inicial
    textcolor(LIGHTGRAY);
    printf("Monte1\tMonte2\t");
    printf("Monte3\tMonte4\t");
    printf("Monte5\tMonte6\tMonte7\n");//n� de cada monte para as valida��es e menus
    textcolor(YELLOW);
    printf("--------------------------------------------------------------------\n");//linha final
    //contador();
}

void imprime_tabuleiro()//imprime inicial a matriz......
{
    int i,j;
    //novacarta[i]
    impressao_texto();
    for(i=0; i<MAXLINHAS; i++)//linhas de 0 ate 6 para percorre de 0 ate 6
    {
       for(j=0; j<MAXCOLUNAS; j++)//colunas 0-6//o 7 � uma variavel de itera��o pois imprime consoante o numero de cartas que ai est�
       //cartas que estao la as 28 - um incremento qualquer
       {
          if (tabuleiro[i][j].valor==0)
               printf("\t");
          else
               //printf("%d%c\t",tabuleiro[i][j].valor,tabuleiro[i][j].naipe);
               imprime_carta(i,j);
       }
       printf("\n");

    }
    printf("--------------------------------------------------------------------\n");
    imprime_pontuacao();
}

/**********************Prodedimento construir o tabuleiro******************************************/
void dispor_montes()
{
    int i,j;//variaveis de itera��o
     //percorre_novacarta--> variavel a � uma variavel de controlo que serve para percorrer o vector da ultima posi��o,penultima etc.
     int percorre_novacarta=51;//come�a na posi��o 51 de tras para  a frente tira as cartas
     //coloca��o de dados       
     for(j=0; j<MAXCOLUNAS; j++)
     /*provisorio pois tem de ter um decremento qualquer monte todo a zeros, 
     pode entar um R e ficar a ja com 1 posi��o preenchida, ou seja e incremento, tambem para aumentar o tamanho do monte
     e das linas*/
     //linhas de 0 ate 6 para percorre de 0 ate 6//variavel de controlo falta
     {
          for(i=0; i<=j; i++)//colunas 0-6
          {
                tabuleiro[i][j]=novacarta[percorre_novacarta];
                ocultar(i,j);
                percorre_novacarta--;//decrementa ao nova carta ao array pois estamos do inicio para o fim
                //printf("%d%c\t",tabuleiro[i][j].valor,tabuleiro[i][j].naipe);
          }
          //printf("\n");
     }
}


//tabuleiro[0][1]=novacarta[0];
//depois de ter as cartas dipostas e de ter feito um teste ir testar as cores para depois por final imprimir todo direito


//uma variavel que controle as cartas do novacarta[i]

//**************4PASSO************************************************************

/*

void percorrer_baralho();----> percorrelo e tirar a carta que queremos e se ela entar em naipe ao montes removela;
void vira_carta_monte()--->se uma carta � movida e entra num dos montes ou naipe o XXX e virado e mostra a carta que l� est�
ter um menu principal---->seleciona jogar----->abre outro menu
este sub menu tem

INICIAR JOGO INFORME O SEU NOME � LOGO NO INICIO
SE FOR DEPOIS DE IR PARA O JOGO COLOCAR printf("PRESSIONE \"ENTER\" PARA CONTINUAR..."); getchar();
NO FINAL DESEJA JOGAR NOVAMENTE E APRESENTA  printf("DESEJA JOGAR NOVAMENTE (S/N): ");

--->mover cartas ---->mover monte para monte ou mover monte naipe ou naipe monte ou baralho monte ou baralho naipe;
--->mover cartas ---->mover monte para monte ou mover monte naipe ou naipe monte
--->Ir ao baralho ----> mover baralho monte ou baralho naipe;

cada vez que um carta e retirada do baralho e adiciona num monte e elemina-a do baralho....

cada vez que uma carta e colocada na casa do respectivo naipe ele retira-a na matriz e essa posi��o fica a zero e vai para o naipe

Implementar uma fun��o com as regras de movimento monte a monte
implementar uma fun��o com as regras de movimento monte naipe
implementar uma fun��o com as regras de movimento naipe Monte
implementar uma fun��o com as regras de movimento baralho  naipe
implementar uma fun��o com as regras de movimento baralho monte
fun�ao imprime naipes
fun�ao percorre baralho
mover

A pensar em movimentos
----->
----->

/* assinaturas de algumas funcoes uteis */


/* responde se a carta pode ser colocada no naipe ou n�o */
//int pode_ir_naipe(int valor);

/*MOVIMENTOS DOS NAIPES*/
//void naipe_monte();

/*MOVIMENTOS MONTES - MONTES*/
//void monte_monte();
//void monte_naipe();


/* Movimentos Baralho- NAIPES*/

//void move_baralho_naipe();
//void move_baralho_montes();

//MOVIMENTOS N�O PREMITIDOS ATEN��O
//MOVIMENTOS J� ASSOCIADOS A PONTUA��O
//IMPRIMIR A PONTUA��O QUE DEPENDE DOS MOVIMENTOS
// COLOCAR O TOPO FIVE DE ELE TERMINAR O JOGO OS NAIPE ESTIVER TODOS PREENCHIDOS E A MATRIZ A ZEROS E APARECE GANHA
//E DIZ PARA O JOGADOR COLOCAR O NOME
//GUARDA A PONTUA��O E NOME NO FICHEIRO
//TEMOS DE AVALIAR TAMBEM DENTRO DO FICHEIRO AS PONTUA��ES QUE JA L� ESTAO
//NO FINAL PERGUNTA SE QUER JOGAR NOVAMENTE
//SENAO VOLTA AO MENU PRINCIPAL

/* imprime o jogo */
//void imprimeJogo();--->j� temos

/* inicializa o jogo */
//void inicializajogo();//uma ideia
//void movimentos()//movimentos totais
//void submenu_baralho();
//void submenu_naipe();
//void submenu_montes();


//*********************************+FUN��O HELP*********************************
//depois dos naipes estar completos ous seja um deles aparecer naipe completo


//************************************MOVIMENTOS********************************
//fun��o que determina o numero de cartas que estao no monte de destino


            
            
            
     





//"""""""""""""""""""""""""""""""""""""MONTE---->MONTE""""""""""""""""""""""""""

//fun��o pode entar no monte
   
void move_monte_monte()
{//falta a valida��o rei para o vazio e a valida��o para irem as outras juntas
     int linha,coluna,i,pos,colunadestino;
     printf("MONTE ORIGEM\n");
     printf("Introduza a coluna de Origem:");
     scanf("%d",&coluna);
     printf("\n");
     coluna--;
     printf("Introduza a Linha de Origem:");
     scanf("%d",&linha);
     printf("\n");
     linha--;
     if(coluna>7)
     {
                textcolor(LIGHTRED);
                printf("Movimento Impossivel");
     }
        else
        {
            if((linha >19) || (tabuleiro[linha][coluna].valor==0))
            {
                textcolor(LIGHTRED);
                printf("Movimento Impossivel");
            }
            else
            {
                printf("Introduza a coluna de destino:");
                scanf("%d",&colunadestino);
                printf("\n");
                colunadestino--;
                
                pos=0;
                while(tabuleiro[pos][colunadestino].valor!=0)//pesquisa a posi��o vazia na posi��o do monte de destino
                {
                   pos++;
                   //ultima posi��o no monte de destino
                }
                if ((tabuleiro[linha][coluna].cor)!=(tabuleiro[pos-1][colunadestino].cor)&&(tabuleiro[linha][coluna].valor)==(tabuleiro[pos-1][colunadestino].valor-1)||(tabuleiro[linha][coluna].valor==13)&&(tabuleiro[0][colunadestino].valor==0))
                {
                    
                    i=0;
                    while(tabuleiro[linha+i][coluna].valor!=0)
                    {                                                                                                                                                                                                                                   
                         tabuleiro[pos+i][colunadestino]=tabuleiro[linha+i][coluna];
                         tabuleiro[pos+i][colunadestino].ocultas=VISIVEL;
                         tabuleiro[linha+i][coluna].valor=0;
                         
                         if (linha!=0)
                         {
                             tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                             //da carta ter virado;
                             top[pont].pontuacao= top[pont].pontuacao+5;
                             //ainda bem que nao fala no rei e no move monte monte nao e atribuida pontua��o so mesmo quando a carta vira mas isso � geral
                         }
                         i++;
                    }
                        
                        printf("\n");
                }
                else
                {
                       textcolor(LIGHTRED);
                       printf("Movimento Impossivel");
                }   
            }
        }
}
                 
     /*printf("Pretende mover monte a monte novamente");
     printf("Prima->[S]or [s]\n");
     printf("Prima->[N]or [n]\n");
     fflush(stdin);
     scanf("%c",&caracter);
     switch(caracter)
     {
                case 'S':
                case's':
                    move_monte_monte();
                    break;
                case 'N':
                case 'n':
                   //volta atras autom�ticamente ao menu onde ficou suspenso com a chamada da fun��o alterar;
                    break;
     }*/

//descodifica carta naipe


//fun��o pode entar no monte


//zera a posi��o do monte ou seja vira a carta do naipe se a carta e movida para um dos naipes


//limpa os naipes todos coloca os valores todos as 0
//teoricamente ta basta so com que a carta que esta apontar para a zero passe para a um e assim sucessivamente
   
void move_monte_naipe()
{
     int linha,coluna,i,naipe;
     printf("MONTE ORIGEM\n");
     printf("Introduza a Coluna de Origem:");
     scanf("%d",&coluna);
     printf("\n");
     coluna--;
     printf("Introduza a Linha de origem:");
     scanf("%d",&linha);
     printf("\n");
     linha--;
     if(tabuleiro[linha+1][coluna].valor!=0)
     {
            textcolor(LIGHTRED);
            printf("Movimento Impossivel");
     }
     else
     {
        if(coluna>7)
        {
                textcolor(LIGHTRED);
                printf("Movimento Impossivel");
        }
        else
        {  
            if((linha >19) || (tabuleiro[linha][coluna].valor==0))
            {
                textcolor(LIGHTRED);
                printf("Movimento Impossivel");
            }
            else
            {
                textcolor(YELLOW);
                printf("Introduza o Naipe para o qual quer mover\n");
                printf("Naipe 1-Copas, Naipe 2-Ouros, Naipe 3-Espadas, Naipe 4-Paus\n");
                do
                {
                    printf("Introduza o Naipe para o qual quer mover:");
                    scanf("%d",&naipe);
                    printf("\n");
                }while((naipe<0)||(naipe>4));
                switch(naipe)
                {
                    case 1:
                        if((tabuleiro[linha][coluna].naipe==COPAS)&&(tabuleiro[linha][coluna].valor-1)==(naipe1[0].valor))
                        {
                            naipe1[0]=tabuleiro[linha][coluna];
                            tabuleiro[linha][coluna].valor=0;
                            //top[nrecordes].pontuacao=+10;//empilhada correctamente na casa do naipe;
                            //tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                            if (linha!=0)
                            {
                                tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                                top[pont].pontuacao= top[pont].pontuacao+15;//por virar
                            }
                        } 
                        break;//identar codigo
                    case 2:
                        if((tabuleiro[linha][coluna].naipe==OUROS)&&(tabuleiro[linha][coluna].valor-1)==(naipe2[0].valor))
                        {
                            naipe2[0]=tabuleiro[linha][coluna];
                            tabuleiro[linha][coluna].valor=0;
                            //top[nrecordes].pontuacao=+10;//empilhada correctamente na casa do naipe;
                            //tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                            if (linha!=0)
                            {
                                tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                                top[pont].pontuacao= top[pont].pontuacao+15;//por virar e por ir para o local correcto;
                            }
                        } 
                        break;
                    case 3:
                        if((tabuleiro[linha][coluna].naipe==PAUS)&&(tabuleiro[linha][coluna].valor-1)==(naipe3[0].valor))
                        {
                            naipe3[0]=tabuleiro[linha][coluna];
                            tabuleiro[linha][coluna].valor=0;
                            //top[nrecordes].pontuacao=+10;//empilhada correctamente na casa do naipe;
                            //tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                            if (linha!=0)
                            {
                                tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                                top[pont].pontuacao= top[pont].pontuacao+15;
                            }
                        } 
                        break;
                    case 4:
                        if((tabuleiro[linha][coluna].naipe==ESPADAS)&&(tabuleiro[linha][coluna].valor-1)==(naipe4[0].valor))
                        {
                            naipe4[0]=tabuleiro[linha][coluna];//empilhada correctamente na casa do naipe;
                            tabuleiro[linha][coluna].valor=0;
                            
                            //tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                            if (linha!=0)
                            {
                                tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                                //top[nrecordes].pontuacao=+10;
                                top[pont].pontuacao= top[pont].pontuacao+15;//por virar//5 por virar e 10 por ficar correcatamnete
                            }
                        } 
                        break;
             }     
         }
     }
  }
}


/////V� este que nao ta completo e necessario remover do naipe quando ele sai para um monte e ver se fica algum por baixo
//quando se move e preciso remver do naipe nao ta a funcionar
void move_naipe_monte()
{
     int linha,colunadestino,i,naipe;
     textcolor(YELLOW);
     printf("Introduza o Naipe para o qual quer mover\n");
     printf("Naipe 1-Copas, Naipe 2-Ouros, Naipe 3-Espadas, Naipe 4-Paus\n");
     do
     {
        printf("Introduza o Naipe de origem:");
        scanf("%d",&naipe);
        printf("\n");
    }while((naipe<0)||(naipe>4));
    printf("Introduza a coluna de destino:");
    scanf("%d",&colunadestino);
    printf("\n");
    colunadestino--;
    pos=0;
    i=0;//variavel que controla as cartas que cada naipe tem
    //move na boa so que o valor continua l� a ideia � colocar ou implementar o algoritmo trocas directas e apontar sempre para o zero
    // a media que vao entrando cartas ele baixa aumenta a posi��o so que a carta que entrou esta no zero, a media que vao saindo � tirar de um e colocar noutro
    
    while(tabuleiro[pos][colunadestino].valor!=0)//pesquisa a posi��o vazia na posi��o do monte de destino
    {
        pos++;
                   //ultima posi��o no monte de destino
    }

    switch(naipe)
    {
                   case 1:
                        if((tabuleiro[pos-1][colunadestino].cor!=naipe1[i].cor)&&(tabuleiro[pos-1][colunadestino].valor)==(naipe1[i].valor+1))
                        {
                            tabuleiro[pos][colunadestino]=naipe1[i];
                            top[pont].pontuacao=top[pont].pontuacao-15;
                            tabuleiro[pos][colunadestino].ocultas=VISIVEL;
                            //i--;//nao e bem esse i
                        } 
                        break;//identar codigo, e tem os outros 3 casos nao sei e como tira-lo do naipe � necessario uma variavel de controlo
                    case 2:
                        if((tabuleiro[pos-1][colunadestino].cor!=naipe2[i].cor)&&(tabuleiro[pos-1][colunadestino].valor)==(naipe2[i].valor+1))
                        {
                            tabuleiro[pos][colunadestino]=naipe2[i];
                            //i--;
                            top[pont].pontuacao=top[pont].pontuacao-15;//empilhada correctamente na casa do naipe;
                            tabuleiro[pos][colunadestino].ocultas=VISIVEL;
                            
                        } 
                        break;
                    case 3:
                        if((tabuleiro[pos-1][colunadestino].cor!=naipe3[i].cor)&&(tabuleiro[pos-1][colunadestino].valor)==(naipe3[i].valor+1))
                        {
                            tabuleiro[pos][colunadestino]=naipe3[i];
                            //i--;
                            top[pont].pontuacao=top[pont].pontuacao-15;
                            tabuleiro[pos][colunadestino].ocultas=VISIVEL;
                            
                        } 
                        break;
                    case 4://trabalhei com a cor em vex do naipe
                        if((tabuleiro[pos-1][colunadestino].cor!=naipe4[i].cor)&&(tabuleiro[pos-1][colunadestino].valor)==(naipe4[i].valor+1))
                        {
                            tabuleiro[pos][colunadestino]=naipe4[i];
                            //i--;//nao e bem o I 
                            top[pont].pontuacao=top[pont].pontuacao-15;
                            tabuleiro[pos][colunadestino].ocultas=VISIVEL;
                           
                        } 
                        break;
    }
}




//ta correcto

void mover_baralho_monte()
{
     int monte,i,j;
     printf("Introduza o monte para o qual quer Mover:");
     scanf("%d",&monte);
     printf("\n");
     monte--;
     i=0;
     while(tabuleiro[i][monte].valor!=0)
     {
          i++;   
     }
          if((nvirada==nab)||(novacarta[nvirada].valor)==(tabuleiro[i-1][monte].valor-1)&&(novacarta[nvirada].cor)!=(tabuleiro[i-1][monte].cor))//i-1 tem o valor da carta
          {
                                                                                                                                
             tabuleiro[i][monte]=novacarta[nvirada];
             for(j=nvirada;j<nab;j++)
             {
                 novacarta[j]= novacarta[j+1];
             }
             
             nab--;
             nvirada--;
             top[pont].pontuacao= top[pont].pontuacao+5;//empilhada correctamente na casa do monte;
             }
             
             else
             {
                 //valida��o para o rei poder entrar numa casa vazia
                 if ((novacarta[nvirada].valor==13)&&(i==0))
                 {
                       tabuleiro[i][monte]=novacarta[nvirada];
                       for(j=nvirada;j<nab;j++)
                       {
                             novacarta[j]= novacarta[j+1];
                       }
                       top[pont].pontuacao= top[pont].pontuacao+5;//empilhada correctamente no monte
                       nab--;
                       nvirada--;                                       
                  }
                  else
                  {
                      printf("Impossivel");
                  }
             }
             tabuleiro[i][monte].ocultas=VISIVEL;
             //i--> tem o valor da posi��o vazio ta pronto para receber dados etc....
}
//ta coorrecto
void mover_baralho_naipe()
{
     int naipe,i,j;
     /*while((naipe1[i].valor!=0)||(naipe2[i].valor!=0)||(naipe2[i].valor!=0)||(naipe4[i].valor!=0))
     {
          i++;   
     }*/
     do
     {
        printf("Introduza o Naipe para o qual quer mover:");
        scanf("%d",&naipe);
        printf("\n");
      }while((naipe<0)||(naipe>4));
                switch(naipe)
                {
                    case 1:
                        if(((nvirada==nab)||(novacarta[nvirada].naipe==COPAS)&&(novacarta[nvirada].valor-1)==(naipe1[0].valor)))
                        {
                            naipe1[0]=novacarta[nvirada];
                            for(j=nvirada;j<nab;j++)
                            {
                                novacarta[j]= novacarta[j+1];
                            }
                            top[pont].pontuacao= top[pont].pontuacao+10;
                            nab--;
                            nvirada--;
                         }
                            //tabuleiro[linha-1][coluna].ocultas=VISIVEL;
                        break;//identar codigo
                    case 2:
                        if(((nvirada==nab)||(novacarta[nvirada].naipe==OUROS)&&(novacarta[nvirada].valor-1)==(naipe2[0].valor)))
                        {
                            naipe2[0]=novacarta[nvirada];
                            for(j=nvirada;j<nab;j++)
                            {
                                novacarta[j]= novacarta[j+1];
                            }
                            top[pont].pontuacao= top[pont].pontuacao+10;
                            nab--;
                            nvirada--;
                         }
                        break;
                    case 3:
                        if(((nvirada==nab)||(novacarta[nvirada].naipe==PAUS)&&(novacarta[nvirada].valor-1)==(naipe3[0].valor)))
                        {
                            naipe3[0]=novacarta[nvirada];
                            for(j=nvirada;j<nab;j++)
                            {
                                novacarta[j]= novacarta[j+1];
                            }
                            top[pont].pontuacao= top[pont].pontuacao+10;
                            nab--;
                            nvirada--;
                         }
                        break;
                    case 4:
                       if(((nvirada==nab)||(novacarta[nvirada].naipe==ESPADAS)&&(novacarta[nvirada].valor-1)==(naipe4[0].valor)))
                        {
                            naipe4[0]=novacarta[nvirada];
                            
                            for(j=nvirada;j<nab;j++)
                            {
                                novacarta[j]=novacarta[j+1];
                            }
                            top[pont].pontuacao= top[pont].pontuacao+10;
                            nvirada--;
                            nab--;
                         }
                        else
                        {
                            printf("Impossivel");
                        }
                    }//tabuleiro[i][monte].ocultas=VISIVEL;
             //i--> tem o valor da posi��o vazio ta pronto para receber dados etc....
}



int pesquisar_nome(char strnome[50])
{
    int i,pos;

    
    if(nrecordes==0)
    {
        return -1;
    }
    else
    {
        i=0;
        pos=-1;

        while((pos==-1) && (i<nrecordes))
        {
            if ((stricmp(top[i].nome,strnome)==0))
                pos=i;
            i++;
        }


        printf("\n\n%d  -  %d",pos,MAXRECORDES);

        return pos;
    }

}


//quando os quatro naipes estao preenchidos os 4 a 13 ou a ultima posi��o do naipe � igual todas a 13....
//ele chama esta fun��o adicionar nome;mas e preciso trabalhar com a pontua��o sobre isso tambem


//esta merda tem de receber a pontua��o e depois e que vai gravar isto em algum lado.
void adicionar_nome()
{
    char caracter;
    int i;

    if(nrecordes==MAXRECORDES)
    {
        textcolor(YELLOW);
        printf("Nao � possivel Adicionar");
    }
    else
    {
            do
            {
                textcolor(YELLOW);    
                printf("Nome: ");
                fflush(stdin);
                gets(top[nrecordes].nome);
            }while(pesquisar_nome(top[nrecordes].nome)!=-1);//para nao introduzir nomes iguais
    }
}

void gravar_recorde()
{
    FILE *apontador;
    apontador = fopen(CAMINHO, "w");
    if(apontador == (FILE *) NULL)
    {
        printf("\nImposs�vel abrir ficheiro\n");
    }
    else
    {
     printf("\n%d\n",nrecordes);
     fwrite(top, sizeof(struct recordes), nrecordes, apontador);
     fclose(apontador);
    }
}//colocar isto no final do adicionar tem muitos perigos. autom�tico vai a vida vida;


/////////////////////////////////////////ler_ficheiro()//////////////////////////////////////////

void ler_recorde()
{
    FILE *apontador;
    apontador = fopen(CAMINHO, "r");
    if(apontador == (FILE *) NULL)
    {
        printf("\nImposs�vel abrir ficheiro\n");
    }
    else
    {
        nrecordes=0;
        while(fread(&top[nrecordes], sizeof(struct recordes),1, apontador))
        {
            nrecordes++;
        }
        fclose(apontador);
    }

    fflush(stdin);
    getchar();

}


     

//************************************DESCRISAO DO JOGO*************************
void descrisao_jogo()
{
     textcolor(LIGHTBLUE);
     printf("O objectivo do jogo e empilhar separadamente as cartas dos quatro naipes,\n");
     printf("cada uma na casa do seu naipe. As cartas devem ser empilhadas por ordem\n");
     printf("ascendente, isto e, As, 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete, Dama, Rei.\n");
     textcolor(WHITE);
}


//************************************CREDITOS**********************************
void creditos()
{
     
     textcolor(WHITE);
     printf("    ....::: CREDITOS :::....\n");
     textcolor(YELLOW);
     printf(" Desenvolvido por:\n");
     printf("*8080136 - Andre Marcelo\n");
     printf("*8080150 - Luis Barbosa\n"); 
     printf("ESTGF- LINGUAGENS DE PROGRAMACAO LPI\n");
     printf("� Copyrigh 2009 Todos os direitos Reversados\n");             
     printf("Disponivel para download no site:\n");
     printf("www.andremarcelo.tk\n");
     textcolor(WHITE);
}

//construir tabuleiro
void tabuleiros()
{
     system("color 20");//tem que estar no inicio do main senao sobrpoe-se a color do texto;
     //adicionar_nome();
     limpar_matriz();
     limpar_naipe();
     cria_cartas();
     baralhar();
     //teste();//---->teste para ver se estava a gerar os numeros correctos sem repeti��o
     //definir a nossa matrizes do jogo para depois come�ar a dispor cartas;
     dispor_montes(); 
     sub_menu();
}


//****SUBMENU MOVIMENTOS********************************************************
//***********************************Submenu************************************
void sub_menu()
{
    int num;
    do
    {
        clear();
        imprime_tabuleiro();
        textcolor(WHITE);
        printf("\t\t\tSUBMENU\n\n");
        textcolor(BLUE);
        printf("\t\t\t1. PERCORRER BARALHO\n\n");
        textcolor(YELLOW);
        printf("\t\t\tMOVIMENTOS\n\n");
        textcolor(LIGHTCYAN);
        printf("\t\t\t2. BARALHO --> NAIPE\n\n");
        printf("\t\t\t3. BARALHO --> MONTE\n\n");
        printf("\t\t\t4. NAIPE ----> MONTE\n\n");
        printf("\t\t\t5. MONTE ----> MONTE\n\n");
        printf("\t\t\t6. MONTE ----> NAIPE\n\n");
        printf("\t\t\t7. Inserir Nome\n\n");
        printf("\t\t\t8. GRAVAR RECORDE\n\n");
        printf("\t\t\t0. ABANDONAR / RETORNAR AO MENU PRINCIPAL\n\n");
        do
        {
            textcolor(BLACK);
            textcolor(YELLOW);
            printf("\t\t\tQual a sua opcao: ");
            scanf("%d",&num);
        }
        while(num<0 && num>9);
        switch(num)
        {
            case 0:
                //sei que ele sai sozinho nao preciso de nenhuma chamada ele autom�ticamente volta atras
                break;
            case 1 :
     
                if(nvirada==nab)//trabalhar sobre esta variavel,fun��o mover do baralho decrementar
                {
                       nvirada=-1;
                       //top[pont].pontuacao= top[pont].pontuacao-50;////quando percorre nao ta a dar   
                       
                }
                 else
                 {
                        nvirada++;
                 }               
                 break;
            case 2 :                                 
                 mover_baralho_naipe();
                 break;
            case 3:
                mover_baralho_monte();
                break;
            case 4:
                move_naipe_monte();
                break;
            case 5:
                 move_monte_monte();
                break;
            case 6:
                move_monte_naipe();
                break;
            case 7:
                adicionar_nome();
                break;
            case 8:
                gravar_recorde();
                break;
                
        }
        printf("\n");
    }
    while(num!=0);
}


//************************************************* Menu Principal***************************************************************
// a minha fun��o menu.... � muito melhor ter assim uma fun��o
void menuprincipal()
{
    int num;
    do
    {

//
        textcolor(LIGHTRED);
        printf("\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t......:::: SOLITARIO::::.......\n\n");
        textcolor(WHITE);
        printf("\t\t\t[1]---> INICIAR JOGO \n");
        printf("\t\t\t[2]---> TOP 5\n");
        printf("\t\t\t[3]---> DESCRISAO DO JOGO\n");
        printf("\t\t\t[4]---> CREDITOS\n");
        printf("\t\t\t[0]---> SAIR\n");
        printf("\n");
        do
        {
            textcolor(MAGENTA);
            printf("\t\t\tQual a sua Opcao:");
            scanf("%d",&num);
        }
        while(num<0 && num>5);
        switch(num)
        {
            case 0:
                printf("*****BYE TCHAU*****\n");
                //sei que ele sai sozinho nao preciso de nenhuma chamada ele autom�ticamente volta atras
                break;
            case 1:
                 tabuleiros();
                 //
                 break;
            case 2:
                 ler_recorde();
                 break;
            case 3:
                 descrisao_jogo();
                 break;
            case 4:
                 creditos();
                 break;
        }
        printf("\n");
    }
    while(num!=0);
    
}


//******************FUN��O PRINCIPAL********************************************
main()
{
      pont=0;
      nrecordes=0;
      nvirada=-1;
      nab=24;
      menuprincipal();
      system("PAUSE");
}


