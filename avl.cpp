/*
 * @autor: senhordrio
 * Classe da estrutura de dado árvore avl, onde serão armazenados os conjuntos.
 * Agradecimentos a @LimaEduardo por fornecer a implementação
 */

#include "avl.h"

unsigned avl::getTamanhoArvore()
{
	return tamanhoArvore;
}

avl::avl()
{
	raiz = NULL;
	tamanhoArvore = 0;
}

avl::~avl()
{
	delete raiz;
}

void avl::transplanta(nohArvore *antigo, nohArvore *novo)
{
	if (raiz == antigo)
	{
		raiz = novo;
	}
	else if (antigo == antigo->pai->esquerdo)
	{
		antigo->pai->esquerdo = novo;
	}
	else
	{
		antigo->pai->direito = novo;
	}

	if (novo != NULL)
	{
		novo->pai = antigo->pai;
	}
}

void avl::insereArvore(Dado dado)
{
	raiz = insereArvoreAux(raiz, dado);
}

nohArvore *avl::insereArvoreAux(nohArvore *atual, Dado dado)
{
	if (atual == NULL)
	{
		nohArvore *novo = new nohArvore(dado);
		tamanhoArvore++;
		return novo;
	}

	if (dado < atual->valor)
	{
		atual->esquerdo = insereArvoreAux(atual->esquerdo, dado);
		atual->esquerdo->pai = atual;
	}
	else if (dado > atual->valor)
	{
		atual->direito = insereArvoreAux(atual->direito, dado);
		atual->direito->pai = atual;
	}
	else
	{
		return atual;
	}

	return arrumaBalanceamento(atual);
}

nohArvore *avl::arrumaBalanceamento(nohArvore *atual)
{
	unsigned int alturaEsq = atual->calculaAltura(atual->esquerdo);
	unsigned int alturaDir = atual->calculaAltura(atual->direito);
	atual->altura = 1 + std::max(alturaEsq, alturaDir);
	int bal = atual->fatorBalanceamento();

	if ((bal >= -1) and (bal <= 1))
	{
		return atual;
	}
	if ((bal > 1) and (atual->calculaBalanceamento(atual->esquerdo) >= 0))
	{
		return rotacionaDireita(atual);
	}
	if ((bal > 1) and (atual->calculaBalanceamento(atual->esquerdo) < 0))
	{
		atual->esquerdo = rotacionaEsquerda(atual->esquerdo);
		atual->esquerdo->pai = atual;
		return rotacionaDireita(atual);
	}
	if (bal < -1 and (atual->calculaBalanceamento(atual->direito) <= 0))
	{
		return rotacionaEsquerda(atual);
	}
	if ((bal < -1) and (atual->calculaBalanceamento(atual->direito) > 0))
	{
		atual->direito = rotacionaDireita(atual->direito);
		atual->direito->pai = atual;
		return rotacionaEsquerda(atual);
	}
	return NULL;
}
nohArvore *avl::rotacionaEsquerda(nohArvore *atual)
{
	nohArvore *aux = atual->direito;

	atual->direito = aux->esquerdo;

	if (aux->esquerdo != NULL)
	{
		aux->esquerdo->pai = atual;
	}

	aux->pai = atual->pai;

	if (atual->pai == NULL)
	{
		raiz = aux;
	}
	else if (atual == atual->pai->esquerdo)
	{
		atual->pai->esquerdo = aux;
	}
	else
	{
		atual->pai->direito = aux;
	}

	aux->esquerdo = atual;
	atual->pai = aux;

	unsigned int alturaEsq = atual->calculaAltura(atual->esquerdo);
	unsigned int alturaDir = atual->calculaAltura(atual->direito);

	atual->altura = 1 + std::max(alturaEsq, alturaDir);
	aux->altura = 1 + std::max(alturaEsq, alturaDir);

	return aux;
}

nohArvore *avl::rotacionaDireita(nohArvore *atual)
{
	nohArvore *aux = atual->esquerdo;
	atual->esquerdo = aux->direito;
	if (aux->direito != NULL)
	{
		aux->direito->pai = atual;
	}
	aux->pai = atual->pai;
	if (atual->pai == NULL)
	{
		raiz = aux;
	}
	else if (atual == atual->pai->esquerdo)
	{
		atual->pai->esquerdo = aux;
	}
	else
	{
		atual->pai->direito = aux;
	}
	aux->direito = atual;
	atual->pai = aux;
	unsigned int alturaEsq = atual->calculaAltura(atual->esquerdo);
	unsigned int alturaDir = atual->calculaAltura(atual->direito);
	atual->altura = 1 + std::max(alturaEsq, alturaDir);
	aux->altura = 1 + std::max(alturaEsq, alturaDir);
	return aux;
}

