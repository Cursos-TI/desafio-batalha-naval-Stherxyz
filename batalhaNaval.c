#include <stdio.h>
#include <locale.h>
#include <stdlib.h> // para abs()

#define habilidade 5 // Tamanho da matriz de habilidade
#define navio 3      // Valor que representa o navio
#define hab 5        // Valor que representa a área da habilidade

// Cone
void criarCone(int matriz[habilidade][habilidade]) {
    for (int i = 0; i < habilidade; i++) {
        for (int j = 0; j < habilidade; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int i = 0; i < habilidade; i++) {
        for (int j = habilidade / 2 - i; j <= habilidade / 2 + i; j++) {
            if (j >= 0 && j < habilidade) matriz[i][j] = 1;
        }
    }
}

// Cruz
void criarCruz(int matriz[habilidade][habilidade]) {
    for (int i = 0; i < habilidade; i++) {
        for (int j = 0; j < habilidade; j++) {
            matriz[i][j] = (i == habilidade / 2 || j == habilidade / 2) ? 1 : 0;
        }
    }
}

// Octaedro (losango)
void criarOctaedro(int matriz[habilidade][habilidade]) {
    for (int i = 0; i < habilidade; i++) {
        for (int j = 0; j < habilidade; j++) {
            if (abs(i - habilidade / 2) + abs(j - habilidade / 2) <= habilidade / 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Aplicando as habilidade no tabuleiro
void aplicarHabilidade(int tab[10][10], int habilidadeMatriz[habilidade][habilidade], int origemX, int origemY) {
    int offset = habilidade / 2; // Centraliza habilidade
    for (int i = 0; i < habilidade; i++) {
        for (int j = 0; j < habilidade; j++) {
            if (habilidadeMatriz[i][j] == 1) {
                int x = origemX + (i - offset);
                int y = origemY + (j - offset);
                // Verifica se está dentro do tabuleiro
                if (x >= 0 && x < 10 && y >= 0 && y < 10) {
                    if (tab[x][y] == 0) // Substitui a água
                        tab[x][y] = hab;
                }
            }
        }
    }
}

// Imprimindo o tabuleiro
void imprimirTabuleiro(int tab[10][10]) {
    printf(" * ");
    for (int j = 0; j < 10; j++) printf("%c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int tabuleiro[10][10] = {0}; // inicializa tudo com água (0)
    int cone[habilidade][habilidade], cruz[habilidade][habilidade], octaedro[habilidade][habilidade];

    // Matrizes das habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Colocando navios no tabuleiro
    tabuleiro[2][2] = navio;
    tabuleiro[5][5] = navio;
    tabuleiro[7][3] = navio;

    // Aplicando habilidades
    aplicarHabilidade(tabuleiro, cone, 2, 5);
    aplicarHabilidade(tabuleiro, cruz, 6, 2);
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);

    // Mostrar resultado
    imprimirTabuleiro(tabuleiro);

    return 0;
}
