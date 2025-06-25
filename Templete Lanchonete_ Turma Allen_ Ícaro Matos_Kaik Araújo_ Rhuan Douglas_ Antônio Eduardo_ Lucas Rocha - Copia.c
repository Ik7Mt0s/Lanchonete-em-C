#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

// Função para exibir uma barra de progresso animada
void BarraProgressao() {
    int i;
    system("color B"); // Define a cor de fundo do console para azul claro (Windows-specific)
    
    // Exibe uma mensagem de carregamento estilizada
    printf("+===================================================================================================+\n");
    printf("|A   G   U   A   R    D    E       O         S  I   S  T   E   M   A      C  A  R  R  E  G   A   R !|\n");
    printf("+===================================================================================================+\n\n");
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Obtém o manipulador do console para manipulação de cursor
    COORD pos; // Estrutura para definir posições do cursor no console
    
    pos.X = 50; // Define a posição X inicial para o percentual
    pos.Y = 5; // Define a posição Y inicial para o percentual
    SetConsoleCursorPosition(hConsole, pos); // Move o cursor para a posição especificada
    printf("0 %%"); // Exibe o percentual inicial (0%)
    
    // Loop para simular o progresso de 1% a 100%
    for (i = 1; i <= 100; i++) {
        pos.X = 50; // Reposiciona o cursor para atualizar o percentual
        pos.Y = 5;
        SetConsoleCursorPosition(hConsole, pos);
        printf("%d %%", i); // Atualiza o percentual exibido
        
        pos.X = i; // Move o cursor para a posição correspondente ao progresso na barra
        pos.Y = 6;
        SetConsoleCursorPosition(hConsole, pos);
        printf("\xDB"); // Imprime um caractere de bloco para a barra de progresso

        Sleep(100); // Pausa de 100ms para animar a barra
    }

    printf("\n\nConcluido!\n"); // Exibe mensagem de conclusão
    Sleep(500); // Pausa de 500ms antes de limpar a tela
    system("cls"); // Limpa a tela do console
}

// Estruturas de dados
struct Ingrediente {
    char nome[50]; // Nome do ingrediente (máximo 50 caracteres)
    int quantidade; // Quantidade do ingrediente (em unidades)
};

struct Produto {
    int codigo; // Código único do produto
    char nome[50]; // Nome do produto (máximo 50 caracteres)
    struct Ingrediente ingredientes[20]; // Array de até 20 ingredientes
    int num_ingredientes; // Contador de ingredientes no produto
    float preco; // Preço do produto em reais
};

struct ItemPedido {
    int codigoProduto; // Código do produto no pedido
    char nomeProduto[50]; // Nome do produto no pedido
    int quantidade; // Quantidade de unidades do produto
    float precoUnitario; // Preço por unidade do produto
    float subtotal; // Subtotal (quantidade * preço unitário)
};

struct Pedido {
    struct ItemPedido itens[50]; // Array de até 50 itens no pedido
    int numItens; // Contador de itens no pedido
    float total; // Valor total do pedido
};

// Protótipos de funções
void MenuInicial(); // Exibe o menu principal
void AreaCliente(); // Gerencia a área do cliente
void AreaFuncionario(); // Gerencia a área do funcionário (protegida por senha)
void CadastrarProduto(); // Cadastra um novo produto
void ListarProdutos(); // Lista todos os produtos cadastrados
void EditarProduto(); // Edita um produto existente
void ExcluirProduto(); // Exclui um produto
void GerenciarIngredientes(struct Produto *produto); // Gerencia os ingredientes de um produto
void SalvarProdutos(struct Produto produtos[], int total); // Salva produtos no arquivo
void CarregarProdutos(struct Produto produtos[], int *total); // Carrega produtos do arquivo
void MostrarCardapioCliente(struct Produto produtos[], int total, struct Pedido *pedido); // Exibe o cardápio para o cliente
void AdicionarItemPedido(struct Pedido *pedido, struct Produto produto, int quantidade); // Adiciona um item ao pedido
void RemoverItemPedido(struct Pedido *pedido, int index); // Remove um item do pedido
void MostrarPedido(struct Pedido *pedido); // Exibe os detalhes do pedido
void FinalizarPedido(struct Pedido *pedido); // Finaliza o pedido com opções de pagamento

