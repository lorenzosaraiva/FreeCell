#include "SEQUENCIAORDENADA.h"
#include   <malloc.h>
#include <stdio.h>
#include   <assert.h>

ORD_tpCondRet ORD_CriaSequenciaOrdenada(OrdenadaPtr ordenada){
	LIS_tppLista BaralhoOrdenadoporNaipe;
	BaralhoOrdenadoporNaipe = LIS_CriarLista(DestruirValor);
	if(ordenada == NULL){
		return ORD_LISTAORDENADANULA;
	}
	ordenada->listaOrdenada = LIS_CriarLista(DestruirValor);
	IrInicioLista(ordenada->listaOrdenada);
	LIS_InserirElementoApos(ordenada->listaOrdenada,BaralhoOrdenadoporNaipe);
	BaralhoOrdenadoporNaipe = LIS_CriarLista(DestruirValor);
	LIS_InserirElementoApos(ordenada->listaOrdenada,BaralhoOrdenadoporNaipe);
	BaralhoOrdenadoporNaipe = LIS_CriarLista(DestruirValor);
	LIS_InserirElementoApos(ordenada->listaOrdenada,BaralhoOrdenadoporNaipe);
	BaralhoOrdenadoporNaipe = LIS_CriarLista(DestruirValor);
	LIS_InserirElementoApos(ordenada->listaOrdenada,BaralhoOrdenadoporNaipe);
	

	return ORD_ORDENADAOK;


}


void ORD_DestroiSequenciaOrdenada(OrdenadaPtr ordenada){

	assert(ordenada != NULL);

	LIS_DestruirLista(ordenada->listaOrdenada);

	free(ordenada);
}
ORD_tpCondRet ORD_InsereCartaNaOrdenada(OrdenadaPtr ordenada , CartaPtr carta){
	CartaPtr cartaTopo;
	int ValorNaipe ;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	if(ordenada == NULL){
		return ORD_LISTAORDENADANULA;
	}
	if(carta == NULL){
		return ORD_CARTANULA;
	}
	ValorNaipe = (int)carta->tiponaipe;
	IrInicioLista(ordenada->listaOrdenada);
	LIS_AvancarElementoCorrente(ordenada->listaOrdenada,ValorNaipe);
	lista = (LIS_tppLista)LIS_ObterValor(ordenada->listaOrdenada);
	if(carta->tiponumero == A){
		LIS_InserirElementoAntes(lista,carta);
	}else{
			ORD_AnalisaCartadoTopo(ordenada,&cartaTopo,ValorNaipe);
			if( cartaTopo == NULL){
             return ORD_CARTAINVALIDA;
			}else 
		if((int)carta->tiponumero == ((int)cartaTopo->tiponumero + 1)){
			LIS_InserirElementoAntes(lista,carta);
		} else {
			return ORD_CARTAINVALIDA;
		
			}
	}
		return ORD_ORDENADAOK;
	
}
	ORD_tpCondRet ORD_AnalisaCartadoTopo(OrdenadaPtr ordenada, CartaPtr * carta, int posicao){
		LIS_tppLista lista = LIS_CriarLista(DestruirValor);
		if(ordenada == NULL){
			return ORD_LISTAORDENADANULA;
		}
		if(posicao < 0 || posicao > 4){
			return ORD_POSICAOINVALIDA;
		}
		IrInicioLista(ordenada->listaOrdenada);
		LIS_AvancarElementoCorrente(ordenada->listaOrdenada,posicao);
		lista = (LIS_tppLista)LIS_ObterValor(ordenada->listaOrdenada);
		IrInicioLista(lista);
		* carta = (CartaPtr)LIS_ObterValor(lista);
		return ORD_ORDENADAOK;
	}


	void ORD_MostraOrdenada(OrdenadaPtr ordenada){
		int i;
		char * Valor;
		char ValorNaipe;
		CartaPtr carta;
		LIS_tppLista lista = LIS_CriarLista(DestruirValor);
		printf("\n                      O                               ");
		printf("\nORDENADA: ");
		for ( i = 0; i < 4; i++){
			IrInicioLista(ordenada->listaOrdenada);
			LIS_AvancarElementoCorrente(ordenada->listaOrdenada,i);
			lista = (LIS_tppLista)LIS_ObterValor(ordenada->listaOrdenada);
			IrInicioLista(lista);
			carta = (CartaPtr)LIS_ObterValor(lista);
			if( carta == NULL){
				printf(" \t");
			}else{
				Valor = BAR_VerificaTipoCarta(carta->tiponumero);
				ValorNaipe = BAR_VerificaNaipe(carta->tiponaipe);
				printf(" (%s,%c) \t",Valor,ValorNaipe);
			}
		}
		printf("\n");
	}    