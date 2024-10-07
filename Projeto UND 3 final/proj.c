#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "proj.h"

// Função para verificar se uma string contém apenas números
int validarNumeros(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para verificar se uma string contém apenas letras
int validarLetras(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// Função para verificar o formato de um e-mail básico
int validarEmail(char *email) {
    char *arroba = strchr(email, '@');
    char *ponto = strrchr(email, '.');
    return (arroba != NULL && ponto != NULL && arroba < ponto);
}

// Função para verificar se a matrícula é única
int matriculaUnica(Egresso *lista, char *matricula) {
    Egresso *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            return 0;
        }
        atual = atual->lista;
    }
    return 1;
}

void cadastrarEgresso(Egresso **lista) {
    Egresso *novoEgresso = (Egresso *)malloc(sizeof(Egresso));
    if (novoEgresso == NULL) {
        printf("Erro ao alocar memória para novo egresso.\n");
        exit(1);
    }

    printf("Informe a matrícula (apenas números): ");
    scanf("%s", novoEgresso->matricula);

    while (!validarNumeros(novoEgresso->matricula) || !matriculaUnica(*lista, novoEgresso->matricula)) {
        if (!validarNumeros(novoEgresso->matricula)) {
            printf("Erro: Matrícula deve conter apenas números. Tente novamente: ");
        } else {
            printf("Erro: Matrícula já cadastrada. Tente novamente: ");
        }
        scanf("%s", novoEgresso->matricula);
    }

    printf("Informe o nome: ");
    scanf(" %[^\n]", novoEgresso->nome);

    while (!validarLetras(novoEgresso->nome)) {
        printf("Erro: Nome deve conter apenas letras. Tente novamente: ");
        scanf(" %[^\n]", novoEgresso->nome);
    }

    printf("Informe o curso: ");
    scanf(" %[^\n]", novoEgresso->curso);

    while (!validarLetras(novoEgresso->curso)) {
        printf("Erro: Curso deve conter apenas letras. Tente novamente: ");
        scanf(" %[^\n]", novoEgresso->curso);
    }

    printf("Informe o ano de conclusão: ");
    scanf("%s", novoEgresso->anoConclusao);

    while (!validarNumeros(novoEgresso->anoConclusao)) {
        printf("Erro: O ano de conclusão deve conter apenas números. Tente novamente: ");
        scanf("%s", novoEgresso->anoConclusao);
    }

    printf("Informe o status profissional: ");
    scanf(" %[^\n]", novoEgresso->statusProfissional);

    printf("Informe o local de trabalho: ");
    scanf(" %[^\n]", novoEgresso->localDeTrabalho);

    printf("Informe o e-mail: ");
    scanf("%s", novoEgresso->email);

    while (!validarEmail(novoEgresso->email)) {
        printf("Erro: E-mail inválido. Tente novamente: ");
        scanf("%s", novoEgresso->email);
    }

    novoEgresso->lista = *lista; // Insere no início da lista
    *lista = novoEgresso; // Atualiza o cabeçalho
    printf("Egresso cadastrado com sucesso!\n");
}

void listarEgressos(Egresso *lista) {
    if (lista == NULL) {
        printf("Nenhum egresso cadastrado.\n");
    } else {
        Egresso *atual = lista;
        while (atual != NULL) {
            printf("Matrícula: %s\n", atual->matricula);
            printf("Nome: %s\n", atual->nome);
            printf("Curso: %s\n", atual->curso);
            printf("Ano de Conclusão: %s\n", atual->anoConclusao);
            printf("Status Profissional: %s\n", atual->statusProfissional);
            printf("Local de Trabalho: %s\n", atual->localDeTrabalho);
            printf("E-mail: %s\n", atual->email);
            printf("---------------------------\n");
            atual = atual->lista;
        }
    }
}

void buscarEgresso(Egresso *lista) {
    char matricula[20];
    printf("Informe a matrícula do egresso que deseja buscar: ");
    scanf("%s", matricula);

    Egresso *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            printf("Egresso encontrado!\n");
            printf("Matrícula: %s\n", atual->matricula);
            printf("Nome: %s\n", atual->nome);
            printf("Curso: %s\n", atual->curso);
            printf("Ano de Conclusão: %s\n", atual->anoConclusao);
            printf("Status Profissional: %s\n", atual->statusProfissional);
            printf("Local de Trabalho: %s\n", atual->localDeTrabalho);
            printf("E-mail: %s\n", atual->email);
            return;
        }
        atual = atual->lista;
    }

    printf("Egresso não encontrado.\n");
}

void excluirEgresso(Egresso **lista) {
    char matricula[20];
    printf("Informe a matrícula do egresso que deseja excluir: ");
    scanf("%s", matricula);

    Egresso *atual = *lista;
    Egresso *ant = NULL;

    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            if (ant == NULL) {
                *lista = atual->lista; // Atualiza o cabeçalho
            } else {
                ant->lista = atual->lista; // Remove o egresso da lista
            }
            free(atual); // Libera a memória
            printf("Egresso excluído com sucesso!\n");
            return;
        }
        ant = atual;
        atual = atual->lista;
    }

    printf("Egresso não encontrado.\n");
}

