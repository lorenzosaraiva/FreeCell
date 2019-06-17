#ifndef __PARTIDA_h__
#define __PARTIDA_h__
#include "SEQUENCIAORDENADA.H"
#include "SEQUENCIASVISIVEIS.H"
#include "ESPVAZIOS.H"
#include "TRATADORERROS.h"
#include "JOGADOR.H"



typedef enum {
PAR_MOVIMENTOINVALIDO,
PAR_MOVIMENTOVALIDO,
PAR_REINICIA

}PAR_tpCondRet;




PAR_tpCondRet PAR_MoveCartaDoCampoparaCampo(CampoPtr campo,int posicaoAtual, int posicaoFinal, TratarMovimentoPtr * tratador);

PAR_tpCondRet PAR_MoveCartaCampoParaEspVazios(CampoPtr campo, CamposVaziosPtr campoVazio, int posicaoCampo, TratarMovimentoPtr * tratador);

PAR_tpCondRet PAR_MoveCartaEspVazioParaCampo(CampoPtr campo, CamposVaziosPtr campoVazio, int posicaoVazio, int posicaoCampo,  TratarMovimentoPtr * tratador);

PAR_tpCondRet PAR_MoveCartaCampoParaOrdenada(CampoPtr campo, OrdenadaPtr ordenada, int posicaoCampo,  TratarMovimentoPtr * tratador);

PAR_tpCondRet PAR_MoveCartasDoCampoParaoCampo(CampoPtr campo, CamposVaziosPtr campoVazio,  int posicaoInicial, int posicaoFinal, int nCartas, TratarMovimentoPtr * tratador);

PAR_tpCondRet PAR_MoveCartaEspacoVazioParaOrdenada(CamposVaziosPtr campoVazio, OrdenadaPtr ordenada, int posicaoVazio, TratarMovimentoPtr * tratador);

int PAR_FimDoJogo(OrdenadaPtr ordenada);

void PAR_Jogo(JogadorPtr j, CampoPtr campo, CamposVaziosPtr campoVazio, OrdenadaPtr ordenada);



#endif /* __PARTIDA_h_ */