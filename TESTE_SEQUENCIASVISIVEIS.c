#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"
#include "SEQUENCIASVISIVEIS.H"

#include    "Lista.h"



static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char FORMACAMPO_CMD         [ ] = "=FormaCampo"     ;
static const char DESTROI_CAMPO_CMD            [ ] = "=DestroiCampo"   ;
static const char ANALISA_CARTA_DO_TOPO_CMD             [ ] = "=AnalisaCartaDoTopo"   ;
static const char RETIRA_CARTA_DO_TOPO_CMD             [ ] = "=RetiraCartaDoTopo"   ;
static const char INSERE_CARTA_DO_TOPO_CMD             [ ] = "=InsereCartaNoTopo"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CAMPO   10
#define DIM_VT_CARTA   10
#define DIM_VALOR     100

CampoPtr   vtCampos[ DIM_VT_CAMPO ] ;
CartaPtr       vtCartas[ DIM_VT_CARTA];


   static void DestruirValor( void * pValor ) ;

   static int ValidarInxCampo( int inxCampo , int Modo ) ;

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

	    int ValidarInxCampo( int inxCampo , int Modo )
   {

      if ( ( inxCampo <  0 )
        || ( inxCampo >= DIM_VT_CAMPO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtCampos[ inxCampo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtCampos[ inxCampo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   }

     TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   CAM_tpCondRet condicao = CAM_CAMPONULO;
	   CartaPtr carta = NULL, cartaCompara = NULL;
	   LIS_tppLista lista ;
	   LIS_tppLista listaCorrente = LIS_CriarLista(DestruirValor);

      int inxCampo  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ,
		  inxCarta = -1,
		  coluna = -1,
		  nCartas = -1;

      char   StringDado[  DIM_VALOR ] ;
      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;


      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CAMPO ; i++ )
            {
               vtCampos[ i ] = NULL ;
			   vtCartas[ i ] = NULL;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar fORMA Campo */

		 else if ( strcmp( ComandoTeste , FORMACAMPO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
				&inxCampo, &nCartas, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxCampo( inxCampo , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			if(CondRetEsp == 0){
			vtCampos[inxCampo] = (CampoPtr)malloc(sizeof(struct Campo));
			lista = LIS_CriarLista(DestruirValor);
			BAR_CriaBaralho(lista,nCartas);
			condicao = CAM_FormaCampo(&vtCampos[inxCampo],lista);
			return TST_CompararInt(CondRetEsp, condicao, "Nao criou o campo");
			}
			if(CondRetEsp == 2){
				vtCampos[inxCampo] = NULL;
				lista = LIS_CriarLista(DestruirValor);
				BAR_CriaBaralho(lista,nCartas);
				condicao = CAM_FormaCampo(&vtCampos[inxCampo],lista);
			return TST_CompararInt(CondRetEsp, condicao, "Criou o campo nulo mas nao deveria");
			}
			if(CondRetEsp == 1){
				vtCampos[inxCampo] = (CampoPtr)malloc(sizeof(struct Campo));
				lista = NULL;
					condicao = CAM_FormaCampo(&vtCampos[inxCampo],lista);
			return TST_CompararInt(CondRetEsp, condicao, "Criou o campo com um baralho nulo mas nao deveria");
			}
		 }
		 
		 // Insere carta no Campo
		
		 else if ( strcmp( ComandoTeste , INSERE_CARTA_DO_TOPO_CMD) == 0 )
         {
			
            numLidos = LER_LerParametros( "iiii" ,
				&inxCampo, &inxCarta , &coluna , &CondRetEsp) ;
			
			
            if ( ( numLidos != 4 )
				|| ( !ValidarInxCampo(inxCampo, NAO_VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */
				if(CondRetEsp == 3){
					condicao = CAM_InsereCartaNoTopo(vtCampos[inxCampo],vtCartas[inxCarta],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Inseriu numa posicao invalida!"); 
				}

				if(CondRetEsp == 2){
					condicao = CAM_InsereCartaNoTopo(NULL,vtCartas[inxCarta],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Inseriu em um campo Nulo"); 
				}
				if(CondRetEsp == 4){
					condicao = CAM_InsereCartaNoTopo(vtCampos[inxCampo],NULL,coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Inseriu uma carta Invalida"); 
				}
                if(CondRetEsp == 6){
					BAR_CriaCarta(DEZ,PAUS,PRETO,&vtCartas[inxCarta]);
					condicao = CAM_InsereCartaNoTopo(vtCampos[inxCampo],vtCartas[inxCarta],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Nao inseriu a carta"); 

				}
		 }

		 // Destroi Campo
		 else if ( strcmp( ComandoTeste , DESTROI_CAMPO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxCampo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxCampo( inxCampo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			CAM_DestroiCampo(vtCampos[inxCampo]);
			vtCampos[inxCampo] = NULL;

				return TST_CondRetOK;
		 }
		 // Analisa carta do topo
		 else if ( strcmp( ComandoTeste , ANALISA_CARTA_DO_TOPO_CMD) == 0 )
         {
			
            numLidos = LER_LerParametros( "iii" ,
				&inxCampo, &coluna , &CondRetEsp) ;
			
			
            if ( ( numLidos != 3 )
				|| ( !ValidarInxCampo(inxCampo, NAO_VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */
				if(CondRetEsp == 3){
					condicao = CAM_AnalisaCartaDoTopo(&vtCartas[inxCarta],vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Analisou uma carta numa posicao invalida!"); 
				}

				if(CondRetEsp == 2){
					condicao = CAM_AnalisaCartaDoTopo(&vtCartas[inxCarta],NULL,coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Analisou uma carta de um campo Nulo"); 
				}
				if(CondRetEsp == 5){
					condicao = CAM_AnalisaCartaDoTopo(&vtCartas[inxCarta],vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Carta do topo nao é nula!"); 
				}
                if(CondRetEsp == 6){
					condicao = CAM_AnalisaCartaDoTopo(&vtCartas[inxCarta],vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Nao analisou a carta"); 

				}
		 }
				// Remove uma carta do topo do Campo
				 else if ( strcmp( ComandoTeste , RETIRA_CARTA_DO_TOPO_CMD) == 0 )
         {
			
            numLidos = LER_LerParametros( "iii" ,
				&inxCampo, &coluna , &CondRetEsp) ;
			
			
            if ( ( numLidos != 3 )
				|| ( !ValidarInxCampo(inxCampo, NAO_VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */
				if(CondRetEsp == 3){
					condicao = CAM_RetiraCartaDoTopo(vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Removeu uma carta numa posicao invalida!"); 
				}

				if(CondRetEsp == 2){
					condicao = CAM_RetiraCartaDoTopo(NULL,coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Removeu uma carta de um campo Nulo"); 
				}
				if(CondRetEsp == 5){
					condicao = CAM_RetiraCartaDoTopo(vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Removeu a carta do top , mas deveria ser nula!"); 
				}
                if(CondRetEsp == 6){
					condicao = CAM_RetiraCartaDoTopo(vtCampos[inxCampo],coluna);
								return TST_CompararInt(CondRetEsp, condicao, "Nao removeu a carta"); 

				                   }
				}
		 return TST_CondRetNaoConhec;
	 }