int main() {
    BarraProgressao(); // Chama a função de animação de carregamento
    setlocale(LC_ALL, "Portuguese"); // Define o idioma do programa como Português
    MenuInicial(); // Inicia o menu principal
    return 0; // Encerra o programa
}

void MenuInicial() {
    int opcao; // Variável para armazenar a opção escolhida pelo usuário
    do {
        system("cls"); // Limpa a tela
        // Exibe o menu inicial com opções para cliente, funcionário ou sair
        printf("|===================================|\n");
        printf("|       LANCHONETE MENOS É MAIS     |\n");
        printf("|-----------------------------------|\n");
        printf("|Onde você gasta mais e compra menos|\n");
        printf("|-----------------------------------|\n");
        printf("|    1-Cliente   |  2-Funcionário   |\n");
        printf("|-----------------------------------|\n");
        printf("|               3-Sair              |\n");
        printf("|===================================|\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao); // Lê a opção do usuário

        switch(opcao) {
            case 1: 
                AreaCliente(); // Acessa a área do cliente
                break;
            case 2: 
                AreaFuncionario(); // Acessa a área do funcionário
                break;
            case 3: 
                exit(0); // Encerra o programa
            default:
                printf("Opção inválida!\n"); // Exibe mensagem de erro para opção inválida
                system("pause"); // Pausa para o usuário ler a mensagem
        }
    } while(1); // Loop infinito até o usuário escolher sair
}

void AreaFuncionario() {
    const int SENHA_CORRETA = 1234; // Senha fixa para acesso (insegura)
    int senha, tentativas = 0; // Variáveis para senha e contador de tentativas
    
    do {
        system("cls"); // Limpa a tela
        printf("|===============================|\n");
        printf("|       ÁREA DO FUNCIONÁRIO     |\n");
        printf("|-------------------------------|\n");
        printf("Digite a senha (1234): ");
        scanf("%d", &senha); // Lê a senha digitada
        
        if(senha != SENHA_CORRETA) {
            tentativas++; // Incrementa o contador de tentativas
            printf("\nSenha incorreta! Tentativas restantes: %d\n", 3 - tentativas);
            system("pause"); // Pausa para o usuário ler
            
            if(tentativas >= 3) {
                printf("\nAcesso bloqueado!\n"); // Bloqueia após 3 tentativas
                system("pause");
                return; // Retorna ao menu inicial
            }
        }
    } while(senha != SENHA_CORRETA); // Repete até a senha estar correta
    
    int opcao; // Variável para a opção do menu do funcionário
    do {
        system("cls"); // Limpa a tela
        // Exibe o menu do funcionário
        printf("|===============================|\n");
        printf("|        MENU FUNCIONÁRIO       |\n");
        printf("|-------------------------------|\n");
        printf("|  1-Cadastrar Produto          |\n");
        printf("|  2-Listar Produtos            |\n");
        printf("|  3-Editar Produto             |\n");
        printf("|  4-Excluir Produto            |\n");
        printf("|  5-Voltar                     |\n");
        printf("|===============================|\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao); // Lê a opção
        
        switch(opcao) {
            case 1: 
                CadastrarProduto(); // Chama função para cadastrar produto
                break;
            case 2: 
                ListarProdutos(); // Chama função para listar produtos
                break;
            case 3:
                EditarProduto(); // Chama função para editar produto
                break;
            case 4:
                ExcluirProduto(); // Chama função para excluir produto
                break;
            case 5: 
                return; // Volta ao menu inicial
            default:
                printf("Opção inválida!\n"); // Exibe mensagem de erro
                system("pause"); // Pausa para leitura
        }
    } while(1); // Loop infinito até escolher voltar
}

void CadastrarProduto() {
    system("cls"); // Limpa a tela
    printf("|===============================|\n");
    printf("|      CADASTRO DE PRODUTO      |\n");
    printf("|===============================|\n");
    
    struct Produto novo; // Estrutura para o novo produto
    printf("Código do produto: ");
    scanf("%d", &novo.codigo); // Lê o código do produto
    getchar(); // Limpa o buffer do '\n'
    
    printf("Nome do produto: ");
    fgets(novo.nome, 50, stdin); // Lê o nome do produto
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o '\n' do final
    
    novo.num_ingredientes = 0; // Inicializa o contador de ingredientes
    char continuar; // Variável para controle de adição de ingredientes
    do {
        if(novo.num_ingredientes >= 20) {
            printf("Limite de ingredientes atingido!\n"); // Verifica o limite de 20 ingredientes
            break;
        }
        
        printf("\nIngrediente %d:\n", novo.num_ingredientes + 1); // Exibe o número do ingrediente
        printf("Nome: ");
        fgets(novo.ingredientes[novo.num_ingredientes].nome, 50, stdin); // Lê o nome do ingrediente
        novo.ingredientes[novo.num_ingredientes].nome[strcspn(
            novo.ingredientes[novo.num_ingredientes].nome, "\n")] = '\0'; // Remove '\n'
        
        printf("Quantidade: ");
        scanf("%d", &novo.ingredientes[novo.num_ingredientes].quantidade); // Lê a quantidade
        getchar(); // Limpa o buffer
        
        novo.num_ingredientes++; // Incrementa o contador de ingredientes
        
        printf("Adicionar outro ingrediente? (s/n): ");
        scanf(" %c", &continuar); // Lê a escolha de continuar
        getchar(); // Limpa o buffer
    } while(continuar == 's' || continuar == 'S'); // Repete se o usuário quiser
    
    printf("Preço do produto: ");
    scanf("%f", &novo.preco); // Lê o preço do produto
    
    struct Produto produtos[100]; // Array para armazenar produtos
    int total = 0; // Contador de produtos
    CarregarProdutos(produtos, &total); // Carrega produtos existentes do arquivo
    
    if(total < 100) { // Verifica se há espaço para mais produtos
        produtos[total] = novo; // Adiciona o novo produto
        total++; // Incrementa o contador
        SalvarProdutos(produtos, total); // Salva no arquivo
        printf("\nProduto cadastrado com sucesso!\n");
    } else {
        printf("\nLimite de produtos atingido!\n"); // Mensagem de limite atingido
    }
    
    system("pause"); // Pausa para leitura
}

void EditarProduto() {
    system("cls"); // Limpa a tela
    printf("|===============================|\n");
    printf("|        EDITAR PRODUTO         |\n");
    printf("|===============================|\n");
    
    struct Produto produtos[100]; // Array para produtos
    int total = 0; // Contador de produtos
    CarregarProdutos(produtos, &total); // Carrega produtos do arquivo
    
    if(total == 0) {
        printf("\nNenhum produto cadastrado para editar!\n"); // Verifica se há produtos
        system("pause");
        return;
    }
    
    ListarProdutos(); // Exibe a lista de produtos
    
    int codigo, i, encontrado = 0; // Variáveis para código, índice e flag de encontrado
    printf("\nDigite o código do produto que deseja editar: ");
    scanf("%d", &codigo); // Lê o código do produto
    
    for(i = 0; i < total; i++) {
        if(produtos[i].codigo == codigo) { // Verifica se o código existe
            encontrado = 1;
            int opcao; // Variável para a opção de edição
            
            do {
                system("cls"); // Limpa a tela
                printf("|===============================|\n");
                printf("| EDITANDO PRODUTO: %-12d |\n", produtos[i].codigo); // Exibe o código do produto
                printf("|-------------------------------|\n");
                printf("| 1 - Alterar código            |\n");
                printf("| 2 - Alterar nome              |\n");
                printf("| 3 - Alterar preço             |\n");
                printf("| 4 - Gerenciar ingredientes    |\n");
                printf("| 5 - Salvar e voltar           |\n");
                printf("|===============================|\n");
                printf("Digite sua opção: ");
                scanf("%d", &opcao); // Lê a opção de edição
                
                switch(opcao) {
                    case 1:
                        printf("Novo código: ");
                        scanf("%d", &produtos[i].codigo); // Altera o código
                        printf("Código alterado com sucesso!\n");
                        break;
                    case 2:
                        printf("Novo nome: ");
                        getchar(); // Limpa o buffer
                        fgets(produtos[i].nome, 50, stdin); // Lê o novo nome
                        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0'; // Remove '\n'
                        printf("Nome alterado com sucesso!\n");
                        break;
                    case 3:
                        printf("Novo preço: ");
                        scanf("%f", &produtos[i].preco); // Altera o preço
                        printf("Preço alterado com sucesso!\n");
                        break;
                    case 4:
                        GerenciarIngredientes(&produtos[i]); // Gerencia os ingredientes
                        break;
                    case 5:
                        SalvarProdutos(produtos, total); // Salva as alterações
                        printf("Alterações salvas!\n");
                        break;
                    default:
                        printf("Opção inválida!\n"); // Mensagem de erro
                }
                if(opcao != 5) system("pause"); // Pausa, exceto ao salvar
            } while(opcao != 5); // Repete até salvar
            
            break; // Sai do loop após encontrar o produto
        }
    }
    
    if(!encontrado) {
        printf("\nProduto não encontrado!\n"); // Mensagem se o código não for encontrado
        system("pause");
    }
}

void GerenciarIngredientes(struct Produto *produto) {
    int opcao; // Variável para a opção de gerenciamento
    do {
        system("cls"); // Limpa a tela
        printf("|===============================|\n");
        printf("|   GERENCIAR INGREDIENTES      |\n");
        printf("|-------------------------------|\n");
        printf("| Produto: %-20s |\n", produto->nome); // Exibe o nome do produto
        printf("|-------------------------------|\n");
        printf("| 1 - Listar ingredientes      |\n");
        printf("| 2 - Adicionar ingrediente    |\n");
        printf("| 3 - Remover ingrediente      |\n");
        printf("| 4 - Voltar                   |\n");
        printf("|===============================|\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao); // Lê a opção
        
        switch(opcao) {
            int i; // Índice para loops
            case 1:
                system("cls"); // Limpa a tela
                printf("Ingredientes de %s:\n", produto->nome); // Exibe o nome do produto
                for(i = 0; i < produto->num_ingredientes; i++) {
                    printf("%d - %s (%d)\n", i+1, 
                           produto->ingredientes[i].nome, 
                           produto->ingredientes[i].quantidade); // Lista os ingredientes
                }
                system("pause"); // Pausa para leitura
                break;
            case 2:
                if(produto->num_ingredientes >= 20) {
                    printf("Limite máximo de ingredientes atingido!\n"); // Verifica o limite
                    system("pause");
                    break;
                }
                
                printf("Nome do novo ingrediente: ");
                getchar(); // Limpa o buffer
                fgets(produto->ingredientes[produto->num_ingredientes].nome, 50, stdin); // Lê o nome
                produto->ingredientes[produto->num_ingredientes].nome[strcspn(
                    produto->ingredientes[produto->num_ingredientes].nome, "\n")] = '\0'; // Remove '\n'
                
                printf("Quantidade: ");
                scanf("%d", &produto->ingredientes[produto->num_ingredientes].quantidade); // Lê a quantidade
                
                produto->num_ingredientes++; // Incrementa o contador
                printf("Ingrediente adicionado com sucesso!\n");
                system("pause");
                break;
            case 3:
                if(produto->num_ingredientes == 0) {
                    printf("Não há ingredientes para remover!\n"); // Verifica se há ingredientes
                    system("pause");
                    break;
                }
                
                printf("Digite o número do ingrediente a remover:\n");
                for(i = 0; i < produto->num_ingredientes; i++) {
                    printf("%d - %s\n", i+1, produto->ingredientes[i].nome); // Lista os ingredientes
                }
                
                int num; // Número do ingrediente a remover
                printf("Opção: ");
                scanf("%d", &num); // Lê a opção
                
                if(num < 1 || num > produto->num_ingredientes) {
                    printf("Opção inválida!\n"); // Verifica se a opção é válida
                } else {
                    for(i = num-1; i < produto->num_ingredientes-1; i++) {
                        strcpy(produto->ingredientes[i].nome, produto->ingredientes[i+1].nome); // Desloca os ingredientes
                        produto->ingredientes[i].quantidade = produto->ingredientes[i+1].quantidade;
                    }
                    produto->num_ingredientes--; // Decrementa o contador
                    printf("Ingrediente removido com sucesso!\n");
                }
                system("pause");
                break;
            case 4:
                break; // Sai do loop
            default:
                printf("Opção inválida!\n"); // Mensagem de erro
                system("pause");
        }
    } while(opcao != 4); // Repete até escolher voltar
}

void ExcluirProduto() {
    system("cls"); // Limpa a tela
    printf("|===============================|\n");
    printf("|       EXCLUIR PRODUTO         |\n");
    printf("|===============================|\n");
    
    struct Produto produtos[100]; // Array para produtos
    int total = 0; // Contador de produtos
    CarregarProdutos(produtos, &total); // Carrega produtos do arquivo
    
    if(total == 0) {
        printf("\nNenhum produto cadastrado para excluir!\n"); // Verifica se há produtos
        system("pause");
        return;
    }
    
    ListarProdutos(); // Exibe a lista de produtos
    
    int codigo, i, encontrado = 0; // Variáveis para código, índice e flag
    printf("\nDigite o código do produto que deseja excluir: ");
    scanf("%d", &codigo); // Lê o código
    
    for(i = 0; i < total; i++) {
        int j; // Índice para deslocamento
        if(produtos[i].codigo == codigo) {
            encontrado = 1; // Marca como encontrado
            
            printf("\nTem certeza que deseja excluir o produto %s? (s/n): ", produtos[i].nome);
            char confirmacao; // Variável para confirmação
            scanf(" %c", &confirmacao); // Lê a confirmação
            
            if(confirmacao == 's' || confirmacao == 'S') {
                for(j = i; j < total-1; j++) {
                    produtos[j] = produtos[j+1]; // Desloca os produtos
                }
                total--; // Decrementa o contador
                SalvarProdutos(produtos, total); // Salva no arquivo
                printf("Produto excluído com sucesso!\n");
            } else {
                printf("Operação cancelada.\n"); // Cancela a exclusão
            }
            
            system("pause");
            break; // Sai do loop
        }
    }
    
    if(!encontrado) {
        printf("\nProduto não encontrado!\n"); // Mensagem se não encontrado
        system("pause");
    }
}

void SalvarProdutos(struct Produto produtos[], int total) {
    FILE *arquivo = fopen("cardapio.txt", "w"); // Abre o arquivo para escrita
    if(arquivo == NULL) {
        printf("Erro ao salvar arquivo!\n"); // Verifica erro na abertura
        return;
    }
    
    int i, j; // Índices para loops
    for(i = 0; i < total; i++) {
        fprintf(arquivo, "%d\n%s\n%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].num_ingredientes); // Salva código, nome e número de ingredientes
        
        for(j = 0; j < produtos[i].num_ingredientes; j++) {
            fprintf(arquivo, "%s\n%d\n", 
                   produtos[i].ingredientes[j].nome, 
                   produtos[i].ingredientes[j].quantidade); // Salva cada ingrediente
        }
        
        fprintf(arquivo, "%.2f\n", produtos[i].preco); // Salva o preço
    }
    
    fclose(arquivo); // Fecha o arquivo
}

void CarregarProdutos(struct Produto produtos[], int *total) {
    FILE *arquivo = fopen("cardapio.txt", "r"); // Abre o arquivo para leitura
    if(arquivo == NULL) {
        *total = 0; // Define total como 0 se o arquivo não existir
        return;
    }
    
    *total = 0; // Inicializa o contador
    int j; // Índice para ingredientes
    
    // Loop para carregar produtos até o limite ou falha na leitura
    while(*total < 100) {
        if(fscanf(arquivo, "%d\n", &produtos[*total].codigo) != 1) {
            break; // Sai se a leitura do código falhar
        }
        if(!fgets(produtos[*total].nome, 50, arquivo)) {
            break; // Sai se a leitura do nome falhar
        }
        produtos[*total].nome[strcspn(produtos[*total].nome, "\n")] = '\0'; // Remove '\n'
        
        if(fscanf(arquivo, "%d\n", &produtos[*total].num_ingredientes) != 1) {
            break; // Sai se a leitura do número de ingredientes falhar
        }
        
        for(j = 0; j < produtos[*total].num_ingredientes; j++) {
            if(!fgets(produtos[*total].ingredientes[j].nome, 50, arquivo)) {
                break; // Sai se a leitura do nome do ingrediente falhar
            }
            produtos[*total].ingredientes[j].nome[strcspn(produtos[*total].ingredientes[j].nome, "\n")] = '\0'; // Remove '\n'
            if(fscanf(arquivo, "%d\n", &produtos[*total].ingredientes[j].quantidade) != 1) {
                break; // Sai se a leitura da quantidade falhar
            }
        }
        
        if(fscanf(arquivo, "%f\n", &produtos[*total].preco) != 1) {
            break; // Sai se a leitura do preço falhar
        }
        (*total)++; // Incrementa o contador apenas se todas as leituras forem bem-sucedidas
    }
    
    fclose(arquivo); // Fecha o arquivo
}

void ListarProdutos() {
    system("cls"); // Limpa a tela
    printf("|===============================|\n");
    printf("|        LISTA DE PRODUTOS      |\n");
    printf("|===============================|\n");
    
    struct Produto produtos[100]; // Array para produtos
    int total = 0; // Contador de produtos
    int i, j; // Índices para loops
    
    CarregarProdutos(produtos, &total); // Carrega produtos do arquivo
    
    if(total == 0) {
        printf("\nNenhum produto cadastrado!\n"); // Verifica se há produtos
    } else {
        for(i = 0; i < total; i++) {
            printf("\nCódigo: %d\n", produtos[i].codigo); // Exibe o código
            printf("Produto: %s\n", produtos[i].nome); // Exibe o nome
            printf("Ingredientes:\n");
            
            for(j = 0; j < produtos[i].num_ingredientes; j++) {
                printf("- %s (%d)\n", produtos[i].ingredientes[j].nome, 
                       produtos[i].ingredientes[j].quantidade); // Exibe os ingredientes
            }
            
            printf("Preço: R$ %.2f\n", produtos[i].preco); // Exibe o preço
            printf("----------------------------\n");
        }
    }
    
    system("pause"); // Pausa para leitura
}

void AreaCliente() {
    struct Produto produtos[100]; // Array para produtos
    int totalProdutos = 0; // Contador de produtos
    CarregarProdutos(produtos, &totalProdutos); // Carrega produtos do arquivo
    
    struct Pedido pedido; // Estrutura para o pedido
    pedido.numItens = 0; // Inicializa o contador de itens
    pedido.total = 0.0; // Inicializa o total
    
    int opcao; // Variável para a opção do menu
    do {
        system("cls"); // Limpa a tela
        printf("|===================================|\n");
        printf("|        ÁREA DO CLIENTE            |\n");
        printf("|-----------------------------------|\n");
        printf("| 1 - Ver Cardápio                  |\n");
        printf("| 2 - Ver Meu Pedido                |\n");
        printf("| 3 - Finalizar Pedido              |\n");
        printf("| 4 - Voltar ao Menu Inicial        |\n");
        printf("|===================================|\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao); // Lê a opção
        
        switch(opcao) {
            case 1:
                MostrarCardapioCliente(produtos, totalProdutos, &pedido); // Exibe o cardápio
                break;
            case 2:
                MostrarPedido(&pedido); // Exibe o pedido atual
                break;
            case 3:
                FinalizarPedido(&pedido); // Finaliza o pedido
                pedido.numItens = 0; // Reseta o número de itens
                pedido.total = 0.0; // Reseta o total
                return; // Volta ao menu inicial
            case 4:
                return; // Volta ao menu inicial
            default:
                printf("Opção inválida!\n"); // Mensagem de erro
                system("pause");
        }
    } while(1); // Loop infinito até voltar
}

void MostrarCardapioCliente(struct Produto produtos[], int total, struct Pedido *pedido) {
    int opcao, quantidade, i, j; // Variáveis para opção, quantidade e índices
    
    do {
        system("cls"); // Limpa a tela
        printf("|============================================|\n");
        printf("|                CARDÁPIO                    |\n");
        printf("|--------------------------------------------|\n");
        
        if(total == 0) {
            printf("\nNenhum produto disponível no momento!\n"); // Verifica se há produtos
            system("pause");
            return;
        }
        
        for(i = 0; i < total; i++) {
            printf("%d - %s\n", produtos[i].codigo, produtos[i].nome); // Exibe código e nome
            printf("   Ingredientes: ");
            for(j = 0; j < produtos[i].num_ingredientes; j++) {
                printf("%s", produtos[i].ingredientes[j].nome); // Exibe ingredientes
                if(j < produtos[i].num_ingredientes-1) printf(", "); // Adiciona vírgula
            }
            printf("\n");
            printf("   Preço: R$ %.2f\n\n", produtos[i].preco); // Exibe o preço
        }
        
        printf("|--------------------------------------------|\n");
        printf("| Digite o código do produto (0 para voltar): |\n");
        printf("|============================================|\n");
        printf("Opção: ");
        scanf("%d", &opcao); // Lê o código do produto
        
        if(opcao == 0) return; // Volta ao menu anterior
        
        int encontrado = 0; // Flag para produto encontrado
        for(i = 0; i < total; i++) {
            if(produtos[i].codigo == opcao) {
                encontrado = 1; // Marca como encontrado
                printf("\nQuantidade desejada de %s: ", produtos[i].nome);
                scanf("%d", &quantidade); // Lê a quantidade
                
                if(quantidade > 0) {
                    AdicionarItemPedido(pedido, produtos[i], quantidade); // Adiciona ao pedido
                    printf("\n%d %s adicionado(s) ao pedido!\n", quantidade, produtos[i].nome);
                } else {
                    printf("\nQuantidade inválida!\n"); // Mensagem de erro
                }
                system("pause");
                break;
            }
        }
        
        if(!encontrado && opcao != 0) {
            printf("\nProduto não encontrado!\n"); // Mensagem se o código não for encontrado
            system("pause");
        }
    } while(opcao != 0); // Repete até escolher voltar
}

void AdicionarItemPedido(struct Pedido *pedido, struct Produto produto, int quantidade) {
    int i; // Índice para loop
    // Verifica se o item já existe no pedido
    for(i = 0; i < pedido->numItens; i++) {
        if(pedido->itens[i].codigoProduto == produto.codigo) {
            pedido->itens[i].quantidade += quantidade; // Incrementa a quantidade
            pedido->itens[i].subtotal = pedido->itens[i].quantidade * pedido->itens[i].precoUnitario; // Atualiza o subtotal
            pedido->total += quantidade * produto.preco; // Atualiza o total
            return;
        }
    }
    
    // Se não existir, adiciona novo item
    if(pedido->numItens < 50) { // Verifica o limite de itens
        pedido->itens[pedido->numItens].codigoProduto = produto.codigo; // Define o código
        strcpy(pedido->itens[pedido->numItens].nomeProduto, produto.nome); // Copia o nome
        pedido->itens[pedido->numItens].quantidade = quantidade; // Define a quantidade
        pedido->itens[pedido->numItens].precoUnitario = produto.preco; // Define o preço unitário
        pedido->itens[pedido->numItens].subtotal = quantidade * produto.preco; // Calcula o subtotal
        
        pedido->total += pedido->itens[pedido->numItens].subtotal; // Atualiza o total
        pedido->numItens++; // Incrementa o contador de itens
    }
}

void MostrarPedido(struct Pedido *pedido) {
    int i, opcao, index; // Variáveis para índices, opção e índice do item
    
    do {
        system("cls"); // Limpa a tela
        printf("|===================================|\n");
        printf("|            MEU PEDIDO             |\n");
        printf("|-----------------------------------|\n");
        
        if(pedido->numItens == 0) {
            printf("\nSeu pedido está vazio!\n"); // Verifica se o pedido está vazio
            system("pause");
            return;
        }
        
        for(i = 0; i < pedido->numItens; i++) {
            printf("%d - %s\n", i+1, pedido->itens[i].nomeProduto); // Exibe o item
            printf("   Quantidade: %d\n", pedido->itens[i].quantidade); // Exibe a quantidade
            printf("   Preço unitário: R$ %.2f\n", pedido->itens[i].precoUnitario); // Exibe o preço unitário
            printf("   Subtotal: R$ %.2f\n\n", pedido->itens[i].subtotal); // Exibe o subtotal
        }
        
        printf("|-----------------------------------|\n");
        printf("| TOTAL: R$ %.2f\n", pedido->total); // Exibe o total
        printf("|-----------------------------------|\n");
        printf("| 1 - Remover item                  |\n");
        printf("| 2 - Alterar quantidade            |\n");
        printf("| 0 - Continuar                     |\n");
        printf("|===================================|\n");
        printf("Opção: ");
        scanf("%d", &opcao); // Lê a opção
        
        switch(opcao) {
            case 1:
                printf("\nDigite o número do item a remover: ");
                scanf("%d", &index); // Lê o índice do item
                if(index > 0 && index <= pedido->numItens) {
                    RemoverItemPedido(pedido, index-1); // Remove o item
                    printf("\nItem removido com sucesso!\n");
                } else {
                    printf("\nItem inválido!\n"); // Mensagem de erro
                }
                system("pause");
                break;
            case 2:
                printf("\nDigite o número do item a alterar: ");
                scanf("%d", &index); // Lê o índice do item
                if(index > 0 && index <= pedido->numItens) {
                    int novaQuantidade; // Variável para nova quantidade
                    printf("Nova quantidade: ");
                    scanf("%d", &novaQuantidade); // Lê a nova quantidade
                    
                    if(novaQuantidade > 0){
                        pedido->total -= pedido->itens[index-1].subtotal; // Subtrai o subtotal antigo
                        pedido->itens[index-1].quantidade = novaQuantidade; // Atualiza a quantidade
                        pedido->itens[index-1].subtotal = novaQuantidade * pedido->itens[index-1].precoUnitario; // Atualiza o subtotal
                        pedido->total += pedido->itens[index-1].subtotal; // Atualiza o total
                        printf("\nQuantidade atualizada!\n");
                    } else {
                        RemoverItemPedido(pedido, index-1); // Remove se quantidade for 0 ou negativa
                        printf("\nItem removido do pedido!\n");
                    }
                } else {
                    printf("\nItem inválido!\n"); // Mensagem de erro
                }
                system("pause");
                break;
            case 0:
                return; // Volta ao menu anterior
            default:
                printf("\nOpção inválida!\n"); // Mensagem de erro
                system("pause");
        }
    } while(opcao != 0); // Repete até escolher continuar
}

void RemoverItemPedido(struct Pedido *pedido, int index) {
    pedido->total -= pedido->itens[index].subtotal; // Subtrai o subtotal do item
    int i; // Índice para deslocamento
    for(i = index; i < pedido->numItens-1; i++) {
        pedido->itens[i] = pedido->itens[i+1]; // Desloca os itens
    }
    
    pedido->numItens--; // Decrementa o contador de itens
}

void FinalizarPedido(struct Pedido *pedido) {
    if(pedido->numItens == 0) {
        printf("\nSeu pedido está vazio!\n"); // Verifica se o pedido está vazio
        system("pause");
        return;
    }
    
    system("cls"); // Limpa a tela
    printf("|===================================|\n");
    printf("|         FINALIZAR PEDIDO          |\n");
    printf("|-----------------------------------|\n");
    
    MostrarPedido(pedido); // Exibe o pedido atual
    
    int opcao; // Variável para a opção de pagamento
    printf("\n|-----------------------------------|\n");
    printf("| FORMA DE PAGAMENTO:               |\n");
    printf("| 1 - PIX                           |\n");
    printf("| 2 - Cartão de Débito              |\n");
    printf("| 3 - Cartão de Crédito             |\n");
    printf("| 4 - Cancelar Pedido               |\n");
    printf("|===================================|\n");
    printf("Opção: ");
    scanf("%d", &opcao); // Lê a opção de pagamento
    
    switch(opcao) {
        case 1:
        case 2:
        case 3:
            system("cls"); // Limpa a tela
            printf("+=========================================+\n");
            printf("|          PEDIDO FINALIZADO!             |\n");
            printf("|-----------------------------------------|\n");
            printf("| Total: R$ %.2f\n", pedido->total); // Exibe o total
            printf("|                                         |\n");
            printf("|        Pague na maquininha abaixo       |\n");
            printf("|                                         |\n");
            printf("| Obrigado pela preferencia!              |\n");
            printf("+=========================================+\n");
            break;
        case 4:
            printf("\nPedido cancelado.\n"); // Cancela o pedido
            break;
        default:
            printf("\nOpção inválida!\n"); // Mensagem de erro
    }
    system("pause"); // Pausa para leitura
}