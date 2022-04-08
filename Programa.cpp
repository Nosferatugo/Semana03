#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define ARQ_DIR "inst"
#define VETOR_TAM 200000
#define ARQVETOR_TAM 16



typedef int vetor[ VETOR_TAM ];
typedef char arqvetor[ ARQVETOR_TAM ][ 256 ];


void countingSort(vetor vet, int tam, int RANGE);
void radixSort(vetor vet, int tam);



long long get_ms();

int ler_amostras_vet( char* arq, vetor vet, int* tam );
void imprimir_amostras_vet( vetor vet, int tam );

void carrega_nomearquivo( char* arqnome, int i, int vettam );
void carrega_nomearquivo_vet( arqvetor arqvet, int* cont );
void lista_nomearquivo_vet( arqvetor arqvet, int tam );
void carrega_arqpath( char* path, char* arqnome, char* basedir );

void menu();
void menu_ordenamento();

int main() {
	vetor vet;	
	int tam;
	int tam2;
	long long ms1, ms2;
	
	int n=sizeof(vet)/sizeof(vet[0]);
	int RANGE;
	
	arqvetor arqvet;
	int arqvet_tam;
	int leu;
	
	char op = '1';
	char op2 = '0';
	int arqnum = 0;
	
	char path[ 256 ];
	
	carrega_nomearquivo_vet( arqvet, &arqvet_tam );
	do {					
		menu();
		printf( "\nInforme a sua escolha: " );		
		
		fflush( stdin );
		fflush( stdout );
		op = getchar();				
				
		switch( op ) {
			case '1':
			lista_nomearquivo_vet( arqvet, arqvet_tam );				
				printf( "\nInforme o numero do arquivo da amostra desejada: " );
				scanf( "%d", &arqnum );
								
				if ( arqnum < 1 || arqnum > arqvet_tam ) {
					printf( "\nEste arquivo nao consta na lista." );
				} else {				
					carrega_arqpath( path, arqvet[ arqnum-1 ], ARQ_DIR );
					leu = ler_amostras_vet( path, vet, &tam );
					if ( leu ) {
						printf( "\nAs Amostras foram carregadas com sucesso!" );
					} else {
						printf( "\nHouve uma falha na leitura do arquivo: %s", path );
					}	
				}
				break;	
				
			case '2':
				imprimir_amostras_vet( vet, tam );
			    break;
			    
			case '3':
			menu_ordenamento();
				printf( "\nInforme uma opcao: " );
				
				fflush( stdin );
				fflush( stdout );
				op2 = getchar();
				
				switch( op2 ) {
					case '1':
						ms1 = get_ms();					
						//////////////////////////////////////////////////////////////////////////////
						
						countingSort(vet, tam, RANGE);
						imprimir_amostras_vet( vet, tam );	
																			
						ms2 = get_ms();
						printf( "\nFoi possivel ordenar o vetor com sucesso em: %lldms", (ms2-ms1) );
						menu();
						break;
					case '2':
						ms1 = get_ms();
						///////////////////////////////////////////////////////////////////////////////
						
						radixSort(vet, tam);
						imprimir_amostras_vet( vet, tam );
						
															
						ms2 = get_ms();
						printf( "\nFoi possivel ordenar o vetor com sucesso em: %lldms", (ms2-ms1) );
						break;	
					case '3': 
						break;
					default:
						printf( "\nEsta Opcao � invalida!" );
				}	
				
				if ( op2 != '3' ) {
					printf( "\nPrecione enter para continuar..." );
					fflush( stdin );
					fflush( stdout );
					getc( stdin );
				}							
				break;	
										
			case '0':
				printf( "\nPrecione enter para sair...\n" );
				break;
			default:
				printf( "\nOpcao invalida!" );
		}
			
		if ( op != '0' && op != '4' ) {
			if ( op != '0' )
				printf( "\nPrecione a tecla enter para finalizar..." );
			fflush( stdin );
			fflush( stdout );
			getc( stdin );				
		}
		
	} while( op != '0' );
		
	
	return 0;
}

