#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int destino=0, origem=0,vertices=0;
int custo=0, *custos = NULL; 

void menu_aluno(void);
void cabecalho(void);
void adicionar(void);
void grafoManual();
void adicionalManual(void);
void procurar(void);
void dijkstra(int vertices,int origem,int destino,int *custos);

int main(int argc, char **argv) {
   	int opt=-1;
	setlocale(LC_ALL,"Portuguese");
	do{
		system("cls");
		system("color 07");
		menu_aluno();
		cabecalho();
		scanf("%d", &opt);
		
		switch(opt){
			case 1:
				adicionar();
				system("pause"); 		
			break;
			
			case 2:
				grafoManual();
			break;	
			
			case 3:
				if(vertices!=0||vertices==5){
					procurar();
				}else{
					system("cls");
					system("color 4f");
					printf("Erro: Grafo inexistente.\n\n");
				}
				system("pause");
			break;
		}
	}while(opt!=0);
	printf("\nAlgoritimo de Dijkstra finalizando...\n\n");
	free(custos);
	system("pause");
	return(0);	
}

void menu_aluno(void){	
	printf("*******************************************************************************");
	printf("\nAluno:Lucas Vinícius Sampaio Lima\t\t\t\tR.A:20026518-5\nFaculdade:Bacharelado em Engenharia de Software");
	printf("\n********************************************************************************\n\n");
}

void cabecalho(void){
 	printf("MAPA - ESOFT - ESTRUTURA DE DADOS I - 52/2021\nImplementacao do Algoritmo de Dijasktra\n\nComandos:\n\n");
 	printf("\t 1 - Adicionar um Grafo pré definido;\n\t 2 - Criar manualmente um novo Grafo;\n\t 3 - Procura Os Menores Caminhos no Grafo;\n\t 0 - Sair do programa.\n\nEscolha uma opção: ");
}

void adicionar(void){
	int i, j;
	vertices=5;
   
	if (!custos)
    	free(custos);
      
   custos = (int *) malloc(sizeof(int)*vertices*vertices);
   
	for (i = 0; i <= vertices * vertices; i++)
		custos[i] = -1;
       
	system("cls");
	system("color 2");
	printf("Inserindo arestas pré definidas, por favor aguarde...\n\n");
	
	printf("\tOrigem:1\n\tDestino:2\n\tCusto:200.\n\n");
    origem=1;
    destino=2;
    custo=200;
	custos[(origem-1) * vertices + destino - 1] = custo;
	
	printf("\tOrigem:1\n\tDestino:3\n\tCusto:0.\n\n");
	origem=1;
    destino=3;
    custo=0;
	custos[(origem-1) * vertices + destino - 1] = custo;
	
	printf("\tOrigem:2\n\tDestino:4\n\tCusto:0.\n\n");
	origem=2;
    destino=4;
    custo=0;
	custos[(origem-1) * vertices + destino - 1] = custo;
 
 	printf("\tOrigem:2\n\tDestino:5\n\tCusto:200.\n\n");
 	origem=2;
    destino=5;
    custo=200;
	custos[(origem-1) * vertices + destino - 1] = custo;
 
 	printf("\tOrigem:3\n\tDestino:2\n\tCusto:600.\n\n");
 	origem=3;
    destino=2;
    custo=600;
	custos[(origem-1) * vertices + destino - 1] = custo;
 
 	printf("\tOrigem:3\n\tDestino:5\n\tCusto:500.\n\n");
 	origem=3;
    destino=5;
    custo=500;
	custos[(origem-1) * vertices + destino - 1] = custo;
 
 	printf("\tOrigem:4\n\tDestino:5\n\tCusto:100.\n\n");
 	origem=4;
    destino=5;
    custo=100;
	custos[(origem-1) * vertices + destino - 1] = custo;
}

void grafoManual(){
	int op=-1;
	system("cls");
	printf("Aviso: caso tenha já definido um grafo, o Grafo anterior será pedido, deseja continuar?\n\n \t 1 - Sim;\n\t 2 - Não;\n\nEscolha um opção: ");
	scanf("%d", &op);
	if(op==1){
		system("cls");
		adicionalManual();
		printf("\n\nVoltando ao menu...\n");
		system("pause"); 
	}else{
		printf("\n\nVoltando ao menu...\n");
		system("pause"); 
	}	
}

