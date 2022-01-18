/**
 * @autores:
 * Nome:                    Número de Aluno:
 * Nome:                    Número de Aluno:
 * Nome:                    Número de Aluno:
 **/

#include <stdio.h>
#include <stdlib.h>

#define B 6
#define N 8
#define M 8

/**Representa uma coordenada*/
typedef struct
{
    int x;
    int y;
} Position;

/**Associa cada coordenada do barco com um estado**/
typedef struct
{
    int afloat;   // 0 indica que está afundada, 1 indica que não
    Position pos; // Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
    int afloat;          // Posições que ainda não foram afundadas
    int tSize;           // Tamanho do tipo do barco
    StateCoord coord[5]; // O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
    char type;           // Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
    int numBoatsAfloat; // Número de barcos não afundados
    int numBoats;       // Número de barcos que foram colocados
    Boat boats[B];      // Array de barcos. Cada barco é do tipo Boat.
    char board[N][M];   // Array que contém a informação de cada posição do tabuleiro
} Board;

/**
 * NOTA IMPORTANTE:
 * Não pode alterar nenhuma das assinaturas das funções abaixo.
 * Este ficheiro tem de ser considerado em conjunção com o enunciado do TP2.
 **/

/**
 * Function: init_board
 *
 * Inicializa um Board.
 *
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * b: apontador para o Board que vai ser inicializado
 *
 **/
void init_board(int n, int m, Board *b)
{
    b->numBoatsAfloat = 0;
    b->numBoats = 0;

    // Inicializa o array board
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            b->board[i][j] = ' ';
        }
    }
}

/**
 * Function: print_board
 *
 * Mostra no ecrã o estado atual do tabuleiro.
 * Se a flag é 0 (zero) não mostra os barcos, se for 1, mostra.
 * Quando a flag é 1, para indicar a posição de cada barco, é colocada em todas
 * as posições do barco a letra que representa o seu tipo.
 *
 * n: número de linhas do tabuleiro
 * m: número de colunas do tabuleiro
 * board: estado do tabuleiro
 * flag: indicador do modo de visualização do tabuleiro -- se for 0 (zero) não
 *       mostra os barcos; se for diferente de 0 (zero) mostra.
 */

void print_board(int n, int m, char board[n][m], int flag)
{
    printf("+");
    for (int j = 0; j < n; j++)
    {
        printf("---+");
    }
    printf("\n");

    for (int i = 0; i < m; i++)
    {
        printf("|");
        if (flag) // Mostra tudo
        {
            for (int j = 0; j < n; j++)
            {
                printf(" %c |", board[i][j]);
            }
            printf("\n");
        }
        else // Esconde os barcos
        {
            // Implementar
            for (int j = 0; j < n; j++)
            {
                printf(" ");
            }
            printf("\n");
        }

        printf("+");
        for (int j = 0; j < n; j++)
        {
            printf("---+");
        }
        printf("\n");
    }
}

/**
 * Function: typeToSize
 *
 * Dado o tipo do barco devolve o seu tamanho.
 *
 * type: tipo do barco ('P', 'N', 'C', ou 'S')
 *
 * return
 *  -1 se o tipo de barco for inválido
 *  caso contrário, devolve o tamanho do barco
 **/
int typeToSize(char type)
{
    switch (type)
    {
    case 'P':
        /*P - Porta Avioes;
    O Porta aviões ocupa 5 espaços do tabuleiro:*/
        return 5;

    case 'N':
        /*N - Navio Tanque;
    O Navio Tanque ocupa 4 espaços do tabuleiro:*/
        return 4;

    case 'C':
        /*C - Contrapedeiro;
    O Contrapedeiro ocupa 3 espaços do tabuleiro:*/
        return 3;

    case 'S':
        /*S - Submarino;
    O Submarino ocupa 2 espaços do tabuleiro:*/
        return 2;

    default:
        // Tipo de Barco inválido:
        return -1;
    }
}

/**
 * Function: init_boat
 *
 * Dado um apontador para um barco, o tipo, a posição inicial e a direcção,
 * inicializa o barco com todas as sua posições, tamanho e tipo.
 * Por exemplo, se o tipo do barco é 'C' (contratorpedeiro),
 * a posição inicial (1,1), e a direcção 'H', então o barco fica inicializado
 * com os seguintes valores
 *
 * afloat = 3;
 * tSize = 3;
 * coord = [(1,(1,1)),(1,(1,2)),(1,(1,3))]; Onde (s,(x,y)) representa um elemento do tipo StateCoord
 * type = 'C';
 *
 * b: barco que vai ser inicializado
 * type: tipo do barco
 * xy: posição inicial do barco
 * dir: direcção do barco
 *
 **/

