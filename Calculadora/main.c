#include <stdio.h>
#include "calculadora.h"

int main() {

    char posFixa[] = "0.5 45 sen 2 ^ +";
    
    char *inFixa = getFormaInFixa(posFixa);
    
    float valor = getValor(posFixa);

    printf("Expressão Pós-fixada: %s\n", posFixa);
    printf("Expressão Infixa: %s\n", inFixa);
    printf("Valor da expressão: %f\n", valor);
    
    return 0;
}