void editarEgresso(Egresso *lista) {
    char matricula[20];
    printf("Informe a matrícula do egresso que deseja editar: ");
    scanf("%s", matricula);

    Egresso *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            printf("Editando egresso com matrícula %s\n", matricula);

            printf("Informe o novo nome: ");
            scanf(" %[^\n]", atual->nome);

            printf("Informe o novo curso: ");
            scanf(" %[^\n]", atual->curso);

            printf("Informe o novo ano de conclusão: ");
            scanf("%s", atual->anoConclusao);

            printf("Informe o novo status profissional: ");
            scanf(" %[^\n]", atual->statusProfissional);

            printf("Informe o novo local de trabalho: ");
            scanf(" %[^\n]", atual->localDeTrabalho);

            printf("Informe o novo e-mail: ");
            scanf("%s", atual->email);

            printf("Egresso editado com sucesso!\n");
            return;
        }
        atual = atual->lista;
    }

    printf("Egresso não encontrado.\n");
}

void consultarPorStatus(Egresso *lista) {
    char status[MAX_STR];
    printf("Informe o status profissional que deseja consultar: ");
    scanf(" %[^\n]", status);

    Egresso *atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->statusProfissional, status) == 0) {
            printf("Matrícula: %s\n", atual->matricula);
            printf("Nome: %s\n", atual->nome);
            printf("Curso: %s\n", atual->curso);
            printf("Ano de Conclusão: %s\n", atual->anoConclusao);
            printf("Status Profissional: %s\n", atual->statusProfissional);
            printf("Local de Trabalho: %s\n", atual->localDeTrabalho);
            printf("E-mail: %s\n", atual->email);
            printf("---------------------------\n");
            encontrado = 1;
        }
        atual = atual->lista;
    }

    if (!encontrado) {
        printf("Nenhum egresso com esse status encontrado.\n");
    }
}

void consultarPorAnoConclusao(Egresso *lista) {
    char ano[5];
    printf("Informe o ano de conclusão que deseja consultar: ");
    scanf("%s", ano);

    Egresso *atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->anoConclusao, ano) == 0) {
            printf("Matrícula: %s\n", atual->matricula);
            printf("Nome: %s\n", atual->nome);
            printf("Curso: %s\n", atual->curso);
            printf("Ano de Conclusão: %s\n", atual->anoConclusao);
            printf("Status Profissional: %s\n", atual->statusProfissional);
            printf("Local de Trabalho: %s\n", atual->localDeTrabalho);
            printf("E-mail: %s\n", atual->email);
            printf("---------------------------\n");
            encontrado = 1;
        }
        atual = atual->lista;
    }

    if (!encontrado) {
        printf("Nenhum egresso com esse ano de conclusão encontrado.\n");
    }
}

void carregarDados(Egresso **lista) {
    FILE *file = fopen("egressos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de dados.\n");
        exit(1);
    }

    while (!feof(file)) {
        Egresso *novoEgresso = (Egresso *)malloc(sizeof(Egresso));
        if (fscanf(file, "%s %s %s %s %s %s %s", 
                   novoEgresso->matricula,
                   novoEgresso->nome,
                   novoEgresso->curso,
                   novoEgresso->anoConclusao,
                   novoEgresso->statusProfissional,
                   novoEgresso->localDeTrabalho,
                   novoEgresso->email) == 7) {
            novoEgresso->lista = *lista;
            *lista = novoEgresso;
        } else {
            free(novoEgresso);
        }
    }

    fclose(file);
}

void salvarDados(Egresso *lista) {
    FILE *file = fopen("egressos.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        exit(1);
    }

    Egresso *atual = lista;
    while (atual != NULL) {
        fprintf(file, "%s %s %s %s %s %s %s\n", 
                atual->matricula,
                atual->nome,
                atual->curso,
                atual->anoConclusao,
                atual->statusProfissional,
                atual->localDeTrabalho,
                atual->email);
        atual = atual->lista;
    }

    fclose(file);
}

void ordenarEgressosPorNome(Egresso **lista) {
    if (*lista == NULL) return;

    Egresso *atual, *index;
    char temp[MAX_STR];

    for (atual = *lista; atual->lista != NULL; atual = atual->lista) {
        for (index = atual->lista; index != NULL; index = index->lista) {
            if (strcmp(atual->nome, index->nome) > 0) {
                // Troca os nomes
                strcpy(temp, atual->nome);
                strcpy(atual->nome, index->nome);
                strcpy(index->nome, temp);

                // Troca os outros dados do egresso
                strcpy(temp, atual->matricula);
                strcpy(atual->matricula, index->matricula);
                strcpy(index->matricula, temp);
                strcpy(temp, atual->curso);
                strcpy(atual->curso, index->curso);
                strcpy(index->curso, temp);
                strcpy(temp, atual->anoConclusao);
                strcpy(atual->anoConclusao, index->anoConclusao);
                strcpy(index->anoConclusao, temp);
                strcpy(temp, atual->statusProfissional);
                strcpy(atual->statusProfissional, index->statusProfissional);
                strcpy(index->statusProfissional, temp);
                strcpy(temp, atual->localDeTrabalho);
                strcpy(atual->localDeTrabalho, index->localDeTrabalho);
                strcpy(index->localDeTrabalho, temp);
                strcpy(temp, atual->email);
                strcpy(atual->email, index->email);
                strcpy(index->email, temp);
            }
        }
    }
}

void liberaLista(Egresso *lista) {
    Egresso *atual = lista;
    Egresso *prox;

    while (atual != NULL) {
        prox = atual->lista;
        free(atual);
        atual = prox;
    }
}