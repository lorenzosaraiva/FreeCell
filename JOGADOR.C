#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include <string.h>
#include "JOGADOR.H"


void JOG_CriaJogador(JogadorPtr j){
	j->RecordeMovimentos = 0;
	j->UltimoNumerodeMovimentos = 0;
}


void JOG_RecebeNovoNumerodeMovimentos(JogadorPtr j, int nMovimentos){
	j->UltimoNumerodeMovimentos = nMovimentos;
}


int JOG_VerificaNovoRecorde(JogadorPtr j){
	if( j->RecordeMovimentos > j->UltimoNumerodeMovimentos){
		j->RecordeMovimentos = j->UltimoNumerodeMovimentos;
		return 1;
	}
	return 0;
}