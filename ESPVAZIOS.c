#include "ESPVAZIOS.H"
#include   <malloc.h>
#include   <stdio.h>
#include   <assert.h>



VAZ_tpCondRet VAZ_CriaEspacosVazios(CamposVaziosPtr campoVazio){
	CartaPtr c = NULL;

if(campoVazio == NULL){
	return VAZ_LISTAVAZIANULA;
}
campoVazio->lista = LIS_CriarLista(DestruirValor);

LIS_InserirElementoApos(campoVazio->lista, c);
LIS_InserirElementoApos(campoVazio->lista, c);
LIS_InserirElementoApos(campoVazio->lista, c);
LIS_InserirElementoApos(campoVazio->lista, c);

campoVazio->posicoesVazias = 4;

return VAZ_ESPACOOK;

}

void VAZ_DestroiEspacosVazios(CamposVaziosPtr campovazio){
	assert(campovazio != NULL);

	LIS_DestruirLista(campovazio->lista);
	campovazio->posicoesVazias = 4;

	free(campovazio);
}



VAZ_tpCondRet VAZ_InsereNoEspacoVazio(CamposVaziosPtr campoVazio, CartaPtr carta){
	int i = 0;
	CartaPtr cartaAtual;
	if(campoVazio == NULL){
		return VAZ_LISTAVAZIANULA;
	}
	if(carta == NULL){
		return VAZ_CARTANULA;
	}
	if(campoVazio->posicoesVazias > 0 ){
		for( i = 0; i < 4 ; i++){
			IrInicioLista(campoVazio->lista);
			LIS_AvancarElementoCorrente(campoVazio->lista,i);
			cartaAtual = (CartaPtr)LIS_ObterValor(campoVazio->lista);
			if( cartaAtual == NULL){
				LIS_ExcluirElemento(campoVazio->lista);
		LIS_InserirElementoAntes(campoVazio->lista,carta);
		campoVazio->posicoesVazias--;
		return VAZ_ESPACOOK;
			}
		}


	/*	IrInicioLista(campoVazio->lista);
		LIS_AvancarElementoCorrente(campoVazio->lista,4- campoVazio->posicoesVazias);
		if(campoVazio->posicoesVazias == 0){
			LIS_ExcluirElemento(campoVazio->lista);
		LIS_InserirElementoAntes(campoVazio->lista,carta);
		campoVazio->posicoesVazias--;
		}else{
		LIS_ExcluirElemento(campoVazio->lista);
		LIS_InserirElementoApos(campoVazio->lista,carta);
		campoVazio->posicoesVazias--;
		}
}else{*/

}
	return VAZ_LISTACHEIA;
}
VAZ_tpCondRet VAZ_AnalisaCartaDoEspacoVazio(CamposVaziosPtr campovazio, int posicao, CartaPtr * carta ){

	if(posicao < 0 || posicao > 4) {
		return VAZ_POSICAONEXISTE;
	}
	if(campovazio == NULL){
		return VAZ_LISTAVAZIANULA;
	}
	IrInicioLista(campovazio->lista);
	LIS_AvancarElementoCorrente(campovazio->lista,posicao);
	* carta  = (CartaPtr )LIS_ObterValor(campovazio->lista);
		if(* carta == NULL){
			return VAZ_CARTANULA;
	}
	return VAZ_ESPACOOK;
}

VAZ_tpCondRet VAZ_RemoveDoEspacoVazio(CamposVaziosPtr campoVazio, int posicao){
	CartaPtr carta, cartaVazia = NULL;
		if(posicao < 0 || posicao > 4) {
		return VAZ_POSICAONEXISTE;
	}
		if(campoVazio == NULL){
			return VAZ_LISTAVAZIANULA;
		}
	IrInicioLista(campoVazio->lista);
	LIS_AvancarElementoCorrente(campoVazio->lista,posicao);
	carta = (CartaPtr)LIS_ObterValor(campoVazio->lista);
	if(carta == NULL){
		return VAZ_CARTANULA;
	}else{

	LIS_ExcluirElemento(campoVazio->lista);
	if(posicao == 0){
	LIS_InserirElementoAntes(campoVazio->lista, cartaVazia);
	}else{
		LIS_InserirElementoApos(campoVazio->lista, cartaVazia);
	}
	campoVazio->posicoesVazias++;
	}
	return VAZ_ESPACOOK;
}


void VAZ_MostraVazio(CamposVaziosPtr campoVazio){
	char * Valor;
	char ValorNaipe;
	CartaPtr carta;
	int i;
	printf("\n           a       b       c       d            ");
	printf("\nVAZIOS: ");
	for( i = 0; i < 4; i++){
		IrInicioLista(campoVazio->lista);
		LIS_AvancarElementoCorrente(campoVazio->lista,i);
		carta = (CartaPtr)LIS_ObterValor(campoVazio->lista); 
		if( carta == NULL){
			printf("\t");
		}else{
			Valor = BAR_VerificaTipoCarta(carta->tiponumero);
			ValorNaipe = BAR_VerificaNaipe(carta->tiponaipe);
			printf(" (%s,%c)\t",Valor,ValorNaipe);
		}
	}
	printf("\n");
}