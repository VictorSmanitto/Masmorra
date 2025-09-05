#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define Linha 5
#define Coluna 7
#define Itens 4

struct Item {
    char nome[100];
    char descricao[512];
    int quantidade;
};

struct Lugar {
    char nome[100];
    int temItem;
    int itemIndex;
};

void inventario(struct Item item[Itens]) {
    char opcao1[100];
    char entrada[10];
    int temItem = 0;

    printf("\nSeu inventário:\n");
    for (int i = 0; i < Itens; i++) {
        if (item[i].quantidade > 0) {
            printf("- %s (x%d)\n", item[i].nome, item[i].quantidade);
            temItem = 1;
        }
    }

    if (!temItem) {
        printf("Você não possui nenhum item no inventário.\n");
        return;
    }

    do {
        printf("Deseja ver a descrição de algum item? (s/n): ");
        scanf("%s", entrada);

        if (strcmp(entrada, "s") == 0) {
            printf("Digite o nome do item: ");
            scanf(" %[^\n]", opcao1);

            int achou = 0;
            for (int i = 0; i < Itens; i++) {
                if (strstr(item[i].nome, opcao1) && item[i].quantidade > 0) {
                    printf("\nDescrição de %s:\n%s\n", item[i].nome, item[i].descricao);
                    achou = 1;
                    break;
                }
            }
            if (!achou) printf("Você não possui este item.\n");
        } else if (strcmp(entrada, "n") == 0) {
            break;
        } else {
            printf("Opção inválida. Digite apenas 's' ou 'n'.\n");
        }
    } while (1);
}

void limite() {
    printf("Você não pode atravessar paredes.\n");
}

void matriz(int posL, int posC) {
    printf("\nMapa:\n");
    for (int i = 0; i < Linha; i++) {
        for (int j = 0; j < Coluna; j++) {
            if (i == posL && j == posC) printf(" P ");
            else printf(" . ");
        }
        printf("\n");
    }
}

void visitarLugar(int i, int j, struct Item item[Itens], struct Lugar mapa[Linha][Coluna]) {
    printf("\nVocê está em: %s\n", mapa[i][j].nome);
    if (mapa[i][j].temItem) {
        int idx = mapa[i][j].itemIndex;
        printf("Você encontrou %s!\n", item[idx].nome);
        item[idx].quantidade++;
        mapa[i][j].temItem = 0;
    }
}

void inicializarItens(struct Item item[Itens]) {
    strcpy(item[0].nome, "Espada do seu Zé");
    strcpy(item[0].descricao, "\nNa antiga Roma, quando Júpiter caiu do céu, aterrissou em terra e com seu poder supremo destruiu Roma, subjulgando todos os demônios...\n");
    item[0].quantidade = 0;

    strcpy(item[1].nome, "Arco de João");
    strcpy(item[1].descricao, "\nO Arco do Grandioso João de Barro III, capaz de perfurar até o aço com fezes como flecha.\n");
    item[1].quantidade = 0;

    strcpy(item[2].nome, "Escudo de Enzu");
    strcpy(item[2].descricao, "\nO escudo feito de órgãos e pele, símbolo de defesa e covardia.\n");
    item[2].quantidade = 0;

    strcpy(item[3].nome, "Chave dos Três Reinos");
    strcpy(item[3].descricao, "\nA Chave Mística que abre portais proibidos entre Terra, Céu e Inferno.\n");
    item[3].quantidade = 0;
}