void init_boat(Boat *b, char type, Position xy, char dir)
{
    int size = typeToSize(type);
    printf("---------->   %d", size);
    if (dir == 'H')
    {
        for (int i = 0; i < size; i++)
        {
            Position pos = {xy.x, xy.y + i};
            // printf("x--> %d", xy.x);
            // printf("y--> %d", xy.y+i);
            b->coord[i].afloat = 1;
            b->coord[i].pos = pos;
        }
    }
    else if (dir == 'V')
    {
        for (int i = 0; i < size; i++)
        {
            Position pos = {xy.x + i, xy.y};
            // printf("x--> %d", xy.x + i);
            // printf("y--> %d", xy.y);
            b->coord[i].afloat = 1;
            b->coord[i].pos = pos;
        }
    }
    // Depositar os valores dados pelo utilizador nas respetivas structs
    b->tSize = size;
    b->type = type;
}

/**
 * Function: check_free
 *
 * Verifica se estão livres todas as posições que serão ocupadas por um
 * barco no tabuleiro.
 *
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * boat: barco a colocar no tabuleiro
 * board: estado atual do tabuleiro
 *
 * returns:
 *  1 se todas as posições estão livres
 *  0 caso contrário
 *
 **/

int check_free(int n, int m, Boat *boat, char board[n][m])
{
    // Implementar
    // retirar as corenadas do boat
    int res = -1;

    int boatSize = typeToSize(boat->type);
    for (int i = 0; i < boatSize; i++)
    {
        printf("boatSize %d", boatSize);
        int x = boat->coord[i].pos.x;
        printf("posicao do barco x--> %d", x);

        int y = boat->coord[i].pos.y;

        printf("posicao do barco y--> %d", y);

        // verificar se tem outro barco designado no mesmo local
        if (board[x][y] != ' ')
        {
            // printf("\n x --> %d \n y--> %d", x, y);
            // printf("wrong");
            res = 0;
        }
    }
    return res;
}

/*
 * Function: place_boat
 *
 * Cria e coloca, se tal for possível, um barco no tabuleiro.
 *
 * x1: coordenada x inicial do barco
 * y1: coordenada y inicial do barco
 * dir: dirrecção do barco ('H' ou 'V')
 * type: o tipo de barco
 * board: estado atual do tabuleiro
 *
 * returns:
 * 0 se o barco for colocado com sucesso.
 * -1 se alguma das posições já está ocupada.
 * -2 se as coordenadas forem inválidas.
 * -3 se a direcção for inválida.
 * -4 se o tipo de barco for inválido.
 **/
int place_boat(int x1, int y1, int dir, char type, Board *board)
{
    int nBoats = board->numBoats;
    Boat b;
    Position p = {x1, y1};
    // char board[N][M] = board->board;

    // verifica se a direcao esta correta
    if (dir != 'H' || dir != 'V')
    {
        return -3;
    }
    // verifica se as cordenadas estao correctas
    if (!(x1 >= 0 || y1 >= 0 || x1 <= N || y1 <= M))
    {
        return -2;
    }
    // verifica se o tipo de barco esta correcto
    if (typeToSize(type) == -1)
    {
        return -4;
    }
    init_boat(&b, type, p, dir);

    // verifica se a posicao ja esta ocupada
    if (check_free(N, M, &b, board->board) == 0)
    {
        return -1;
    }

    board->boats[nBoats] = b;
    board->numBoats++; // testar se isto funciona
    return 0;
}

/**
 * Function: check_sink
 *
 * Verifica se ao atacar a posição (x,y) algum barco é afundado.
 *
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 *
 * returns:
 *   'F' se não for afundado nenhum barco. acerto em um barco mas nao afunda.
 *   Se afundar um barco devolve a letra que representa o seu tipo: 'P', 'N', 'C' ou 'S'
 *   'I' se a coordenada for inválida.
 *
 **/
char check_sink(int x, int y, Board *board)
{
    // verifica se a cordenada e valida
    if (!(x >= 0 && y >= 0 && x < N && y < M))
    {
        return 'I';
    }
    for (int i = 0; i < B; i++)
    {
        // add o barco[i].
        for (int j = 0; j < board->boats[i].tSize; j++)
        {

            int xb = board->boats[i].coord[j].pos.x;
            int yb = board->boats[i].coord[j].pos.y;

            if (xb == x && yb == y)
            {
                // hit
                //
                if (board->boats[i].afloat > 1)
                {
                    board->boats[i].coord[j].afloat = 0;

                    return 'F';
                }
                else if (board->boats[i].afloat == 1)
                {
                    board->numBoatsAfloat--;
                    board->boats[i].afloat = 0;
                    board->boats[i].coord[j].afloat = 0;
                    return board->boats[i].type;
                }
            }
        }
    }
    return ' ';
}

/**
 * Function: target
 *
 * Ataca a coordenada (x,y) no tabuleiro.
 * Se a coordenada (x,y) é parte de um barco, então coloca um '*' nessa
 * posição '*'; caso contrário coloca a letra 'F' nessa posição; caso afunde
 * um barco coloca em todas as posições desse barco a letra 'A'.
 *
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 *
 * returns:
 *   0 se a posicao já foi atacada anteriormente
 *   1 se acerta numa coordenada de um barco mas sem o afundar
 *   -1 se nao tiver sucesso
 *   -2 se a coordenada for inválida.
 *   caso afunde um barco, devolve o número correspondente ao tamanho do barco
 *   que afundou (valor de 2 a 5)
 *
 **/
