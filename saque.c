#include <stdio.h>
#include "saque.h"

void realizarSaque(Usuario* u) {
    float valor;

    printf("\n========== MENU DE SAQUE ==========\n");
    printf("Saldo atual: R$ %.2f\n", u->saldo);
    printf("Digite o valor que deseja sacar: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor inválido! Digite um valor maior que zero.\n");
        return;
    }

    if (valor > u->saldo) {
        printf("Saldo insuficiente!\n");
        return;
    }

    u->saldo -= valor;
    printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
    printf("Novo saldo: R$ %.2f\n", u->saldo);
}
