#include <stdio.h>
#include <string.h>
#include <locale.h>


void mostrar_menu() {
	setlocale(LC_ALL, "pt_PT");
    printf("\n");
    printf("  +------------------------------+\n");
    printf("  |   === CAIXA ELETRÔNICO ===   |\n");
    printf("  +------------------------------+\n");
    printf("  |  [1] Ver saldo               |\n");
    printf("  |  [2] Sacar                   |\n");
    printf("  |  [3] Depositar               |\n");
    printf("  |  [4] Sair                    |\n");
    printf("  +------------------------------+\n");
    printf("  |  >> Selecione uma opção:     |\n");
    printf("  +------------------------------+\n");
    printf("  ");
}

int main() {
    char conta_digitada[7];
    char senha_digitada[5];
    int tentativas = 0;
    int bloqueada = 0;
    
    // Conta pré-cadastrada
    char conta_correta[7] = "123456";
    char senha_correta[5] = "1111";
    float saldo = 1000.0;
    
    // Tela inicial com design
    printf("\n");
    printf("  +------------------------------+\n");
    printf("  |  BEM-VINDO AO CAIXA 24H      |\n");
    printf("  +------------------------------+\n");
    printf("  |                              |\n");
    printf("  | Por favor, insira seus dados |\n");
    printf("  |                              |\n");
    printf("  +------------------------------+\n");
    
    // Sistema de login
    while(1) {
        if(bloqueada) {
            printf("\n");
            printf("  +------------------------------+\n");
            printf("  |  CONTA BLOQUEADA!            |\n");
            printf("  |  Procure o gerente.          |\n");
            printf("  +------------------------------+\n");
            return 0;
        }
        
        printf("  Conta (6 digitos): ");
        scanf("%6s", conta_digitada);
        
        printf("  Senha (4 digitos): ");
        scanf("%4s", senha_digitada);
        
        // Verificação de login
        if(strcmp(conta_digitada, conta_correta) == 0 && 
           strcmp(senha_digitada, senha_correta) == 0) {
            tentativas = 0;
            break;
        } 
        else {
            tentativas++;
            printf("\n");
            printf("  +------------------------------+\n");
            printf("  |  SENHA INCORRETA!            |\n");
            printf("  |  Tentativas restantes: %d     |\n", 3 - tentativas);
            printf("  +------------------------------+\n");
            
            if(tentativas >= 3) {
                bloqueada = 1;
            }
        }
    }
    
    // Menu principal
    int opcao;
    do {
        mostrar_menu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("\n");
                printf("  +------------------------------+\n");
                printf("  |  SALDO ATUAL: R$ %.2f        |\n", saldo);
                printf("  +------------------------------+\n");
                break;
            case 2:
                printf("\n");
                printf("  +------------------------------+\n");
                printf("  |  SAQUE SELECIONADO           |\n");
                printf("  +------------------------------+\n");
                break;
            case 3:
                printf("\n");
                printf("  +------------------------------+\n");
                printf("  |  DEPOSITO SELECIONADO        |\n");
                printf("  +------------------------------+\n");
                break;
            case 4:
                printf("\n");
                printf("  +------------------------------+\n");
                printf("  |  OBRIGADO POR USAR NOSSO CE |\n");
                printf("  |  TENHA UM BOM DIA!           |\n");
                printf("  +------------------------------+\n");
                break;
            default:
                printf("\n");
                printf("  +------------------------------+\n");
                printf("  |  OPCAO INVALIDA!             |\n");
                printf("  |  Tente novamente.            |\n");
                printf("  +------------------------------+\n");
        }
    } while(opcao != 4);
    
    return 0;
}
