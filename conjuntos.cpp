#include <iostream>

using namespace std;

typedef int Dado;

class nohArvore
{
	friend class avl;

private:
	nohArvore *esquerda;
	nohArvore *direita;
	nohArvore *pai;
	Dado valor;
	int altura;
	int calculaBalanceamento(nohArvore *no);
	unsigned int calculaAltura(nohArvore *no);

public:
	int fatorBalanceamento();
	nohArvore(Dado dado);
	~nohArvore();
};

class avl
{
	friend class conjunto;

private:
	nohArvore *raiz;
	unsigned tamanhoArvore;
	void percorrePosOrdemAux(nohArvore *atual, int nivel);
	nohArvore *maximoAux(nohArvore *atual);
	nohArvore *minimoAux(nohArvore *atual);
	nohArvore *insereArvoreAux(nohArvore *atual, Dado dado);
	nohArvore *arrumaBalanceamento(nohArvore *atual);
	nohArvore *rotacionaEsquerda(nohArvore *atual);
	nohArvore *rotacionaDireita(nohArvore *atual);
	nohArvore *removeArvoreAux(nohArvore *atual, Dado dado);
	void percorreInserindoEmArvoreAux(nohArvore *umNoh);
	void armazenaArvoreEmVetorAux(nohArvore* raiz, int *vetor, unsigned int *i);

public:
	avl();
	~avl();
	void insereArvore(Dado dado);
	void removeArvore(Dado dado);
	void percorrePosOrdem();
	Dado maximo();
	Dado minimo();
	void transplanta(nohArvore *antigo, nohArvore *novo);
	bool buscaArvore(int dado);
	unsigned getTamanhoArvore();
	void percorreInserindoEmArvore(nohArvore *raiz);
	void intersecaoArvores(nohArvore *raizC1, nohArvore *raizC2);
};

unsigned avl::getTamanhoArvore()
{
	return tamanhoArvore;
}

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
	return (calculaAltura(esquerda) - calculaAltura(direita));
}

nohArvore::nohArvore(Dado dado)
{
	valor = dado;
	esquerda = NULL;
	direita = NULL;
	altura = 1;
	pai = NULL;
}

nohArvore::~nohArvore()
{
	delete esquerda;
	delete direita;
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
	else if (antigo == antigo->pai->esquerda)
	{
		antigo->pai->esquerda = novo;
	}
	else
	{
		antigo->pai->direita = novo;
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
		atual->esquerda = insereArvoreAux(atual->esquerda, dado);
		atual->esquerda->pai = atual;
	}
	else if (dado > atual->valor)
	{
		atual->direita = insereArvoreAux(atual->direita, dado);
		atual->direita->pai = atual;
	}
	else
	{
		return atual;
	}

	return arrumaBalanceamento(atual);
}

nohArvore *avl::arrumaBalanceamento(nohArvore *atual)
{
	unsigned int alturaEsq = atual->calculaAltura(atual->esquerda);
	unsigned int alturaDir = atual->calculaAltura(atual->direita);
	atual->altura = 1 + max(alturaEsq, alturaDir);
	int bal = atual->fatorBalanceamento();

	if ((bal >= -1) and (bal <= 1))
	{
		return atual;
	}
	if ((bal > 1) and (atual->calculaBalanceamento(atual->esquerda) >= 0))
	{
		return rotacionaDireita(atual);
	}
	if ((bal > 1) and (atual->calculaBalanceamento(atual->esquerda) < 0))
	{
		atual->esquerda = rotacionaEsquerda(atual->esquerda);
		atual->esquerda->pai = atual;
		return rotacionaDireita(atual);
	}
	if (bal < -1 and (atual->calculaBalanceamento(atual->direita) <= 0))
	{
		return rotacionaEsquerda(atual);
	}
	if ((bal < -1) and (atual->calculaBalanceamento(atual->direita) > 0))
	{
		atual->direita = rotacionaDireita(atual->direita);
		atual->direita->pai = atual;
		return rotacionaEsquerda(atual);
	}
	return NULL;
}
nohArvore *avl::rotacionaEsquerda(nohArvore *atual)
{
	nohArvore *aux = atual->direita;

	atual->direita = aux->esquerda;

	if (aux->esquerda != NULL)
	{
		aux->esquerda->pai = atual;
	}

	aux->pai = atual->pai;

	if (atual->pai == NULL)
	{
		raiz = aux;
	}
	else if (atual == atual->pai->esquerda)
	{
		atual->pai->esquerda = aux;
	}
	else
	{
		atual->pai->direita = aux;
	}

	aux->esquerda = atual;
	atual->pai = aux;

	unsigned int alturaEsq = atual->calculaAltura(atual->esquerda);
	unsigned int alturaDir = atual->calculaAltura(atual->direita);

	atual->altura = 1 + max(alturaEsq, alturaDir);
	aux->altura = 1 + max(alturaEsq, alturaDir);

	return aux;
}

