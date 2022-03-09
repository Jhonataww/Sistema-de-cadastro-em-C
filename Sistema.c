#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>

struct filecadastro                                      //Estrutura de cadastro
{
    char nome[256];
    char matricula[256];
    char email[256];
    char dataad[256];
    char salario[256];
};
struct filecadastro cadastro;                            //variavel global de cadastro


int frontand(void);                                      //protótipos das funções
void bdados(void);
void matricula(void);
void lista(void);
int verifica();
void remover(void);
void alterar(void);
void atualizar(void);
void info(void);


int
main(void)
{
    setlocale(0, "Portuguese" );
    int sair = -1;
    do
    {
        int menu = frontand();

        switch(menu)                                      //segmentação do código para suas respectivas funções
        {
        case 0:                                           //sair

            return 1;
            break;
        case 1:                                           //cadastrar

            matricula();

            int test = verifica();                        //verifica se o usuário já está cadastrado
            if(test !=  5)                                //não permitindo escrever no arquivo
            {
                bdados();
            }
            break;
        case 2:                                           //listar

            lista();
            break;
        case 3:                                           //excluir

            remover();
            atualizar();
            break;
        case 4:                                           //alterar

            alterar();
            break;
        case 5:                                           //informação sobre o projeto

            info();
            break;
        }

        char buffer[5];
        printf("========================================================================\n");   //retorna para o menu ou sai do programa
        printf(" DIGITE [ 0 ] PARA SAIR DO PROGRAMA\n DIGITE [ 1 ] PARA VOLTAR PARA O MENU\n\n");
        printf("  INSERIR: ");
        fgets(buffer, 5, stdin);
        sscanf(buffer, "%i", &sair);

    }
    while( sair != 0 );                                   //verificação de dados



    return 0;
}

int
frontand(void)                                            //função Front-and responsável pela parte visual do menu
{

    int menu = -1;
    char buffer[5];
    do
    {
        system("cls");
        printf("             /#\\   *             *                   **        *       \n");
        printf("    *       /###\\     /\\                  *                           \n");
        printf("           /  ###\\   /##\\  /\\       *                  *          *  \n");
        printf("          /      #\\ /####\\/##\\                                       \n");
        printf("         /  /      /   # /  ##\\            _      /\\                  \n");
        printf("       // //  /\\  /    _/  /  #\\ _        /#\\   _/##\\    /\\        \n");
        printf("      // /   /  \\     /   /    #\\ \\      /###\\ /   ##\\__/ _\\      \n");
        printf("========================================================================\n");
        printf("|\t     SISTEMA DE GERENCIAMENTO DE RECURSOS HUMANOS\t\t|\n");
        printf("========================================================================\n");
        printf("\n Cadastrar\t[1]\n Listar\t\t[2]\n Excluir\t[3]\n Alterar\t[4]\n Informações\t[5]\n Sair\t\t[0]\n\n  INICIAR : ");

        fgets(buffer, 5, stdin);                         //casting
        sscanf(buffer, "%i", &menu);


    }
    while( menu < 0 || menu > 5 );                       //verificação de dados

    return menu;


}

void
bdados(void)                                             //responsável pelo banco de dados / arquivo
{
    FILE *bdados;
    bdados = fopen("bd_cadastrados.txt", "a+");          //pasta raiz do programa

    if(bdados == NULL)
    {
        printf("Erro ao abrir o arquivo! | LOG 1");
    }
    else
    {
        fprintf(bdados,"%s%s%s%s%s-\n", cadastro.matricula, cadastro.nome, cadastro.email, cadastro.dataad, cadastro.salario);

        fclose(bdados);                                  //fecha arquivo
    }

}

