#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ==============================
// Estrutura de dados principal
// ==============================

// A struct Item representa qualquer objeto que o jogador colete no jogo.
// Cada item tem um nome (ex: "Pistola"), um tipo (ex: "Arma") e uma quantidade.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ==============================
// Constantes e variáveis globais
// ==============================

#define MAX_ITENS 10  // Capacidade máxima da mochila
Item mochila[MAX_ITENS]; // Vetor que armazena os itens do jogador
int totalItens = 0;      // Quantidade atual de itens na mochila

// ==============================
// Funções auxiliares do sistema
// ==============================

// Função responsável por cadastrar um novo item no inventário
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Cadastro de Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome); // lê string com espaços

    printf("Tipo do item (arma, munição, cura, ferramenta...): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    // Adiciona o item no vetor
    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n✅ Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// Função para remover um item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Mochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Remoção de Item ---\n");
    printf("Informe o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;

    // Busca o item pelo nome
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    } else {
        // Desloca os elementos para "apagar" o item removido
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\n🗑️  Item '%s' removido com sucesso!\n", nomeBusca);
    }
}

// Função que lista todos os itens da mochila
void listarItens() {
    printf("\n--- Itens na Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial por nome do item
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Mochila vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca de Item ---\n");
    printf("Informe o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\n❌ Item '%s' não encontrado.\n", nomeBusca);
}

// ==============================
// Função principal (menu do jogo)
// ==============================

int main() {
    int opcao;

    printf("=============================================\n");
    printf("🎒 Sistema de Inventário - Mochila de Loot 🎯\n");
    printf("=============================================\n");

    do {
        printf("\nMenu de Opções:\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair do jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n💾 Salvando dados e saindo do jogo... Até a próxima!\n");
                break;
            default:
                printf("\n❗ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
