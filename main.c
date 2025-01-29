#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_REGISTROS 100

typedef struct{
    char dataInicio[11];
    char dataFim[11];
    char sintomas[200];
} Ciclo;

void limparTela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void removerNovaLinha(char *str){
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}

void adicionarCiclo(Ciclo ciclos[], int *numCiclos){
    if (*numCiclos >= MAX_REGISTROS){
        printf("Limite de registros atingido.\n");
        return;
    }
    printf("Digite a data de inicio do ciclo (DD/MM/YYYY): ");
    fgets(ciclos[*numCiclos].dataInicio, 11, stdin);
    removerNovaLinha(ciclos[*numCiclos].dataInicio);
    getchar();
    printf("Digite a data de fim do ciclo (DD/MM/YYYY): ");
    fgets(ciclos[*numCiclos].dataFim, 11, stdin);
    removerNovaLinha(ciclos[*numCiclos].dataFim);
    getchar();
    printf("Digite os sintomas (separados por virgulas): ");
    fgets(ciclos[*numCiclos].sintomas, 200, stdin);
    removerNovaLinha(ciclos[*numCiclos].sintomas);

    (*numCiclos)++;
    printf("Ciclo adicionado com sucesso!\n");
}

void preverProximoCiclo(Ciclo ciclos[], int numCiclos){
    if (numCiclos == 0){
        printf("Nenhum ciclo registrado.\n");
        return;
    }

    struct tm tm = {0}; 
    char buffer[11];
    int dia, mes, ano;

    sscanf(ciclos[numCiclos - 1].dataInicio, "%d/%d/%d", &dia, &mes, &ano);
    tm.tm_mday = dia + 28;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    mktime(&tm);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &tm);
    limparTela();
    printf("+-----------------------------------+\n");
    printf("Proxima menstruacao prevista para: %s\n", buffer);
    printf("+-----------------------------------+\n");

    sscanf(ciclos[numCiclos - 1].dataInicio, "%d/%d/%d", &dia, &mes, &ano);
    tm.tm_mday = dia + 14;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    mktime(&tm);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &tm);
    printf("Data prevista para ovulacao: %s\n", buffer);
    printf("+-----------------------------------+\n");

    sscanf(ciclos[numCiclos - 1].dataInicio, "%d/%d/%d", &dia, &mes, &ano);
    tm.tm_mday = dia + 9;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    mktime(&tm);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &tm);
    printf("Inicio do periodo fertil: %s\n", buffer);
    
    tm.tm_mday = dia + 16;
    mktime(&tm);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &tm);
    printf("Fim do periodo fertil: %s\n", buffer);
    printf("+-----------------------------------+\n");

}

void visualizarHistorico(Ciclo ciclos[], int numCiclos){
    if (numCiclos == 0){
        printf("Nenhum ciclo registrado.\n");
        return;
    }

    limparTela();
    for (int i = 0; i < numCiclos; i++){
        printf("+------------------------------------------+\n");
        printf("| Ciclo %d: \n", i + 1);
        printf("| Inicio: %s\n", ciclos[i].dataInicio);
        printf("| Fim: %s\n", ciclos[i].dataFim);
        printf("| Sintomas: %s\n", ciclos[i].sintomas);
        printf("+------------------------------------------+\n");
    }
}

int main(){
    Ciclo ciclos[MAX_REGISTROS];
    int numCiclos = 0;
    int opcao;

    do{
        limparTela();
        printf("+---------------------------------------+\n");
        printf("|     CALCULADORA DE CICLO MENSTRUAL    |\n");
        printf("+---------------------------------------+\n");
        printf("| 1 - Adicionar ciclo                   |\n");
        printf("| 2 - Prever proxima menstruacao        |\n");
        printf("| 3 - Visualizar historico              |\n");
        printf("| 4 - Sair                              |\n");
        printf("+---------------------------------------+\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:
            adicionarCiclo(ciclos, &numCiclos);
            printf("Pressione Enter para continuar...\n");
            getchar();
            break;
        case 2:
            preverProximoCiclo(ciclos, numCiclos);
            printf("Pressione Enter para continuar...\n");
            getchar();
            break;
        case 3:
            visualizarHistorico(ciclos, numCiclos);
            printf("Pressione Enter para continuar...\n");
            getchar();
            break;
        case 4:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opcao Invalida! Pressione Enter para tentar novamente...\n");
            getchar();
            break;
        }

    } while (opcao != 4);

    return 0;
}
