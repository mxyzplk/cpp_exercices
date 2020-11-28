/* Exercício A3
Local: https://github.com/mxyzplk/cpp_exercices
Arquivo: A3_Rafael_Pieslak.cpp


*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/*****************************************************************************************/
#define MAX_FILENAME 50
#define MAX_NAME 30
/*****************************************************************************************/
struct Dados_clientes
{
    char Nome[MAX_NAME];
    int Ano;
    float Valor;
};
Dados_clientes* alocar_clientes();
/*****************************************************************************************/
/*****************************************************************************************/
Dados_clientes* alocar_clientes()
{
    Dados_clientes *p = (Dados_clientes*) malloc(10*sizeof(Dados_clientes));
    if (p!= NULL)
    {
        return p;
    }
    else
    {
        printf("\nErro de Alocação de Memória\n");
        exit(1);
    }
}
/*****************************************************************************************/
/*****************************************************************************************/
int realocar_clientes(Dados_clientes *p,int i)
{
    p = (Dados_clientes*) realloc(p,i*sizeof(Dados_clientes));
    if(p!= NULL)
    {
        return 1; //Ok
    }
    else
    {
        return 0; //Não ok
    }
}
/*****************************************************************************************/
/*****************************************************************************************/
void copia(Dados_clientes *ent, Dados_clientes *sai, int j)
{
    int i;
    for (i = 0; i < j; i++){
        strcpy(sai[i].Nome, ent[i].Nome);
        sai[i].Ano = ent[i].Ano;
        sai[i].Valor = ent[i].Valor;
    }
}
/*****************************************************************************************/
/*****************************************************************************************/
void imprime_cab(char dbclientes[MAX_FILENAME])
{
    printf("Escolha uma das opções:\n");
    printf("(0) Ler database de cadastro de clientes. Database ativa: %s\n", dbclientes);
    printf("(1) Salvar arquivos de database de clientes.\n");
    printf("(2) Inserir/Atualizar/Remover dados de clientes.\n");   
    printf("(3) Opções de visualização.\n");
    printf("(4) Sair.\n");
}
/*****************************************************************************************/
/*****************************************************************************************/
int main(void)
{
    printf("-------------------------------------------\n");
    printf("---------- Cadastro de Clientes -----------\n");
    printf("-------------------------------------------\n\n\n");

    /*****************************************************************************************/
    int sair = 0; int voltar = 0;                              
    char dbclientes[MAX_FILENAME]=""; 
    int ngastos; int nclientes; int nalocs;
    int opcao; int opcao2; int opcao3; int opcao4; int MAX_CLIENTES;
    int slot;
    float Valor;
    char InputName[MAX_NAME];          
    /*                                                                                       */
    Dados_clientes *Clientes = alocar_clientes();
    Dados_clientes *Dummy = alocar_clientes();
    MAX_CLIENTES = 10; 
    /*                                                                                       */
    /*                                                                                       */
    int i; int j; int k;
    /*****************************************************************************************/ 
    FILE *inDBClientes;

    while (sair < 1)
    {
        imprime_cab(dbclientes);
        
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 0:
            printf("Digite o nome da database de clientes a ser lido: ");
            fgets(dbclientes, MAX_FILENAME, stdin);
            dbclientes[strcspn(dbclientes, "\r\n")] = 0;
            // Checa tamanho atual do vetor
            nalocs = 0;
            for (i = 0; i < MAX_CLIENTES; i++) {
                if (strlen(Clientes[i].Nome) != 0) {
                    nalocs = nalocs + 1;
                }
            }

            // Leitura clientes Cadastrados
            if (!(inDBClientes = fopen(dbclientes,"r"))) {
                printf("Nome de arquivo inválido.\n");
            } else {
                fscanf(inDBClientes, "%d\n", &nclientes);
                for (i = nalocs; i < nalocs+nclientes; i++) {
                    if (i < MAX_CLIENTES) {
                        fgets(Clientes[i].Nome, MAX_NAME, inDBClientes);
                        Clientes[i].Nome[strcspn(Clientes[i].Nome, "\r\n")] = 0;
                        fscanf(inDBClientes, "%d\n", &Clientes[i].Ano);
                        fscanf(inDBClientes, "%f\n", &Clientes[i].Valor);
                    } else {
                        copia(Clientes,Dummy,MAX_CLIENTES);
                        MAX_CLIENTES = MAX_CLIENTES + 10;
                        realocar_clientes(Clientes, MAX_CLIENTES);
                        copia(Dummy,Clientes,MAX_CLIENTES-10);
                        realocar_clientes(Dummy, MAX_CLIENTES);
                        fgets(Clientes[i].Nome, MAX_NAME, inDBClientes);
                        Clientes[i].Nome[strcspn(Clientes[i].Nome, "\r\n")] = 0;
                        fscanf(inDBClientes, "%d\n", &Clientes[i].Ano);
                        fscanf(inDBClientes, "%f\n", &Clientes[i].Valor);                        
                    }
                }
                fclose(inDBClientes);
            }
            // Leitura Clientes Cadastrados
            break;
            case 1:
            // Salvando novo database de clientes
            printf("Digite o nome do arquivo de database de clientes a ser salvo: ");
            fgets(dbclientes, MAX_FILENAME, stdin);
            dbclientes[strcspn(dbclientes, "\r\n")] = 0;
            if (!(inDBClientes = fopen(dbclientes,"w"))) {
                printf("Nome de arquivo inválido.\n");
            } else {
                printf("Salvando arquivo %s\n", dbclientes);
                nalocs = 0;
                for (i = 0; i < MAX_CLIENTES; i++) {
                    if (strlen(Clientes[i].Nome) != 0) {
                        nalocs = nalocs + 1;
                    }
                }
                fprintf(inDBClientes,"%-d\n",nalocs);
                for (i = 0; i < MAX_CLIENTES; i++) {
                    if (strlen(Clientes[i].Nome) != 0){
                        fprintf(inDBClientes, "%-s\n",Clientes[i].Nome);
                        fprintf(inDBClientes, "%-d\n",Clientes[i].Ano);
                        fprintf(inDBClientes, "%-.2f\n",Clientes[i].Valor);
                    }
                }
                fclose(inDBClientes);
            }
            // Salvando novo database de clientes            
            break;            
            case 2:
            voltar = 0;

            while (voltar == 0){

                printf("Escolha uma das opções:\n");
                printf("(0) Inserir novo cliente.\n");
                printf("(1) Remover dados de clientes.\n");
                printf("(2) Editar gastos.\n");
                printf("(3) Zerar gastos para o próximo mês.\n");
                printf("(4) Voltar.\n");

                scanf("%d", &opcao2);       
                getchar();

                switch(opcao2) 
                {
                    case (0): //Insere Clientes

                    slot = -1;
                    j = 0;

                    while (j < MAX_CLIENTES){
                        if (strlen(Clientes[j].Nome) == 0 && slot < 0){
                            slot = j;
                        }
                        j++;    
                    }                    
                    if (slot < 0) { // não achou slot
                        slot = MAX_CLIENTES;
                        for (i = 0; i < MAX_CLIENTES; i++)
                        {
                            printf("slot: %d Nome: %s\n", slot, Clientes[i].Nome);
                        }
                        copia(Clientes,Dummy,MAX_CLIENTES);                        
                        MAX_CLIENTES = MAX_CLIENTES + 10;
                        realocar_clientes(Clientes, MAX_CLIENTES);
                        copia(Dummy, Clientes, MAX_CLIENTES-10);
                        realocar_clientes(Dummy, MAX_CLIENTES);
                        for (i = 0; i < MAX_CLIENTES; i++)
                        {
                            printf("slot: %d Nome: %s\n", slot, Clientes[i].Nome);
                        } 
                    }    
                    
                    printf("Digite o nome do cliente:\n");
                    fgets(Clientes[slot].Nome, MAX_NAME, stdin);
                    Clientes[slot].Nome[strcspn(Clientes[slot].Nome, "\r\n")] = 0;
                    printf("Digite o ano de nascimento do cliente:\n");
                    scanf("%d", &Clientes[slot].Ano);
                    getchar();
                    printf("Digite o valos dos gastos:\n");
                    scanf("%f", &Clientes[slot].Valor);
                    getchar();                    

                    break;

                    //
                    case (1): //Remove Cliente

                    printf("Selecione um cliente para remover.\n");
                    printf("Digite o código ID do cliente e aperte Enter.\n");
                    printf("ID  NOME                          ANO DE NASCIMENTO\n");
                    for (j = 0; j < MAX_CLIENTES; j++) {
                        if (strlen(Clientes[j].Nome) != 0) {
                            printf("%-3d %-30s %-4d\n", j, Clientes[j].Nome, Clientes[j].Ano);
                        }  
                    }
                    scanf("%d", &opcao3);
                    getchar();

                    if (opcao3 <= MAX_CLIENTES) {
                        for (j = opcao3; j < MAX_CLIENTES-1; j++) {
                            strcpy(Clientes[j].Nome,Clientes[j+1].Nome);
                            Clientes[j].Ano = Clientes[j+1].Ano;
                            Clientes[j].Valor = Clientes[j+1].Valor;
                        }
                        strcpy(Clientes[MAX_CLIENTES-1].Nome,"");
                    } else {
                        printf("Opção inválida.\n");
                    }

                    break;
                    
                    //
                    case (2): //Atualiza valores gastos

                    printf("Selecione um cliente para editar gastos.\n");
                    printf("Digite o código ID do cliente e aperte Enter.\n");
                    printf("ID   NOME                           VALOR\n");
                    for (j = 0; j < MAX_CLIENTES; j++) {
                        if (strlen(Clientes[j].Nome) != 0) {
                            printf("%-4d %-30s %-.2f\n", j, Clientes[j].Nome, Clientes[j].Valor);
                        }  
                    }
                    scanf("%d", &opcao3);
                    getchar();
                    if (opcao3 < MAX_CLIENTES) {
                        printf("\nValor atual: %s\n Cliente: %f\n",Clientes[opcao3].Nome, Clientes[opcao3].Valor);
                        printf("1: Somar 2: Subtrair 3: Editar\n");
                        scanf("%d", &opcao4);
                        getchar();
                        switch (opcao4) {
                            case 1:
                            printf("Digite valor a somar.\n");
                            scanf("%f", &Valor);
                            getchar();
                            Clientes[opcao3].Valor = Clientes[opcao3].Valor + Valor;

                            break;

                            case 2:
                            printf("Digite valor a subtrair.\n");
                            scanf("%f", &Valor);
                            getchar();
                            Clientes[opcao3].Valor = Clientes[opcao3].Valor - Valor;

                            break;

                            case 3:
                            printf("Digite novo valor.\n");
                            scanf("%f", &Valor);
                            getchar();
                            Clientes[opcao3].Valor = Valor;

                            break;

                            default:
                            printf("Opção inválida.\n");
                            break;

                        }

                    } else {
                        printf("Opção inválida.\n");
                    }
                    break;
                    
                    //
                    case 3: // Zera
                    for (i = 0; i < MAX_CLIENTES; i++){
                        Clientes[i].Valor = 0;
                        printf("Valores de gastos zerados.\n");
                    }
                    break;                    

                    //
                    case (4):
                    voltar = 1; 
                    break;
                }
            }
            break;  
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 3:
            voltar = 0;

            while (voltar == 0)
            {
            printf("Opções de visualização.\n");
            printf("0) Lista todos os dados:\n");
            printf("1) Lista o valor de compras de um cliente:\n");
            printf("2) Lista melhor comprador.\n");
            printf("3) Voltar\n");
            scanf("%d",&opcao2);
            getchar();
            
            switch (opcao2) {
                case 0:
                printf("NOME                           ANO   VALOR\n");
                for (j = 0; j < MAX_CLIENTES; j++) {
                    if (strlen(Clientes[j].Nome) != 0) {
                        printf("%-30s %-4d %-.2f\n", Clientes[j].Nome, Clientes[j].Ano, Clientes[j].Valor);
                    }  
                }
                break;
                //
                case 1:
                printf("Digite o nome de um cliente para visualizar seus gastos.\n");
                fgets(InputName, MAX_NAME, stdin);
                InputName[strcspn(InputName, "\r\n")] = 0;

                slot = -1;
                for (i = 0; i < MAX_CLIENTES; i++) {
                    if (strlen(Clientes[i].Nome) != 0) {
                        k = 0;
                        for (j = 0; j < strlen(InputName); j++) {
                            if (tolower(InputName[j]) != tolower(Clientes[i].Nome[j])) {
                                k = 1;
                            }
                        }
                        if (k == 0) {
                            slot = i;
                        }
                    }
                }
                if (slot >= 0) {
                    printf("Nome: %s Gastos: %.2f\n", Clientes[slot].Nome, Clientes[slot].Valor);
                } else {
                    printf("Nome de usuário inválido.\n");
                }
                break;
                //
                case 2:
                slot = -1;
                Valor = 0;
                for (i = 0; i < MAX_CLIENTES; i++){
                    if (strlen(Clientes[i].Nome) != 0) {
                        if (Clientes[i].Valor > Valor) {
                            Valor = Clientes[i].Valor;
                            slot = i;
                        }
                    }
                }
                printf("Maior comprador: %s\n", Clientes[slot].Nome);
                printf("Valor: %.2f\n", Clientes[slot].Valor);

                break;

                case 3:
                voltar = 1;
                break;
                }
            }

            break;
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            case 4:


            sair = 1;
            break;
        /*****************************************************************************************/ 
        /*****************************************************************************************/ 
            default:
            printf("Opção inválida.\n");

        }
    }

    return 0;
}

