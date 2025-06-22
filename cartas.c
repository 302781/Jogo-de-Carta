#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Enums para valores e naipes
typedef enum {ESPADAS, PAUS, COPAS, OUROS} Naipe;
typedef enum {A=1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, J, Q, K} Valor;

// Struct de uma carta
typedef struct {
    Valor valor;
    Naipe naipe;
} Carta;

// Lista encadeada para cartas (baralho e mãos)
typedef struct NoCarta {
    Carta carta;
    struct NoCarta *prox;
} NoCarta;

// Struct de jogador
typedef struct {
    char nome[50];
    NoCarta *mao;
} Jogador;

// Funções auxiliares
const char* nomeNaipe(Naipe n) {
    char* nomes[] = {"Espadas", "Paus", "Copas", "Ouros"};
    return nomes[n];
}

const char* nomeValor(Valor v) {
    char* nomes[] = {"", "A", "2", "3","4","5","6","7","8","9","10","J","Q","K"};
    return nomes[v];
}

Carta criarCartaAleatoria() {
    Carta c;
    c.valor = (Valor)(rand() % 13 + 1);
    c.naipe = (Naipe)(rand() % 4);
    return c;
}

void adicionarCarta(NoCarta **mao, Carta c) {
    NoCarta *novo = (NoCarta*)malloc(sizeof(NoCarta));
    novo->carta = c;
    novo->prox = *mao;
    *mao = novo;
}

void mostrarMao(Jogador j) {
    NoCarta *atual = j.mao;
    printf("%s recebeu:\n", j.nome);
    while(atual != NULL) {
        printf("  %s de %s\n", nomeValor(atual->carta.valor), nomeNaipe(atual->carta.naipe));
        atual = atual->prox;
    }
}

void liberarMao(NoCarta *mao) {
    while(mao != NULL) {
        NoCarta *tmp = mao;
        mao = mao->prox;
        free(tmp);
    }
}

void salvarPlacar(char *vencedor) {
    FILE *f = fopen("placar.txt", "a");
    if (f != NULL) {
        fprintf(f, "Vencedor: %s\n", vencedor);
        fclose(f);
    }
}

int main() {
    srand(time(NULL));

    Jogador p1 = {"Jogador 1", NULL};
    Jogador p2 = {"Jogador 2", NULL};

    // Sorteia cartas
    Carta c1 = criarCartaAleatoria();
    Carta c2 = criarCartaAleatoria();

    adicionarCarta(&p1.mao, c1);
    adicionarCarta(&p2.mao, c2);

    mostrarMao(p1);
    mostrarMao(p2);

    // Decide vencedor
    if (c1.valor > c2.valor) {
        printf("Vencedor: %s\n", p1.nome);
        salvarPlacar(p1.nome);
    } else if (c2.valor > c1.valor) {
        printf("Vencedor: %s\n", p2.nome);
        salvarPlacar(p2.nome);
    } else {
        printf("Empate!\n");
        salvarPlacar("Empate");
    }

    // Libera memória
    liberarMao(p1.mao);
    liberarMao(p2.mao);

    return 0;
}