void avl::percorrePosOrdem()
{
	percorrePosOrdemAux(raiz);
	std::cout << std::endl;
}

void avl::percorrePosOrdemAux(nohArvore *atual)
{
	if (atual != NULL)
	{
		percorrePosOrdemAux(atual->esquerdo);
		percorrePosOrdemAux(atual->direito);
		std::cout << atual->valor << " ";
	}
}

void avl::percorreInserindoEmArvore(nohArvore *raiz)
{
	percorreInserindoEmArvoreAux(raiz);
}

//percorre a arvore em ordem inserindo em outra arvore
void avl::percorreInserindoEmArvoreAux(nohArvore *atual)
{
	if (atual != NULL)
	{
		percorreInserindoEmArvoreAux(atual->esquerdo);
		percorreInserindoEmArvoreAux(atual->direito);
		this->insereArvore(atual->valor);
	}
}

void avl::armazenaArvoreEmVetorAux(nohArvore *atual, int *vetor, unsigned int *i)
{
	if (atual == NULL)
		return;
	if (atual->esquerdo != NULL)
		armazenaArvoreEmVetorAux(atual->esquerdo, vetor, i);
	if (atual->direito != NULL)
		armazenaArvoreEmVetorAux(atual->direito, vetor, i);
	vetor[*i] = atual->valor;
	(*i)++;
}

void avl::removeArvore(Dado dado)
{
	raiz = removeArvoreAux(raiz, dado);
}

nohArvore *avl::removeArvoreAux(nohArvore *atual, Dado dado)
{
	if (atual == NULL)
	{
		return atual;
	}
	nohArvore *novaRaizSubArvore = atual;
	if (dado < atual->valor)
	{
		atual->esquerdo = removeArvoreAux(atual->esquerdo, dado);
	}
	else if (dado > atual->valor)
	{
		atual->direito = removeArvoreAux(atual->direito, dado);
	}
	else
	{
		if (atual->esquerdo == NULL)
		{
			novaRaizSubArvore = atual->direito;
			transplanta(atual, atual->direito);
		}
		else if (atual->direito == NULL)
		{
			novaRaizSubArvore = atual->esquerdo;
			transplanta(atual, atual->direito);
		}
		else
		{
			nohArvore *sucessor = minimo(atual->direito);
			novaRaizSubArvore = sucessor;
			if (sucessor->pai != atual)
			{
				transplanta(sucessor, sucessor->direito);
				nohArvore *aux = sucessor->pai;
				while (aux != atual->direito)
				{
					unsigned int alturaEsq = atual->calculaAltura(atual->esquerdo);
					unsigned int alturaDir = atual->calculaAltura(atual->direito);
					aux->altura = 1 + std::max(alturaEsq, alturaDir);
					aux = aux->pai;
				}
				sucessor->direito = arrumaBalanceamento(atual->direito);
				sucessor->direito->pai = sucessor;
			}

			transplanta(atual, sucessor);
			sucessor->esquerdo = atual->esquerdo;
			sucessor->esquerdo->pai = sucessor;
		}
		atual->esquerdo = NULL;
		atual->direito = NULL;
		tamanhoArvore--;
		delete atual;
	}
	if (novaRaizSubArvore == NULL)
	{
		return novaRaizSubArvore;
	}
	return arrumaBalanceamento(novaRaizSubArvore);
}

nohArvore *avl::minimo(nohArvore *atual)
{
	while (atual->esquerdo != NULL)
	{
		atual = atual->esquerdo;
	}
	return atual;
}

bool avl::buscaArvore(int dado)
{
	nohArvore *atual = raiz;
	while (atual != NULL)
	{
		if (atual->valor == dado)
		{
			return true;
		}
		else if (atual->valor > dado)
		{
			atual = atual->esquerdo;
		}
		else
		{
			atual = atual->direito;
		}
	}
	return false;
}

void avl::imprimeArvoreBonita()
{
	imprimeArvoreBonita("", raiz ,false);
}


void avl::imprimeArvoreBonita(const std::string &prefixo, const nohArvore* atual, bool esquerdo)
{
	if(atual != NULL)
	{
		std::cout << prefixo;
		std::cout << (esquerdo ? "|---" : "'---");
		std::cout << atual->valor << std::endl;
		imprimeArvoreBonita(prefixo + (esquerdo ? "|   " : "   "), atual->esquerdo, true);
		imprimeArvoreBonita(prefixo + (esquerdo ? "|   " : "   "), atual->direito, false);
	}
}
