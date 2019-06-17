#include "SEQUENCIASVISIVEIS.H"
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include <stdlib.h>


CAM_tpCondRet CAM_FormaCampo(CampoPtr * campo, LIS_tppLista baralho){
	CartaPtr carta, cartaLista;
	LIS_tppLista lista;
	int nElem ;

	int coluna = -1, nElemde7 = 0, nElemde6 = 0;
	 if( *campo == NULL){
		 return CAM_CAMPONULO;
	 }
	 if(baralho == NULL){
		 return CAM_BARALHONULO;
	 }
	 nElem = pegaNumeroElementos(baralho);
     (*campo)->seqvisiveis = LIS_CriarLista(DestruirValor);
	 EMB_Embaralha(&baralho);
	 while(pegaNumeroElementos(baralho) > 0){
		 if(nElemde7 == 0 && nElemde6 == 0){
			 coluna++;
			 lista = LIS_CriarLista(DestruirValor);
			LIS_InserirElementoApos((*campo)->seqvisiveis,lista);
			IrInicioLista(baralho);
	 carta = (CartaPtr)LIS_ObterValor(baralho);
	 CAM_InsereCartaNoTopo(*campo, carta, coluna);
	 LIS_ExcluirElemento(baralho);
	 nElemde7 = 6, nElemde6 = 5;
		 }
		 if((coluna >= 0 && coluna < 4 ) && nElemde7 != 0 && pegaNumeroElementos(baralho) != 0){
			 nElemde6 = 0;
			  IrInicioLista(baralho);
	 carta = (CartaPtr)LIS_ObterValor(baralho);
	  CAM_InsereCartaNoTopo(* campo, carta, coluna);
	   LIS_ExcluirElemento(baralho);
	  nElemde7--;
}
		 if(( coluna >= 4 ) && nElemde6 != 0 && pegaNumeroElementos(baralho)){
			 nElemde7 = 0;
			  IrInicioLista(baralho);
	 carta = (CartaPtr)LIS_ObterValor(baralho);
	 LIS_ExcluirElemento(baralho);
	  CAM_InsereCartaNoTopo( *campo, carta, coluna);
	  nElemde6--;

		 }
	 }
	 return CAM_CAMPOOK;
}

void CAM_DestroiCampo(CampoPtr campo){

	assert (campo != NULL);

	LIS_DestruirLista(campo->seqvisiveis);

	free(campo);
}

CAM_tpCondRet CAM_AnalisaCartaDoTopo(CartaPtr * carta, CampoPtr campo, int coluna){
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	if(coluna < 0 || coluna > 8){
		return CAM_POSICAOINVALIDA;
	}
	if(campo == NULL){
		return CAM_CAMPONULO;
	}
	IrInicioLista(campo->seqvisiveis);
	LIS_AvancarElementoCorrente(campo->seqvisiveis, coluna);
	lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
	IrInicioLista(lista);
	* carta  = (CartaPtr)LIS_ObterValor(lista);
	if(* carta == NULL ){
		return CAM_CARTADOTOPONULA;
	}
	return CAM_CARTAOK;
}

CAM_tpCondRet CAM_RetiraCartaDoTopo(CampoPtr campo,  int coluna){
	CartaPtr carta;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	if(coluna < 0 || coluna > 8){
		return CAM_POSICAOINVALIDA;
	}
	if(campo == NULL){
		return CAM_CAMPONULO;
	}
	IrInicioLista(campo->seqvisiveis);
	LIS_AvancarElementoCorrente(campo->seqvisiveis, coluna);
	lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
	IrInicioLista(lista);
	carta = (CartaPtr)LIS_ObterValor(lista);
	if( carta == NULL){
		return CAM_CARTADOTOPONULA;
	}
	LIS_ExcluirElemento(lista);
	return CAM_CARTAOK;
}


CAM_tpCondRet CAM_InsereCartaNoTopo(CampoPtr campo, CartaPtr carta, int coluna){
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	if(coluna < 0 || coluna > 8 ){
		return CAM_POSICAOINVALIDA;
	}

	if(campo == NULL){
		return CAM_CAMPONULO;
	}
	if(carta == NULL){
		return CAM_CARTAINVALIDA;
	}
	IrInicioLista(campo->seqvisiveis);
	LIS_AvancarElementoCorrente(campo->seqvisiveis,coluna);
	lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
	LIS_InserirElementoAntes(lista,carta);
	return CAM_CARTAOK;

}

