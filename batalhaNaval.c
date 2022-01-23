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

#define PORTA_AVIOES 0
#define NAVIO_TANQUE 0
#define CONTRAPEDEIRO 0
#define SUBMARINO 1
#define HITSPERPLAYER 5

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

void print_board(int n, int m, char board[N][M], int flag)
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
                if (board[i][j] == 'P' || board[i][j] == 'N' || board[i][j] == 'C' || board[i][j] == 'S' )
                {
                    printf("   |");
                }
                else
                {
                    printf(" %c |", board[i][j]);
                }
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
    b->afloat = size;
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

int check_free(int n, int m, Boat *boat, char board[N][M])
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
     if(dir != 'H' && dir != 'V')
    {
        printf("direction_____%c______\n", dir);
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

//colocar na board
    for (int i = 0; i < b.tSize; i++)
    {
        int x = b.coord[i].pos.x;
        int y = b.coord[i].pos.y;

        board->board[x][y] = type;
    }
    printf("--------------------------");
    print_board(N, M, board->board, 1);
    printf("--------------------------");
    board->boats[nBoats] = b;
    board->numBoats++;
    board->numBoatsAfloat++;
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
        for (int j = 0; j < board->boats[i].tSize; j++)
        {

            int xb = board->boats[i].coord[j].pos.x;
            int yb = board->boats[i].coord[j].pos.y;

            if (xb == x && yb == y)
            {
                // hit
                //
                printf("-_-___---_---_-_-_acertou ver se  afunda ou nao\n");
                printf("boat -afoat %d\n", board->boats[i].afloat);
                printf("boat -tSize %d\n", board->boats[i].tSize);
                printf("boat -type %c\n", board->boats[i].type);
                if (board->boats[i].afloat > 1)
                {
                    printf("-_-_---_---_-_-acertou mas nao afundou boat afund -_-_-_-_-_  %d \n", board->boats[i].afloat);
                    board->boats[i].coord[j].afloat = 0;
                    board->boats[i].afloat--;
                    printf("-_-_---_---_-_-acertou mas nao afundou boat afund -_-_-_-_-_  %d \n", board->boats[i].afloat);
                    return 'F';
                }
                else if (board->boats[i].afloat == 1)
                {
                    printf("-_-___---_---_-_-_acetou e afundou\n");
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

    if (!(x >= 0 && x <= N && y >= 0 && y <= M))
    {
        return -2; // Introduzidas coordenadas inválidas
    }

    if (board->board[x][y] == '*' || board->board[x][y] == 'F' || board->board[x][y] == 'A')
    {
        // cordenada ja atacada antes
        return 0;
    }
    else if (board->board[x][y] == ' ')
    {

        board->board[x][y] = 'F';
        return -1;
    }
    else
    {
        char check = check_sink(x, y, board);

        switch (check)
        {
        case 'I':
            //cordenadas invalidas
            return -2;
            break;
        case 'F':
            board->board[x][y] = '*';

            return 1;
            break;

        case 'P':
        case 'N':
        case 'C':
        case 'S':

            printf("you sink it all");
            for (int i = 0; i < B; i++)
            {
                for (int j = 0; j < board->boats[i].tSize; j++)
                {
                    int x_status = board->boats[i].coord[j].pos.x;
                    int y_status = board->boats[i].coord[j].pos.y;

                    if (x_status == x && y_status == y)
                    {
                        for (int z = 0; z < board->boats[i].tSize; z++)
                        {
                            int x = board->boats[i].coord[z].pos.x;
                            int y = board->boats[i].coord[z].pos.y;

                            board->board[x][y] = 'A';
                        }
                        return typeToSize(check);
                    }
                }
                break;
            }
        }
    }
    return -10;
}

int placexCord(){
    int xCord = 0;
    int flagFun = 1;
    while (flagFun)
    {
        printf("Coloque a coordenada do x?\n");
        int test = scanf("%d", &xCord);
        getchar();

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
    return xCord;
}

int palceyCord(){
    int yCord = 0;
    int flagFun = 1;
    while (flagFun)
    {
        printf("Coloque a coordenada do y?\n");
        int test = scanf("%d", &yCord);
        getchar();
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
    return yCord;
}

char placeDirection(){
    char direction;
    int flagFun = 1;
    while (flagFun)
    {
        printf("Coloque a direcao do barco H para Horizontal e V para Vertical?\n");
        int test = scanf("%c", &direction);

        if (test != 1)
        {
            printf("o valor colocado nao esta correcto\n");
            continue;
        }
        if (direction != 'H' && direction != 'V')
        {

            continue;
        }
        else
        {
            printf("A direcçao introduzida nao esta correta\n");
            break;
        }
    }
    return direction;
}

typedef struct
{
    char namePlayer1[40];
    char namePlayer2[40];
    int pointsPlayer1;
    int pointsPlayer2;
} Players;





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
int counterShots = 0;

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
int flagTarget = 1;
int xCord = -1;
int yCord = -1;
char direction;
char typeOfBoat;
int playCount = 0;

int *boatNow;
int *playerNow;

playerNow = &players.pointsPlayer1;

// char typeOfBoat;

    while (flagEnd)
    {
        while (players.pointsPlayer1 < 3 || players.pointsPlayer2 < 3)
        {
            playCount++;
            Board brd;
            init_board(N, M, &brd);
            print_board(N, M, brd.board, 1);
            counterShots = 0;

            int porta_Avioes = PORTA_AVIOES;
            int navio_tanque = NAVIO_TANQUE;
            int contrapedeiro = CONTRAPEDEIRO;
            int sumbarino = SUBMARINO;

            //print_board(N, M, brd.board, 0);
            flagFun = 1;
            while (flagFun){
                printf("Coloque a letra para o tipo de barco que quer colocar?\n");
                printf("P -->  Porta-Avioes --> tem %d\nN --> Navio-Tanque--> tem %d\nC --> Contrapedeiro --> tem %d\nS --> Submarino --> tem %d\n ", porta_Avioes,navio_tanque,contrapedeiro,sumbarino);
                scanf("%c", &typeOfBoat);
                switch (typeOfBoat)
                {
                case 'P':
                    if(porta_Avioes <= 0){
                        printf("ja nao tens porta avioes para colocar");
                        continue;
                    }else{
                    printf("Vamos colocar o porta Avioes que ocupa 5 lugares no tabuleiro\n");
                    typeOfBoat = 'P';
                    porta_Avioes--;
                    flagFun = 0;
                    boatNow = &porta_Avioes;
                    break;
                    }
                case 'N':
                    if (navio_tanque <= 0)
                    {
                        printf("ja nao tens navio tanque para colocar");
                        continue;
                    }
                    printf("Vamos colocar o Navio Taque que ocupa 4 lugares no tabuleiro\n");
                    typeOfBoat = 'N';
                    navio_tanque--;
                    flagFun = 0;
                    boatNow = &navio_tanque;
                    break;
                case 'C':
                    if (contrapedeiro <= 0)
                    {
                        printf("ja nao tens contrapedeiro para colocar");
                        continue;
                    }
                    printf("Vamos colocar o Contrapedeiro que ocupa 3 lugares no tabuleiro\n");
                    typeOfBoat = 'C';
                    contrapedeiro--;
                    flagFun = 0;
                    boatNow = &contrapedeiro;
                    break;
                case 'S':
                    if (sumbarino <= 0)
                    {
                        printf("ja nao tens submarinos para colocar");
                        continue;
                    }
                    printf("Vamos colocar o Submarino que ocupa 2 lugares no tabuleiro\n");
                    typeOfBoat = 'S';
                    sumbarino--;
                    flagFun = 0;
                    boatNow = &sumbarino;
                    break;

                default:
                    printf("Coloque uma letra Correspodente a tabela\n");
                    printf("---_____-_-_-_-%c-- -- - -", typeOfBoat);
                    continue;
                }
            }
            // cordenada x
            xCord = placexCord();

            // cordenada y
            yCord = palceyCord();
            // direction
            direction = placeDirection();

            int test = place_boat(xCord, yCord, direction, typeOfBoat, &brd);
            if(test ==-1){
                    (*boatNow)++;
                    printf("nao foi possivel colocar o barco volte a tentar");
    }
            if (porta_Avioes == 0 && navio_tanque == 0 && contrapedeiro == 0 && sumbarino == 0)
            {   
                printf("todos os barcos estao colocados");
                flagTarget = 1;
                while (flagTarget)
                {
                
                printf("jogador %s prepare-se para atacar\n", players.namePlayer2);
                print_board(N, M, brd.board, 0);

                xCord = placexCord();
                yCord = palceyCord();

                int impact = target(xCord, yCord, &brd);
                counterShots++;

                switch (impact)
                {
                case 0:
                    printf("esta coordenada ja foi atacada antes");
                    break;
                case -1:
                    printf("nao acertou em nada");
                    break;
                case -2:
                    printf("as cordenadas estao invalidas");
                    break;
                case 1:
                    printf("Acertou em um barco mas ainda nao o afundou");
                    break;

                default:
                    printf("o barco foi afundado parabens continua o bom trabalho\n");
                    break;
                    }
                    printf("----_--_-_-_-_-_-__--_-barcos aflot %d", brd.numBoatsAfloat);
                    if (brd.numBoatsAfloat == 0)
                    {
                        (*playerNow)++;
                        printf("the game is over");
                        flagTarget = 0;
                        
                    }
                    else if (counterShots == HITSPERPLAYER)
                    {
                        printf("Usou todos os tiros permitidos");
                        break;
                    }
                }
            }
        }
    }
}