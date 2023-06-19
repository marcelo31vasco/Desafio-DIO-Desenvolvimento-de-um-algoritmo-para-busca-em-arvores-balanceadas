/* Desenvolvimento de um algoritmo para busca em árvores balanceadas

Neste projeto final é proposta a implementação de uma árvore balanceada para busca binária.
Em nossas aulas aprendemos como este tipo de estrutura se comporta, no entanto, não tratamos 
a questão do balanceamento, que visa garantir sempre o melhor custo de busca neste tipo de estrutura. 
Este então é nosso desafio para este projeto. O balanceamento em uma árvore é a forma de ajustar os 
elementos de forma que nunca aconteça o problema de desbalanceamento. Sendo que o desbalanceamento 
é a forma de uma árvore com suas “folhas” caídas para um único lado, como pode ser observado na figura 
abaixo. O processo para uma árvore de busca balanceada é o mesmo para uma árvore binária convencional, 
com o adicional de uma função de balanceamento, que deve a todo momento rearranjar a estrutura de dados da árvore.

*/
#include <iostream>

struct No {
    int dado;
    No* esquerda;
    No* direita;
    int altura;
};

int obterAltura(No* no) {
    if (no == nullptr) {
        return -1;
    }
    return no->altura;
}

int fatorBalanceamento(No* no) {
    if (no == nullptr) {
        return 0;
    }
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

No* rotacionarDireita(No* no) {
    No* novaRaiz = no->esquerda;
    no->esquerda = novaRaiz->direita;
    novaRaiz->direita = no;

    no->altura = std::max(obterAltura(no->esquerda), obterAltura(no->direita)) + 1;
    novaRaiz->altura = std::max(obterAltura(novaRaiz->esquerda), obterAltura(novaRaiz->direita)) + 1;

    return novaRaiz;
}

No* rotacionarEsquerda(No* no) {
    No* novaRaiz = no->direita;
    no->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = no;

    no->altura = std::max(obterAltura(no->esquerda), obterAltura(no->direita)) + 1;
    novaRaiz->altura = std::max(obterAltura(novaRaiz->esquerda), obterAltura(novaRaiz->direita)) + 1;

    return novaRaiz;
}

No* inserir(No* no, int dado) {
    if (no == nullptr) {
        No* novoNo = new No;
        novoNo->dado = dado;
        novoNo->esquerda = nullptr;
        novoNo->direita = nullptr;
        novoNo->altura = 0;
        return novoNo;
    }

    if (dado < no->dado) {
        no->esquerda = inserir(no->esquerda, dado);
    } else if (dado > no->dado) {
        no->direita = inserir(no->direita, dado);
    } else {
        // Ignora valores duplicados (suposição: não são permitidos valores duplicados)
        return no;
    }

    no->altura = std::max(obterAltura(no->esquerda), obterAltura(no->direita)) + 1;

    int fator = fatorBalanceamento(no);

    if (fator > 1 && dado < no->esquerda->dado) {
        // Caso Esquerda-Esquerda
        return rotacionarDireita(no);
    }

    if (fator < -1 && dado > no->direita->dado) {
        // Caso Direita-Direita
        return rotacionarEsquerda(no);
    }

    if (fator > 1 && dado > no->esquerda->dado) {
        // Caso Esquerda-Direita
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (fator < -1 && dado < no->direita->dado) {
        // Caso Direita-Esquerda
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

void percorrerEmOrdem(No* no) {
    if (no != nullptr) {
        percorrerEmOrdem(no->esquerda);
        std::cout << no->dado << " ";
        percorrerEmOrdem(no->direita);
    }
}

int main() {
    No* raiz = nullptr;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    std::cout << "Percurso em ordem da arvore balanceada: ";
    percorrerEmOrdem(raiz);
    std::cout << std::endl;

    return 0;
}
