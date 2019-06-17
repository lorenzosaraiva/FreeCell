#ifndef __EMBARALHAMENTO_h__
#define __EMBARALHAMENTO_h__
#include "BARALHO.H"

typedef enum {
	EMB_EMBARALHA_OK ,
	EMB_EMBARALHADONULO, 
	EMB_FALTAMEMORIA
}EMB_tpCondRet;


void EMB_DestroiBaralhoEmbaralhado(LIS_tppLista baralho);

EMB_tpCondRet EMB_Embaralha(LIS_tppLista  * listaAtual);

#endif /* __EMBARALHAMENTO_h_ */