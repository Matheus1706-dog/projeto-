#include <stdio.h>
#include <stdlib.h>

void realizarDeposito(float *saldo) {
    float valorDeposito;

    printf("Digite o valor a ser depositado: R$ ");
    scanf("%f", &valorDeposito);

    if (valorDeposito <= 0) {
        printf("Valor invalido! O deposito deve ser maior que zero.\n");
        return;
    }

    *saldo += valorDeposito;
    printf("Deposito de R$ %.2f realizado com sucesso!\n", valorDeposito);
    printf("Novo saldo: R$ %.2f\n", *saldo);
}


int main() {
    float saldo = 1000.00;
    int opcao;

    do {
        printf("1- Ver saldo\n");
        printf("2- Realizar deposito\n");
        printf("0- Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Saldo atual: R$ %.2f\n", saldo);
                break;
            case 2:
                realizarDeposito(&saldo);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

