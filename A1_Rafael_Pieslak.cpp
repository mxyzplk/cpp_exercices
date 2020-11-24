/* Exercício A1
Este programa faz as seguintes funções:
1) Lê um arquivo com os dados dos carros armazenados. 
Coloquei esta opção para facilitar checar.

2) Salva um arquivo com os dados da memória.

3) Insere dados de carros. Os dados de carros são inseridos dentro do
structure carros. O structure pode alocar no máximo 10 carros (ou valor MAX_CARROS).
O programa a cada inserção checa se tem espaço para alocação. O vetor alocacao controla isto.
Se não houver espaço, ele sugere deletar uma das inserções e deixa o usuário escolher.
A remoção implica apenas em alterar o vetor alocacao permitindo que algo seja escrito naquele espaço.
A cada inserção, o programa roda uma rotina que atualiza o vetor ordem que é usado para
ordenar os carros por ano nas rotinas de visualizacao.

4)As rotinas de visualizacao fazem:
- listam todos os carros, ordenados por ano de fabricacao
- listam os carros de um determinado ano
- listam os carros fabricados a partir de determinado ano
- listam os carros de um determinado modelo.


*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/*****************************************************************************************/
#define MAX_CARROS 10
#define MAX_FILENAME 50
#define MAX_PLACA 10
#define MAX_NAME 20
/*****************************************************************************************/
void get_order(int dados_anos[], int dados_ordem[], int alocacao[]);
int verifica_placa(char temp_placa[]);
/*****************************************************************************************/
struct Dados_carros
{
    char marca[MAX_NAME];
    char modelo[MAX_NAME];
    int ano_fabricacao;
    char placa[MAX_PLACA];
};
/*****************************************************************************************/
/*****************************************************************************************/
void get_order(int dados_anos[], int dados_ordem[], int alocacao[]){

    int i; int j; int ref; int chk[MAX_CARROS]={0}; int sel;

    for (i = 0; i < MAX_CARROS; i++){ 
        ref = 99999;
        for (j = 0; j < MAX_CARROS; j++){
            if (dados_anos[j] <= ref && alocacao[j] == 1 && chk[j] == 0) {
                sel = j;
                ref = dados_anos[j];
            }
            /*printf("i: %d j: %d ano: %d sel: %d ref: %d aloc: %d chk: %d\n", i, j, dados_anos[j], sel, ref, alocacao[j], chk[j]);*/
        }
        dados_ordem[i] = sel;
        chk[sel] = 1;
    }
}
/*****************************************************************************************/
/*****************************************************************************************/
void imprime_cab(char arquivo[50])
{
    printf("Escolha uma das opções:\n");
    printf("(1) Ler arquivos de dados de carros. Arquivo atual: %s\n", arquivo);
    printf("(2) Salvar arquivo de dados de carros.\n");
    printf("(3) Inserir dados de carros.\n");
    printf("(4) Ferramentas de visualização.\n");
    printf("(5) Sair.\n");
}
/*****************************************************************************************/
/*****************************************************************************************/
char * trim_string(char *temp_placa)
{
    int i; int j;
    static char retorno[MAX_PLACA];

    for (i = 0, j = 0; i < strlen(temp_placa); i++, j++)
    {
        if (temp_placa[i] != ' ' && i != 3) {
            retorno[j] = temp_placa[i];
        } else if (isdigit(temp_placa[i]) != 0 && i == 3) {
            retorno[j] = '-';
            j++;
            retorno[j] = temp_placa[i];
        } else if (temp_placa[i] == ' ' && i == 3) {
            retorno[j] = '-'; 
        } else if (temp_placa[i] == '-' && i == 3) {
            retorno[j] = temp_placa[i];;             
        } else {
            j--;
        }
    }
    retorno[j]=0;
    return retorno;
}
/*****************************************************************************************/
/*****************************************************************************************/
int verifica_placa(char temp_placa[])
{
    int i;
    int retorno=0;
    int nletras=0;
    int nnums=0;

    if (strlen(temp_placa) != 8){
        retorno = 1;
        printf("Placa com número de caracteres diferente do esperado.\n");
        return retorno;
    }

    for (i = 0; i < strlen(temp_placa); i++)
    {
        if (isalpha(temp_placa[i]) && nletras < 3) {
            nletras = nletras + 1;
        } else if (isalpha(temp_placa[i]) && nletras > 3) {
            retorno = 1; 
            printf("Número de letras da placa diferente do esperado.\n");
            return retorno;
        } else if (isdigit(temp_placa[i]) && nletras < 3) {
            retorno = 1;
            printf("Número de letras da placa diferente do esperado.\n");
            return retorno;
        } else if (temp_placa[i]=='-' && nletras < 3 && i==3) {
            retorno = 1;
            printf("Número de letras da placa diferente do esperado.\n");
            return retorno;          
        } else if (temp_placa[i]=='-'  && i!=3) {
            retorno = 1; 
            printf("Hífen colocado fora de posição.\n");
            return retorno;             
        } else if (isdigit(temp_placa[i]) && nletras == 3) {
            nnums = nnums + 1;            
        } else if (isdigit(temp_placa[i])==0 && isalpha(temp_placa[i]) ==0 && i != 3) {
            retorno = 1;
            printf("Caracter não identificado.\n");
            return retorno;          
        }       
    } 
    if (nnums == 4 && nletras == 3) {
        return retorno;
    } else
    {
        retorno = 1;
        printf("Número de letras e/ou números errado.\n");
        return retorno;
    }      
}
/*****************************************************************************************/
/*****************************************************************************************/
int conta_alocados(int alocados[]){
    int i; int res;
    res = 0;
    for (i = 0; i<MAX_CARROS; i++){
        if (alocados[i] == 1) {
            res = res + 1;
        }
    }
    return res;
}
/*****************************************************************************************/
/*****************************************************************************************/
int main(void)
{
    printf("-------------------------------------------\n");
    printf("---------- Cadastro de Veículos -----------\n");
    printf("-------------------------------------------\n\n\n");

    /*****************************************************************************************/
    int sair = 0; int sair2=0;                              
    char arquivo[MAX_FILENAME]="";              
    int opcao; int opcao2;                                  
    int check;                                  
    /*                                                                                       */
    struct Dados_carros carros[MAX_CARROS];    
    /*                                                                                       */
    /*                                                                                       */
    char *trimmed_placa;
    int slot;
    char dummy; char dummya[MAX_NAME]; int ano;
    int vecs1[MAX_CARROS];
    int order[MAX_CARROS]={0};
    int alocacao[MAX_CARROS]={0};
    int i; int j; int k; char E; int C;
    int ncarros_file;
    char modelo[MAX_NAME];
    /*****************************************************************************************/ 
    FILE *inFile;

    while (sair < 1)
    {
        imprime_cab(arquivo);
        
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 1:
            printf("Digite o nome do arquivo a ser lido: ");
            fgets(arquivo, MAX_FILENAME, stdin);
            arquivo[strcspn(arquivo, "\r\n")] = 0;
            printf("Lendo arquivo %s\n", arquivo);
            if (!(inFile = fopen(arquivo,"r"))) {
                printf("Nome de arquivo inválido");
            } else {
                fscanf(inFile, "%d\n", &ncarros_file);
                for (i = 0; i < ncarros_file; i++) {

                    fgets(carros[i].marca, MAX_NAME, inFile);
                    carros[i].marca[strcspn(carros[i].marca, "\r\n")] = 0;
                    fgets(carros[i].modelo, MAX_NAME, inFile);
                    carros[i].modelo[strcspn(carros[i].modelo, "\r\n")] = 0;
                    fscanf(inFile, "%d\n", &carros[i].ano_fabricacao);
                    fgets(carros[i].placa, MAX_NAME, inFile);
                    carros[i].placa[strcspn(carros[i].placa, "\r\n")] = 0;
                    alocacao[i] = 1;
                    fgets(dummya, MAX_NAME, inFile);
                    
                }
                fclose(inFile);
                for ( int i = 0; i < MAX_CARROS; i++ )
                {
                    order[i]=0;
                    vecs1[i]=carros[i].ano_fabricacao;
                }
                get_order(vecs1, order, alocacao);
            }
            /*ler_dados_carros(arquivo);*/
            break;
        /*****************************************************************************************/ 
        /*****************************************************************************************/
            case 2:
            printf("Digite o nome do arquivo a ser salvo: ");
            fgets(arquivo, MAX_FILENAME, stdin);
            arquivo[strcspn(arquivo, "\r\n")] = 0;
            if (!(inFile = fopen(arquivo,"w"))) {
                printf("Nome de arquivo inválido");
            } else {
                printf("Salvando arquivo %s\n", arquivo);
                /*salvar_dados_carros(arquivo);*/
                ncarros_file = conta_alocados(alocacao);
                fprintf(inFile,"%-d\n",ncarros_file);
                for (i = 0; i < MAX_CARROS; i++) {
                    printf("%d",alocacao[i]);
                    if (alocacao[i] > 0) {
                        fprintf(inFile, "%-s\n",carros[i].marca);
                        fprintf(inFile, "%-s\n",carros[i].modelo);
                        fprintf(inFile, "%-d\n",carros[i].ano_fabricacao);
                        fprintf(inFile, "%-s\n",carros[i].placa);
                        fprintf(inFile,"\n");
                    }
                }
                fclose(inFile);
            }
            break;            
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 3:
            /*********************************************************************************/
            i=0; check=0;
            while (check==0)
            {
                if (i < MAX_CARROS && alocacao[i] == 0) {
                    slot = i;
                    check = 1;
                    alocacao[slot] = 1;
                    printf("Preencha o formulário.\n");
                } else {
                    i++;
                }

                if (i>=MAX_CARROS-1 && check == 0){
                    printf("Todos os espaços de alocação estão ocupados.");
                    printf("(S)air ou (E)xcluir um dos carros?");
                    while (1) 
                    {
                        scanf("%c",&E);
                        getchar();
                        if (E == 'S' || E == 's') {
                            break;
                        } else if (E == 'E' || E == 'e') {
                            printf("ID    Marca                Modelo               Ano     Placa  \n");
                            for (int j = 0; j < MAX_CARROS; j++) {
                                if (alocacao[j] == 1) {
                                    printf("%-5d %20s %20s %4d    %8s\n", j,carros[j].marca, carros[j].modelo, carros[j].ano_fabricacao, carros[j].placa);
                                }
                            }
                            printf("Escolha uma das entradas para ser excluidas.\n");
                            scanf("%d",&C);
                            getchar();
                            if (C >= 0  && C < MAX_CARROS) {
                                alocacao[C] = 0;
                                i=0;
                                break;
                            } 
                        }
                    }
                }
            } 
        /*************************************************************************************/         
            check = 0;
            while (check == 0)
            {
                printf("Digite o nome da marca: ");
                fgets(carros[slot].marca, MAX_NAME, stdin);
                carros[slot].marca[strcspn(carros[slot].marca, "\r\n")] = 0;
                printf("\n");

                if (carros[slot].marca[0] != '\0'){
                    check = 1;
                    printf("Marca %s armazenada.\n", carros[slot].marca);
                }              
            }
            
            check = 0;
            while (check == 0)
            {
                printf("Digite o nome do modelo: ");
                fgets(carros[slot].modelo, MAX_NAME, stdin);
                carros[slot].modelo[strcspn(carros[slot].modelo, "\r\n")] = 0;
                printf("\n");

                if (carros[slot].modelo[0] != '\0'){
                    check = 1;
                    printf("Modelo %s armazenado.\n", carros[slot].modelo);
                }
            }
            
            check = 0;
            while (check == 0)
            {
                printf("Digite o ano de fabricação: ");
                if (scanf("%d", &carros[slot].ano_fabricacao) != 1) {
                    check = 0;
                } else
                {
                    check = 1;
                    printf("Ano %d armazenado.\n", carros[slot].ano_fabricacao);                    
                }            
                getchar();
                printf("\n");
            }
            
            check = 1;
            while (check != 0) 
            {
                printf("Digite a placa do carro:");
                fgets (carros[slot].placa, MAX_PLACA, stdin);
                carros[slot].placa[strcspn(carros[slot].placa, "\r\n")] = 0;
                printf("\n");

                trimmed_placa = trim_string(carros[slot].placa);
                check = verifica_placa(trimmed_placa);   
                
                if (check > 0){
                    printf("Placa do carro deve ser no formato XXXYYYY ou XXX-YYYY\n"); 
                    printf("onde X são letras e Y são números\n");
                }  else {
                    printf("Placa %s armazenada.\n", trimmed_placa);
                }             
            }
                        
            /**/
            for ( int i = 0; i < MAX_CARROS; i++ )
            {
                order[i]=0;
                vecs1[i]=carros[i].ano_fabricacao;
            }
            get_order(vecs1, order, alocacao);
            
            /**/
            break;
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 4:
            
            sair2 = 0;
            while (sair2 < 1)
            {
                printf("\n");
                printf("Escolha uma das opções de visualização:\n");
                printf("(1) Listar todos os carros\n");
                printf("(2) Listar carros filtrando por ano de fabricação.\n");
                printf("(3) Listar carros mais novos dado um ano de fabricação.\n");
                printf("(4) Filtrar por modelo.\n");
                printf("(5) Voltar.\n");

                scanf("%d", &opcao2);
                getchar();

                switch (opcao2)
                {
                    case 1:
                    printf("Marca                Modelo               Ano     Placa  \n");
                    for (i = 0; i < MAX_CARROS; i++) {
                        /*printf("%d  %d\n", order[i], alocacao[order[i]]);*/
                        if (alocacao[order[i]] > 0) {
                            printf("%-20s %-20s %-4d    %8s\n", carros[order[i]].marca, carros[order[i]].modelo, carros[order[i]].ano_fabricacao, carros[order[i]].placa);
                        }
                    }
                    printf("Pressione Enter duas vezes para continuar\n");
                    scanf("%c",&dummy);
                    getchar();
                    break;

                    case 2:
                    printf("Deseja visualizar os carros de qual ano?\n");
                    scanf("%d", &ano);
                    getchar();

                    printf("Marca                Modelo               Ano     Placa  \n");
                    for (i = 0; i < MAX_CARROS; i++) {
                        /*printf("%d  %d\n", order[i], alocacao[order[i]]);*/
                        if (alocacao[order[i]] > 0 && carros[order[i]].ano_fabricacao == ano) {
                            printf("%-20s %-20s %-4d    %8s\n", carros[order[i]].marca, carros[order[i]].modelo, carros[order[i]].ano_fabricacao, carros[order[i]].placa);
                        }
                    }
                    printf("Pressione Enter duas vezes para continuar\n");
                    scanf("%c",&dummy);
                    getchar();                                        
                    break;

                    case 3:
                    printf("Deseja visualizar os carros mais novos apartir de qual ano?\n");
                    scanf("%d", &ano);
                    getchar();

                    printf("Marca                Modelo               Ano     Placa  \n");
                    for (i = 0; i < MAX_CARROS; i++) {
                        /*printf("%d  %d\n", order[i], alocacao[order[i]]);*/
                        if (alocacao[order[i]] > 0 && carros[order[i]].ano_fabricacao >= ano) {
                            printf("%-20s %-20s %-4d    %8s\n", carros[order[i]].marca, carros[order[i]].modelo, carros[order[i]].ano_fabricacao, carros[order[i]].placa);
                        }
                    }
                    break;

                    case 4:
                    printf("Deseja visualizar os carros de qual modelo?\n");
                    fgets (modelo, MAX_PLACA, stdin);
                    modelo[strcspn(modelo, "\r\n")] = 0;
                    printf("\n");

                    printf("Marca                Modelo               Ano     Placa  \n");
                    for (i = 0; i < MAX_CARROS; i++) {
                        /*printf("%d  %d\n", order[i], alocacao[order[i]]);*/
                        if (alocacao[order[i]] > 0) {
                            k = 0;
                            for (j=0; j<strlen(modelo); j++){
                                if (tolower(modelo[j]) != tolower(carros[order[i]].modelo[j])) {
                                    k=1;
                                }
                            }
                            if (k == 0) {
                                printf("%-20s %-20s %-4d    %8s\n", carros[order[i]].marca, carros[order[i]].modelo, carros[order[i]].ano_fabricacao, carros[order[i]].placa);   
                            }
                        }
                    }

                    break;
                    case 5:
                    sair2 = 1;
                    break;

                    default:
                    printf("Opção inválida");
                }
            }
            break;
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 5:
            sair = 1;
            break;

        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            default:
            printf("Opção inválida");

        }
    }

    return 0;
}

