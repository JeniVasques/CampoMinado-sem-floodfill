#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINA -1

//Fun��o para criar e alocar dinamicamente uma matriz de caracteres(char)
char** criaMatrizC(int linha, int coluna){
	
	char** matC = (char**) malloc(linha * sizeof(char*));
	for(int i = 0; i < linha; i++){
		matC[i] = (char*) malloc(coluna * sizeof(char));
	}
	
	return matC;
}

//Fun��o para criar e alocar dinamicamente uma matriz de inteiros(int)
int** criaMatrizInt(int linha, int coluna){
	
	int** matInt = (int**) malloc(linha * (sizeof(int*)));
	for(int i = 0; i < linha; i++){
		matInt[i] = (int*) malloc(coluna * sizeof(int));
	}
	
	return matInt;
}

//Fun��o para imprimir a matriz de caracteres. Imprime o campo minado com os x
void imprimirMatC(char** matrizC, int linha, int coluna) {
    
    printf("\n");
    
    printf(" ");
    for(int j = 0; j < coluna; j++){
    	printf("   %2d ", j + 1);
	}
	printf("\n");
	
	for (int i = 0; i < linha; i++) {
		printf("\n");
		printf("%2d", i + 1);
        for (int j = 0; j < coluna; j++) {
        	printf("%5c ", matrizC[i][j]); 
        }
        printf("\n");
	}
}


//Fun��o para imprimir a matriz de inteiros. Imprime o campo minado com as minas e os numeros da matriz
void imprimirMatInt(int** matriz, int linha, int coluna) {
    
	printf("\n");
	
    printf(" ");
    for (int j = 0; j < coluna; j++) {
        printf("   %2d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < linha; i++) {
        printf("\n");
        printf("%2d", i + 1); 
        for (int j = 0; j < coluna; j++) {
        	
        	//verifica se � uma mina, se for, imprime -1
            if (matriz[i][j] == MINA) {
                printf("%5d ", MINA);
            }else {
                printf("%5d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

//Fun��o que inicializa o campo minado(matriz) apenas com  x 
void iniciaCampo(char** matCampo, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matCampo[i][j] = 'x';
        }
    }
}

//Fun��o para verificar se o jogador esta passando uma coordenada que j� foi escolhida
int repetidaXY(char** campoMinado, int x, int y){
	
	//verifica se a coordenada j� foi escolhida 
	if(campoMinado[x][y] != 'x'){
		printf("\n");
		printf("Essa coordenada ja foi escolhida.\nPor favor, escolha outra.\n");
        return 1; // retorna 1 caso a coordenada seja repetida
	}
	return 0; //retorna 0 caso a coordenada seja nova
}

//Fun��o para verificar se as coordenadas s�o v�lidas
int coordenadasValidas(int x, int y, int linha, int coluna) {
	
	//verifica se a coordenada esta dentro dos limites da matriz
    if (x < 0 || x >= linha || y < 0 || y >= coluna) {
        return 0; // retorna 0 se a coordenada � inv�lida
    }
    return 1; // retorna 1 se a coordenada � v�lida
}

//Fun��o que gera mina aleatoriamente na matriz e atualiza os numeros pr�ximos
void geraMina(int** campoMinado, int linha, int coluna, int quantMina) {
	
    srand(time(NULL)); // inicia o gerador de numeros aleatorios
    int minasCont = 0; // conta quantas minas foram colocadas
	
	//Inicializa a matriz campoMinado com 0
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            campoMinado[i][j] = 0;
        }
    }
	
	//continua gerando mina ate a quantidade de minas necess�rias
    while (minasCont < quantMina) {
    	
    	//gera linha e coluna aleatoria
        int x = rand() % linha; 
        int y = rand() % coluna;
		
		//Verifica se j� n�o existe uma mina nessa posi��o
        if (campoMinado[x][y] != MINA) {
            campoMinado[x][y] = MINA; //Coloca uma mina na posi��o(indice)
            minasCont++;
			
			//Atualiza os �ndices proximos em rela��o a mina alocada
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (i == x && j == y){ // Ignora o �ndice onde a mina foi colocada
                        continue;
                    } 
                    
                    // Faz chamada da fun��o coordenadasValidas para verificar se as coordenadas est�o validas e tambem verifica se n�o cont�m uma mina
                    if(coordenadasValidas(i, j, linha, coluna) && campoMinado[i][j] != MINA) {
                        campoMinado[i][j]++; //incrementa o valor dos numeros proximos
                    }
                }
            }
        }
    }
}

