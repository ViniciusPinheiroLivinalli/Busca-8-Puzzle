

// Gera os movimentos possiveis e retorna a matriz
int sucessora(Node *current, int i_moves, int *newX, int *newY){

        int zeroX, zeroY;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (current->puzzle[i][j] == 0) {
                    zeroX = i;
                    zeroY = j;
                }
            }
        }

         int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movimentos poss�veis (cima, baixo, esquerda, direita)
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                *newX = zeroX + moves[i_moves][0];
                *newY = zeroY + moves[i_moves][1];
            }
}
