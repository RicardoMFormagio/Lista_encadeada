#include <stdio.h>
#include <stdlib.h>

//define a struct No
typedef struct No{
    int valor;
    struct No *prox;
}No;

//função cria nó no fim da lista
void criar_no_fim (No **no);

//função cria nó no inicio da lista
void criar_no_inicio (No **no);

//função imprime valores da lista em formato de pilha
void mostrar_valores_pilha(No *no);

//função imprime valores da lista em formato de lista
void mostrar_valores_fila(No *no);

//função para remover ultimo elemento da lista
void remove_fim (No **no);

//funcao para remover primeiro elemento da lista
void remove_inicio (No **no);

//funçao para limpar memoria alocada
void free_memoria_alocada (No *no);

//salvar lista em arquivo txt
void salvar_lista (No *no, const char *lista_encadeada);

int main(void){
    int valor, opcao=1;
    
    //cria o primeiro no da lista como Null
    No *no = (No*)malloc(sizeof(No));
    
    if (no == NULL){
        printf("erro ao alocar memoria\n");
        return 1;
    }
    
    no->prox = NULL;
    
    //menu da lista encadeada
    while (opcao != 0){
        printf("1 - Inserir valor no fim lista\n");
        printf("5 - Inserir valor no inicio lista\n");
        printf("2 - Remover ultimo no da lista\n");
        printf("6 - Remover primeiro no da lista\n");
        printf("3 - Mostrar a lista em formato de pilha\n");
        printf("4 - Mostrar a lista em formato de fila\n");
        printf("7 - Salvar a lista encadeada\n");
        printf("0 - Encerrar lista\n");
        printf("\nSelecione  opcao desejada: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            
        case 0:
            free_memoria_alocada(no);
            exit(1); // Termina o programa com um código de erro
            break;
        case 1:
            criar_no_fim (&no);
            salvar_lista (no, "lista_encadeada");
            printf("\n------------------------------------------------------\n");
            break;
        case 2:
            remove_fim(&no);
            salvar_lista (no, "lista_encadeada");
            printf("\n------------------------------------------------------\n");
            break;
        case 3:
            mostrar_valores_pilha (no);
            printf("\n------------------------------------------------------\n");
            break;
        case 4:
            mostrar_valores_fila (no);
            printf("\n------------------------------------------------------\n");
            break;
        case 5:
            criar_no_inicio(&no);
            salvar_lista (no, "lista_encadeada");
            printf("\n------------------------------------------------------\n");
            break;
        case 6:
            remove_inicio(&no);
            salvar_lista (no, "lista_encadeada");
            printf("\n------------------------------------------------------\n");
            break;
        case 7:
            salvar_lista (no, "lista_encadeada");
            printf("\n------------------------------------------------------\n");
            break;
        default:
            printf("Valor digitado invalido");
            printf("\n------------------------------------------------------\n");
            break;
        }
    }
    return 0;
}

void criar_no_fim (No **no){
    
    int valor;
    
    printf("\nDigite o valor que deseja inserir na lista: ");
    scanf("%d",&valor);
    
    No *novono = (No*)malloc(sizeof(No));
    
    if (novono == NULL) {
        printf("Falha na alocação de memória para o nó.\n");
        exit(1); // Termina o programa com um código de erro;
    }
    
    if ((*no)->prox == NULL && (*no)->valor == 0){
        (*no)->valor = valor;
    }
    
    else{
        novono->valor = valor;
        novono->prox = *no;
        *no = novono;
    }
}

void criar_no_inicio (No **no){
    int valor;
    No *aux;
    No *novono = (No*)malloc(sizeof(No));
    
    if (aux == NULL || novono == NULL){
        printf("Memoria insuficiente para alocar");
        exit(1); //Sai do programa com mensagem de erro
    }
    
    printf("Digite o valor que deseja inserir no inicio da lista: ");
    scanf("%d",&valor);
    
    if ((*no)->prox == NULL && (*no)->valor == 0){
        (*no)->valor = valor;
    }
    else{
        aux = *no;
        while (aux->prox != NULL){
            aux = aux->prox;
        }   
        novono->valor = valor;
        novono->prox = NULL;
        aux->prox = novono;
    }
}

void mostrar_valores_pilha(No *no){
    
    while (no != NULL){
        printf("\nValor do no: %d\n", no->valor);
        no = no->prox;
    }
}

void mostrar_valores_fila(No *no){
    
    if (no == NULL){
        return;
    }
    
    //chamada recursiva
    mostrar_valores_fila(no->prox);
    
    printf("\nValor do no: %d\n",no->valor);
}

void remove_fim (No **no){
    No *aux = *no;
    
    if((*no)->prox == NULL) return;
    
    *no = (*no)->prox;
    free(aux);
}

void remove_inicio (No **no){
    
    No *aux = (No*)malloc(sizeof(No));
    No *aux2 = (No*)malloc(sizeof(No));
    
    if (aux == NULL || aux2 == NULL){
        printf("Memoria indisponivel para alocacao");
        exit(1);
    }
    
    aux = *no;
    
    while((*no)->prox != NULL){
        aux2 = *no;
        *no = (*no)->prox;
    }
    
    *no = NULL;
    aux2->prox = NULL;
    *no = aux;
}

void free_memoria_alocada (No *no){
    No *aux;
    
    while(no != NULL){
        aux = no;
        no = no->prox;
        free(aux);
    }
}

void salvar_lista (No *no, const char *lista_encadeada){
    FILE *arquivo = fopen(lista_encadeada, "w");
    
    if (arquivo == NULL) {
        perror("Não foi possível abrir o arquivo");
        return;
    }
    
    No *aux = no;
    while (aux != NULL){
        fprintf(arquivo, "%d\n", aux->valor);
        aux = aux->prox;
    }
    fclose(arquivo);
}


