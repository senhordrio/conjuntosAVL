/*
 * @autor: senhordrio
 * Classe da estrutura de dado árvore avl, onde serão armazenados os conjuntos.
 * Agradecimentos a @LimaEduardo por fornecer a implementação
 */

#ifndef AVL_H
#define AVL_H

#include "nohArvore.h"
#include <string>

class avl
{
	friend class conjunto;

private:
	nohArvore *raiz;
	unsigned tamanhoArvore;
	void percorrePosOrdemAux(nohArvore *atual);
	nohArvore *minimo(nohArvore *atual);
	nohArvore *insereArvoreAux(nohArvore *atual, Dado dado);
	nohArvore *arrumaBalanceamento(nohArvore *atual);
	nohArvore *rotacionaEsquerda(nohArvore *atual);
	nohArvore *rotacionaDireita(nohArvore *atual);
	nohArvore *removeArvoreAux(nohArvore *atual, Dado dado);
	void percorreInserindoEmArvoreAux(nohArvore *umNoh);
	void armazenaArvoreEmVetorAux(nohArvore *raiz, int *vetor, unsigned int *i);

public:
	avl();
	~avl();
	void insereArvore(Dado dado);
	void removeArvore(Dado dado);
	void percorrePosOrdem();
	void transplanta(nohArvore *antigo, nohArvore *novo);
	bool buscaArvore(int dado);
	unsigned getTamanhoArvore();
	void percorreInserindoEmArvore(nohArvore *raiz);
	void imprimeArvoreBonita();
	void imprimeArvoreBonita(const std::string &prefixo, const nohArvore* raiz, bool esquerdo);
};

#endif