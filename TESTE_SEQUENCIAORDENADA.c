#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "SEQUENCIAORDENADA.H"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_SEQUENCIAORDENADA_CMD         [ ] = "=CriaSequenciaOrdenada"     ;
static const char DESTROI_SEQUENCIAORDENADA_CMD      [ ] = "=DestroiSequenciaOrdenada"  ;
static const char INSERE_CARTANAORDENADA_CMD      [ ] = "=InsereCartaNaOrdenada"  ;
static const char ANALISA_CARTANAORDENADA_CMD      [ ] = "=AnalisaCartaNaOrdenada"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_ORDENADA   10
#define DIM_VALOR     100

OrdenadaPtr   vtOrdenadas[ DIM_VT_ORDENADA ] ;
CartaPtr      vtCartas[ DIM_VT_ORDENADA];


   static void DestruirValor( void * pValor ) ;

   static int ValidarInxOrdenada( int inxOrdenada , int Modo ) ;

   static int ValidarInxCarta( int inxCarta , int Modo ) ;

   static int ValidarInxCampo( int inxCampo , int Modo ) ;

   
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


   int ValidarInxOrdenada( int inxOrdenada , int Modo )
   {

      if ( ( inxOrdenada <  0 )
        || ( inxOrdenada >= DIM_VT_ORDENADA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtOrdenadas[ inxOrdenada ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtOrdenadas[ inxOrdenada ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   }

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	   LIS_tppLista baralho = LIS_CriarLista(DestruirValor);
      int inxOrdenada  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  posicaoBaralho = -1,
		  posicaoOrdenada = -1,
		  inxCarta = - 1 ;

	  ORD_tpCondRet condicao;

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
               vtOrdenadas[ i ] = NULL ;
			   vtCartas [ i ] = NULL;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarSequenciaOrdenada */

         else if ( strcmp( ComandoTeste , CRIAR_SEQUENCIAORDENADA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
				&inxOrdenada, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxOrdenada( inxOrdenada , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if( CondRetEsp == 0){
				 vtOrdenadas[inxOrdenada] == NULL;
				 condicao = ORD_CriaSequenciaOrdenada(vtOrdenadas[ inxOrdenada ] );
				 return TST_CompararInt(CondRetEsp,condicao, "Criou a Sequencia Ordenada mas nao deveria");
			}
			if(CondRetEsp == 2){
            vtOrdenadas[inxOrdenada] = (OrdenadaPtr)malloc(sizeof(struct Ordenada));
				condicao = ORD_CriaSequenciaOrdenada(vtOrdenadas[ inxOrdenada ] );
				 return TST_CompararInt(CondRetEsp,condicao, "Nao criou a Sequencia Ordenada");

			}

         } 
		 // Destroi Sequencia Ordenada
		 else if ( strcmp( ComandoTeste , DESTROI_SEQUENCIAORDENADA_CMD) == 0 )
         {

		   numLidos = LER_LerParametros( "i" ,
			   &inxOrdenada ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			ORD_DestroiSequenciaOrdenada(vtOrdenadas[inxOrdenada]);
			vtOrdenadas[inxOrdenada] = NULL;

			return TST_CondRetOK;

		 }
		 // Insere carta na Sequencia Ordenada
		 else if ( strcmp( ComandoTeste , INSERE_CARTANAORDENADA_CMD) == 0 )
         {

		   numLidos = LER_LerParametros( "iiii" ,
			   &inxOrdenada, &inxCarta, &posicaoBaralho, &CondRetEsp) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if( CondRetEsp == 0){
				vtOrdenadas[inxOrdenada] = NULL;
			condicao = ORD_InsereCartaNaOrdenada(vtOrdenadas[inxOrdenada], vtCartas[inxCarta]);

			return TST_CompararInt(CondRetEsp, condicao, "Inseriu carta em uma Sequencia Ordenada inexistente!");
			}
			if( CondRetEsp == 2){

				BAR_CriaBaralho(baralho,52);
				IrInicioLista(baralho);
				LIS_AvancarElementoCorrente(baralho,posicaoBaralho);
				vtCartas[inxCarta] = (CartaPtr)LIS_ObterValor(baralho);
			condicao = ORD_InsereCartaNaOrdenada(vtOrdenadas[inxOrdenada], vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp, condicao, "Não inseriu a carta!");

			}
			if( CondRetEsp == 1){
				vtCartas[inxCarta] = NULL;
				condicao = ORD_InsereCartaNaOrdenada(vtOrdenadas[inxOrdenada], vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp, condicao, "Inseriu uma carta nula!");
		 }
			if( CondRetEsp == 4){
				BAR_CriaBaralho(baralho,52);
				IrInicioLista(baralho);
				LIS_AvancarElementoCorrente(baralho,posicaoBaralho);
				vtCartas[inxCarta] = (CartaPtr)LIS_ObterValor(baralho);
			condicao = ORD_InsereCartaNaOrdenada(vtOrdenadas[inxOrdenada], vtCartas[inxCarta]);
				return TST_CompararInt(CondRetEsp, condicao, "Inseriu carta mas não era a proxima da Ordenada!");
			}
		 }
		 // Analisa carta do topo da Ordenada
		  else if ( strcmp( ComandoTeste , ANALISA_CARTANAORDENADA_CMD) == 0 )
         {

		   numLidos = LER_LerParametros( "iiii" ,
			   &inxOrdenada, &inxCarta, &posicaoOrdenada,  &CondRetEsp) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxOrdenada( inxOrdenada , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if( CondRetEsp == 0){
				vtOrdenadas[inxOrdenada] = NULL;
				condicao = ORD_AnalisaCartadoTopo(vtOrdenadas[inxOrdenada], &vtCartas[inxCarta], posicaoOrdenada);
               return TST_CompararInt(CondRetEsp, condicao, "Analisou carta em uma Sequencia Ordenada inexistente!");
			}
			if( CondRetEsp == 3){
			condicao = ORD_AnalisaCartadoTopo(vtOrdenadas[inxOrdenada], &vtCartas[inxCarta],posicaoOrdenada);
				return TST_CompararInt(CondRetEsp, condicao, "Pegou uma carta de uma posicao que nao existe!");

			}
			if( CondRetEsp == 2){
				condicao = ORD_AnalisaCartadoTopo(vtOrdenadas[inxOrdenada], &vtCartas[inxCarta],posicaoOrdenada);
				return TST_CompararInt(CondRetEsp, condicao, "Nao pegou a carta");
		 }
			
		 }
		 return TST_CondRetNaoConhec;
		
			}