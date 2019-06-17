#ifndef __BARALHO_h__
#define __BARALHO_h__
#include "LISTA.H"

typedef enum {
	BAR_BARALHO_OK ,
	BAR_BARALHONULO,
	BAR_CARTAOK,
	BAR_CARTAINVALIDA ,
	BAR_FALTOUMEMORIA
}BAR_tpCondRet;

enum naipe {
	OUROS, 
    ESPADAS,
	COPAS,
	PAUS
};

enum cor {
	PRETO,
	VERMELHO
};

enum numero {
	A, 
	DOIS, 
	TRES, 
	QUATRO, 
	CINCO,
	SEIS, 
	SETE, 
	OITO, 
	NOVE, 
	DEZ, 
	J, 
	Q, 
	K
};

struct Carta{
	enum naipe tiponaipe;
	enum cor tipocor;
	enum numero tiponumero;
};


typedef struct Carta* CartaPtr;

// Cria uma carta
// @returns CartaPtr Ponteiro para Carta
BAR_tpCondRet BAR_CriaCarta(enum numero tipoNum, enum naipe tipoNaipe, enum cor tipoCor, CartaPtr * carta);


 void DestruirValor(void * pDado);

 BAR_tpCondRet BAR_CriaBaralho(LIS_tppLista listbaralho, int nCartas);

 char * BAR_VerificaTipoCarta(enum numero num);

 void BAR_DestroiBaralho(LIS_tppLista baralho);

 char  BAR_VerificaNaipe(enum naipe tipoNaipe);

#endif /* __BARALHO_h_ */