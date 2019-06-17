#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include "EMBARALHAMENTO.H"

#include    "Lista.h"



static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char EMBARALHA_CMD         [ ] = "=Embaralha"     ;
static const char DESTROI_BARALHOEMBARALHADO_CMD            [ ] = "=DestroiBaralhoEmbaralhado"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;


   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;



     void DestruirValor( void * pValor )
   {

   }

	  int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   }

     TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   EMB_tpCondRet condicao = EMB_EMBARALHADONULO;
	   CartaPtr carta = NULL;

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ,
		  nElem = -1;


      char   StringDado[  DIM_VALOR ] ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar Embaralha */

         else if ( strcmp( ComandoTeste , EMBARALHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
				&inxLista, &nElem, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			if( CondRetEsp == 0){
			vtListas[inxLista] = LIS_CriarLista(DestruirValor);
			BAR_CriaBaralho(vtListas[inxLista], nElem);
			condicao = EMB_Embaralha( &vtListas[ inxLista ]);
			return TST_CompararInt(CondRetEsp,condicao, "Nao Embaralhou");
			}
			if( CondRetEsp == 1){
				vtListas[inxLista] = NULL;
                 condicao = EMB_Embaralha( &vtListas[ inxLista ]);
				 return TST_CompararInt(CondRetEsp,condicao, "Embaralhou mas nao deveria(Lista Nula)");
		 }
		 }
		 // Testa destruir uma baralho embaralhado
		   else if ( strcmp( ComandoTeste , DESTROI_BARALHOEMBARALHADO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			EMB_DestroiBaralhoEmbaralhado( vtListas[inxLista]);
			vtListas[inxLista] = NULL;

			return TST_CondRetOK;
		  }
		
		 return TST_CondRetNaoConhec;
	 }