void
matricula(void)                                          //Função responsável pelo cadastro na struct
{
    int resp;
    do
    {
        system("cls");
        printf("=================================||||||=================================\n");
        printf("\t\t\t\tCADASTRO\t\t\t");
        printf("\n========================================================================\n\n");

        printf(" Digite a Matrícula: ");                 // imput dos dados para variavel da estrutura
        fgets(cadastro.matricula, 255, stdin);

        char c [5] = "\n";
        resp = strcmp( c, cadastro.matricula);
        printf("\n");

    }
    while( resp == 0 );                                  //condição da matricula não ser nula

    printf(" Digite o Nome:  ");
    fgets(cadastro.nome, 255, stdin);
    printf("\n");

    printf(" Digite o Email: ");
    fgets(cadastro.email, 255, stdin);
    printf("\n");

    printf(" Digite o Salário: ");
    fgets(cadastro.salario, 255, stdin);
    printf("\n");

    printf(" Digite a Data de Admissão [d/m/a]: ");
    fgets(cadastro.dataad, 255, stdin);
    printf("\n");

    printf("========================================================================\n");
    printf("                    CADASTRO REALIZADO COM SUCESSO!                     \n");
    printf("========================================================================\n");




}

void
lista(void)                                              //Função responsável por listar os dados
{
    system("cls");
    FILE *lista;

    lista = fopen("bd_cadastrados.txt", "a+");
    if(lista == NULL)
    {
        printf("Erro ao abrir o arquivo! | LOG 2");
    }
    else
    {
        printf("=================================||||||=================================\n");
        printf("A LISTA SEGUE A ORDEM DE CADASTRO\n");
        printf("========================================================================\n");
        printf("\t| Matricula\t|\n\t| Nome\t\t|\n\t| Email\t\t|\n\t| Data Admissão\t|\n\t| Salário\t|\n");
        printf("========================================================================\n");

        char c;

        int temp = 0;
        do                                                 //lista caractere por caractere do arquivo
        {
            c = fgetc(lista);
            if(c != EOF)
            {
                printf("%c", c);
                temp = temp + 1;
                if(c == '-')
                {
                    printf("-----------------------------------------------------------------------");
                }
            }

        }
        while(c != EOF);

        if(temp == 0)
        {
            printf("=================================||||||=================================\n\n");
            printf("Nenhuma matrícula encontrada!");

        }


    }
    printf("\n\n");
}

int
verifica()                                                  //Função responsável por verificar se dados já foram cadastrados
{
    FILE *veri;

    char c[255];
    veri = fopen("bd_cadastrados.txt", "a+");

    if(veri == NULL)
    {
        printf("Erro ao abrir o arquivo! | LOG 3");
    }
    else
    {
        while(fgets( c,  sizeof(cadastro.matricula),  veri)   !=    NULL)
        {
            int resp = strcmp( c, cadastro.matricula);      //compara as matrículas no banco de dados
            if( resp == 0)
            {
                system("cls");
                printf("=================================||||||=================================\n");
                printf("\t\t\tUSUÁRIO JÁ CADASTRADO\n");
                printf("\t\t _.........._\n");
                printf("\t\t| |        | |\n");
                printf("\t\t| |        | |\tO usuário já possui cadastro no sistema\n");
                printf("\t\t| |        | |\tCaso não lembre da matricula\n");
                printf("\t\t| |________| |\trealizar a listagem no menu!\n");
                printf("\t\t|   ______   |\n");
                printf("\t\t|  |    | |  |\n");
                printf("\t\t|__|____|_|__|\n\n");


                return 5;
            }
        }

    }
    fclose(veri);
}

