/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN
#define _DEBUG

#ifdef _DEBUG
#include "GENERICO.H"
#include  "CONTA.H"
#include "CESPDIN.H"
#include "IdTipoEspaco.def"
#endif
/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;


     #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

      #endif


/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
#ifdef _DEBUG
	  CNT_CONTAR("Cria Lista");
#endif
      if ( pLista == NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Lista Vazia");
         #endif
         return NULL ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Lista Criada");
#endif
      LimparCabeca( pLista ) ;
	  
	  #ifdef _DEBUG
         CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
	   CNT_CONTAR("Destroi Lista");
#endif
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Esvazia Lista");
#endif
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Elemento da origem existe");
#endif
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */
#ifdef _DEBUG
	  CNT_CONTAR("Elemento da origem não existe");
#endif
      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Insere elemento Antes");
#endif
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Inserir antes um elemento nulo");
#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */
		 #ifdef _DEBUG
		 CNT_CONTAR("Inserir antes Elemento não nulo");
#endif
         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Insere elemento antes com elemento corrente nulo");
#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else {
#ifdef _DEBUG
			 CNT_CONTAR("Insere elemento antes com elemento corrente não nulo");
#endif
            if ( pLista->pElemCorr->pAnt != NULL )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Insere elemento com anterior ao corrente não nulo");
#endif
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else {
				#ifdef _DEBUG
				CNT_CONTAR("Insere elemento com anterior ao corrente nulo");
#endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;
		 #ifdef _DEBUG
		 CNT_CONTAR("Efetua inserção do elemento antes na lista");
#endif
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Insere elemento apos na lista");
#endif
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Insere elemento nulo apos na lista");
#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */
		 #ifdef _DEBUG
		 CNT_CONTAR("Insere elemento nao nulo apos na lista");
#endif
         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Insere elemento apos na lista com elemento corrente nulo");
#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Insere elemento apos na lista com elemento corrente nao nulo");
#endif
            if ( pLista->pElemCorr->pProx != NULL )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Insere elemento apos com o elemento proximo do corrente nao nulo");
#endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				#ifdef _DEBUG
				CNT_CONTAR("Insere elemento apos com elemento proximo do corrente nulo");
#endif
               pLista->pFimLista = pElem ;
            } /* if */
            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
		 #ifdef _DEBUG
              CNT_CONTAR("Efetua insercao do elemento apos na lista");  
#endif
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Exclui Elemento");
#endif
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Exclui elemento corrente nulo");
#endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Exclui elemento corrente não nulo");
#endif
      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Elemento anterior ao corrente nao e nulo"); 
#endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
			 #ifdef _DEBUG
			 CNT_CONTAR("Elemento anterior ao corrente e nulo");
#endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Elemento proximo ao corrente nao e nulo");
#endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Elemento proximo ao corrente e nulo");
#endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */
		 #ifdef _DEBUG
		 CNT_CONTAR("Exclui o elemento corrente");
#endif
      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
		 #ifdef _DEBUG
		 CNT_CONTAR("Inicia obtencao de valor");
#endif
      if ( pLista->pElemCorr == NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Obtem valor de elemento corrente nulo");
#endif
        return NULL ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Efetua obtencao do valor");
#endif
      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Vai ao inicio da lista");
	  #endif
   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Vai ao final da lista");
#endif
   } /* Fim função: LIS  &Ir para o elemento final */



   int pegaNumeroElementos(LIS_tppLista pLista)
   {
	   #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
		 #ifdef _DEBUG
		 CNT_CONTAR("Pega o numero de elementos da lista");
#endif
		return pLista->numElem ;

   }
/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */
		 #ifdef _DEBUG
		 CNT_CONTAR("Avanca elemento corrente da lista");
#endif
         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Avanca elemento corrente nulo");
#endif
            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */
         if ( numElem > 0 )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Numero de elementos a percorre na lista e maior que 0");
#endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Percorre todos os elementos da lista");
#endif
               if ( pElem == NULL )
               {
				   #ifdef _DEBUG
				   CNT_CONTAR("Percorre um elemento nulo da lista");
#endif
                  break ;
               } /* if */
			   #ifdef _DEBUG
			   CNT_CONTAR("Percorre um elemento e ele recebe o valor do proximo");
#endif
               pElem    = pElem->pProx ;
            } /* for */
			#ifdef _DEBUG
			CNT_CONTAR("Para o percorrimento de elementos da lista");
