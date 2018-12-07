#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgbd.h"
#include <dirent.h>

#define size_str 200

char nome[200];
char *campos;
FILE *arq;

void Menu(){

   	int aux, opt = -1;
   	int done = 0;

   	while(done == 0){ // variável --> por causa do switch
   		printf("\n[1] - Criar uma tabela\n[2] - Listar todas as tabelas\n[3] - Criar uma nova linha na tabela");
        printf("\n[4] - Listar todos os dados de uma tabela\n[5] - Pesquisar valor em uma tabela\n[6] - Apagar o valor de uma tabela");
        printf("\n[7] - Apagar uma tabela\n[0] - Sair\n");
        aux = scanf("%d", &opt);
        getchar(); // limpar para não passar direto do scanf

    	if(opt == 0){
    		break;
    	} 

    	// verificar se a entrada é válida
    	if(aux == 0){
    		printf("\nDigite um valor inteiro!\n");
    		Menu();
    	}

    	switch(opt){

			case 1:
				done = 1;
				criarTabela();
			break;

			case 2:
				done = 1;
				listarTabelas();
			break;

			case 3:
				done = 1;
				criarLinha();
			break;

			case 4:
				done = 1;
				listarDados();
			break;

			case 5:
				done = 1;
				pesquisarValor();
			break;

			case 6:
				done = 1;
				apagarValor();
			break;

			case 7:
				done = 1;
				apagarTabela();
				break;
		}
	}
}

void criarTabela(){
	char c;

	printf("\nInforme o nome da tabela: ");
	scanf("%s", nome);
	strcat(nome, ".txt");
	getchar();

	arq = fopen(nome, "w"); // leitura de arquivo
	campos = (char*) malloc(200);

	if(arq == NULL){
		printf("\nErro! Não foi possível abrir o arquivo\n"); // verifica se o arquivo existe	
		exit(0);
	} 

	while(1){
		printf("\nInsira o nome de um campo e do seu tipo, seguidos de ponto-e-vírgula. ");
		printf("\nEx: pessoas string;\nOu digite 0 (zero) para concluir: ");
		scanf("%[^\n]%*c", campos); // sem escrever com espaço
		getchar();

		if(strcmp (campos, "0") == 0){
			break;	
		} 

		printf("%s", campos);
		
		while (1){
			printf("\nÉ chave primária? - S ou N: ");
			scanf("%c", &c);
			getchar();

			if (c == 's' || c == 'S'){
				strcat (campos, "£"); // se tiver £ = PK
				fprintf(arq, "%s", campos);	
				break;
			}

			else if (c != 'n' || c != 'N'){
				fprintf(arq, "%s", campos);
				break;
			}

			else {
				printf("\nInforme um valor válido! (S ou N)");
				continue;
			}

			break;
		}
	}

	fclose(arq);
	free(campos);
}

void listarTabelas(){
	DIR *d;
  	struct dirent *dd;     
  	d = opendir ("./");

  	if (d != NULL)
  	{
    	while ((dd = readdir (d))!=NULL) {
      	int length = strlen(dd->d_name);
      	if (strncmp(dd->d_name + length - 4, ".txt", 4) == 0) {
          puts (dd->d_name);
      	}
    }

    (void) closedir (d);
  }
}

void criarLinha(){
	char c, valor[200];
	int i, x;
	arq = fopen(nome, "r");

	if(arq == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
 	else{
 		while( (c=fgetc(arq))!= EOF){
 			//if(strcmp(c, ";")) x++;
 			if(c == ';') x++;
 		}
 	}

	while(i != x){
		printf("\nInsira um valor para o %d o campo: ", i);
		scanf("%[^\n]%*c", valor);
		i++;
	}
}

void listarDados(){
	char info[200];

	printf("\nInsira o nome da tabela: ");
	scanf("%s", nome);
	
	arq = fopen(nome, "r");

	if(arq == NULL){
		printf("Erro! Não foi possível ler o arquivo.");
	}

	else{
		while(fgets(info, sizeof(info), arq)!=NULL){
			printf("%s", info);
		}
	}

	fclose(arq);
}

void pesquisarValor(){
	arq = fopen(nome, "r");
	char mot [200];
	printf("\nInforme o valor a ser pesquisado: ");
	scanf("%s", mot);
	char c[strlen(mot)];

	int cont=0, letra=0;

	while(!feof(arq)){
		letra++;
		c[cont]=fgetc(arq);

		if(cont==(strlen(mot))){

			if(!(strcpy(c, mot))){
				printf("\n*********VALUE MATCHES!*********\n");
				printf("\nResultado encontrado após %d caracteres.", letra);
			}
			
			else{
				printf("\nNão encontrado!");
				cont=0;
			} 
		}

	}
}

void apagarValor(){
	char info[200];

	printf("\nInsira o nome da tabela que terá um valor a ser removido: ");
	listarTabelas();
	scanf("%s", nome);

	arq = fopen(nome, "rw");

	if(arq == NULL){
		printf("Erro! Não foi possível ler o arquivo.");
	}

	else{
		char C[200];
		FILE* novoArquivo = fopen("temp.txt", "w");

		printf("\nQual valor deseja apagar?");
	
		// Listar os valores
		while(fgets(info, sizeof(info), arq)!=NULL){
			printf("%s", info);
		}
		scanf("%s", C);

		// Copiar todos campos para novo arquivo e apagar o que há de diferente

		while(!feof(arq)){
		    fread(&C, sizeof(C), 1, arq);
		    if(strcmp(nome, C)){
		       fwrite(&C, sizeof(C), 1, novoArquivo);
		    }
		}

 		//E, por fim, remove o velho arquivo e renomeia o novo. 

    	fclose(novoArquivo);
	   	fclose(arq);
	   	remove(nome);
	   	rename("temp.txt", nome);
	}
	//fclose(novoArquivo);
	//fclose(arq);
}

void apagarTabela(){
	char r[50] = "rm ";

	printf("\nTabelas que podem ser removidas: ");
	printf("\n");
	listarTabelas();

	printf("\nNome da tabela a ser removida: ");
	scanf("%s", nome);

	strcat(r, nome);

	system(r);
}