void
remover(void)                                               //função responsável por remover dados
{

    int resp;
    do
    {
        system("cls");
        printf("\n========================================================================\n\n");
        printf("DESEJA VISUALIZAR AS MATRÍCULAS CADASTADAS? \n\n\n\nSIM[1] NÃO[0] \n\n");
        printf("\n========================================================================\n\n");
        printf(" INSERIR : ");

        char buffer[5];
        int sn;
        fgets(buffer, 4, stdin);
        sscanf(buffer, "%i", &sn);

        if(sn == 1)
        {
            lista();
        }
        else
        {
            system("cls");
        }

        printf("=================================||||||=================================\n");
        printf("\t\tDIGITE A MATRICULA QUE DESEJA EXCLUIR\n");
        printf("========================================================================\n");
        printf(" INSERIR : ");

        fgets(cadastro.matricula, 255, stdin);

        char c [5] = "\n" ;
        resp = strcmp( c, cadastro.matricula);



    }
    while( resp == 0 );                                     //condição que verifica o \n do imput

    FILE *remover, *remover2;

    char c[256];
    int i = 0;
    int j = 1;
    int k = 0;

    remover = fopen("bd_cadastrados.txt", "r+");
    remover2 = fopen("temp.txt", "w");                              //Ultilizando um arquivo temporário para armazenar a alteração

    if(remover == NULL && remover2 == NULL)
    {
        printf("Erro ao abrir o arquivo! | LOG 4");
    }
    else
    {
        while(fgets( c,  255,  remover)   !=    NULL)
        {
            if(j != 0)                                              //verifica que não fará outra alteração no cadastro
            {
                int resp = strcmp( c, cadastro.matricula);
                if( resp == 0)
                {
                    i = 6;                                          //caso encontre a matricula irá pular as linhas
                    j = 0;                                          //Ao entrar na condição não irá se repetir
                    k = 1;                                          //informa que matricula não existe

                }
            }

            if(i <= 0)                                              //condição de escrita
            {
                fprintf(remover2,"%s", c);
            }

            i = i - 1;                                              //atualização da condição

        }
    }

    fclose(remover);
    fclose(remover2);

    printf("=================================||||||=================================\n\n");
    printf("\t\t\t ______\n");
    printf("\t\t\t| |__| |\n");
    printf("\t\t\t|  ()  | REMOVENDO... \n");
    printf("\t\t\t|______|\n\n");
    printf("\t\t\tCADASTRO REMOVIDO\t\t\t\n\n\n");

    if( k == 0 )                                                    //condição de existencia
    {
        system("cls");
        printf("=================================||||||=================================\n\n");
        printf("\t\t ______\n");
        printf("\t\t| |__| |\tNenhuma matrícula encontrada\n");
        printf("\t\t|  ()  |\tverificar a listagem no menu!\n");
        printf("\t\t|______|\n\n");
    }
}

