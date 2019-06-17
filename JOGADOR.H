#ifndef __JOGADOR_h__
#define __JOGADOR_h__




struct Jogador {
	char  nome[50];
	int RecordeMovimentos;
	int UltimoNumerodeMovimentos;

};

typedef struct Jogador * JogadorPtr;

int JOG_VerificaNovoRecorde(JogadorPtr j, int nMovimentos);

void JOG_CriaJogador(JogadorPtr j);

void JOG_RecebeNovoNumerodeMovimentos(JogadorPtr j, int nMovimentos);













#endif /* __JOGADOR_h_ */