nohArvore *avl::rotacionaDireita(nohArvore *atual)
{
	nohArvore *aux = atual->esquerda;
	atual->esquerda = aux->direita;
	if (aux->direita != NULL)
	{
		aux->direita->pai = atual;
	}
	aux->pai = atual->pai;
	if (atual->pai == NULL)
	{
		raiz = aux;
	}
	else if (atual == atual->pai->esquerda)
	{
		atual->pai->esquerda = aux;
	}
	else
	{
		atual->pai->direita = aux;
	}
	aux->direita = atual;
	atual->pai = aux;
	unsigned int alturaEsq = atual->calculaAltura(atual->esquerda);
	unsigned int alturaDir = atual->calculaAltura(atual->direita);
	atual->altura = 1 + max(alturaEsq, alturaDir);
	aux->altura = 1 + max(alturaEsq, alturaDir);
	return aux;
}

void avl::percorrePosOrdem()
{
	percorrePosOrdemAux(raiz, 0);
	cout << endl;
}

void avl::percorrePosOrdemAux(nohArvore *atual, int nivel)
{
	if (atual != NULL)
	{
		percorrePosOrdemAux(atual->esquerda, nivel + 1);
		percorrePosOrdemAux(atual->direita, nivel + 1);
		cout << atual->valor << " ";
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
		percorreInserindoEmArvoreAux(atual->esquerda);
		percorreInserindoEmArvoreAux(atual->direita);
		this->insereArvore(atual->valor);
	}
}



void avl::armazenaArvoreEmVetorAux(nohArvore* atual, int *vetor, unsigned int *i)
{
	if(atual == NULL)
		return;
	if(atual->esquerda != NULL)
		armazenaArvoreEmVetorAux(atual->esquerda, vetor, i);
	if(atual->direita != NULL)
		armazenaArvoreEmVetorAux(atual->direita, vetor, i);
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
		atual->esquerda = removeArvoreAux(atual->esquerda, dado);
	}
	else if (dado > atual->valor)
	{
		atual->direita = removeArvoreAux(atual->direita, dado);
	}
	else
	{
		if (atual->esquerda == NULL)
		{
			novaRaizSubArvore = atual->direita;
			transplanta(atual, atual->direita);
		}
		else if (atual->direita == NULL)
		{
			novaRaizSubArvore = atual->esquerda;
			transplanta(atual, atual->direita);
		}
		else
		{
			nohArvore *sucessor = minimoAux(atual->direita);
			novaRaizSubArvore = sucessor;
			if (sucessor->pai != atual)
			{
				transplanta(sucessor, sucessor->direita);
				nohArvore *aux = sucessor->pai;
				while (aux != atual->direita)
				{
					unsigned int alturaEsq = atual->calculaAltura(atual->esquerda);
					unsigned int alturaDir = atual->calculaAltura(atual->direita);
					aux->altura = 1 + max(alturaEsq, alturaDir);
					aux = aux->pai;
				}
				sucessor->direita = arrumaBalanceamento(atual->direita);
				sucessor->direita->pai = sucessor;
			}

			transplanta(atual, sucessor);
			sucessor->esquerda = atual->esquerda;
			sucessor->esquerda->pai = sucessor;
		}
		atual->esquerda = NULL;
		atual->direita = NULL;
		tamanhoArvore--;
		delete atual;
	}
	if (novaRaizSubArvore == NULL)
	{
		return novaRaizSubArvore;
	}
	return arrumaBalanceamento(novaRaizSubArvore);
}