void
alterar(void)                                                       //função responsável por alterar dados já cadastrados
{
    int resp;
    do                                                              //pré-lista e condição de verificação de cadastro
    {
        system("cls");
        printf("\n========================================================================\n\n");
        printf("DESEJA VISUALIZAR AS MATRÍCULAS CADASTADAS? \n\n\n\nSIM[1] NÃO[0] \n\n");
        printf("\n========================================================================\n\n");
        printf(" INSERIR : ");

        char buffer[5];
        int sn;
        fgets(buffer, 4, stdin);
        sscanf(buffer, "%i", &sn);

        if(sn == 1)
        {
            lista();                                                //uso da função lista
        }
        else
        {
            system("cls");
        }

        printf("=================================||||||=================================\n");
        printf("\t\tDIGITE A MATRICULA QUE DESEJA ALTERAR\n");
        printf("========================================================================\n\n");
        printf(" INSERIR : ");

        fgets(cadastro.matricula, 255, stdin);
        char c [5] = "\n" ;
        resp = strcmp( c, cadastro.matricula);

        printf("\n========================================================================\n\n");

    }
    while( resp == 0 );                                             //condição de imput

    FILE *alterar, *alterar2;

    char c[256];
    int i = 0;
    int j = 1;
    int k = 0;

    alterar = fopen("bd_cadastrados.txt", "r+");                    //sobre escrita no mesmo arquivo
    alterar2 = fopen("bd_cadastrados.txt", "r+");

    if(alterar == NULL && alterar2 == NULL)
    {
        printf("Erro ao abrir o arquivo! | LOG 4");
    }
    else
    {
        while(fgets( c,  255,  alterar)   !=    NULL)
        {
            if(j != 0)                                              //verifica que não fará outra alteração no cadastro
            {
                int resp = strcmp( c, cadastro.matricula);
                if( resp == 0)
                {

                    printf(" Novo Nome:  ");
                    fgets(cadastro.nome, 255, stdin);
                    printf("\n");

                    printf(" Novo Email: ");
                    fgets(cadastro.email, 255, stdin);
                    printf("\n");

                    printf(" Novo Salário: ");
                    fgets(cadastro.salario, 255, stdin);
                    printf("\n");

                    printf(" Nova Data de Admissão [d/m/a]: ");
                    fgets(cadastro.dataad, 255, stdin);
                    printf("\n");

                    char c[5] = "\n";
                    int temp[4];                                    //condição que n permite \n nos dados
                    temp[0] = strcmp( c, cadastro.nome);
                    temp[1] = strcmp( c, cadastro.email);
                    temp[2] = strcmp( c, cadastro.salario);
                    temp[3] = strcmp( c, cadastro.dataad);

                    if(temp[0] == 0 || temp[1] == 0 || temp[2] == 0 || temp[3] == 0 )
                    {
                        printf("\n========================================================================\n");
                        printf("             DADOS EM BRANCO - ERRO NA ALTERAÇÃO DO CADASTRO                ");
                        printf("\n========================================================================\n");

                        k = 1;
                        j = 0;
                    }
                    else
                    {
                        fprintf(alterar2,"%s%s%s%s%s-\n", cadastro.matricula, cadastro.nome, cadastro.email, cadastro.dataad, cadastro.salario);
                        printf("\n========================================================================\n\n");
                        printf("                MATRICULA FEITA COM SUCESSO!                               \n\n");

                        i = 6;                                      //mesma forma de verificação, pulando as linhas que desejamos alterar.
                        j = 0;                                      //não permite que altere mais de uma vez
                        k = 1;                                      //atualização da variavel, matricula não encontrada
                    }
                }
            }

            if(i <= 0)                                              //condição de escrita    - re-escrever o arquivo
            {
                fprintf(alterar2,"%s", c);
            }

            i = i - 1;

        }

    }

    fclose(alterar);
    fclose(alterar2);

    if( k == 0 )                                                    //verificação de existencia
    {
        system("cls");
        printf("=================================||||||=================================\n\n");
        printf("\t\t ______\n");
        printf("\t\t| |__| |\tNenhuma matrícula encontrada\n");
        printf("\t\t|  ()  |\tverificar a listagem no menu!\n");
        printf("\t\t|______|\n\n");
    }


}

void
atualizar(void)                                                     //função responsável por atualizar o bd - usado conjunto da função excluir
{
    char d[256];                                                    //passa os dados de temp para o banco de dados original
    FILE *atualizar, *temp;

    atualizar = fopen("bd_cadastrados.txt", "w");
    temp = fopen("temp.txt", "r");

    while(fgets( d,  255, temp  )   !=    NULL)
    {
        fprintf(atualizar, "%s", d);
    }

    fclose(atualizar);
    fclose(temp);

    remove("temp");
}

void
info(void)                                                          //informações sobre alunos e o programa
{
    system("cls");
    printf("=================================||||||=================================\n");
    printf("|=======================================================================|\n");
    printf("|                                                                       |\n");
    printf("|                                                                       |\n");
    printf("|     Descrição:   Implementação do sistema de cadastro	                |\n");
    printf("|     Sistema:     Desenvolvido para Windows                            |\n");
    printf("|     Versão:      1.4                                                  |\n");
    printf("|     Criado:      26/1/2022                                            |\n");
    printf("|     Compilador:  gcc - codeblocks IDE                                 |\n");
    printf("|                                                                       |\n");
    printf("|                                                                       |\n");
    printf("|     Dev:         Jhonataww										    |\n");
    printf("|                                                                       |\n");
    printf("|                                                                       |\n");
    printf("|=======================================================================|\n");

}