void inicializarMapa(struct Lugar mapa[Linha][Coluna]) {
    for (int x = 0; x < Linha; x++) {
        for (int y = 0; y < Coluna; y++) {
            strcpy(mapa[x][y].nome, "Sala Desconhecida");
            mapa[x][y].temItem = 0;
            mapa[x][y].itemIndex = -1;
        }
    }

    // Definindo nomes e itens em lugares
    strcpy(mapa[0][0].nome, "Catedral das Sombras");
    strcpy(mapa[0][1].nome, "Corredor Sombrio");
    strcpy(mapa[0][2].nome, "Biblioteca Perdida");
    strcpy(mapa[0][3].nome, "Sala do Trono");
    strcpy(mapa[0][4].nome, "Sala de Ossos");
    strcpy(mapa[0][5].nome, "Portal Arcano (Saída)");
    strcpy(mapa[0][6].nome, "Santuário Oculto");

    strcpy(mapa[1][0].nome, "Cripta");
    strcpy(mapa[1][1].nome, "Laboratório Arcano");
    strcpy(mapa[1][2].nome, "Sala dos Espelhos");
    strcpy(mapa[1][3].nome, "Jardim Envenenado");
    strcpy(mapa[1][4].nome, "Oficina do Artífice");
    strcpy(mapa[1][5].nome, "Galeria das Almas");
    strcpy(mapa[1][6].nome, "Corredor Estreito");

    strcpy(mapa[2][0].nome, "Caixão de Jaya");
    strcpy(mapa[2][1].nome, "Antessala Sombria");
    strcpy(mapa[2][2].nome, "Altar Perdido");
    strcpy(mapa[2][3].nome, "Beco"); mapa[2][3].temItem = 1; mapa[2][3].itemIndex = 0;
    strcpy(mapa[2][4].nome, "Sala dos Tambores");
    strcpy(mapa[2][5].nome, "Sala Secreta");
    strcpy(mapa[2][6].nome, "Prisão Abandonada"); mapa[2][6].temItem = 1; mapa[2][6].itemIndex = 2;

    strcpy(mapa[3][0].nome, "Salão das Runas");
    strcpy(mapa[3][1].nome, "Câmara das Chamas");
    strcpy(mapa[3][2].nome, "Caverna Escura");
    strcpy(mapa[3][3].nome, "Cemitério Antigo");
    strcpy(mapa[3][4].nome, "Caverna de Cristais");
    strcpy(mapa[3][5].nome, "Passagem Oculta");
    strcpy(mapa[3][6].nome, "Salão Congelado");

    strcpy(mapa[4][0].nome, "Caverna Submersa");
    strcpy(mapa[4][1].nome, "Beco"); mapa[4][1].temItem = 1; mapa[4][1].itemIndex = 3;
    strcpy(mapa[4][2].nome, "Corredor Abissal");
    strcpy(mapa[4][3].nome, "Arena Perdida");
    strcpy(mapa[4][4].nome, "Sala da Lua"); mapa[4][4].temItem = 1; mapa[4][4].itemIndex = 1;
    strcpy(mapa[4][5].nome, "Salão dos Ecos");
    strcpy(mapa[4][6].nome, "Portal Antigo");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Item item[Itens];
    inicializarItens(item);

    struct Lugar mapa[Linha][Coluna];
    inicializarMapa(mapa);

    int i = 2, j = 0;
    char opcao;

    printf("Bem-vindo ao jogo!\n");

    do {
        matriz(i, j);
        visitarLugar(i, j, item, mapa);

        printf("\nUse w (Norte), s (Sul), d (Leste), a (Oeste), i (Inventário), q (Sair): ");
        scanf(" %c", &opcao);

        if (opcao == 'w' && i > 0) i--;
        else if (opcao == 's' && i < Linha - 1) i++;
        else if (opcao == 'a' && j > 0) j--;
        else if (opcao == 'd' && j < Coluna - 1) j++;
        else if (opcao == 'i') inventario(item);
        else if (opcao == 'q') break;
        else limite();

        if (i == 0 && j == 5) {
            if (item[3].quantidade > 0) {
                printf("\nVocê usou a chave e escapou da masmorra! Parabéns!\n");
                break;
            } else {
                printf("\nVocê encontrou a saída, mas não tem a chave!\n");
            }
        }

        system("pause");
        system("cls");

    } while (1);

    return 0;
}

