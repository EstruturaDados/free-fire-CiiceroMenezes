#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ======================================================
// ESTRUTURAS DE DADOS
// ======================================================

// Representa um item coletado pelo jogador
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada, que contém um Item e um ponteiro para o próximo
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ======================================================
// VARIÁVEIS GLOBAIS E DEFINIÇÕES
// ======================================================

#define MAX_ITENS 10
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
No* mochilaLista = NULL; // início da lista encadeada

// Contadores de comparações (para análise de desempenho)
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ======================================================
// FUNÇÕES DE MOCHILA (VERSÃO VETOR)
// ======================================================

// Insere um item no vetor
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n⚠️  Mochila (vetor) está cheia!\n");
        return;
    }

    Item novo;
    printf("\n--- Inserir Item (Vetor) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;
    printf("\n✅ Item '%s' adicionado na mochila (vetor).\n", novo.nome);
}

// Remove item por nome no vetor
void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\n⚠️  Mochila (vetor) está vazia!\n");
        return;
    }

    char nome[30];
    printf("\n--- Remover Item (Vetor) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    printf("\n❌ Item '%s' não encontrado no vetor.\n", nome);
}

// Lista os itens do vetor
void listarItensVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    if (totalItensVetor == 0) {
        printf("Vazia.\n");
        return;
    }
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. %s | Tipo: %s | Qtd: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\n🔍 Item encontrado (busca sequencial): %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            return i;
        }
    }
    printf("\n❌ Item '%s' não encontrado (busca sequencial).\n", nome);
    return -1;
}

// Ordena o vetor por nome (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\n📦 Mochila (vetor) ordenada por nome!\n");
}

// Busca binária no vetor
int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = totalItensVetor - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            printf("\n🎯 Item encontrado (busca binária): %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n❌ Item '%s' não encontrado (busca binária).\n", nome);
    return -1;
}

// ======================================================
// FUNÇÕES DE MOCHILA (VERSÃO LISTA ENCADEADA)
// ======================================================

// Insere item na lista encadeada (no início)
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("\n❌ Falha ao alocar memória!\n");
        return;
    }

    printf("\n--- Inserir Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\n✅ Item '%s' adicionado na mochila (lista encadeada).\n", novo->dados.nome);
}

// Remove item por nome na lista encadeada
void removerItemLista() {
    if (!mochilaLista) {
        printf("\n⚠️  Mochila (lista) está vazia!\n");
        return;
    }

    char nome[30];
    printf("\n--- Remover Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    No *atual = mochilaLista, *anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("\n❌ Item '%s' não encontrado na lista.\n", nome);
        return;
    }

    if (anterior == NULL)
        mochilaLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("\n🗑️  Item '%s' removido com sucesso!\n", nome);
}

// Lista itens da lista encadeada
void listarItensLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    if (!mochilaLista) {
        printf("Vazia.\n");
        return;
    }

    No* atual = mochilaLista;
    int i = 1;
    while (atual) {
        printf("%d. %s | Tipo: %s | Qtd: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada
void buscarItemLista() {
    if (!mochilaLista) {
        printf("\n⚠️  Mochila (lista) vazia.\n");
        return;
    }

    char nome[30];
    printf("\n--- Buscar Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    int comparacoes = 0;
    No* atual = mochilaLista;
    while (atual) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n🔍 Item encontrado (lista): %s | Tipo: %s | Qtd: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("\n❌ Item '%s' não encontrado. Comparações: %d\n", nome, comparacoes);
}

// ======================================================
// MENU PRINCIPAL
// ======================================================

int main() {
    int escolhaEstrutura, opcao;
    char nomeBusca[30];

    printf("=============================================\n");
    printf("🎒 Sistema de Inventário - Nível Intermediário 🧠\n");
    printf("Comparação: Vetor vs Lista Encadeada\n");
    printf("=============================================\n");

    do {
        printf("\nEscolha a estrutura:\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &escolhaEstrutura);

        if (escolhaEstrutura == 1) {
            do {
                printf("\n--- Menu (Vetor) ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar sequencial\n5. Ordenar\n6. Buscar binária\n0. Voltar\nOpção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4:
                        printf("Nome do item: ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarSequencialVetor(nomeBusca);
                        printf("Comparações (sequencial): %d\n", comparacoesSequencial);
                        break;
                    case 5: ordenarVetor(); break;
                    case 6:
                        printf("Nome do item: ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarBinariaVetor(nomeBusca);
                        printf("Comparações (binária): %d\n", comparacoesBinaria);
                        break;
                    case 0: break;
                    default: printf("\nOpção inválida!\n");
                }
            } while (opcao != 0);
        }

        else if (escolhaEstrutura == 2) {
            do {
                printf("\n--- Menu (Lista Encadeada) ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item\n0. Voltar\nOpção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarItemLista(); break;
                    case 0: break;
                    default: printf("\nOpção inválida!\n");
                }
            } while (opcao != 0);
        }

    } while (escolhaEstrutura != 0);

    printf("\n🏁 Jogo encerrado! Estruturas comparadas com sucesso.\n");
    return 0;
}
