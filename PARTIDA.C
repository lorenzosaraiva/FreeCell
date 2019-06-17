#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include <math.h>
#include "PARTIDA.H"


PAR_tpCondRet PAR_MoveCartaDoCampoparaCampo(CampoPtr campo,int posicaoAtual, int posicaoFinal, TratarMovimentoPtr * tratador){
	CartaPtr cartaAtual, cartaTopo;
	CAM_tpCondRet condicaoCampo = CAM_CARTAOK;
	posicaoAtual = posicaoAtual - 1;
	posicaoFinal = posicaoFinal - 1;
	condicaoCampo =  CAM_AnalisaCartaDoTopo(&cartaAtual,campo,posicaoAtual);
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
       condicaoCampo =  CAM_AnalisaCartaDoTopo(&cartaTopo,campo,posicaoFinal);
	   if(cartaTopo == NULL){
		   CAM_RetiraCartaDoTopo(campo,posicaoAtual);
		   CAM_InsereCartaNoTopo(campo,cartaAtual,posicaoFinal);
		   return PAR_MOVIMENTOVALIDO;
	   }
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	if(cartaAtual->tipocor != cartaTopo->tipocor && cartaTopo->tiponumero == (cartaAtual->tiponumero + 1)){
		condicaoCampo =  CAM_RetiraCartaDoTopo(campo,posicaoAtual);
		if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
		condicaoCampo = CAM_InsereCartaNoTopo(campo,cartaAtual,posicaoFinal);
		if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}

		return PAR_MOVIMENTOVALIDO;
	}
	    (*tratador)->origem = MOVIMENTO;
		(*tratador)->tipoErro = MOV_CORESIGUAIS;
		return PAR_MOVIMENTOINVALIDO;

}