int target(int x, int y, Board *board)
{

    if (board->board[x][y] != ' ')
    {
        // cordenada ja atacada antes
        return 0;
    }

    if (!(x >= 0 && x <= N && y >= 0 && y <= M))
    {
        return -2; // Introduzidas coordenadas inválidas
    }

    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < board->boats[i].tSize; j++)
        {

            int x_status = board->boats[i].coord[j].pos.x;
            int y_status = board->boats[i].coord[j].pos.y;

            if (x_status == x && y_status == y)
            {

                char checkSink = check_sink(x, y, board);
                switch (checkSink)
                {
                case 'I':
                    return -2;
                    // cordenadas esta invalida

                    break;
                case 'F':
                    // put * on the board[][]
                    board->board[x][y] = '*';
                    return 1;
                default:
                    // hit e afundo o barco
                    // alterar todas as letras no board[][] do barco para type
                    // int size =board->boats[i].tSize;
                    for (int z = 0; z < (board->boats[i].tSize); z++)
                    {
                        int x = board->boats[i].coord[z].pos.x;
                        int y = board->boats[i].coord[z].pos.y;

                        board->board[x][y] = board->boats[i].type;
                    }

                    return typeToSize(checkSink);
                }
            }
        }
    }

    board->board[x][y] = 'F';
    return -1;
}

typedef struct
{
    char namePlayer1[40];
    char namePlayer2[40];
    int pointsPlayer1;
    int pointsPlayer2;
} Players;

enum boatsNames
{
    PORTA_AVIOES = 'P',
    NAVIO_TANQUE = 'N',
    CONTRAPEDEIRO = 'C',
    SUBMARINO = 'S'
};

int main(void)
{
    /*
        Board brd;
        init_board(N, M, &brd);
        print_board(N, M, brd.board, 1);

        Boat b;

        Position p = {3, 3};
        brd.board[3][3] = 'N';
        init_boat(&b, 'C', p, 'H');
        check_free(N, M, &b, brd.board);
    */
    /**Exemplo de uso da print_board e da place_boat**/
    /**Precisa de as implementar primeiro**/
    // print_board(N, M, brd.board, 0);
    // place_boat(1,3, 'H', 'P', &brd);

    Board brd;
    init_board(N, M, &brd);
    print_board(N, M, brd.board, 1);

    Players players;
    // names
    printf("Introduza nomes player 1\n");
    scanf("%s", players.namePlayer1);

    printf("Introduza nomes player 2\n");
    scanf("%s", players.namePlayer2);

    players.pointsPlayer1 = 0;
    players.pointsPlayer2 = 0;
    printf("%s", players.namePlayer1);

    int flagEnd = 1;
    int flagFun = 1;
    int xCord = -1;
    int yCord = -1;
    char direction;
    // char typeOfBoat;

    while (flagEnd)
    {

        // start game
        printf("player place boat\n");

        print_board(N, M, brd.board, 1);

        // cordenada x
        while (flagFun)
        {
            printf("Coloque a coordenada do barco para x?\n");
            int test = scanf("%d", &xCord);

            if (test != 1)
            {
                printf("coloque apenas um valor entre 0 e %d\n", N);
                continue;
            }
            if (xCord >= 0 && xCord <= N)
            {
                break;
            }
            else
            {
                printf("A cordenada introduzida nao esta correta\n");
                continue;
            }
        }

        // cordenada y
        while (flagFun)
        {
            printf("Coloque a coordenada do barco para y?\n");
            int test = scanf("%d", &yCord);

            if (test != 1)
            {
                printf("coloque apenas um valor entre 0 e %d\n", N);
                continue;
            }
            if (yCord >= 0 && yCord <= N)
            {
                break;
            }
            else
            {
                printf("A cordenada introduzida nao esta correta\n");
                continue;
            }
        }
        // direction
        while (flagFun)
        {
            printf("Coloque a direcao do barco H para Horizontal e V para Vertical?\n");
            int test = scanf("%c", &direction);

            if (test != 1)
            {
                printf("o valor colocado nao esta correcto\n");
                continue;
            }
            if (direction == 'H' || direction == 'V')
            {
                break;
            }
            else
            {
                printf("A cordenada introduzida nao esta correta\n");
                continue;
            }
        }

        // tipo de barco
        // verificar se o local esta vazio if(board[x][y] != ' '){

        // fazer a verificacao se cabe dentro da board

        // printf("Coloque a letra do barco que pretende introduzir?\n");
        // printf("P --> Porta Avioes\nN --> Navio tanque\nC --> Contrapedeiro\n S --> Sumarino\n");

        for (int i = PORTA_AVIOES; i <= SUBMARINO; i++)
        {

            printf("%c\n", i);
        }

        // init_boat(&b, 'C', p, 'H');
    }
    return 0;
}
