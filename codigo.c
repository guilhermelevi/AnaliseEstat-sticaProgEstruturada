#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100 

struct Aluno {
    char nome[50];
    int idade;
    char sexo;
    float nota[3];
    float media;
    bool aprovado;
};

struct Aluno setAluno(int qntd_notas) {
    struct Aluno aluno;

    printf("\nNome: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; 

    do {
        printf("Sexo: ");
        scanf(" %c", &aluno.sexo);
        while (getchar() != '\n');  // Limpa o buffer do teclado após scanf
    } while (aluno.sexo != 'M' && aluno.sexo != 'm' && aluno.sexo != 'F' && aluno.sexo != 'f');

    do {
        printf("Idade: ");
        scanf("%d", &aluno.idade);
        while (getchar() != '\n');  // Limpa o buffer do teclado após scanf
    } while (aluno.idade < 16 || aluno.idade > 100);

    for(int i = 0; i < qntd_notas; i++) {
        do {
            printf("Digite a %d nota: ", i + 1);
            scanf("%f", &aluno.nota[i]);
            while (getchar() != '\n');  // Limpa o buffer do teclado após scanf
        } while (aluno.nota[i] < 0 || aluno.nota[i] > 10);  // Corrige a condição para valores de nota
    }

    return aluno;
}

float media_aluno(struct Aluno aluno, int qntd_notas) {
    float total = 0.0;
    
    for(int i = 0; i < qntd_notas; i++) {
        total += aluno.nota[i];
    }
    
    return total / qntd_notas;
}

bool funcao_aprovado(float media_aluno, float media_aprovacao) {
    return media_aluno >= media_aprovacao;
}

void maiorMenorIdade(int quantidade, struct Aluno aluno[], int *maior, int *menor) {
  *maior = aluno[0].idade;
  *menor = aluno[0].idade;

  for(int i = 0; i < quantidade; i++) {
    if(aluno[i].idade < *menor) {
      *menor = aluno[i].idade;
    }
    if(aluno[i].idade > *maior) {
      *maior = aluno[i].idade;
    }
  }
}

void aprovadoReprovado(int quantidade, struct Aluno aluno[], float *porcentagem_aprovado, float *porcentagem_reprovado) {
  float aprovado = 0;
  float reprovado = 0;
  *porcentagem_aprovado = 0;  
  *porcentagem_reprovado = 0;

  for(int i = 0; i < quantidade; i++){
    if(aluno[i].aprovado == true){
      aprovado++;
    }
    else{
      reprovado++;
    }
  }
  
  *porcentagem_aprovado = (aprovado / quantidade) * 100;
  *porcentagem_reprovado = (reprovado / quantidade) * 100;
}
int main() {
    int qntd_notas = 0;
    int continuar = 1;
    float media_aprovacao = 0;
    float total_idades = 0;
    float total_media = 0;

    printf("\nQuantas notas serão registradas: ");
    scanf("%d", &qntd_notas);
    while (getchar() != '\n'); 

    printf("Média para aprovação: ");
    scanf("%f", &media_aprovacao);
    while (getchar() != '\n'); 

    struct Aluno aluno[MAX];
    int i = 0;

    while(continuar == 1) {
        
      aluno[i] = setAluno(qntd_notas);
      total_idades += aluno[i].idade;
      
      aluno[i].media = media_aluno(aluno[i], qntd_notas);
      total_media += aluno[i].media;

      aluno[i].aprovado = funcao_aprovado(aluno[i].media, media_aprovacao);

      printf("Media: %.2f", aluno[i].media);
      printf("\n%s", aluno[i].aprovado ? "Aprovado" : "Reprovado");
      
      printf("\n\nDeseja continuar?\n[1] - SIM\n[0] - NAO\n");
      scanf("%d", &continuar);
      while (getchar() != '\n'); 
      i++;        
      
    }

    int maiorIdade, menorIdade;
    maiorMenorIdade(i, aluno, &maiorIdade, &menorIdade);
    float porcentagem_aprovado, porcentagem_reprovado;
    aprovadoReprovado(i, aluno, &porcentagem_aprovado, &porcentagem_reprovado);

    printf("\n");
    printf("Menor idade Registrada: %d\n", menorIdade);
    printf("Maior idade Registrada: %d\n", maiorIdade);
    printf("Media total idades: %.1f\n", total_idades / i);
    printf("Media total notas: %.2f\n", total_media / i);
    printf("Porcentagem Aprovada: %.2f%%\n", porcentagem_aprovado);
    printf("Porcentagem reprovada: %.2f%%\n", porcentagem_reprovado);
    printf("\n");


    return 0;
}