void menu() {
	printf( "\n|*********** MENU DE ACOES ************|" );
	printf( "\n|  (1) Carregar as amostras disponiveis" );
	printf( "\n|  (2) Listar o vetor" );
	printf( "\n|  (3) Ordenar o vetor" );
	printf( "\n|  (0) Sair" );
	printf( "\n|************************************|\n" );		
}

void menu_ordenamento() {
	printf( "\n****** APLICAR ORDENACAO ******" );
	printf( "\n                         " );
	printf( "\n  (1) Aplicar o Algoritimo Counting Sort     " );
	printf( "\n  (2) Aplicar o Algoritimo Radix Sort     " );
	printf( "\n  (3) Voltar             " );
	printf( "\n                        " );
	printf( "\n*************************\n" );
}

void carrega_arqpath( char* path, char* nomearquivo, char* basedir ) {
	strcpy( path, basedir );
	strcat( path, "/" );
	strcat( path, nomearquivo );
}

void lista_nomearquivo_vet( arqvetor arqvet, int tam ) {	
	int i;
	
	printf( "\n| *** Relacao de amostras Disponiveis *** |\n\n" );
	for( i = 0; i < tam; i++ )
		printf( " (%d) %s\n", (i+1), arqvet[ i ] );
	printf( "\n" );
}

void carrega_nomearquivo_vet( arqvetor arqvet, int* cont ) {
	int i, j; 
		
	*cont = 0;
	for( i = 1; i <= 4; i++ )
		for( j = 1000; j <= 100000; j*=10 )
			carrega_nomearquivo( arqvet[ (*cont)++ ], i, j );			
}

void carrega_nomearquivo( char* nomearquivo, int i, int vettam ) {
	sprintf( nomearquivo, "%s%d%s%d%s", "num.", vettam, ".", i, ".in" );	
}

int ler_amostras_vet( char* nomearquivo, vetor vet, int* tam ) {
	int i;
	FILE* arq;
	char linha[ 10 ];
	
	arq = fopen( nomearquivo, "r" );
	if ( arq == NULL )
		return 0;		
		
	fgets( linha, sizeof( linha ), arq );
	*tam = atoi( linha );
	
	for( i = 0; i < *tam; i++ ) {
		fgets( linha, sizeof( linha ), arq );
		vet[ i ] = atoi( linha );		
	}
	
	fclose( arq );
	
	return 1;
}

void imprimir_amostras_vet( vetor vet, int tam ) {
	int i;
	
	printf( "\nVetor=\n" );
	for( i = 0; i < tam; i++ ) {
		printf( "%11d", vet[ i ] ); 
		if ( (i+1) % 7 == 0 )
			printf( "\n" );
	}
	printf( "\n" );
}



//Aplica��o do Algoritmo Counting Sort

void countingSort(int arr[],int n,int RANGE){
    int count[RANGE]={0};
    int i;
    int out[n];
    
    
    for(i=0;i<n;i++)
    ++count[arr[i]];
    
    for(i=1;i<RANGE;i++)
    count[i]+=count[i-1];
    
   
    
    for(i=n-1;i>=0;i--){
        out[count[arr[i]]-1]=arr[i];
        --count[arr[i]];
    }
    
    for(i=0;i<n;i++)
    arr[i]=out[i];
  
    
    
}




long long get_ms() {
	struct timeval t;
	gettimeofday( &t, NULL );	
	return ( ((long long)(t.tv_sec) * 1000) ) + ( t.tv_usec/1000 );
}

//Aplica��o do Algoritmo Radix Sort


void radixSort(int *vet, int n) {
	int i, exp = 1, m = 0, bucket[n], temp[n];

	for(i = 0; i < n; i++) {
		if(vet[i] > m) {
			m = vet[i];
		}
	}

	while((m/exp) > 0) {
		for (i = 0; i < n; i++) {
			bucket[i] = 0;
		}
		for(i = 0; i < n; i++) {
			bucket[(vet[i] / exp) % 10]++;
		}
		for(i = 1; i < n; i++) {
			bucket[i] += bucket[i-1];
		}
		for(i = (n - 1); i >= 0; i--) {
			temp[--bucket[(vet[i] / exp) % 10]] = vet[i];
		}
		for(i = 0; i < n; i++) {
			vet[i] = temp[i];
		}
		exp *= 10;
	}
}


