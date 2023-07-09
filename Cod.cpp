#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> calculaDistanciaEdicao(const std::string& palavra1, const std::string& palavra2) {
    int m = palavra1.length();
    int n = palavra2.length();

    // Criação da tabela
    std::vector<std::vector<int>> tabela(m + 1, std::vector<int>(n + 1));

    // Preenchimento da primeira linha
    for (int i = 0; i <= m; ++i) {
        tabela[i][0] = i;
    }

    // Preenchimento da primeira coluna
    for (int j = 0; j <= n; ++j) {
        tabela[0][j] = j;
    }

    // Preenchimento do restante da tabela
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (palavra1[i - 1] == palavra2[j - 1]) {
                tabela[i][j] = tabela[i - 1][j - 1];
            } else {
                tabela[i][j] = std::min({ tabela[i - 1][j - 1], tabela[i][j - 1], tabela[i - 1][j] }) + 1;
            }
        }
    }

    // Impressão da tabela
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            std::cout << tabela[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Retorno do valor na última célula da tabela
    return tabela;
}

void imprimeOperacoes(const std::string& x, const std::string& y, const std::vector<std::vector<int>>& E) {
    std::vector<std::string> operacoes;  // Vetor para armazenar as operações

    int i = x.length();
    int j = y.length();

    // Percorre a tabela de distância de edição de trás para frente
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            // Caracteres iguais, nenhuma operação necessária
            i--;
            j--;
        } else if (E[i][j] == E[i - 1][j - 1] + 1) {
            // Operação de substituição
            operacoes.push_back("Substituir '" + std::string(1, x[i - 1]) + "' por '" + std::string(1, y[j - 1]) + "'");
            i--;
            j--;
        } else if (E[i][j] == E[i - 1][j] + 1) {
            // Operação de remoção
            operacoes.push_back("Remover '" + std::string(1, x[i - 1]) + "'");
            i--;
        } else if (E[i][j] == E[i][j - 1] + 1) {
            // Operação de inserção
            operacoes.push_back("Inserir '" + std::string(1, y[j - 1]) + "'");
            j--;
        }
    }

    // Se sobraram caracteres em x, são removidos
    while (i > 0) {
        operacoes.push_back("Remover '" + std::string(1, x[i - 1]) + "'");
        i--;
    }

    // Se sobraram caracteres em y, são inseridos
    while (j > 0) {
        operacoes.push_back("Inserir '" + std::string(1, y[j - 1]) + "'");
        j--;
    }

    // Imprime as operações na ordem correta (invertida)
    for (auto it = operacoes.rbegin(); it != operacoes.rend(); ++it) {
        std::cout << *it << std::endl;
    }
}

int main() {
    std::string x = "logaritmo";
    std::string y = "algoritmo";
    std::vector<std::vector<int>> E= calculaDistanciaEdicao(x, y);

    imprimeOperacoes(x, y, E);

    return 0;
}
