#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ======================================================
// ESTRUTURA PRINCIPAL
// ======================================================

// Representa cada peça necessária para a construção da torre de fuga
typedef struct {
    char nome[30];     // Nome do componente (ex: “Chip Central”)
    char tipo[20];     // Tipo do componente (ex: “Propulsão”, “Controle”)
    int prioridade;    // Nível de importância (1 a 10)
} Componente;

// ======================================================
// VARIÁVEIS GLOBAIS
// ======================================================

#define MAX_COMPONENTES 20
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;

int comparacoes = 0; // Contador de comparações (para análise de desempenho)

// ======================================================
// FUNÇÕES DE UTILIDADE
// ======================================================

// Função para cadastrar um novo componente
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n⚠️  Limite máximo de componentes atingido!\n");
        return;
    }

    Componente novo;
    printf("\n--- Cadastro de Novo Componente ---\n");
    printf("Nome do componente: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do componente: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);

    torre[totalComponentes++] = novo;
    printf("\n✅ Componente '%s' adicionado com sucesso!\n", novo.nome);
}

// Exibe todos os componentes cadastrados
void mostrarComponentes(Componente vetor[], int n) {
    printf("\n--- Lista de Componentes ---\n");
    if (n == 0) {
        printf("Nenhum componente registrado.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// Função auxiliar para trocar dois componentes de lugar
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ======================================================
// ALGORITMOS DE ORDENAÇÃO
// ======================================================

// 1️⃣ Bubble Sort — Ordena por NOME
void bubbleSortNome(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
    printf("\n📦 Componentes ordenados por NOME usando Bubble Sort!\n");
}

// 2️⃣ Insertion Sort — Ordena por TIPO
void insertionSortTipo(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
            comparacoes++;
        }
        vetor[j + 1] = chave;
        comparacoes++;
    }
    printf("\n🧩 Componentes ordenados por TIPO usando Insertion Sort!\n");
}

// 3️⃣ Selection Sort — Ordena por PRIORIDADE
void selectionSortPrioridade(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[minIndex].prioridade)
                minIndex = j;
        }
        trocar(&vetor[i], &vetor[minIndex]);
    }
    printf("\n⚙️  Componentes ordenados por PRIORIDADE usando Selection Sort!\n");
}

// ======================================================
// BUSCA BINÁRIA (aplicável após ordenação por nome)
// ======================================================

int buscaBinariaPorNome(Componente vetor[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;
    int comparacoesBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) {
            printf("\n🎯 Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                   vetor[meio].nome, vetor[meio].tipo, vetor[meio].prioridade);
            printf("Comparações realizadas: %d\n", comparacoesBusca);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n❌ Componente '%s' não encontrado.\n", nome);
    printf("Comparações realizadas: %d\n", comparacoesBusca);
    return -1;
}

// ======================================================
// FUNÇÃO DE MEDIÇÃO DE TEMPO DE EXECUÇÃO
// ======================================================

void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int n) {
    clock_t inicio, fim;
    inicio = clock(); // marca o tempo inicial

    algoritmo(vetor, n); // executa o algoritmo de ordenação

    fim = clock(); // marca o tempo final
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("⏱️  Tempo de execução: %.5f segundos\n", tempo);
    printf("🔢 Comparações: %d\n", comparacoes);
}

// ======================================================
// MENU PRINCIPAL
// ======================================================

int main() {
    int opcao;
    char nomeBusca[30];

    printf("=============================================\n");
    printf("🏗️  Sistema de Montagem da Torre de Fuga - Nível Mestre 🧠\n");
    printf("=============================================\n");

    do {
        printf("\nMenu Principal:\n");
        printf("1. Cadastrar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar componente-chave (Binária - após ordenação por nome)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                mostrarComponentes(torre, totalComponentes);
                break;
            case 3:
                medirTempo(bubbleSortNome, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;
            case 4:
                medirTempo(insertionSortTipo, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;
            case 5:
                medirTempo(selectionSortPrioridade, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;
            case 6:
                if (totalComponentes == 0) {
                    printf("\n⚠️  Nenhum componente cadastrado!\n");
                    break;
                }
                printf("\nDigite o nome do componente-chave: ");
                scanf(" %[^\n]", nomeBusca);
                buscaBinariaPorNome(torre, totalComponentes, nomeBusca);
                break;
            case 0:
                printf("\n🚀 Torre montada com sucesso! Boa sorte na fuga!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
