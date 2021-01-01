/*
 * @autor: senhordrio
 * Classe da estrutura nó. Os nós da árvore.
 */

#include "nohArvore.h"

unsigned int nohArvore::calculaAltura(nohArvore *no)
{
	if (no == NULL)
	{
		return 0;
	}
	return no->altura;
}

int nohArvore::calculaBalanceamento(nohArvore *no)
{
	if (no == NULL)
	{
		return 0;
	}
	return no->fatorBalanceamento();
}

int nohArvore::fatorBalanceamento()
{
	return (calculaAltura(esquerdo) - calculaAltura(direito));
}

nohArvore::nohArvore(Dado dado)
{
	valor = dado;
	esquerdo = NULL;
	direito = NULL;
	altura = 1;
	pai = NULL;
}

nohArvore::~nohArvore()
{
	delete esquerdo;
	delete direito;
}