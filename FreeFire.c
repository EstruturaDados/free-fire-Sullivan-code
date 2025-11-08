#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

int comparacoes = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarComponentes(Componente componentes[], int n) {
    printf("\n--- Lista de Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d: %-30s | %-20s | Prioridade: %d\n", 
               i+1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("----------------------------\n");
}

void bubbleSortNome(Componente componentes[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j+1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j+1];
                componentes[j+1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente componentes[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = componentes[i];
        int j = i - 1;
        comparacoes++;
        while (j >= 0 && strcmp(componentes[j].tipo, key.tipo) > 0) {
            componentes[j+1] = componentes[j];
            j = j - 1;
            comparacoes++;
        }
        componentes[j+1] = key;
    }
}

void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        Componente temp = componentes[min_idx];
        componentes[min_idx] = componentes[i];
        componentes[i] = temp;
    }
}

int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    int esq = 0, dir = n-1;
    comparacoes = 0;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        comparacoes++;
        
        int cmp = strcmp(componentes[meio].nome, nome);
        
        if (cmp == 0) return meio;
        if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char* nomeAlgoritmo) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, componentes, sizeof(Componente) * n);
    
    inicio = clock();
    algoritmo(copia, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n%s concluído!", nomeAlgoritmo);
    printf("\nTempo de execução: %f segundos", tempo_gasto);
    printf("\nComparações realizadas: %d\n", comparacoes);
    
    if (strcmp(nomeAlgoritmo, "Bubble Sort") == 0) {
        mostrarComponentes(copia, n);
    }
}

void cadastrarComponentes(Componente componentes[], int *n) {
    printf("Quantos componentes deseja cadastrar? (max %d): ", MAX_COMPONENTES);
    scanf("%d", n);
    limparBuffer();
    
    if (*n > MAX_COMPONENTES) *n = MAX_COMPONENTES;
    
    for (int i = 0; i < *n; i++) {
        printf("\nComponente %d:\n", i+1);
        
        printf("Nome: ");
        fgets(componentes[i].nome, TAM_NOME, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
        
        printf("Tipo: ");
        fgets(componentes[i].tipo, TAM_TIPO, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
        
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        limparBuffer();
        
        while(componentes[i].prioridade < 1 || componentes[i].prioridade > 10) {
            printf("Prioridade inválida! Digite um valor entre 1 e 10: ");
            scanf("%d", &componentes[i].prioridade);
            limparBuffer();
        }
    }
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    int num_componentes = 0;
    int opcao;
    char nome_busca[TAM_NOME];
    
    printf("=== SISTEMA DE MONTAGEM DA TORRE DE RESGATE ===\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente por nome (Busca Binária)\n");
        printf("6. Mostrar componentes atuais\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &num_componentes);
                break;
                
            case 2:
                if (num_componentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                } else {
                    medirTempo(bubbleSortNome, componentes, num_componentes, "Bubble Sort");
                }
                break;
                
            case 3:
                if (num_componentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                } else {
                    medirTempo(insertionSortTipo, componentes, num_componentes, "Insertion Sort");
                }
                break;
                
            case 4:
                if (num_componentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                } else {
                    medirTempo(selectionSortPrioridade, componentes, num_componentes, "Selection Sort");
                }
                break;
                
            case 5:
                if (num_componentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                } else {
                    printf("Digite o nome do componente a buscar: ");
                    fgets(nome_busca, TAM_NOME, stdin);
                    nome_busca[strcspn(nome_busca, "\n")] = 0;
                    
                    int resultado = buscaBinariaPorNome(componentes, num_componentes, nome_busca);
                    
                    if (resultado != -1) {
                        printf("\nComponente encontrado!\n");
                        printf("Nome: %s\n", componentes[resultado].nome);
                        printf("Tipo: %s\n", componentes[resultado].tipo);
                        printf("Prioridade: %d\n", componentes[resultado].prioridade);
                        printf("Comparações realizadas: %d\n", comparacoes);
                    } else {
                        printf("\nComponente não encontrado!\n");
                        printf("Comparações realizadas: %d\n", comparacoes);
                    }
                }
                break;
                
            case 6:
                if (num_componentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                } else {
                    mostrarComponentes(componentes, num_componentes);
                }
                break;
                
            case 0:
                printf("Saindo do sistema...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
        
    } while(opcao != 0);
    
    return 0;
}