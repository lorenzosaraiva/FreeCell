#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include <string.h>
#include "BARALHO.H"

void  DestruirValor( void * pValor )
{
	
}

void BAR_DestroiBaralho(LIS_tppLista baralho){
	LIS_DestruirLista(baralho);

}

BAR_tpCondRet BAR_CriaCarta(enum numero tipoNum,enum naipe tipoNaipe,enum  cor tipoCor, CartaPtr * carta){
	* carta = ( CartaPtr ) malloc( sizeof( struct Carta ));
	(*carta)->tiponumero = tipoNum;
	(*carta)->tiponaipe = tipoNaipe;
	(*carta)->tipocor = tipoCor;
	return BAR_CARTAOK;
}

BAR_tpCondRet BAR_CriaBaralho(LIS_tppLista baralho, int nCartas){
	CartaPtr cartaPreta, cartaVermelha;
	int valorVermelho = 0, valorPreto = 0,  cor = 0,  naipeVermelho = 0, naipePreto = 1, vez = 1;
	int contador = nCartas ;
	if(baralho == NULL){
		return BAR_BARALHONULO;
	}
	while( contador > 0){

		if( (valorVermelho < 13 )&& (vez == 1)){
		BAR_CriaCarta((enum numero)valorVermelho, (enum naipe)naipeVermelho, VERMELHO, &cartaVermelha);
		LIS_InserirElementoApos(baralho,cartaVermelha);
		vez = 0;
		valorVermelho++;
		 if(valorVermelho >= 13){
			 naipeVermelho = 2;
			 valorVermelho = 0;
		 }
		 contador--;
		}else
         if((valorPreto < 13) && (vez == 0)){
			 BAR_CriaCarta((enum numero)valorPreto, (enum naipe)naipePreto, PRETO, &cartaPreta);
		LIS_InserirElementoApos(baralho,cartaPreta);
		vez = 1;
		contador--;
		valorPreto++;
				 if(valorPreto >= 13){
			 naipePreto = 3;
			 valorPreto = 0;
		 }
		 }
		}
	return BAR_BARALHO_OK;
	}


char * BAR_VerificaTipoCarta(enum numero num){
	char * valor;
	switch(num){
	case 0 :
		valor = "A";
		break;

	case 1 :
		valor = "2";
		break;

	case 2 :
		valor = "3";
		break;
	case 3 :
		valor = "4";
		break;
	case 4 : 
		valor = "5";
		break;
	case 5 : 
		valor = "6";
			break;
	case 6 :
		valor = "7";
		break;
	case  7:
		valor = "8";
		break;
	case 8 :
		valor = "9";
		break;
	case 9: 
		valor = "10";
		break;
	case 10 : 
		valor = "J";
		break;
	case 11 : 
		valor = "Q";
		break;
	case 12:
		valor = "K";
		break;
	}
	return valor;
	}


char  BAR_VerificaNaipe(enum naipe tipoNaipe){
	char  valor;
	switch(tipoNaipe){

	case 0 :
		valor = '\x04';
		break;

	case 1:
		valor = '\x05';
		break;

	case 2 :
		valor = '\x03';
		break;

	case 3:
		valor = '\x06';
		break;
	}
	return valor;
	}






