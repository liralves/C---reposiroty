/*
  Implemente um programa para calcular o volume de sólidos geométricos. Os sólidos cujas 
  áreas poderemos calcular serão: cubo, esfera, cilindro e paralelepípedo. O programa principal 
  (método main) deverá ter quatro funções: uma para o cálculo de cada tipo de volume.

  (a) Função para calcular o volume de um cubo. Esta função deverá receber como parâmetro de 
      entrada o valor do lado do cubo e deverá retornar o volume calculado.

  (b) Função para calcular o volume de um paralelepípedo. Esta função deverá receber como 
      parâmetros de entrada os valores da altura, largura e comprimento do paralelepípedo e deverá 
      retornar o volume calculado.

  (c) Função para calcular o volume de uma esfera. Esta função deverá receber como parâmetro de 
      entrada o valor do raio da esfera e deverá retornar o volume calculado.

  (d) Função para calcular o volume de um cilindro. Esta função deverá receber como parâmetros 
      de entrada os valores da altura e raio da base do cilindro e deverá retornar o volume calculado.

  OBS1: Toda entrada e saída (exibição) de dados deve ser feita pelo programa principal (método 
  main).

  OBS2: O programa principal (método main) deverá ter um menu de opções que permita ao usuário 
  executar os sub-programas quantas vezes desejar e só deverá terminar sua execução se o usuário 
  solicitar.
*/

#include <stdio.h>
#include <ctype.h>
#define PI 3.14

//proced para limpar o buffer sujo
void clearInput(){
    char c;
    c = getchar();
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

float cube_vol(float a){
    float vol = (a * a * a);
    return vol;
}
float parallelepiped(float height, float width, float length){
    float vol;
    
    vol = (height * width * length);
    return vol;
}
float ball(float radius){
    float vol;
    
    vol = (1.3 * PI * (radius * radius * radius));
    return vol;
}
float cylinder(float height, float radius){
    float vol;
    
    vol = (PI * (radius * radius) * height);
    return vol;
}

int main()
{
    int op;
    float result, size, height, width, length, radiusb, radiusc;

    do{
        
        printf("\nMENU\n");
        printf("1 - Calculate volume of cube.\n");
        printf("2 - Calculate volume of parallelepiped.\n");
        printf("3 - Calculate volume of a sphere.\n");
        printf("4 - Calculate cylinder volume.\n");
        printf("5 - Exit.\n");
        printf(">> ");
        scanf("%d", &op);
        
        switch(op){
            case 1:
            printf("Enter the value of the cube side: ");
            scanf("%f", &size);
            result = cube_vol(size);
            printf("Volume of the cube: %.2f\n", result);
            break;
            
            case 2:
            printf("Enter the value height: \n");
            scanf("%f", &height);
            printf("Enter the value of width: \n");
            scanf("%f", &width);
            printf("Enter the value of length: \n");
            scanf("%f", &length);
            result = parallelepiped(height, width, length);
            printf("Volume of the parallelepiped: %.2f\n", result);
            break;
            
            case 3:
            printf("Enter the value of radius: \n");
            scanf("%f", &radiusb);
            result = ball(radiusb);
            printf("Volume of the ball: %.2f\n", result);
            break;
            
            case 4:
            printf("Enter the value of height: \n");
            scanf("%f", &height);
            printf("Enter the value of radius: \n");
            scanf("%f", &radiusc);
            result = cylinder(height, radiusc);
            printf("Volume of the cylinder: %2.f\n", result);
            break;
            
            case 5:
            break;
            
        }
        
    }while(op != 5);
    
    
    return 0;
}