void adicionalManual(void){
	int i, j;
	do {
	printf("Qual a quantidade de vertices no Grafo? (Numero minimo = 2 ): ");
	scanf("%d",&vertices);
	} while (vertices < 2 );

	if (!custos)
		free(custos);
	custos = (int *) malloc(sizeof(int)*vertices*vertices);
	
	for (i = 0; i <= vertices * vertices; i++)
   		custos[i] = -1;

	printf("\n\nInsira as arestas:\n\n");
	do {
    	do {
      		printf("\tOrigem da aresta (entre 1 e %d ou '0' para sair): ", vertices);
      		scanf("%d",&origem);
   		 } while (origem < 0 || origem > vertices);

    if (origem) {
      	do {
       		printf("\n\tDestino da aresta (entre 1 e %d, menos %d): ", vertices, origem);
       		scanf("%d", &destino);
      	} while (destino < 1 || destino > vertices || destino == origem);

   		 do {
       		printf("\n\tCusto (positivo) da aresta do vertice %d para o vertice %d: ",origem, destino);
       		scanf("%d",&custo);
       		printf("\n\n ");
     	} while (custo < 0);
      	custos[(origem-1) * vertices + destino - 1] = custo;
    }
  }while (origem);
}

void procurar(void){
   int i, j;
   system("cls");
   system("color 03");
   printf("Lista dos Menores Caminhos no Grafo Inserido no Sistema: \n\n");
          
   for (i = 1; i <= vertices; i++) {
      	for (j = 1; j <= vertices; j++)
   			dijkstra(vertices, i,j, custos);
      	printf("\n");
   }
}

void dijkstra(int vertices,int origem,int destino,int *custos){
   int i,v, cont = 0;
   int *ant, *tmp;  
   int *z;     /* vertices para os quais se conhece o caminho minimo */
   double min;
   double dist[vertices]; /* vetor com os custos dos caminhos */

   /* aloca as linhas da matriz */
   ant = calloc (vertices, sizeof(int *));
   tmp = calloc (vertices, sizeof(int *));
   if (ant == NULL){
    	printf ("** Erro: Memoria Insuficiente **");
    	exit(-1);
   }
   z = calloc (vertices, sizeof(int *));
   if (z == NULL) {
    	printf ("** Erro: Memoria Insuficiente **");
    	exit(-1);
   }

	for (i = 0; i < vertices; i++) {
    	if (custos[(origem - 1) * vertices + i] !=- 1) {
        	ant[i] = origem - 1;
        	dist[i] = custos[(origem-1)*vertices+i];
      	}else{
    		ant[i]= -1;
    		dist[i] = HUGE_VAL;
		}
	z[i]=0;
   }
   z[origem-1] = 1;
   dist[origem-1] = 0;

   do{
      /* Encontrando o vertice que deve entrar em z */
    	min = HUGE_VAL;
    	for (i=0;i<vertices;i++)
        	if (!z[i])
        		if (dist[i]>=0 && dist[i]<min) {
            		min=dist[i];v=i;
            	}
      /* Calculando as distancias dos novos vizinhos de z */
    	if (min != HUGE_VAL && v != destino - 1) {
        	z[v] = 1;
        	for (i = 0; i < vertices; i++)
        		if (!z[i]) {
            	if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
            		dist[i] = dist[v] + custos[v*vertices+i];
                	ant[i] =v;
                }
            }
    	}
   }while(v != destino - 1 && min != HUGE_VAL);

	/* Mostra o Resultado da busca */
   printf("\tDe %d para %d: \t", origem, destino);
   if (min == HUGE_VAL) {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
   }else{
   		i = destino;
    	i = ant[i-1];
    	
    	while (i != -1) {
       		tmp[cont] = i+1;
      		cont++;
    		i = ant[i];
      	}
    	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i-1]);
    	}
    	printf("%d", destino);
    	printf("\n\tCusto:  %d\n",(int) dist[destino-1]);
   }
}