PAR_tpCondRet PAR_MoveCartaCampoParaEspVazios(CampoPtr campo, CamposVaziosPtr campoVazio, int posicaoCampo, TratarMovimentoPtr * tratador){
		CartaPtr carta;
	VAZ_tpCondRet condicaoVazio = VAZ_ESPACOOK;
	CAM_tpCondRet condicaoCampo = CAM_CARTAOK;
	posicaoCampo = posicaoCampo - 1;
	condicaoCampo =  CAM_AnalisaCartaDoTopo(&carta,campo,posicaoCampo);
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoVazio = VAZ_InsereNoEspacoVazio(campoVazio,carta);
	if( condicaoVazio != VAZ_ESPACOOK )
	{
		(*tratador)->origem = VAZIO;
		(*tratador)->tipoErro = (int)condicaoVazio;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoCampo = CAM_RetiraCartaDoTopo(campo,posicaoCampo);
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	return PAR_MOVIMENTOVALIDO;

}

PAR_tpCondRet PAR_MoveCartaEspVazioParaCampo(CampoPtr campo, CamposVaziosPtr campoVazio, int posicaoVazio, int posicaoCampo,  TratarMovimentoPtr * tratador){
	VAZ_tpCondRet condicaoVazio = VAZ_ESPACOOK;
	CAM_tpCondRet condicaoCampo = CAM_CARTAOK;
	CartaPtr cartaVazio, cartaCampo;
	posicaoVazio = posicaoVazio - 1;
	posicaoCampo = posicaoCampo - 1;
	condicaoVazio = VAZ_AnalisaCartaDoEspacoVazio(campoVazio, posicaoVazio, &cartaVazio);
	if( condicaoVazio != VAZ_ESPACOOK )
	{
		(*tratador)->origem = VAZIO;
		(*tratador)->tipoErro = (int)condicaoVazio;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoCampo = CAM_AnalisaCartaDoTopo(&cartaCampo, campo , posicaoCampo);
	 if(cartaCampo == NULL){
		   VAZ_RemoveDoEspacoVazio(campoVazio, posicaoVazio);
		   CAM_InsereCartaNoTopo(campo,cartaVazio,posicaoCampo);
		   return PAR_MOVIMENTOVALIDO;
	   }
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	if(cartaVazio->tipocor != cartaCampo->tipocor && cartaCampo->tiponumero == (cartaVazio->tiponumero + 1)){
		condicaoVazio = VAZ_RemoveDoEspacoVazio(campoVazio, posicaoVazio);
		if( condicaoVazio != VAZ_ESPACOOK )
	{
		(*tratador)->origem = VAZIO;
		(*tratador)->tipoErro = (int)condicaoVazio;
		return PAR_MOVIMENTOINVALIDO;
	}
		condicaoCampo = CAM_InsereCartaNoTopo(campo,cartaVazio,posicaoCampo);
		if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
		return PAR_MOVIMENTOVALIDO;
	}
	(*tratador)->origem = MOVIMENTO;
		(*tratador)->tipoErro = MOV_CORESIGUAIS;
	return PAR_MOVIMENTOINVALIDO;
}


PAR_tpCondRet PAR_MoveCartaCampoParaOrdenada(CampoPtr campo, OrdenadaPtr ordenada, int posicaoCampo,  TratarMovimentoPtr * tratador){
	ORD_tpCondRet condicaoOrdenada = ORD_ORDENADAOK;
    CAM_tpCondRet condicaoCampo = CAM_CARTAOK;
	CartaPtr cartaCampo;
	posicaoCampo = posicaoCampo - 1;
	condicaoCampo = CAM_AnalisaCartaDoTopo(&cartaCampo,campo,posicaoCampo);
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoOrdenada = ORD_InsereCartaNaOrdenada(ordenada,cartaCampo);
	if( condicaoOrdenada != ORD_ORDENADAOK ){
		(*tratador)->origem = ORDENADA;
		(*tratador)->tipoErro = (int)condicaoOrdenada;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoCampo = CAM_RetiraCartaDoTopo(campo,posicaoCampo);
	if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
	}
	return PAR_MOVIMENTOVALIDO;

}

PAR_tpCondRet PAR_MoveCartasDoCampoParaoCampo(CampoPtr campo, CamposVaziosPtr campoVazio,  int posicaoInicial, int posicaoFinal, int nCartas, TratarMovimentoPtr * tratador){
	CartaPtr CartaTopo, CartaProx, CartaTopoFinal;
	CAM_tpCondRet condicaoCampo = CAM_CARTAOK;
	int qntCartas = nCartas,  posColuna = 0;
	int nCartaspossiveis = (1 + campoVazio->posicoesVazias) * pow(2.0,CAM_VerificaNumSeqVisiveisVazias(campo));
	posicaoInicial = posicaoInicial -1;
	posicaoFinal = posicaoFinal - 1;
	if(nCartaspossiveis < nCartas){
		(*tratador)->origem = MOVIMENTO;
		(*tratador)->tipoErro =  MOV_CARTASLIMITE;
		return PAR_MOVIMENTOINVALIDO;
	}
	if( nCartas <= 1){
		(*tratador)->origem = MOVIMENTO;
		(*tratador)->tipoErro =  MOV_CARTASINSUFICIENTES;
		return PAR_MOVIMENTOINVALIDO;
	}
	while(nCartas > 0){
		if(posColuna == 0){
			nCartas--;
		}
	condicaoCampo = CAM_AnalisaCartaNaPosicao(campo,&CartaTopo,posicaoInicial,posColuna);
			if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
			}
		posColuna++;

	condicaoCampo = CAM_AnalisaCartaNaPosicao(campo,&CartaProx,posicaoInicial,posColuna);
			if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
			}
			if(!((CartaTopo->tipocor != CartaProx->tipocor) && (CartaProx->tiponumero == CartaTopo->tiponumero + 1))){
		(*tratador)->origem = MOVIMENTO;
		(*tratador)->tipoErro = MOV_CORESIGUAIS;
			return PAR_MOVIMENTOINVALIDO;
		}
		nCartas--;
	}
	 condicaoCampo =  CAM_AnalisaCartaNaPosicao(campo,&CartaProx,posicaoInicial,posColuna);
		if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
		}
		condicaoCampo = CAM_AnalisaCartaDoTopo(&CartaTopoFinal,campo,posicaoFinal);
		if(CartaTopoFinal == NULL){
			while(nCartas < qntCartas){
		CAM_AnalisaCartaNaPosicao(campo,&CartaProx,posicaoInicial,posColuna);
		CAM_RetiraCartaNaPosicao(campo,posicaoInicial,posColuna);
		CAM_InsereCartaNoTopo(campo,CartaProx,posicaoFinal);
		nCartas++;
		posColuna--;
	}
			return PAR_MOVIMENTOVALIDO;
		}
			if( condicaoCampo != CAM_CARTAOK ){
		(*tratador)->origem = CAMPO;
		(*tratador)->tipoErro = (int)condicaoCampo;
		return PAR_MOVIMENTOINVALIDO;
			}
		if(!((CartaProx->tipocor != CartaTopoFinal->tipocor) && (CartaTopoFinal->tiponumero == (CartaProx->tiponumero + 1)))){
			(*tratador)->origem = MOVIMENTO;
			(*tratador)->tipoErro = MOV_CORESIGUAIS;
			return PAR_MOVIMENTOINVALIDO;
		}

		while(nCartas < qntCartas){
		CAM_AnalisaCartaNaPosicao(campo,&CartaProx,posicaoInicial,posColuna);
		CAM_RetiraCartaNaPosicao(campo,posicaoInicial,posColuna);
		CAM_InsereCartaNoTopo(campo,CartaProx,posicaoFinal);
		nCartas++;
		posColuna--;
	}
	return PAR_MOVIMENTOVALIDO;
}

