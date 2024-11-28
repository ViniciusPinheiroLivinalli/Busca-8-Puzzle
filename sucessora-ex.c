

// Gera os movimentos possiveis e retorna a matriz
int sucessora(Node *current, int i_moves){

        int zeroX, zeroY;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (current->puzzle[i][j] == 0) {
                    zeroX = i;
                    zeroY = j;
                }
            }
        }

         int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movimentos possíveis (cima, baixo, esquerda, direita)

            int newX = zeroX + moves[i_moves][0];
            int newY = zeroY + moves[i_moves][1];

            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                int newPuzzle[3][3];
                memcpy(newPuzzle, current->puzzle, sizeof(newPuzzle));
                // Trocar o espaço vazio com a posição adjacente
                newPuzzle[zeroX][zeroY] = newPuzzle[newX][newY];
                newPuzzle[newX][newY] = 0;
                return newPuzzle;
            }
}
