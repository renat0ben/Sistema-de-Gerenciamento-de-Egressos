#ifndef PROJ_H
#define PROJ_H

#define MAX_STR 100

/* Definição do tipo estruturado Egresso */
typedef struct Egresso {
    char matricula[20];
    char nome[MAX_STR];
    char curso[MAX_STR];
    char anoConclusao[5];
    char statusProfissional[MAX_STR];
    char localDeTrabalho[MAX_STR];
    char email[MAX_STR];
    struct Egresso *lista;  // Ponteiro para o próximo egresso na lista encadeada
} Egresso;

/* Funções de Validação */

/**
 * Valida se a string contém apenas números.
 *
 * @param str A string a ser validada.
 * @return 1 se a string contiver apenas números, 0 caso contrário.
 */
int validarNumeros(char *str);

/**
 * Valida se a string contém apenas letras.
 *
 * @param str A string a ser validada.
 * @return 1 se a string contiver apenas letras, 0 caso contrário.
 */
int validarLetras(char *str);

/**
 * Valida se o email fornecido segue o formato correto.
 *
 * @param email A string do email a ser validada.
 * @return 1 se o email for válido, 0 caso contrário.
 */
int validarEmail(char *email);

/**
 * Verifica se a matrícula é única na lista de egressos.
 *
 * @param lista Ponteiro para o início da lista de egressos.
 * @param matricula A matrícula a ser verificada.
 * @return 1 se a matrícula for única, 0 se já existir na lista.
 */
int matriculaUnica(Egresso *lista, char *matricula);

/* Funções Principais */

/**
 * Cadastra um novo egresso na lista encadeada.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada de egressos.
 */
void cadastrarEgresso(Egresso **lista);

/**
 * Lista todos os egressos armazenados na lista encadeada.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void listarEgressos(Egresso *lista);

/**
 * Busca um egresso na lista encadeada de egressos com base no nome fornecido.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void buscarEgresso(Egresso *lista);

/**
 * Exclui um egresso da lista encadeada com base na matrícula fornecida.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada de egressos.
 */
void excluirEgresso(Egresso **lista);

/**
 * Edita os dados de um egresso na lista encadeada com base na matrícula fornecida.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void editarEgresso(Egresso *lista);

/**
 * Consulta egressos por status profissional.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void consultarPorStatus(Egresso *lista);

/**
 * Consulta egressos com base no ano de conclusão.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void consultarPorAnoConclusao(Egresso *lista);

/**
 * Carrega os dados dos egressos de um arquivo e os insere na lista encadeada.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada de egressos.
 */
void carregarDados(Egresso **lista);

/**
 * Salva os dados da lista encadeada de egressos em um arquivo.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void salvarDados(Egresso *lista);

/**
 * Ordena a lista de egressos em ordem alfabética pelo nome.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada de egressos.
 */
void ordenarEgressosPorNome(Egresso **lista);

/**
 * Libera toda a memória alocada para a lista encadeada de egressos.
 *
 * @param lista Ponteiro para o início da lista encadeada de egressos.
 */
void liberaLista(Egresso *lista);

#endif // PROJ_H