PAR_tpCondRet PAR_MoveCartaEspacoVazioParaOrdenada(CamposVaziosPtr campoVazio, OrdenadaPtr ordenada, int posicaoVazio, TratarMovimentoPtr * tratador){
	CartaPtr carta;
	VAZ_tpCondRet condicaoVazio = VAZ_ESPACOOK;
	ORD_tpCondRet condicaoOrdenada = ORD_ORDENADAOK;
		posicaoVazio = posicaoVazio - 1;
	condicaoVazio =  VAZ_AnalisaCartaDoEspacoVazio(campoVazio,posicaoVazio,&carta);
		if( condicaoVazio != VAZ_ESPACOOK )
	{
		(*tratador)->origem = VAZIO;
		(*tratador)->tipoErro = (int)condicaoVazio;
		return PAR_MOVIMENTOINVALIDO;
	}
		condicaoOrdenada =  ORD_InsereCartaNaOrdenada(ordenada,carta);
	if( condicaoOrdenada != ORD_ORDENADAOK ){
		(*tratador)->origem = ORDENADA;
		(*tratador)->tipoErro = (int)condicaoOrdenada;
		return PAR_MOVIMENTOINVALIDO;
	}
	condicaoVazio = VAZ_RemoveDoEspacoVazio(campoVazio,posicaoVazio);
		if( condicaoVazio != VAZ_ESPACOOK )
	{
		(*tratador)->origem = VAZIO;
		(*tratador)->tipoErro = (int)condicaoVazio;
		return PAR_MOVIMENTOINVALIDO;
	}
		return PAR_MOVIMENTOVALIDO;

}
int PAR_FimDoJogo(OrdenadaPtr ordenada){
	int i = 0;
	LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	for ( i = 0; i < 4; i++){
		IrInicioLista(ordenada->listaOrdenada);
		LIS_AvancarElementoCorrente(ordenada->listaOrdenada,i);
		lista = (LIS_tppLista)LIS_ObterValor(ordenada->listaOrdenada);
		if(pegaNumeroElementos(lista) != 13){
			return 0;
		}
	}
	return 1;
}