//Fun��o para processar a jogada e verificar se o jogador acertou uma mina ou n�o
int jogada(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y) {
     
	//Verifica��o caso tenha escolhido uma coordenada que tenha uma mina.
	if (campoMinado[x][y] == MINA) {
		printf("\n");
        printf("  GAME OVER. VOCE PERDEU :/ \n");
        imprimirMatInt(campoMinado, linha, coluna); //imprime o campo minado com todos os valores sem o 'x'
        return 1; // retorna 1 para indicar que o jogo acabou.
    } else {
    	//caso contrario, mostra a quantidade de minas proximas
        campoM2[x][y] = campoMinado[x][y] + '0';
        return 0; // retorna 0 para continuar com o jogo rodando.
    }
}

//Fun��o para liberar a mem�ria da matriz alocada de inteiros
void liberarMat(int** matriz, int linha) {
    for (int i = 0; i < linha; i++) {
        free(matriz[i]); // libera cada linha
    }
    free(matriz); // libera o vetor de ponteiros de inteiros 
}

//Fun��o para liberar a mem�ria da matriz alocada de caracteres
void liberarMatC(char** matrizC, int linha){
	for(int i = 0; i < linha; i++){
		free(matrizC[i]); // libera cada linha
	}
	free(matrizC); // libera o vetor de ponteiros de caracteres
}

int main() {
    int linha, coluna, quantMinas, restoMinas, x, y, nivel;
	int perdeu = 0;
    int** campoMinado;
    char** campoM2;
   

	/*Aqui dentro do while escolhe o nivel de dificuldade e verifica se ele � v�lido ou n�o, 
	se n�o for ele imprime uma mensagem que manda a pessoa escolher de novo.
	*/
    while(1){
    	printf("Digite o numero do nivel de dificuldade que voce deseja:\n");
    	printf("\n");
    	printf("1 = Facil\n");
		printf("2 = Medio\n");
		printf("3 = Dificil\n");
		printf("\n");
    	scanf("%d", &nivel);
    	
    	if(nivel == 1){
    		linha = coluna = 10;
    		quantMinas = 3;
    		break;
		}else if(nivel == 2){
			linha = coluna = 20;
			quantMinas = 6;
			break;
		}else if(nivel == 3){
			linha = coluna = 30;
			quantMinas = 9;
			break;
		}else{
			printf("Nivel de dificuldade invalido. Por Favor, tente novamente.\n");
		}
	}
	
	//Cria a matriz de inteiro e de char.
	campoMinado = criaMatrizInt(linha, coluna);
	campoM2 = criaMatrizC(linha, coluna);
	
	//inicializa o campo minado com 'x'
	iniciaCampo(campoM2, linha, coluna); 
	
	// gera as minas no campo minado e atualiza os numeros proximos
	geraMina(campoMinado, linha, coluna, quantMinas);
	
	// Quantidade de espa�os sem mina que o jogador ainda precisa descobrir
	restoMinas = linha * coluna - quantMinas;
	
	/*Dentro desse while acontece o processamento de cada jogada, a cada intera��o do jogador � solicitado uma coordenada e
	e se ela for v�lida, o loop verifica se foi revelado uma mina ou nao. Caso nao for revelado o contador "restoMinas" � decrementado 
	e assim o loop vai verificando cada jogada ate que o jogador acerte uma mina ou ganhe e assim exibindo uma mensagem de vit�ria. 
	*/
	while(!perdeu && restoMinas > 0){
		
		imprimirMatC(campoM2, linha, coluna); // imprime o campo minado com 'x'
		
		printf("\n");
		printf("Digite as coordendas (x,y): \n");
		scanf("%d,%d", &x, &y);
		
		// ajusta as coordenadas para os indices da matriz
		x --;
		y --;
		
		if(!coordenadasValidas(x, y, linha, coluna)){
		printf("\n");
		printf("Coordenada invalida.\n");
		printf("Por favor, digite outra coordenada.\n");
		continue;
	}
	
		if(repetidaXY(campoM2, x, y)){
			continue;
		}
    	
    	// processa a jogada e verifica se o jogador perdeu
  		perdeu = jogada(campoMinado, campoM2, linha, coluna, x, y);
	
		// se n�o perdeu e a coordenada escolhida n�o cont�m mina ent�o decrementa o n�mero de posi��es restantes
		if(!perdeu && campoMinado[x][y] != MINA){
			restoMinas--;
		}
  	}
  	
  	// verifica se o jogador ganhou
  	if(!perdeu){
  		printf("!!PARABENS!!. VOCE EH FERA!:) \n");
  		imprimirMatInt(campoMinado, linha, coluna);
	  }
	
	//libera a memoria das matriz que foram alocadas dinamicamente
	liberarMat(campoMinado, linha);
    liberarMatC(campoM2, linha);
    
    return 0;
}
