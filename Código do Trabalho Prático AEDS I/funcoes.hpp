#ifndef FUNCOES_H
#define FUNCOES_H

#define MAXTAM 5
#define INICIO 0

typedef int TChave;

typedef struct TCelula_str *TApontador;

typedef struct{
    TChave codigo;
    char nome[30];
    int horas;
} TProjeto;

typedef struct{
    TProjeto item[MAXTAM];
    int primeiro;
    int ultimo;
} TListaSequencial;

typedef struct{

    TChave codfuncionario;
    char nomefuncionario[40];
    char endereco[40];
    int dependentes;
    TListaSequencial projetos;
} TFuncionario;

typedef struct TCelula_str{
    TFuncionario item;
    TApontador prox;
} TCelula;

typedef struct{
    TApontador primeiro;
    TApontador ultimo;
} TListaEncadeada;

void menu();

// Funções TAD
void CriarListaEncadeadaVazia(TListaEncadeada *lista);// Cria uma lista encadeada vazia
int VerificarListaEncadeadaVazia(TListaEncadeada lista);// Verifica se a lista encadeada está vazia
void CriarListaSequencialVazia(TListaSequencial *Lista);// Cria uma lista sequencial vazia
int VerificarListaSequencialVazia(TListaSequencial lista);// Verifica se a lista sequencial está vazia
void InsereListaEncadeada(TFuncionario f, TListaEncadeada *lista);// Insere a lista encadeada
void InsereListaSequencial(TProjeto x, TListaSequencial *lista);// Insere a lista sequencial
int BuscaEncadeada(TChave cod, TListaEncadeada lista, TApontador *p);// Busca a lista encadeada
int BuscaSequencial(int cod, TListaSequencial lista, int *p);// Busca a lista sequencial
// Funções específicas
void CadastroDeFuncionarios(TListaEncadeada *lista);// Cadastra os funcionarios
void CadastroDeProjetos(TListaEncadeada *lista);// Cadastra os projetos
void MostraProjetos(TListaSequencial Lista);// Imprime os projetos
void ExclusaoDeProjeto(TListaEncadeada *lista);// Exclui os projetos
void BuscaFuncionario(TListaEncadeada lista);// Consulta os funcionarios
void ExcluiFuncionarioSemProjeto(TListaEncadeada *lista);// Exclui funcionarios sem projetos
void ExcluiFuncionario(TListaEncadeada *lista);// Exclui funcionario
void MostraContraCheques(TListaEncadeada *lista);// Imprime o contra cheque
void RemoveFuncionario(int p, TListaSequencial *lista, TProjeto *Proj);// Remove funcionarios


#endif