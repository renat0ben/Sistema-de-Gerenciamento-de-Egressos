#include "proj.h"
#include<locale.h>
#include <stdio.h>

int main() {
setlocale(LC_ALL, "Portuguese");
    Egresso *lista = NULL;
    int opcao;

    carregarDados(&lista);

    do {
        printf("Sistema de Cadastro de Egressos\n");
        printf("1. Cadastrar Egresso\n");
        printf("2. Listar Egressos\n");
        printf("3. Buscar Egresso\n");
        printf("4. Excluir Egresso\n");
        printf("5. Editar Egresso\n");
        printf("6. Consultar por Status Profissional\n");
        printf("7. Consultar por Ano de Conclusão\n");
        printf("8. Ordenar Egressos por Nome\n");
        printf("9. Salvar Dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarEgresso(&lista);
                break;
            case 2:
                listarEgressos(lista);
                break;
            case 3:
                buscarEgresso(lista);
                break;
            case 4:
                excluirEgresso(&lista);
                break;
            case 5:
                editarEgresso(lista);
                break;
            case 6:
                consultarPorStatus(lista);
                break;
            case 7:
                consultarPorAnoConclusao(lista);
                break;
            case 8:
                ordenarEgressosPorNome(&lista);
                printf("Egressos ordenados por nome com sucesso!\n");
                break;
            case 9:
                salvarDados(lista);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberaLista(lista); // Libera a memória ao sair
    return 0;
}