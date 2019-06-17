#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "ESPVAZIOS.H"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_CAMPOSVAZIOS_CMD         [ ] = "=CriaEspacosVazios"     ;
static const char DESTROI_CAMPOSVAZIOS_CMD      [ ] = "=DestroiEspacosVazios"  ;
static const char INSERE_CARTADOTOPO_CMD      [ ] = "=InsereNoEspacoVazio"  ;
static const char ANALISA_CARTADOTOPO_CMD      [ ] = "=AnalisaCartaDoEspacoVazio"  ;
static const char REMOVE_CARTADOTOPO_CMD      [ ] = "=RemoveDoEspacoVazio"  ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_ORDENADA   10
#define DIM_VALOR     100

CamposVaziosPtr   vtVazios[ DIM_VT_ORDENADA ] ;
CartaPtr      vtCartas[ DIM_VT_ORDENADA];

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxVazio( int inxVazio , int Modo ) ;

   static int ValidarInxCarta( int inxCarta , int Modo ) ;


   
   void DestruirValor( void * pValor )
   {


   }

     int ValidarInxCarta( int inxCarta , int Modo )
   {

      if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_ORDENADA ))
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


   int ValidarInxVazio( int inxVazio , int Modo )
   {

      if ( ( inxVazio <  0 )
        || ( inxVazio >= DIM_VT_ORDENADA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
		  if ( vtVazios[ inxVazio ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVazios[ inxVazio ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   }



   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	   LIS_tppLista lista = LIS_CriarLista(DestruirValor);
	   CartaPtr carta = NULL;
      int inxVazio  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxCarta = - 1 ;

	  VAZ_tpCondRet condicao;
	  int posicao = 0;

      char   StringDado[  DIM_VALOR ] ;

      int ValEsp = -1 ;

      int i ;
	  int numElem = -1 ;
	  
      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_ORDENADA ; i++ )
            {
               vtVazios[ i ] = NULL ;
			   vtCartas [ i ] = NULL;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarSequenciaOrdenada */

         else if ( strcmp( ComandoTeste , CRIAR_CAMPOSVAZIOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
				&inxVazio , &CondRetEsp) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxVazio( inxVazio , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if(CondRetEsp == 1){
			vtVazios[inxVazio] = (CamposVaziosPtr)malloc(sizeof(struct CamposVazios));
			condicao = VAZ_CriaEspacosVazios(vtVazios[inxVazio]);
			return TST_CompararInt(CondRetEsp,condicao, "Nao criou Espaco Vazio");
			}
			if(CondRetEsp == 0){
				vtVazios[inxVazio] = NULL;
			condicao = VAZ_CriaEspacosVazios(vtVazios[inxVazio]);
			return TST_CompararInt(CondRetEsp,condicao, "Criou Espaco Vazio mas nao deveria");

			}
            

         } /* fim ativa: Testar CriarLista */

		 // Destroi campos vazios
		 else if ( strcmp( ComandoTeste , DESTROI_CAMPOSVAZIOS_CMD) == 0 )
         {

		   numLidos = LER_LerParametros( "i" ,
                       &inxVazio ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxVazio( inxVazio , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			VAZ_DestroiEspacosVazios(vtVazios[inxVazio]);
			vtVazios[inxVazio] = NULL;

			return TST_CondRetOK;

		 }
		 // Insere elemento no Espaco Vazio
		  else if ( strcmp( ComandoTeste , INSERE_CARTADOTOPO_CMD ) == 0 )
         {
			
			 numLidos = LER_LerParametros( "iii" , &inxVazio,
				&inxCarta, &CondRetEsp) ;
			
			
            if ( ( numLidos != 3 )
				|| ( !ValidarInxVazio(inxVazio, NAO_VAZIO)) )
            {
               return TST_CondRetParm ;
            } /* if */

			if(CondRetEsp == 0){
				vtVazios[inxVazio] = NULL;
				BAR_CriaCarta(K,OUROS,VERMELHO,&vtCartas[inxCarta]);
				condicao = VAZ_InsereNoEspacoVazio(vtVazios[inxVazio],vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp, condicao, "Nao deveria ter inserido pois Espaco Vazio é nulo");
			}
			if( CondRetEsp == 3){
				vtCartas[inxCarta] = NULL;
                   condicao = VAZ_InsereNoEspacoVazio(vtVazios[inxVazio],vtCartas[inxCarta]);
				   return TST_CompararInt(CondRetEsp, condicao, "Nao deveria ter inserido pois nao existe carta");
			}
			if( CondRetEsp == 1){
				BAR_CriaCarta(K,OUROS,VERMELHO,&vtCartas[inxCarta]);
		       condicao = VAZ_InsereNoEspacoVazio(vtVazios[inxVazio],vtCartas[inxCarta]);
			   return TST_CompararInt(CondRetEsp, condicao, "Nao inseriu");

			}
		if( CondRetEsp == 2){
				BAR_CriaCarta(K,OUROS,VERMELHO,&vtCartas[inxCarta]);
		       condicao = VAZ_InsereNoEspacoVazio(vtVazios[inxVazio],vtCartas[inxCarta]);
			   return TST_CompararInt(CondRetEsp, condicao, "Inseriu com a lista cheia !");
		}
			// Remove carta do Espaco Vazio
		 }  else if ( strcmp( ComandoTeste ,REMOVE_CARTADOTOPO_CMD ) == 0 )
         {
			
			 numLidos = LER_LerParametros( "iii" , &inxVazio,
				 &posicao, &CondRetEsp) ;
			
			
            if ( ( numLidos != 3 )
				|| ( !ValidarInxVazio(inxVazio, NAO_VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */

			if(CondRetEsp == 0){
				vtVazios[inxVazio] = NULL;
				condicao  = VAZ_RemoveDoEspacoVazio(vtVazios[inxVazio],posicao);
				return TST_CompararInt(CondRetEsp, condicao, "Removeu de um espaco Vazio nulo");
			}

			if( CondRetEsp == 4){
			condicao = VAZ_RemoveDoEspacoVazio(vtVazios[inxVazio],posicao);
			return TST_CompararInt(CondRetEsp, condicao, "Removeu com uma posicao Inexistente");
			}
			if(CondRetEsp == 1){
			condicao = 	VAZ_RemoveDoEspacoVazio(vtVazios[inxVazio],posicao);
			return TST_CompararInt(CondRetEsp, condicao, "Nao removeu a carta");
			
		 }
			if(CondRetEsp == 3){
				condicao = 	VAZ_RemoveDoEspacoVazio(vtVazios[inxVazio],posicao);
			return TST_CompararInt(CondRetEsp, condicao, "Removeu de uma posicao que nao possui carta");
		 }
			// Analisa Carta do Espaco Vazio
		  }  else if ( strcmp( ComandoTeste ,ANALISA_CARTADOTOPO_CMD ) == 0 )
			  {
				  numLidos = LER_LerParametros( "iii" , &inxVazio,
				 &posicao, &CondRetEsp) ;
			
			
            if ( ( numLidos != 3 )
				|| ( !ValidarInxVazio(inxVazio, NAO_VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */

			if(CondRetEsp == 4){
				condicao = 	VAZ_AnalisaCartaDoEspacoVazio(vtVazios[inxVazio],posicao,&vtCartas[inxCarta]);
			return TST_CompararInt(CondRetEsp, condicao, "Removeu carta de uma posicao inexistente!");

		  }
			if(CondRetEsp == 0){
				vtVazios[inxVazio] = NULL;
				condicao  = VAZ_AnalisaCartaDoEspacoVazio(vtVazios[inxVazio],posicao,&vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp, condicao, "Removeu de um espaco Vazio nulo");
			}

				if(CondRetEsp == 3){
				condicao = 	VAZ_AnalisaCartaDoEspacoVazio(vtVazios[inxVazio],posicao,&vtCartas[inxCarta]);
			return TST_CompararInt(CondRetEsp, condicao, "Pegou de uma posicao que nao possui carta");
		 }

				if(CondRetEsp == 1){
			condicao = 	VAZ_AnalisaCartaDoEspacoVazio(vtVazios[inxVazio],posicao,&vtCartas[inxCarta]);
			return TST_CompararInt(CondRetEsp, condicao, "Nao pegou a carta");
			
		 }

		  }
		 return TST_CondRetNaoConhec;
		 }