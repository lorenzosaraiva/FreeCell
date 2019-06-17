 #include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include "TRATADORERROS.h"



void VerificaErro( TratarMovimentoPtr tratador ){

	if(tratador->origem == CAMPO){
		VerificaErroCampo((CAM_tpCondRet)tratador->tipoErro);
	}
	else{
		if( tratador->origem == VAZIO){
			VerificaErroVazio((VAZ_tpCondRet)tratador->tipoErro);
		}
		 else{
			if(tratador->origem == ORDENADA){
				VerificaErroOrdenada((ORD_tpCondRet)tratador->tipoErro);
			}
			else {
				if( tratador->origem == MOVIMENTO){
					VerificaErroMovimento((MOV_tpCondRet)tratador->tipoErro);
				}
		 }
	}

	}
}
void VerificaErroVazio( VAZ_tpCondRet condicao){

	if( condicao == VAZ_CARTANULA){
		printf(" Nao pode realizar a operação pois a carta é nula\n");
	} else{
		if( condicao == VAZ_LISTACHEIA){
			printf(" Os Espaços estão todos preenchidos! \n");
		}else{
			if( condicao == VAZ_LISTAVAZIANULA){
				printf(" O Espaço Vazio que voce esta tentando realizar uma operação nao existe !\n");
			}else {
				if( condicao == VAZ_POSICAONEXISTE){
					printf("A posição que voce deseja inserir, remover ou analisar uma carta no Espaco Vazio nao existe !\n");
				}
			}
		}
	}

}


	void VerificaErroCampo(CAM_tpCondRet condicao){

		if( condicao == CAM_CAMPONULO){
			printf("Campo nao existe !\n");
		}else{
			if(condicao == CAM_POSICAOINVALIDA){
				printf(" A posição que voce deseja inserir, remover ou analisar uma carta no Campo nao existe !\n");
			}else{
				if(condicao == CAM_BARALHONULO){
					printf(" Campo não possui cartas!\n");
				}else{
					if( condicao == CAM_CARTADOTOPONULA){
						printf("Nao possui carta(s) suficientes na coluna para realizar o movimento!\n");
					}else {
						if( condicao == CAM_CARTAINVALIDA){
							printf(" Nãa pode realizar operação pois a carta é nula!\n");
						} else {
							if( condicao == CAM_CARTASINVALIDAS){
								printf(" Bloco de cartas invalido \n");
							}
					}
						}
			}
			}
		}
	}
	
	void VerificaErroOrdenada(ORD_tpCondRet condicao){

		if( condicao == ORD_CARTAINVALIDA){
			printf( " Nao e a proxima carta da sequencia! \n");

		}else{
			if( condicao == ORD_CARTANULA){
				printf(" A carta que voce esta tentando inserir é nula !\n");
			}else{
				if( condicao == ORD_LISTAORDENADANULA){
					printf(" A Sequencia Ordenada nao existe !\n");
				}else {
					if ( condicao == ORD_POSICAOINVALIDA){
						printf("A posição dessa carta da Sequencia Ordenada nao existe !\n");
					}
				}
			}
		}



	}


	void VerificaErroMovimento(MOV_tpCondRet condicao){
		if( condicao == MOV_CORESIGUAIS){
			printf("Nao pode realizar movimento pois cartas tem cores iguais\n");
		}else {
			if( condicao == MOV_CARTASLIMITE){
				printf(" Nao pode realizar movimento com esse numero de cartas!(Cartas Demais!)\n");
			} else {
				if(condicao == MOV_CARTASINSUFICIENTES){
					printf("Nao pode realizar movimento com esse numero de cartas!( Cartas Insuficientes!)\n");
				}
			}
		}
	}
	