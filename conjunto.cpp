/*
 * @autor: senhordrio
 * Classe conjunto que representa a estrutura de dado conjunto.
 * Aqui estão presentes as operações básicas de conjuntos.
 * 
 */
#include "conjunto.h"

void conjunto::insere(int elemento)
{
	mDados.insereArvore(elemento);
}

void conjunto::remove(int elemento)
{
	mDados.removeArvore(elemento);
}

bool conjunto::membro(int elemento)
{
	if (mDados.buscaArvore(elemento) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void conjunto::uniao(conjunto &C1, conjunto &C2)
{
	this->mDados.percorreInserindoEmArvore(C1.mDados.raiz);
	this->mDados.percorreInserindoEmArvore(C2.mDados.raiz);
}

void conjunto::intersecao(conjunto &C1, conjunto &C2)
{
	int *vetor1 = new int[C1.mDados.tamanhoArvore];
	int *vetor2 = new int[C2.mDados.tamanhoArvore];
	unsigned int i = 0, j = 0;
	C1.mDados.armazenaArvoreEmVetorAux(C1.mDados.raiz, vetor1, &i);
	C2.mDados.armazenaArvoreEmVetorAux(C2.mDados.raiz, vetor2, &j);
	i = 0;
	while (i < C1.mDados.tamanhoArvore)
	{
		j = 0;
		while (j < C2.mDados.tamanhoArvore)
		{
			if (vetor1[i] == vetor2[j])
			{
				this->mDados.insereArvore(vetor2[j]);
			}
			j++;
		}
		i++;
	}
}

void conjunto::diferenca(conjunto &C1, conjunto &C2)
{
	int *vetor1 = new int[C1.mDados.tamanhoArvore];
	int *vetor2 = new int[C2.mDados.tamanhoArvore];
	unsigned int i = 0, j = 0;
	C1.mDados.armazenaArvoreEmVetorAux(C1.mDados.raiz, vetor1, &i);
	C2.mDados.armazenaArvoreEmVetorAux(C2.mDados.raiz, vetor2, &j);
	for(i = 0; i < C1.mDados.tamanhoArvore; i++)
	{
		bool existe = false;
		for(j = 0; j < C2.mDados.tamanhoArvore; j++)
		{
			if(vetor1[i] == vetor2[j])
			{
				existe = true;
			}
		}
		if(not existe)
		{
			this->mDados.insereArvore(vetor1[i]);
		}
	}
}

unsigned conjunto::tamanho()
{
	return mDados.getTamanhoArvore();
}

void conjunto::imprime()
{
	mDados.percorrePosOrdem();
}

void conjunto::depura()
{
	this->mDados.imprimeArvoreBonita();
}


