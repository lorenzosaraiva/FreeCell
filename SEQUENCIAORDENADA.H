#ifndef __SEQUENCIAORDENADA_h__
#define __SEQUENCIAORDENADA_h__
#include "BARALHO.H"

typedef enum{
	ORD_LISTAORDENADANULA,
	ORD_CARTANULA,
	ORD_ORDENADAOK,
	ORD_POSICAOINVALIDA,
	ORD_CARTAINVALIDA

}ORD_tpCondRet;


struct Ordenada{
	LIS_tppLista listaOrdenada;

};

typedef struct Ordenada *OrdenadaPtr;


ORD_tpCondRet ORD_CriaSequenciaOrdenada(OrdenadaPtr ordenada);


void ORD_DestroiSequenciaOrdenada(OrdenadaPtr ordenada);

ORD_tpCondRet ORD_InsereCartaNaOrdenada(OrdenadaPtr ordenada , CartaPtr carta);

ORD_tpCondRet ORD_AnalisaCartadoTopo(OrdenadaPtr ordenada, CartaPtr * carta, int posicao);

void ORD_MostraOrdenada(OrdenadaPtr ordenada);



#endif /* __SEQUENCIAORDENADA_h_ */