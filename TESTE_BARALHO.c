#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"
#include "BARALHO.H"




static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIABARALHO_CMD         [ ] = "=CriaBaralho"     ;
static const char DESTROI_BARALHO_CMD            [ ] = "=DestroiBaralho"   ;
static const char CRIACARTA_CMD             [ ] = "=CriaCarta"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_CARTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;
CartaPtr       vtCartas[ DIM_VT_CARTA];
int            contador[DIM_VT_CARTA];


   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

   static int ValidarInxCarta ( int inxCarta, int Modo) ;



     void DestruirValor( void * pValor )
   {

   }

	  int ValidarInxCarta( int inxCarta , int Modo )
   {

      if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_CARTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtCartas[ inxCarta ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtCartas[ inxCarta ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

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
	   BAR_tpCondRet condicao = BAR_BARALHONULO;
	   CartaPtr carta = NULL, cartaCompara = NULL;

      int inxLista  = -1 ,
          numLidos   = -1 ,
		  inxcontador = -1 , 
          CondRetEsp = -1  ,
		  inxCarta = -1,
		  nCartas = -1;

       int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;


      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
			   vtCartas[ i ] = NULL;
			   contador [ i ] = NULL;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar ECria Baralho */

         else if ( strcmp( ComandoTeste , CRIABARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
				&inxLista , &nCartas, &CondRetEsp) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			if(CondRetEsp == 0){
			vtListas[inxLista] = LIS_CriarLista(DestruirValor);
			condicao = BAR_CriaBaralho(vtListas[ inxLista], nCartas);
			return TST_CompararInt(CondRetEsp,condicao, "Nao criou baralho certo"); 
			}
			if(CondRetEsp == 1){
				vtListas[inxLista] = NULL;
				condicao = BAR_CriaBaralho(vtListas[ inxLista], nCartas);
			return TST_CompararInt(CondRetEsp,condicao, "Criou baralho mas nao deveria");
		 }
		 }
		//  Cria carta
		 else if ( strcmp( ComandoTeste , CRIACARTA_CMD ) == 0 )
         {
			 numLidos = LER_LerParametros( "ii" , &inxCarta,
				&CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxCarta( inxCarta , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			if( CondRetEsp == 2){
				condicao = BAR_CriaCarta(K, OUROS, VERMELHO,&vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp,condicao, "Nao criou cartas !");
			
		 }
			}	 
		 // Destroi baralho
         else if ( strcmp( ComandoTeste , DESTROI_BARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			BAR_DestroiBaralho(vtListas[inxLista]);
			vtListas[inxLista] = NULL;

				return TST_CondRetOK;
		 
	 }
		  return TST_CondRetNaoConhec;

		 }
		 