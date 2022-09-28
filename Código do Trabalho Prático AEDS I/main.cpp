#include <iostream>
#include <conio.h>
#include "funcoes.hpp"
#include "funcoes.cpp"

using namespace std;

int main()
{

    system("cls");

    TListaEncadeada lista;
    TApontador apontador;
    TFuncionario funcionario;

    CriarListaEncadeadaVazia(&lista);

    FILE *arquivo;
    arquivo = fopen("Funcionario.bin", "a+b");
    apontador = lista.primeiro;

    if (arquivo != NULL)
    {
        while (fread(&funcionario, sizeof(TFuncionario), 1, arquivo))
        {

            InsereListaEncadeada(funcionario, &lista);
        }
        fclose(arquivo);
    }
    else
    {
        cout << "Arquivo inesxistente";
        getch();
        system("cls");
    }

    int opcao;
    do
    {
        menu();
        cout << "Escolha sua opcao: ";
        cin >> opcao;
        system("cls");
        switch (opcao)
        {

        case 1:
            system("cls");
            CadastroDeFuncionarios(&lista);
            system("cls");
            break;

        case 2:
            system("cls");
            CadastroDeProjetos(&lista);
            break;

        case 3:
            ExclusaoDeProjeto(&lista);
            break;

        case 4:
            ExcluiFuncionarioSemProjeto(&lista);
            break;

        case 5:
            ExcluiFuncionario(&lista);
            break;

        case 6:
            BuscaFuncionario(lista);
            break;

        case 7:
            MostraContraCheques(&lista);
            break;
        }
    } while (opcao < 8);

    arquivo = fopen("Funcionario.bin", "wb");

    while (apontador->prox != NULL)
    {
        funcionario = apontador->prox->item;
        fwrite(&funcionario, sizeof(TFuncionario), 1, arquivo);
        apontador = apontador->prox;
    }
    fclose(arquivo);

    system("cls");
    return 0;
}