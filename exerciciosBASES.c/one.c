/* Um banco concederá um crédito pessoal aos seus clientes de acordo com seu saldo médio 
  no último ano. Implemente uma função que receba como parâmetro o valor do saldo médio 
  do cliente no último ano, calcule e retorne o valor do crédito que será concedido a ele. 
  O cálculo deve ser feito de acordo com a tabela abaixo. Para cada cliente, o programa 
  principal (método main) deverá exibir a seguinte frase: 
  "Para um saldo médio igual a R$___, será dado um crédito de R$___."

  ------------------------------------------------
  | Valor do Saldo Médio       | Valor do Crédito |
  ------------------------------------------------
  | Até R$ 200,00              | 10% do saldo médio|
  | Acima de R$ 200,00 até R$ 300,00 | 20% do saldo médio|
  | Acima de R$ 300,00 até R$ 400,00 | 25% do saldo médio|
  | Acima de R$ 400,00          | 30% do saldo médio|
  ------------------------------------------------

  OBS1: Para o fornecimento do crédito, o saldo médio do cliente não pode ser negativo 
  ou nulo. Caso seja, deve ser informado ao cliente que ele não terá direito ao benefício.

  OBS2: A quantidade de clientes que utilizarão o programa para fazer o cálculo de seu 
  crédito pessoal não é previamente conhecida. Desta forma, a cada cálculo realizado, 
  deve-se perguntar ao usuário se ele deseja efetuar um novo cálculo. A esta pergunta 
  o usuário deverá responder, obrigatoriamente, 'S' ou 'N'. O programa principal 
  (método main) não deve aceitar nenhum outro valor de resposta. */

#include <stdio.h>
#include <ctype.h>

//proced para limpar o buffer sujo
void clearInput(){
    char c;
    c = getchar();
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}
float personal_credit(float saldo){
    
    float balance;
    
    if(saldo <= 200){
        balance = (0.10*saldo);
    }else if(saldo <= 300){
        balance = (0.20*saldo);
    }else if(saldo <= 400){
        balance = (0.25*saldo);
    }else if(saldo > 400){
        balance = (0.30*saldo);
    }
    
    return balance;
}

    

int main()
{
    char last, op;
    float saldo, balance;
    
    
    do{
        
    printf("Enter your average balance: \n");
    scanf("%f%c", &saldo, &last);
    clearInput();
    
    if(saldo <= 0){
        printf("Insufficient average balance. You are not entitled to the benefit\n");
        clearInput();
    }
    do{
        if(last != '\n'){
            printf("Invalid input. Enter again.\n");
            scanf("%f%c", &saldo, &last);
            clearInput();
        }
    }while(last != '\n');
    
    
    balance = personal_credit(saldo);
    printf("For an average balance equal to R$%.2f, a credit of R$%.2f will be given.", saldo,  balance);
   
   do{ 
        printf("\nDo you want to perform a new calculation? (S | N)\n");
        printf(">> ");
        scanf(" %c", &op);
        clearInput();
        
        op = toupper(op);
        if (op != 'S' && op != 'N') {
            printf("\nInvalid character. Enter with S or N\n");
            scanf("%c", &op);
            clearInput();
        }
        
   }while(op != 'S' && op != 'N');
    
    }while(op != 'N');
    
    
    
    return 0;
}

