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

// Função para trocar dois nós na lista de egressos
void trocar(Egresso *a, Egresso *b) {
    char temp[MAX_STR];  // Variável temporária para armazenar valores durante a troca

    // Troca os nomes entre os nós a e b
    strcpy(temp, a->nome);
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);

    // Troca os outros dados do egresso: matrícula
    strcpy(temp, a->matricula);
    strcpy(a->matricula, b->matricula);
    strcpy(b->matricula, temp);

    // Troca os cursos entre os dois nós
    strcpy(temp, a->curso);
    strcpy(a->curso, b->curso);
    strcpy(b->curso, temp);

    // Troca os anos de conclusão entre os nós
    strcpy(temp, a->anoConclusao);
    strcpy(a->anoConclusao, b->anoConclusao);
    strcpy(b->anoConclusao, temp);

    // Troca os status profissionais
    strcpy(temp, a->statusProfissional);
    strcpy(a->statusProfissional, b->statusProfissional);
    strcpy(b->statusProfissional, temp);

    // Troca os locais de trabalho
    strcpy(temp, a->localDeTrabalho);
    strcpy(a->localDeTrabalho, b->localDeTrabalho);
    strcpy(b->localDeTrabalho, temp);

    // Troca os e-mails entre os dois nós
    strcpy(temp, a->email);
    strcpy(a->email, b->email);
    strcpy(b->email, temp);
}

// Função para particionar a lista com base no pivô
Egresso* particionar(Egresso *inicio, Egresso *fim) {
    Egresso *pivo = fim;  // Define o último elemento da lista como pivô
    Egresso *i = inicio;  // i será usado para rastrear a posição de elementos menores que o pivô
    Egresso *j = inicio;  // j percorre a lista até o pivô

    // Percorre a lista de egressos até encontrar o pivô
    while (j != fim) {
        // Compara o nome de j com o nome do pivô
        if (strcmp(j->nome, pivo->nome) < 0) {
            // Se o nome de j for menor que o pivô, troca i e j
            trocar(i, j);
            i = i->lista;  // Avança o ponteiro i para o próximo nó
        }
        j = j->lista;  // Avança o ponteiro j para o próximo nó
    }
    // Troca o elemento i com o pivô para posicionar o pivô corretamente
    trocar(i, fim);
    return i;  // Retorna o novo pivô
}

// Função recursiva para aplicar o QuickSort na lista
void quickSort(Egresso *inicio, Egresso *fim) {
    // Verifica se a lista possui mais de um elemento e se os ponteiros são válidos
    if (inicio != fim && inicio != NULL && fim != NULL && inicio != fim->lista) {
        // Particiona a lista e retorna o pivô
        Egresso *pivo = particionar(inicio, fim);
        // Ordena a parte esquerda da lista (elementos menores que o pivô)
        quickSort(inicio, pivo->lista);
        // Ordena a parte direita da lista (elementos maiores que o pivô)
        quickSort(pivo->lista, fim);
    }
}

// Função para encontrar o último elemento da lista encadeada
Egresso* encontrarUltimo(Egresso *lista) {
    // Percorre a lista até encontrar o último nó (onde lista->lista é NULL)
    while (lista != NULL && lista->lista != NULL) {
        lista = lista->lista;  // Avança para o próximo nó
    }
    return lista;  // Retorna o último nó da lista
}

// Função para ordenar a lista de egressos por nome utilizando QuickSort
void ordenarEgressosPorNome(Egresso **lista) {
    // Verifica se a lista está vazia
    if (*lista == NULL) return;

    // Encontra o último elemento da lista
    Egresso *fim = encontrarUltimo(*lista);
    // Aplica o algoritmo de QuickSort na lista
    quickSort(*lista, fim);
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