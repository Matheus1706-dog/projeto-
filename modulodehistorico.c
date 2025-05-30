#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_OPERACOES 100
#define MAX_DESCRICAO 50
#define MAX_DATA 20

typedef struct {
    int id;
    char tipo[20];         
    double valor;
    char descricao[MAX_DESCRICAO];
    char data_hora[MAX_DATA];
    double saldo_anterior;
    double saldo_atual;
} Operacao;


typedef struct {
    Operacao operacoes[MAX_OPERACOES];
    int total_operacoes;
} HistoricoOperacoes;


HistoricoOperacoes historico = {0};


void obter_data_hora(char *buffer) {
    time_t tempo_atual;
    struct tm *info_tempo;
    
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    
    strftime(buffer, MAX_DATA, "%d/%m/%Y %H:%M:%S", info_tempo);
}


void adicionar_operacao(const char *tipo, double valor, const char *descricao, 
                       double saldo_anterior, double saldo_atual) {
    if (historico.total_operacoes >= MAX_OPERACOES) {
        printf("Histórico cheio! Removendo operação mais antiga...\n");
        
        for (int i = 0; i < MAX_OPERACOES - 1; i++) {
            historico.operacoes[i] = historico.operacoes[i + 1];
        }
        historico.total_operacoes--;
    }
    
    Operacao *nova_op = &historico.operacoes[historico.total_operacoes];
    nova_op->id = historico.total_operacoes + 1;
    strcpy(nova_op->tipo, tipo);
    nova_op->valor = valor;
    strcpy(nova_op->descricao, descricao);
    obter_data_hora(nova_op->data_hora);
    nova_op->saldo_anterior = saldo_anterior;
    nova_op->saldo_atual = saldo_atual;
    
    historico.total_operacoes++;
}


void exibir_historico_completo() {
    printf("\n");
    printf("=====================================\n");
    printf("     HISTÓRICO DE OPERAÇÕES\n");
    printf("=====================================\n");
    
    if (historico.total_operacoes == 0) {
        printf("Nenhuma operação encontrada.\n");
        printf("=====================================\n");
        return;
    }
    
    printf("Total de operações: %d\n\n", historico.total_operacoes);
    
    for (int i = historico.total_operacoes - 1; i >= 0; i--) {
        Operacao *op = &historico.operacoes[i];
        
        printf("ID: %03d | %s\n", op->id, op->data_hora);
        printf("Tipo: %s\n", op->tipo);
        
        if (op->valor > 0) {
            printf("Valor: R$ %.2f\n", op->valor);
        }
        
        if (strlen(op->descricao) > 0) {
            printf("Descrição: %s\n", op->descricao);
        }
        
        printf("Saldo anterior: R$ %.2f\n", op->saldo_anterior);
        printf("Saldo atual: R$ %.2f\n", op->saldo_atual);
        printf("-------------------------------------\n");
    }
    
    printf("=====================================\n");
}

// Função para exibir histórico por tipo de operação
void exibir_historico_por_tipo(const char *tipo_filtro) {
    printf("\n");
    printf("=====================================\n");
    printf("   HISTÓRICO - %s\n", tipo_filtro);
    printf("=====================================\n");
    
    int encontradas = 0;
    
    for (int i = historico.total_operacoes - 1; i >= 0; i--) {
        Operacao *op = &historico.operacoes[i];
        
        if (strcmp(op->tipo, tipo_filtro) == 0) {
            printf("ID: %03d | %s\n", op->id, op->data_hora);
            
            if (op->valor > 0) {
                printf("Valor: R$ %.2f\n", op->valor);
            }
            
            if (strlen(op->descricao) > 0) {
                printf("Descrição: %s\n", op->descricao);
            }
            
            printf("Saldo: R$ %.2f -> R$ %.2f\n", 
                   op->saldo_anterior, op->saldo_atual);
            printf("-------------------------------------\n");
            encontradas++;
        }
    }
    
    if (encontradas == 0) {
        printf("Nenhuma operação do tipo '%s' encontrada.\n", tipo_filtro);
    } else {
        printf("Total de operações encontradas: %d\n", encontradas);
    }
    
    printf("=====================================\n");
}


void exibir_ultimas_operacoes(int quantidade) {
    printf("\n");
    printf("=====================================\n");
    printf("   ÚLTIMAS %d OPERAÇÕES\n", quantidade);
    printf("=====================================\n");
    
    if (historico.total_operacoes == 0) {
        printf("Nenhuma operação encontrada.\n");
        printf("=====================================\n");
        return;
    }
    
    int limite = (quantidade > historico.total_operacoes) ? 
                 historico.total_operacoes : quantidade;
    
    for (int i = historico.total_operacoes - 1; i >= historico.total_operacoes - limite; i--) {
        Operacao *op = &historico.operacoes[i];
        
        printf("ID: %03d | %s\n", op->id, op->data_hora);
        printf("Tipo: %s", op->tipo);
        
        if (op->valor > 0) {
            printf(" - R$ %.2f", op->valor);
        }
        
        printf("\nSaldo: R$ %.2f\n", op->saldo_atual);
        printf("-------------------------------------\n");
    }
    
    printf("=====================================\n");
}


