#ifndef __SEQUENCIASVISIVEIS_h__
#define __SEQUENCIASVISIVEIS_h__
#include "embaralhamento.h"

struct Campo{

	LIS_tppLista seqvisiveis;

};

typedef struct Campo * CampoPtr;

typedef enum {
	CAM_CAMPOOK,

	CAM_BARALHONULO,

	CAM_CAMPONULO,

	CAM_POSICAOINVALIDA,

	CAM_CARTAINVALIDA,

	CAM_CARTADOTOPONULA,

	CAM_CARTAOK,

	CAM_CARTASINVALIDAS



}CAM_tpCondRet;


CAM_tpCondRet CAM_FormaCampo(CampoPtr * campo, LIS_tppLista baralho);

void CAM_DestroiCampo(CampoPtr campo);

CAM_tpCondRet CAM_AnalisaCartaDoTopo(CartaPtr * carta, CampoPtr campo, int posicao);

CAM_tpCondRet CAM_RetiraCartaDoTopo(CampoPtr campo,  int coluna);

CAM_tpCondRet CAM_InsereCartaNoTopo(CampoPtr campo, CartaPtr carta, int coluna);

int CAM_VerificaNumSeqVisiveisVazias(CampoPtr campo);

CAM_tpCondRet CAM_AnalisaCartaNaPosicao(CampoPtr campo, CartaPtr * carta, int coluna, int posicaoColuna);

CAM_tpCondRet CAM_RetiraCartaNaPosicao(CampoPtr campo, int coluna, int posicaoColuna);

void CAM_MostraCampo(CampoPtr campo);

int CAM_VerificaLinhaComMaisElementos(CampoPtr campo);

 #endif /* __SEQUENCIASVISIVEIS_h_ */