void PAR_RealizaUmMovimento(CampoPtr campo, CamposVaziosPtr campoVazio, OrdenadaPtr ordenada, TratarMovimentoPtr tratador, PAR_tpCondRet *condicaoPartida){
	int posicaoAtual,posicaoFinal,nCartas;
	char  valor , valor2 , valor3;
	printf(" Digite a casa que deseja mover:");
	scanf(" %c", &valor);

	if( (int)valor == 114){
				printf("Deseja realmente parar o jogo?(s/n):");
				scanf(" %c", &valor3);
				if((int)valor3 == 115){
					*condicaoPartida = PAR_REINICIA;
				}
				return;
	}
	printf(" Digite a casa que deseja inserir: ");
	scanf(" %c", &valor2);

	if( (49 <= (int)valor && (int)valor <= 56) && (49 <= (int)valor2 && (int)valor2 <= 56) ){
		printf(" Digite o numero de cartas que deseja mover : ");
		scanf( "%d",&nCartas);
		if( nCartas == 1){
		 *condicaoPartida =  PAR_MoveCartaDoCampoparaCampo(campo,(valor - 48),(valor2 - 48), &tratador);
	  if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
	  VerificaErro(tratador);
	  }

	  }else{
		  *condicaoPartida =  PAR_MoveCartasDoCampoParaoCampo(campo,campoVazio,(valor - 48),(valor2 - 48),nCartas,&tratador);
	  if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
	  VerificaErro(tratador);
	  }
		}
	} else
	if((49 <= (int)valor && (int)valor <= 56) && (97 <= (int)valor2 && (int)valor2 <= 100) ){
		*condicaoPartida =  PAR_MoveCartaCampoParaEspVazios(campo,campoVazio,(valor - 48),&tratador);
		if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
		VerificaErro(tratador);
		}
	}else
		if((49 <= (int)valor && (int)valor <= 56) && ((int)valor2 == 111) ){
			*condicaoPartida = PAR_MoveCartaCampoParaOrdenada(campo,ordenada,(valor - 48),&tratador);
		if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
		VerificaErro(tratador);
		}
		}else 
			if( (97 <= (int)valor && (int)valor <= 100) && (49 <= (int)valor2 && (int)valor2 <= 56) ){
				*condicaoPartida =  PAR_MoveCartaEspVazioParaCampo(campo,campoVazio,(valor - 96),(valor2 - 48),&tratador);
		if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
		VerificaErro(tratador);
		}
			} else
				if( (97 <= (int)valor && (int)valor <= 100) && ((int)valor2 == 111) ){
					*condicaoPartida =  PAR_MoveCartaEspacoVazioParaOrdenada(campoVazio,ordenada,(valor - 96),&tratador);
		if(*condicaoPartida == PAR_MOVIMENTOINVALIDO){
		VerificaErro(tratador);
		} 		

		}else
			
				printf("Valor digitado invalido !");

}
							

void PAR_Jogo(JogadorPtr j, CampoPtr campo, CamposVaziosPtr campoVazio, OrdenadaPtr ordenada){
	TratarMovimentoPtr tratador;
	LIS_tppLista baralho;
	PAR_tpCondRet condicaoPartida = PAR_MOVIMENTOINVALIDO;
    int nMovimentos = 0;
	tratador = (TratarMovimentoPtr)malloc(sizeof(struct TratarMovimento));
	baralho = LIS_CriarLista(DestruirValor);
	BAR_CriaBaralho(baralho,52);
	CAM_FormaCampo(&campo, baralho);
	VAZ_CriaEspacosVazios(campoVazio);
	ORD_CriaSequenciaOrdenada(ordenada);

	printf("Digite o nome do Jogador : ");
	gets(j->nome);

	while ( !PAR_FimDoJogo(ordenada) ){
				printf("\nCAMPO \n\n");
	printf("(Valor,Naipe)\n");
		CAM_MostraCampo(campo);
		VAZ_MostraVazio(campoVazio);
		ORD_MostraOrdenada(ordenada);
		PAR_RealizaUmMovimento(campo,campoVazio,ordenada,tratador, &condicaoPartida);
	if( condicaoPartida == PAR_MOVIMENTOVALIDO){
		nMovimentos++;
	}
	if(condicaoPartida == PAR_REINICIA){
    return;
	
	}
	}
	printf("FIM DO JOGO\n");
	JOG_RecebeNovoNumerodeMovimentos(j,nMovimentos);
	if ( JOG_VerificaNovoRecorde(j,nMovimentos)){
		printf("NOVO RECORDE DE MOVIMENTOS : %d", j->RecordeMovimentos);
	} else {
		printf("Numero de Movimentos Efetuados : %d",j->UltimoNumerodeMovimentos);
	}

}



