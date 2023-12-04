#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do produto
typedef struct{
    char nome[40];
    int quantidade;
    float valorUni;
    char tipo;
}TProduto;

// Função responsável por solicitar a quantidade de produtos a serem cadastradas
int solicitaNumProduto(){
    int numProdutos;

    printf("Informe o número de produtos a serem cadastrados: ");
    scanf("%d",&numProdutos);

    while (numProdutos <= 0){
        printf("O número informado precisa ser positivo. \nTente novamente: ");
        scanf("%d",&numProdutos);
    }
    return numProdutos;
}

// Função responsável por efetuar o cadastro do nome do produto
void cadastrarNome(char *nome) {
    printf("Informe o nome do produto: ");
    setbuf(stdin,NULL);
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';
}

// Função responsável por efetuar o cadastro da quantidade disponível do produto
int cadastrarQuantidade(){
    int quantidade;

    printf("Informe a quantidade do produto: ");
    scanf("%d",&quantidade);

    while (quantidade < 0){
        printf("O número informado precisa ser positivo. \nTente novamente: ");
        scanf("%d",&quantidade);
    }

    return quantidade;
}

// Função responsável por cadastrar o tipo do produto sendo P para perecível e N para não perecível
void cadastrarTipo(char *tipo) {
    do {
        printf("Informe o tipo do produto (P para perecível, N para não perecível): ");
        scanf(" %c", tipo);

        switch (*tipo) {
            case 'P':
            case 'p':
                *tipo = 'P';
                break;

            case 'N':
            case 'n':
                *tipo = 'N';
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (*tipo != 'P' && *tipo != 'N'); // Continue até que o usuário entre com uma opção válida
}

//Função responsável pelo cadastro do valor unitátio de cada produto
void cadastrarValorUnitario(TProduto *produto){
    printf("Informe o valor unitário do produto: ");
    scanf("%f",&produto->valorUni);

    while (produto->valorUni <= 0){
        printf("O valor do produto não pode ser negativo.\nTente novamente: ");
        scanf("%f",&produto->valorUni);
    }
}

//Função responsável por listar e exibir os produtos
void exibeProdutos(TProduto *listaProd, int numProdutos, int i) {

    if (i < numProdutos) {
        printf("\n----------------------- Produto %d ----------------------\n", i + 1);
        printf("Nome: %s\n", listaProd[i].nome);
        printf("Quantidade: %d\n", listaProd[i].quantidade);
        printf("Valor Unitário: %.2f\n", listaProd[i].valorUni);
        printf("Tipo: %c\n", listaProd[i].tipo);
        printf("--------------------------------------------------------\n");
        exibeProdutos(listaProd, numProdutos, i + 1);
    }
}

// Função responsável por listar e exibir os produtos por tipo
void exibeProdutosTipo(TProduto *listaProd, int numProdutos, char tipo) {
    int quantidade = 0;
    float totalPreco = 0;

    printf("Produtos do tipo %c:\n", tipo);

    for (int i = 0; i < numProdutos; i++) {
        if (listaProd[i].tipo == tipo) {
            printf("\n----------------------- Produto %d ----------------------\n", i + 1);
            printf("Nome: %s\n", listaProd[i].nome);
            printf("Quantidade: %d\n", listaProd[i].quantidade);
            printf("Valor Unitário: %.2f\n", listaProd[i].valorUni);
            printf("Tipo: %c\n", listaProd[i].tipo);
            printf("--------------------------------------------------------\n");

            // Calcular o valor total do produto
            float precoProduto = listaProd[i].valorUni * listaProd[i].quantidade;
            totalPreco += precoProduto;

            // Atualizar a quantidade de produtos
            quantidade++;
        }
    }

    if (quantidade > 0) {
        // Agora, calcule a média somente se houver produtos do tipo especificado
        float mediaPreco = totalPreco / quantidade;
        printf("Média de preço dos produtos do tipo %c: %.2f\n", tipo, mediaPreco);
    } else {
        // Nenhum produto encontrado do tipo especificado
        printf("Nenhum produto do tipo %c encontrado.\n", tipo);
    }
}

// Função responsável por apresentar o menu ao usuário, além de chamar as outras funções
void menu() {
    TProduto *listaProd = NULL;
    int numProdutos = 0;

    char opcao, tipo;

    do {
        printf("\n-------------------------- Menu -------------------------\n");
        printf("|     A – Preencher dados                             |\n");
        printf("|     B – Exibir dados dos produtos                   |\n");
        printf("|     C – Exibir dados dos produtos por tipo          |\n");
        printf("|     D – Finalizar                                   |\n");
        printf("---------------------------------------------------------\n");

        printf("Opção: ");
        scanf(" %s", &opcao);

        switch (opcao) {
            case 'A':
            case 'a':
                if (listaProd != NULL) {
                    free(listaProd);
                }
                numProdutos = solicitaNumProduto();
                listaProd = (TProduto *)malloc(numProdutos * sizeof(TProduto));

                for (int i = 0; i < numProdutos; i++) {
                    printf("\n---------------- Cadastro do produto %d ----------------\n", i + 1);
                    cadastrarNome(listaProd[i].nome);
                    listaProd[i].quantidade = cadastrarQuantidade();
                    cadastrarTipo(&listaProd[i].tipo);
                    cadastrarValorUnitario(&listaProd[i]);
                }
                break;

            case 'B':
            case 'b':
                if (listaProd != NULL && numProdutos > 0) {
                    exibeProdutos(listaProd, numProdutos, 0);
                } else {
                    printf("Nenhum produto cadastrado.\n");
                }
                break;

            case 'C':
            case 'c':
                do {
                    printf("Informe o tipo do produto (P para perecível, N para não perecível): ");
                    scanf(" %c", &tipo);

                    switch (tipo) {
                        case 'P':
                        case 'p':
                            tipo = 'P';
                            break;

                        case 'N':
                        case 'n':
                            tipo = 'N';
                            break;

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (tipo != 'P' && tipo != 'N');
                if (numProdutos > 0) {
                    exibeProdutosTipo(listaProd, numProdutos, tipo);
                } else {
                    printf("Nenhum produto cadastrado.\n");
                }
                break;

            case 'D':
            case 'd':
                printf("Finalizando...\n");
                free(listaProd);
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 'D' && opcao != 'd');
}

int main() {

    menu();

    return 0;
}