CAM_tpCondRet CAM_AnalisaCartaNaPosicao(CampoPtr campo, CartaPtr * carta, int coluna, int posicaoColuna){
	int nElem;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
		if(coluna < 0 || coluna > 8 ){
		return CAM_POSICAOINVALIDA;
	}
	if(campo == NULL){
		return CAM_CAMPONULO;
	}
	IrInicioLista(campo->seqvisiveis);
	LIS_AvancarElementoCorrente(campo->seqvisiveis,coluna);
	lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
	IrInicioLista(lista);
	nElem = pegaNumeroElementos(lista);
	if(nElem < (posicaoColuna + 1)){
		return CAM_CARTASINVALIDAS;
	}
	LIS_AvancarElementoCorrente(lista,posicaoColuna);
	 * carta = (CartaPtr )LIS_ObterValor(lista);

	return CAM_CARTAOK;

}

int CAM_VerificaNumSeqVisiveisVazias(CampoPtr campo){
	CartaPtr carta;
	int nVazios = 0;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	int Colunas = 0;
	while( Colunas < 8 ){
		IrInicioLista(campo->seqvisiveis);
		LIS_AvancarElementoCorrente(campo->seqvisiveis,Colunas);
		lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
		IrInicioLista(lista);
		carta = (CartaPtr)LIS_ObterValor(lista);
		if( carta == NULL){
			nVazios++;
		}
		Colunas++;
	}
	return nVazios;
}

CAM_tpCondRet CAM_RetiraCartaNaPosicao(CampoPtr campo, int coluna, int posicaoColuna){
		CartaPtr carta;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	if(coluna < 0 || coluna > 8){
		return CAM_POSICAOINVALIDA;
	}
	if(campo == NULL){
		return CAM_CAMPONULO;
	}
	IrInicioLista(campo->seqvisiveis);
	LIS_AvancarElementoCorrente(campo->seqvisiveis, coluna);
	lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
	IrInicioLista(lista);
	LIS_AvancarElementoCorrente(lista,posicaoColuna);
	carta = (CartaPtr)LIS_ObterValor(lista);
	if( carta == NULL){
		return CAM_CARTADOTOPONULA;
	}
	LIS_ExcluirElemento(lista);
	return CAM_CARTAOK;
}

int CAM_VerificaLinhaComMaisElementos(CampoPtr campo){
	int NElementos = 0, i = 0;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	for(  i = 0; i < 8; i++){
		IrInicioLista(campo->seqvisiveis);
		LIS_AvancarElementoCorrente(campo->seqvisiveis,i);
		lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
		if(NElementos < pegaNumeroElementos(lista)){
			NElementos = pegaNumeroElementos(lista);
		}
	}
	return NElementos;
}


void CAM_MostraCampo(CampoPtr campo){
	char * Valor;
	char ValorNaipe;
	CartaPtr c;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	int y, x , MaiorLinha= 0;
	MaiorLinha = CAM_VerificaLinhaComMaisElementos(campo);
		for( y=-1; y < MaiorLinha; y++){
		for( x = 0; x < pegaNumeroElementos(campo->seqvisiveis); x++){
			if(y == -1){
				printf("  %d \t",(x+1));
			}else{
			IrInicioLista(campo->seqvisiveis);
			LIS_AvancarElementoCorrente(campo->seqvisiveis,x);
			lista = (LIS_tppLista)LIS_ObterValor(campo->seqvisiveis);
			IrFinalLista(lista);
			LIS_AvancarElementoCorrente(lista,-y);
			if( (y+1) > pegaNumeroElementos(lista)){
				printf("  \t");
			}
			if( (y+1) <= pegaNumeroElementos(lista)){
			c = (CartaPtr)LIS_ObterValor(lista);
			Valor = BAR_VerificaTipoCarta(c->tiponumero);
			ValorNaipe = BAR_VerificaNaipe(c->tiponaipe);
			printf("(%s,%c) \t",Valor,ValorNaipe);
			}
			}
		}
	printf("\n");
	}
}