void gerar_relatorio_movimentacao() {
    printf("\n");
    printf("=====================================\n");
    printf("   RELATÓRIO DE MOVIMENTAÇÃO\n");
    printf("=====================================\n");
    
    if (historico.total_operacoes == 0) {
        printf("Nenhuma operação para gerar relatório.\n");
        printf("=====================================\n");
        return;
    }
    
    double total_saques = 0, total_depositos = 0;
    int qtd_saques = 0, qtd_depositos = 0, qtd_transferencias = 0, qtd_consultas = 0;
    
    for (int i = 0; i < historico.total_operacoes; i++) {
        Operacao *op = &historico.operacoes[i];
        
        if (strcmp(op->tipo, "SAQUE") == 0) {
            total_saques += op->valor;
            qtd_saques++;
        } else if (strcmp(op->tipo, "DEPOSITO") == 0) {
            total_depositos += op->valor;
            qtd_depositos++;
        } else if (strcmp(op->tipo, "TRANSFERENCIA") == 0) {
            qtd_transferencias++;
        } else if (strcmp(op->tipo, "CONSULTA") == 0) {
            qtd_consultas++;
        }
    }
    
    printf("RESUMO DE OPERAÇÕES:\n");
    printf("- Saques: %d operações (R$ %.2f)\n", qtd_saques, total_saques);
    printf("- Depósitos: %d operações (R$ %.2f)\n", qtd_depositos, total_depositos);
    printf("- Transferências: %d operações\n", qtd_transferencias);
    printf("- Consultas: %d operações\n", qtd_consultas);
    printf("\nTotal de operações: %d\n", historico.total_operacoes);
    printf("Movimentação líquida: R$ %.2f\n", total_depositos - total_saques);
    
    if (historico.total_operacoes > 0) {
        printf("Saldo atual: R$ %.2f\n", 
               historico.operacoes[historico.total_operacoes - 1].saldo_atual);
    }
    
    printf("=====================================\n");
}


void menu_historico() {
    int opcao;
    
    do {
        printf("\n");
        printf("=====================================\n");
        printf("      HISTÓRICO DE OPERAÇÕES\n");
        printf("=====================================\n");
        printf("1. Exibir histórico completo\n");
        printf("2. Filtrar por tipo de operação\n");
        printf("3. Últimas operações\n");
        printf("4. Relatório de movimentação\n");
        printf("0. Voltar ao menu principal\n");
        printf("=====================================\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                exibir_historico_completo();
                break;
                
            case 2: {
                int tipo_opcao;
                printf("\nFiltrar por tipo:\n");
                printf("1. SAQUE\n");
                printf("2. DEPOSITO\n");
                printf("3. TRANSFERENCIA\n");
                printf("4. CONSULTA\n");
                printf("Escolha: ");
                scanf("%d", &tipo_opcao);
                
                switch (tipo_opcao) {
                    case 1: exibir_historico_por_tipo("SAQUE"); break;
                    case 2: exibir_historico_por_tipo("DEPOSITO"); break;
                    case 3: exibir_historico_por_tipo("TRANSFERENCIA"); break;
                    case 4: exibir_historico_por_tipo("CONSULTA"); break;
                    default: printf("Opção inválida!\n");
                }
                break;
            }
            
            case 3: {
                int quantidade;
                printf("Quantas operações exibir? ");
                scanf("%d", &quantidade);
                exibir_ultimas_operacoes(quantidade);
                break;
            }
            
            case 4:
                gerar_relatorio_movimentacao();
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPara continuar...");
            getchar(); a
            getchar(); 
        }
        
    } while (opcao != 0);
}


void demonstrar_uso() {
    double saldo = 1000.0;
    
    // Simulando algumas operações
    adicionar_operacao("CONSULTA", 0, "Consulta de saldo", saldo, saldo);
    
    saldo -= 200.0;
    adicionar_operacao("SAQUE", 200.0, "Saque no caixa eletrônico", saldo + 200.0, saldo);
    
    saldo += 500.0;
    adicionar_operacao("DEPOSITO", 500.0, "Depósito em conta", saldo - 500.0, saldo);
    
    saldo -= 150.0;
    adicionar_operacao("TRANSFERENCIA", 150.0, "Transferência para conta 12345", saldo + 150.0, saldo);
    
    adicionar_operacao("CONSULTA", 0, "Consulta após transferência", saldo, saldo);
    
    printf("Demonstração do módulo de histórico de operações:\n");
    printf("Foram adicionadas algumas operações de exemplo.\n");
}


int main() {
    demonstrar_uso();
    menu_historico();
    return 0;
}
