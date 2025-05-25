#include <stdio.h> 
#include <stdlib.h> 


void consultar_saldo(float saldo_atual) {
    printf("\n--- Consulta de Saldo ---\n");
    printf("Seu saldo atual é: R$ %.2f\n", saldo_atual);
    printf("-------------------------\n");
}

int main() {
    
    float saldo_conta = 1250.75; 

    int opcao;

    do {

        printf("\n--- Caixa Eletrônico ---\n");
        printf("1. Consultar Saldo\n");
        printf("2. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultar_saldo(saldo_conta);
                break;
            case 2:
                printf("Obrigado por usar nosso caixa eletrônico. Volte sempre!\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }

        if (opcao != 2) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
            system("clear || cls"); 
        }

    } while (opcao != 2); 

    return 0; 
}
