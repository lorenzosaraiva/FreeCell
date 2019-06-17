#ifndef __TRATADORERROS_h__
#define __TRATADORERROS_h__
#include "ESPVAZIOS.H"
#include "SEQUENCIASVISIVEIS.H"
#include "SEQUENCIAORDENADA.H"


enum Origem{
VAZIO,
CAMPO,
ORDENADA,
MOVIMENTO
};

typedef enum {
MOV_CORESIGUAIS,
MOV_CARTASLIMITE,
MOV_CARTASINSUFICIENTES

}MOV_tpCondRet;

 struct TratarMovimento{
	enum Origem origem;
	int tipoErro;

};

typedef struct TratarMovimento * TratarMovimentoPtr;


void VerificaErro( TratarMovimentoPtr tratador );

void VerificaErroVazio( VAZ_tpCondRet condicao);

void VerificaErroCampo(CAM_tpCondRet condicao);

void VerificaErroOrdenada(ORD_tpCondRet condicao);

void VerificaErroMovimento(MOV_tpCondRet condicao);










#endif /* __ESPVAZIOS_h_ */