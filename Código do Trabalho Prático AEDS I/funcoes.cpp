#include <iostream>
#include <windows.h>
#include "funcoes.hpp"

using namespace std;

void menu()
{
    cout << "___________MENU___________" << endl;
    cout << "1-Incluir novo funcionario" << endl;
    cout << "2-Incluir novos projetos" << endl;
    cout << "3-Excluir Projeto" << endl;
    cout << "4-Excluir funcionario S/Projeto" << endl;
    cout << "5-Excluir Funcionario" << endl;
    cout << "6-Consulta Funcionario" << endl;
    cout << "7-Imprimir Contra-Cheque" << endl;
    cout << "8-Sair" << endl;
    cout << "__________________________" << endl
         << endl;
}

void CriarListaEncadeadaVazia(TListaEncadeada *lista)
{
    lista->primeiro = new TCelula;
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

int VerificarListaEncadeadaVazia(TListaEncadeada lista)
{
    return (lista.primeiro == lista.ultimo);
}

void CriarListaSequencialVazia(TListaSequencial *Lista)
{
    Lista->primeiro = INICIO;
    Lista->ultimo = Lista->primeiro;
}

int VerificarListaSequencialVazia(TListaSequencial lista)
{
    return (lista.primeiro == lista.ultimo);
}

void InsereListaEncadeada(TFuncionario f, TListaEncadeada *lista)
{
    lista->ultimo->prox = new TCelula;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item = f;
    lista->ultimo->prox = NULL;
}

void InsereListaSequencial(TProjeto x, TListaSequencial *Lista)
{
    if (Lista->ultimo == MAXTAM)
        cout << "Limite de projetos" << endl;
    else
    {
        Lista->item[Lista->ultimo] = x;
        Lista->ultimo++;
    }
}

int BuscaEncadeada(TChave cod, TListaEncadeada lista, TApontador *p)
{
    TApontador aux = lista.primeiro;
    int achou = 0;

    while ((!achou) && (aux->prox != NULL))
        if (aux->prox->item.codfuncionario == cod)
            achou = 1;
        else
            aux = aux->prox;
    *p = aux;
    return (achou);
}

int BuscaSequencial(int cod, TListaSequencial lista, int *p)
{
    int i = lista.primeiro;
    int achou = 0;

    while ((!achou) && (i < lista.ultimo))
        if (lista.item[i].codigo == cod)
            achou = 1;
        else
            i++;
    *p = i;
    return (achou);
}

void ApagaFuncionario(TApontador x, TListaEncadeada *lista, TFuncionario *f)
{
    TApontador q;

    if ((VerificarListaEncadeadaVazia(*lista)) || (x == NULL) || (x->prox == NULL))
    {
        cout << "Lista Vazia";
    }
    else
    {
        q = x->prox;
        *f = q->item;
        x->prox = q->prox;

        if (x->prox == NULL)
        {
            lista->ultimo = x;
        }
        delete q;
    }
}

void ExcluiFuncionario(TListaEncadeada *lista)
{
    TFuncionario f;
    TApontador x = lista->primeiro;
    int cont = 0;

    while (x->prox != NULL)
    {
        ApagaFuncionario(x, lista, &f);
        cont++;
    }

    system("cls");

    cout << "EXCLUSAO DE FUNCIONARIOS" << endl;
    cout << endl
         << cont << " Funcionario(s) excluido(s) com sucesso!" << endl;
    system("pause");
    system("cls");
}

void ListaFuncionario(TListaEncadeada *lista)
{
    TApontador aux = lista->primeiro->prox;

    system("cls");

    cout << "LISTAGEM DE FUNCIONARIOS\n";

    while (aux)
    {
        cout << "\nCodigo: " << aux->item.codfuncionario;
        cout << "\nNome: " << aux->item.nomefuncionario;
        cout << "\nEndereco: " << aux->item.endereco;
        cout << "\nDependentes: " << aux->item.dependentes << endl
             << endl;
        aux = aux->prox;
    }
    system("pause");
    system("cls");
}

void BuscaFuncionario(TListaEncadeada lista)
{
    TChave cod;
    TApontador p;
    system("cls");
    int ret;

    cout << "CONSULTA DE FUNCIONARIO" << endl;
    cout << "Informe o codigo do funcionario: ";
    cin >> cod;

    ret = BuscaEncadeada(cod, lista, &p); // buscando funcionario

    if (ret == 1)
    {
        cout << "Codigo: " << p->prox->item.codfuncionario << endl;
        cout << "Nome: " << p->prox->item.nomefuncionario << endl;
        cout << "Endereco: " << p->prox->item.endereco << endl;
        cout << "Dependentes: " << p->prox->item.dependentes << endl
             << endl;
        cout << "O funcionario solicitado possui o(s) seguintes(s) projeto(s)!" << endl;

        MostraProjetos(p->prox->item.projetos); // função para imprimir projetos

        system("pause");
        system("cls");
        cout << endl;
    }
    else
    {
        cout << "Codigo nao registrado!" << endl;
        system("pause");
        system("cls");
    }
}

void CadastroDeFuncionarios(TListaEncadeada *lista)
{
    TFuncionario funcionario;

    cout << "CADASTRO DE FUNCIONARIO" << endl;
    cout << "Codigo: ";
    cin >> funcionario.codfuncionario;
    cin.ignore();
    cout << "Nome: ";
    cin.getline(funcionario.nomefuncionario, 40);
    cout << "Endereco: ";
    cin.getline(funcionario.endereco, 40);
    cout << "Dependentes: ";
    cin >> funcionario.dependentes;

    CriarListaSequencialVazia(&funcionario.projetos); // criando lista de projeto
    InsereListaEncadeada(funcionario, lista);         // inserindo funcionario na lista

    cout << "Funcionario cadastrado" << endl;

    cout << "Deseja cadastrar projetos para o funcionario?" << endl << "1-Sim | 2-Nao: ";
    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        CadastroDeProjetos(lista);
    }
    system("cls");
}

