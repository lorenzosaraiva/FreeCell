#ifndef __ESPVAZIOS_h__
#define __ESPVAZIOS_h__
#include "BARALHO.H"


typedef enum{
	VAZ_LISTAVAZIANULA,
	VAZ_ESPACOOK,
	VAZ_LISTACHEIA,
	VAZ_CARTANULA,
	VAZ_POSICAONEXISTE

}VAZ_tpCondRet;

 struct CamposVazios{
	LIS_tppLista lista;
	int posicoesVazias;
};

typedef struct CamposVazios * CamposVaziosPtr;


VAZ_tpCondRet VAZ_CriaEspacosVazios(CamposVaziosPtr campoVazio);

void VAZ_DestroiEspacosVazios(CamposVaziosPtr campovazio);

VAZ_tpCondRet VAZ_InsereNoEspacoVazio(CamposVaziosPtr campoVazio, CartaPtr carta);

VAZ_tpCondRet VAZ_AnalisaCartaDoEspacoVazio(CamposVaziosPtr campovazio, int posicao, CartaPtr * carta );

VAZ_tpCondRet VAZ_RemoveDoEspacoVazio(CamposVaziosPtr campoVazio, int posicao);

void VAZ_MostraVazio(CamposVaziosPtr campoVazio);

#endif /* __ESPVAZIOS_h_ */