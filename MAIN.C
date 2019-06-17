#include   <stdio.h>
#include "LISTA.H"
#include "BARALHO.H"
#include "SEQUENCIASVISIVEIS.H"
#include "SEQUENCIAORDENADA.H"
#include "ESPVAZIOS.H"
#include "PARTIDA.H"
#include "TRATADORERROS.h"
#include   <malloc.h>
#include "CONTA.H"
#include "CESPDIN.H"
/* TESTES EXECUTADOS PARA OS MÓDULOS */

int main(void){
	LIS_tppLista lista;
	JogadorPtr jogador;
	CampoPtr campo;
	CamposVaziosPtr campoVazio;
	OrdenadaPtr ordenada;
		CNT_InicializarContadores("");
	CNT_LerContadores("C:\\Users\\user\\Documents\\Visual Studio 2010\\Projects\\FreeCellFinal\\FreeCellFinal\\Scripts\\Contadores");
	CNT_IniciarContagem();
	campo = (CampoPtr)malloc(sizeof(struct Campo));
	campoVazio = (CamposVaziosPtr)malloc(sizeof(struct CamposVazios));
	ordenada = (OrdenadaPtr)malloc(sizeof(struct Ordenada));
	jogador = (JogadorPtr)malloc(sizeof(struct Jogador));
	JOG_CriaJogador(jogador);
	PAR_Jogo(jogador,campo,campoVazio,ordenada);
//	CNT_TerminarContadores();
	//CNT_ZerarContadores();
	//lista = LIS_CriarLista(DestruirValor);
	//CNT_ObterContagem("Cria Lista");
	/*CNT_InicializarContadores("");
	CNT_LerContadores("C:\\Users\\user\\Documents\\Visual Studio 2010\\Projects\\FreeCellFinal\\FreeCellFinal\\Scripts\\Contadores");
	CNT_IniciarContagem();
	 lista = LIS_CriarLista(DestruirValor);
	LIS_InserirElementoApos(lista,"abc");
	LIS_InserirElementoApos(lista,"def");
	LIS_InserirElementoApos(lista,"ghi");
	LIS_ProcurarValor(lista,"abc         ");
	*/
	return 0;

}