nohArvore *avl::minimoAux(nohArvore *atual)
{
	while (atual->esquerda != NULL)
	{
		atual = atual->esquerda;
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
			atual = atual->esquerda;
		}
		else
		{
			atual = atual->direita;
		}
	}
	return false;
}

class conjunto
{
private:
	avl mDados;

public:
	// sugestão de métodos públicos para sua classe conjunto
	void insere(int elemento);
	void remove(int elemento);
	bool membro(int elemento);

	void uniao(conjunto &C1, conjunto &C2);
	void intersecao(conjunto &C1, conjunto &C2);
	void diferenca(conjunto &C1, conjunto &C2);

	unsigned tamanho();

	void imprime();
	void depura();
};

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
	while(i < C1.mDados.tamanhoArvore)
	{
		j = 0;
		while(j < C2.mDados.tamanhoArvore)
		{
			if(vetor1[i] == vetor2[j])
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
	i = 0;
	while(i < C1.mDados.tamanhoArvore)
	{
		j = 0;
		while(j < C2.mDados.tamanhoArvore)
		{
			if(vetor1[i] != vetor2[j])
			{
				this->mDados.insereArvore(vetor1[i]);
			}
			j++;
		}
		i++;
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
	//TODO
}

// função que retorna uma posição no vetor para um dado caracter maiúsculo
inline unsigned char2pos(char c)
{
	return unsigned(c) - 65;
}

int main()
{
	conjunto meusConjuntos[26];
	char operacao;
	// conjuntos são representados por letras maiúsculas
	char conjunto1, conjunto2, conjunto3;
	int elemento;
	unsigned pos1, pos2, pos3;

	do
	{
		cin >> operacao;
		switch (operacao)
		{
		case 'i': // inserir
			cin >> conjunto1 >> elemento;
			pos1 = char2pos(conjunto1);
			meusConjuntos[pos1].insere(elemento);
			break;
		case 'r': // remover
			cin >> conjunto1 >> elemento;
			pos1 = char2pos(conjunto1);
			meusConjuntos[pos1].remove(elemento);
			break;
		case 'm': // checa pertinência
			cin >> conjunto1 >> elemento;
			pos1 = char2pos(conjunto1);
			cout << meusConjuntos[pos1].membro(elemento) << endl;
			break;
		case '+': // efetua união
			// conjunto1 terá o resultado da união de conjunto2 com conjunto3
			cin >> conjunto1 >> conjunto2 >> conjunto3;
			pos1 = char2pos(conjunto1);
			pos2 = char2pos(conjunto2);
			pos3 = char2pos(conjunto3);
			meusConjuntos[pos1].uniao(meusConjuntos[pos2], meusConjuntos[pos3]);
			break;
		case '*': // efetua interseção
			// conjunto1 terá o resultado da interseção de conjunto2 com conjunto3
			cin >> conjunto1 >> conjunto2 >> conjunto3;
			pos1 = char2pos(conjunto1);
			pos2 = char2pos(conjunto2);
			pos3 = char2pos(conjunto3);
			meusConjuntos[pos1].intersecao(meusConjuntos[pos2], meusConjuntos[pos3]);
			break;
		case '-': // efetua diferença
			// conjunto1 terá o resultado da diferença de conjunto2 para o conjunto3
			cin >> conjunto1 >> conjunto2 >> conjunto3;
			pos1 = char2pos(conjunto1);
			pos2 = char2pos(conjunto2);
			pos3 = char2pos(conjunto3);
			meusConjuntos[pos1].diferenca(meusConjuntos[pos2], meusConjuntos[pos3]);
			break;
		case 't': // tamanho
			cin >> conjunto1;
			pos1 = char2pos(conjunto1);
			cout << meusConjuntos[pos1].tamanho() << endl;
			break;
		case 'd': // mostrar estrutura
			cin >> conjunto1;
			pos1 = char2pos(conjunto1);
			meusConjuntos[pos1].depura();
			break;
		case 'p': // imprimir dados
			cin >> conjunto1;
			pos1 = char2pos(conjunto1);
			meusConjuntos[pos1].imprime();
			break;
		case 's': // sair
			break;
		default:
			cout << "Opção inválida!" << endl;
		}
	} while (operacao != 's');

	return 0;
}