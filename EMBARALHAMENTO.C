#include "EMBARALHAMENTO.H"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
	

  
EMB_tpCondRet EMB_Embaralha(LIS_tppLista  * listaAtual){
	CartaPtr c = (CartaPtr)malloc(sizeof(struct Carta));
	CartaPtr c2 = (CartaPtr)malloc(sizeof(struct Carta));
	 LIS_tppLista listaEmbaralhada = LIS_CriarLista(DestruirValor); /* Lista a ser embaralhada */
	 	 int r = 1, nCartas = 0;
	LIS_tpCondRet condicao ; /* Condicao de retorno */
	 if(*listaAtual == NULL ){
	 }
	if(pegaNumeroElementos(* listaAtual) == 0){
		return EMB_EMBARALHADONULO;
	}
	nCartas = pegaNumeroElementos(* listaAtual);
	 /* Numero de cartas */ /* Gera um numero aleatorio para acessar na lista */
	 while(nCartas > 0){
			IrInicioLista(*listaAtual);
			c = (CartaPtr)LIS_ObterValor(*listaAtual);/* Volta pro inicio da lista */
			srand((unsigned)time(NULL));
			 r = rand() % nCartas;
		condicao = LIS_AvancarElementoCorrente( *listaAtual, r); /* Avanca r vezes na Lista e acha um novo elemento corrente */
		if(condicao == LIS_CondRetListaVazia){
			return EMB_EMBARALHADONULO;
		}
		c = (CartaPtr)LIS_ObterValor(*listaAtual);
		LIS_InserirElementoApos(listaEmbaralhada, c); /* Pega elemento corrente e insere*/	
		c2 = (CartaPtr) LIS_ObterValor(listaEmbaralhada);
		LIS_ExcluirElemento(*listaAtual); /* Exclui elemento corrente da lista */
	    
	nCartas--;
	}

	* listaAtual = listaEmbaralhada;

	return EMB_EMBARALHA_OK;
}



 void EMB_DestroiBaralhoEmbaralhado(LIS_tppLista baralho){
	 LIS_DestruirLista(baralho);
	 }