void CadastroDeProjetos(TListaEncadeada *lista)
{
    TProjeto x;
    TApontador p;
    TChave cod;
    int j, ret;

    system("cls");

    cout << "CADASTRO DE PROJETOS" << endl;
    cout << "Codigo do funcionario: ";
    cin >> cod;

    ret = BuscaEncadeada(cod, *lista, &p);

    if (ret == 1)
    {
        cout << "Digite um codigo do projeto: ";
        cin >> x.codigo;
        if (BuscaSequencial(x.codigo, p->prox->item.projetos, &j))
        {
            cout << "Codigo ja existe" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout << "Nome do projeto: ";
            cin >> x.nome;
            cout << "Quantidade de horas: ";
            cin >> x.horas;
            InsereListaSequencial(x, &(p->prox->item.projetos));
            system("cls");

            cout << "Projeto cadastrado com sucesso" << endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        cout << "Funcionario nao existe" << endl;
        system("pause");
        system("cls");
    }
}

void MostraProjetos(TListaSequencial Lista)
{
    for (int i = 0; i < Lista.ultimo; i++)
    {
        cout << "Codigo do projeto: " << Lista.item[i].codigo << endl;
        cout << "Nome do projeto: " << Lista.item[i].nome << endl;
        cout << "Horas trabalhadas: " << Lista.item[i].horas << endl;
    }
}

void ExcluiFuncionarioSemProjeto(TListaEncadeada *lista)
{
    TApontador p, ant;
    TChave cod;
    int ret;

    system("cls");

    cout << "EXCLUSAO DE FUNCIONARIO  SEM PROJETO" << endl;
    cout << "Digite o codigo do funcionario: ";
    cin >> cod;
    ret = BuscaEncadeada(cod, *lista, &p);
    if (ret == 1)
    {

        if (p->prox->item.projetos.primeiro == p->prox->item.projetos.ultimo)
        { // verifica se a lista esta vazia
            ant = p;
            p = p->prox;
            ant->prox = p->prox;
            delete p; // exclui o funcionario
            cout << "Funcionario excluido com sucesso!" << endl;
            system("pause");
            system("cls");
        }
        else
        { // se funcionario possuir
            cout << "Funcionario possui projeto!" << endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        cout << "Codigo nao existe!" << endl;
        system("pause");
        system("cls");
    }
}

void RemoveFuncionario(int p, TListaSequencial *lista, TProjeto *Proj)
{
    if (VerificarListaSequencialVazia(*lista))
    {
        cout << "Lista vazia" << endl;
    }
    *Proj = lista->item[p];
    lista->ultimo--;
    for (int i = p; i < lista->ultimo; i++)
    {
        lista->item[i] = lista->item[i + 1];
    }
}

void ExclusaoDeProjeto(TListaEncadeada *lista)
{
    TChave cod;
    TApontador p;
    TProjeto Proj;
    int codExcluido, y, ret;

    system("cls");

    cout << "EXCLUSAO DE PROJETO" << endl;
    cout << "Digite o codigo do funcionario: ";
    cin >> cod;
    ret = BuscaEncadeada(cod, *lista, &p);

    if (ret == 1)
    {
        p = p->prox;
        cout << "Informe o codigo do projeto excluido: ";
        cin >> codExcluido;

        if (BuscaSequencial(codExcluido, p->item.projetos, &y))
        {
            RemoveFuncionario(y, &(p->item.projetos), &Proj);

            cout << "Projeto excluido com sucesso" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout << "Codigo inexistente";
            system("pause");
            system("cls");
        }
    }
    else
    {
        cout << "Codigo do projeto nao existe";
        system("pause");
        system("cls");
    }
}

void MostraContraCheques(TListaEncadeada *lista)

{
    TApontador Aux = lista->primeiro->prox;
    int Total_de_Horas = 0;
    float SalarioBruto, SalarioLiquido, inss, irpf;

    system("cls");

    cout << "Imprimir contra cheques" << endl;

    while (Aux)
    {
        cout << "\nCodigo: " << Aux->item.codfuncionario;
        cout << "\nNome: " << Aux->item.nomefuncionario;

        for (int i = 0; i < Aux->item.projetos.ultimo; i++)
        {
            Total_de_Horas = Total_de_Horas + Aux->item.projetos.item[i].horas;
        }

        SalarioBruto = (Total_de_Horas * 45) + (35 * Aux->item.dependentes);
        inss = SalarioBruto * 0.085;
        irpf = SalarioBruto * 0.15;
        SalarioLiquido = SalarioBruto - (inss + irpf);

        cout << endl << "Total de Horas: " << Total_de_Horas << endl;
        cout << "Salario Bruto: " << SalarioBruto << endl;
        cout << "Desconto Inss: " << inss << endl;
        cout << "Desconto IRPF: " << irpf << endl;
        cout << "Salario Liquido: " << SalarioLiquido << endl
             << endl;

        // zera os valores para entrada de novos valores
        SalarioBruto = 0;
        SalarioLiquido = 0;
        inss = 0;
        Total_de_Horas = 0;
        irpf = 0;
        Aux = Aux->prox;
    }
    system("pause");
    system("cls");
}