#endif
            if ( pElem != NULL )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Elemento nao e nulo, e vira o corrente da lista");
#endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */
			#ifdef _DEBUG
			CNT_CONTAR("Elemento e nulo, e vira o ultimo da lista");
#endif
            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */
         else if ( numElem < 0 )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Numero de elementos a percorre na lista e menor ou igual a 0");
#endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Percorre o numero de Elementos");
#endif
               if ( pElem == NULL )
               {
				   #ifdef _DEBUG
				   CNT_CONTAR("Elemento corrente e nulo");
#endif
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */
			#ifdef _DEBUG
			 CNT_CONTAR("Elemento recebe seu anterior");
#endif
            if ( pElem != NULL )
            {
				#ifdef _DEBUG
				CNT_CONTAR("Elemento nao e nulo");
#endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */
			#ifdef _DEBUG
			CNT_CONTAR("Elemento corrente recebe o elemento Origem da lista");
#endif
            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */
		 #ifdef _DEBUG
		 CNT_CONTAR("Nao avancou nenhum elemento");
#endif
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {
      tpElemLista * pElem ;
	  #ifdef _DEBUG
	  CNT_CONTAR("Procura Valor");
#endif
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Tenta procurar valor com elemento corrente nulo");
#endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Procura valor com elemento corrente não nulo");
#endif
	  IrInicioLista(pLista);
      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Percorre elementos da lista");
#endif
		  if ( pElem->pValor == pValor || strcmp((char*)pElem->pValor,(char*)pValor) == 0)
         {
			 #ifdef _DEBUG
			 CNT_CONTAR("Valor do elemento percorrido atual é igual ao valor passado");
#endif
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */
	  #ifdef _DEBUG
	  CNT_CONTAR("Não achou valores iguais");
#endif
      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */

  void  ExcluirValor( void * pValor )
{
	
}
#ifdef  _DEBUG
  LIS_tpCondRet LIS_VerificarCabeca( LIS_tppLista  pCabecaParm )
   {

      LIS_tppLista  pLista = NULL ;

      /* Verifica o tipo do espaço */
	  
         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
			return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pLista = ( LIS_tppLista  )( pCabecaParm ) ;

		 if(pLista->pOrigemLista != NULL){

			 if ( pLista->numElem == 0)
            {
				TST_NotificarFalha("Origem existente numa lista com 0 elementos");
               return LIS_CondRetErroEstrutura;
            } /* if */
			 if ( pLista->pElemCorr == NULL )
            {
				TST_NotificarFalha("Elemento corrente nao existe com origem existente");
               return LIS_CondRetErroEstrutura ;
            } /* if */
			 if ( pLista->pFimLista == NULL)
				 {
					 TST_NotificarFalha("Elemento final de lista nao existe com origem existente");
			 return LIS_CondRetErroEstrutura;
		         }
		 }
		 if( pLista->pElemCorr != NULL){
			 if ( pLista->pOrigemLista == NULL )
				 {
					 TST_NotificarFalha("Origem da lista nula com elemento corrente existente");
					 return LIS_CondRetErroEstrutura;
				 }
			 
			 if ( pLista->numElem == 0 ){
				     TST_NotificarFalha("Lista zerada com elemento corrente existente");
					 return LIS_CondRetErroEstrutura;
			 }
		 }
		 if( pLista->pFimLista != NULL){
			 if ( pLista->pOrigemLista == NULL )
				 {
					 TST_NotificarFalha("Origem da lista nulo com fim de lista existente");
					 return LIS_CondRetErroEstrutura;
				 }
			 if ( pLista->numElem == 0 ){
				 TST_NotificarFalha("Lista zerada com fim de lista existente");
					 return LIS_CondRetErroEstrutura;
			   }
			 if ( pLista->pElemCorr == NULL ){
				     TST_NotificarFalha("Elemento corrente nulo com fim de lista existente");
					 return LIS_CondRetErroEstrutura;
			   }
		 }
          /* if */
  
      return LIS_CondRetOK ;
	  
   } /* Fim função: LIS  &Verificar um elemento cabeça */


#endif

#ifdef _DEBUG
  LIS_tpCondRet LIS_VerificarElemento( void * pElementoParm, LIS_tppLista  pCabecaParm )
   {
	   int i = 0;
	   tpElemLista * pElemento    = NULL ;

      /* Verificar se é elemento é estrutural */

         if ( pElementoParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
			return LIS_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pElementoParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
			return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoElemento ,
              CED_ObterTipoEspaco( pElementoParm ) ,
              "Tipo do espaço de dados não é elemento de lista." ) != TST_CondRetOK )
         {
            return LIS_CondRetErroEstrutura ;
         } /* if */

         pElemento     = ( tpElemLista * )( pElementoParm ) ;
		 
		 IrInicioLista(pCabecaParm);
		 if ( LIS_ProcurarValor(pCabecaParm,pElemento) == LIS_CondRetOK){

			 if( TST_CompararPonteiro( pCabecaParm->pElemCorr, pElemento, "Elemento não esta na lista") != TST_CondRetOK){

				 return LIS_CondRetErroEstrutura;
			 } else{

				 TST_NotificarFalha("Elemento pertence a lista Vazia");
				 return LIS_CondRetListaVazia;
			 }

		 }
			 if( pCabecaParm->pElemCorr->pProx != NULL){

			if( TST_CompararPonteiro( pCabecaParm->pElemCorr->pProx, pElemento->pProx, "Elemento proximo nao é o mesmo da lista") != TST_CondRetOK){
					 return LIS_CondRetErroEstrutura;
				 }
		 
			 }

			 if( pCabecaParm->pElemCorr->pAnt != NULL){

		 if( TST_CompararPonteiro( pCabecaParm->pElemCorr->pProx, pElemento->pProx, "Elemento proximo nao é o mesmo da lista") != TST_CondRetOK){
					 return LIS_CondRetErroEstrutura;
				  }
			 }


			 return LIS_CondRetOK;

  }
  

#endif

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificarLista( LIS_tppLista pListaParm ) {

	   LIS_tppLista  pLista = NULL ;

      if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK )
      {
         return LIS_CondRetErroEstrutura ;
      } /* if */

      CED_MarcarEspacoAtivo( pListaParm ) ;

	  pLista = ( LIS_tppLista  ) ( pListaParm ) ;

	  return LIS_VerificarElemento( pLista->pOrigemLista, pLista ) ;
		 }
#endif
#ifdef _DEBUG
   void LIS_Deturpar(LIS_tppLista lista,int TipoDeturpacao){
	   LIS_tppLista listaDeturpada;


	   listaDeturpada = (LIS_tppLista) (lista);
	   switch(TipoDeturpacao){



	   case 1 :   // Elimina ponteiro de corrente

		   listaDeturpada->pElemCorr = NULL;
		   CED_Free(listaDeturpada->pElemCorr);
		   break;

	   case 2: // Anula numero de elementos da lista

		   listaDeturpada->numElem = 0;

	   case 3: // Anula cabeca da lista

		  IrInicioLista(listaDeturpada);
		  lista->numElem = 0;
		  lista->pElemCorr = NULL;
		  lista->pFimLista = NULL;
		  lista->pOrigemLista = NULL;
		  break;
	  
	   default :
		   printf("Comando digitado invalido");
		   break;
	   }
   
	   
   }
#endif
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
	   #ifdef _DEBUG
	   CNT_CONTAR("Liberar elemento");
#endif
      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Exclui Valor");
#endif
        pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Não possui valor");
#endif
      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {
      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	  #ifdef _DEBUG
	    CNT_CONTAR("Criar elemento");
#endif
      if ( pElem == NULL )
      {
		  #ifdef _DEBUG
		  CNT_CONTAR("Elemento não alocado(nulo)");
#endif
         return NULL ;
      } /* if */
	  #ifdef _DEBUG
	  CNT_CONTAR("Elemento alocado");
#endif
      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

	    #ifdef _DEBUG
        CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento ) ;
    #endif

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
	   CNT_CONTAR("Limpa Cabeca");
#endif
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;
   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

