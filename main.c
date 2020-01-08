/*****************************************
 *                                       *
 *        TypingMaster �֥�����           *
 *                                       *
 *****************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

void alphabetGenerator(char map[10][4], int round, int time);
void infoPrinter(char map[10][4], int perfectCount, int lostCount, int roundCount, int time);
int inputScanner(char input, char map[10][4], int row);
void moveAlphabet(char map[10][4]);

int main() {

    printf("+----------------[ �C������ ]---------------+\n\n");
    printf("�֥����� (TypingMaster) �O�@�ڤU���������C��\n");
    printf("��C���}�l�ɷ|�H���ͦ��j�p�g���^��r��\n");
    printf("���a�������U�������r���Ӯ����P�w�u�e���r�����~��\n\n");
    printf("+-------------------------------------------+\n\n");

    while(1) {
        srand(time(0));
        //while(1) {
        //[y] [x]
        char map[10][4] = //horizontal(width): 10, vertical: 4
                {
                        {'*', '*', '*', '*'}, //row 0
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'*', '*', '*', '*'},
                        {'=', '=', '=', '='}, //row 9

                };

        int round = 1, time = 0, ctime = 0, arg = 0;
        int perfect = 0, lost = 0, mode = 0;
        //mode 1 = ends the game when time out, mode 2 = ends the game when reach lost limit
        char input;

        printf("+----------------[ ��ܼҦ� ]---------------+\n\n");
        printf("1 - �p�ɼҦ�: ���F���w�ɶ���Y�����C��\n");
        printf("2 - �D�ԼҦ�: ���J�W�L���w�����~�ƫ�Y�����C��\n");
        printf("+-------------------------------------------+\n\n");

        while (1) {
            printf("> ��g�Ҧ��N��: ");
            scanf("%d", &mode);
            printf("\n");
            if (mode == 1) {
                printf("> ��J�A�n�C�����ɶ�(��): ");
                scanf("%d", &arg);
                printf("\n");
                break;
            } else if (mode == 2) {
                printf("> ��J�̰����~����: ");
                scanf("%d", &arg);
                printf("\n");
                break;
            } else {
                printf("> ����즹�Ҧ� ! �ЦA����J\n");
            }
        }

        while (1) {
            ctime++;
            if ((ctime % 2) == 0) { time++; }
            alphabetGenerator(map, round, time);
            infoPrinter(map, perfect, lost, round, time);
            if (kbhit() == 1) {
                input = getch();
                if (input != '*') {
                    if (inputScanner(input, map, 8) == 1) {
                        perfect++;
                        moveAlphabet(map);
                    } else {
                        lost++;
                        moveAlphabet(map);
                    }
                    round++;
                }
            }
            infoPrinter(map, perfect, lost, round, time);

            if (mode == 1 && time == arg) {
                printf("> �ɶ��� ! �C������\n");
                break;
            } else if (mode == 2 && lost == arg) {
                printf("> �w�F���~�ƤW�� ! �C������\n");
                break;
            }
            _sleep(500);
        }

        printf("> �аݬO�_�~��C��? ��J Y ����~��, N ��ܵ���: ");
        scanf(" %c", &input);

        if(input == 'Y' || input == 'y'){
            continue;
        }else if(input == 'N' || input == 'n'){
            break;
        }
        break;
    }
    system("pause");
}

void moveAlphabet(char map[10][4]) {
    for (int y = 9; y >= 0; y--) {
        for (int x = 3; x >= 0; x--) {
            if (y != 9) {
                map[y + 1][x] = map[y][x];
                map[y][x] = '*';
            }
            map[9][x] = '=';
        }
    }
}

int inputScanner(char input, char map[10][4], int row){
    for(int i = 0; i <= 3; i++){
        if(input == map[row][i]){
            return 1;
        }
    }
    return 0;
}

void infoPrinter(char map[10][4], int perfectCount, int lostCount, int roundCount, int time) {
    int min = time / 60;
    int sec = time - min * 60;

    for(int i = 0; i < 20; i++){
        printf("\n");
    }
    printf("+----------------[ �Y�ɲέp ]---------------+\n\n");
    printf("> �^�X: %d\n", roundCount - 1);
    printf("> �w�L�ɶ�: %d Min(s) %d Secs\n\n",min, sec);
    printf("> ���T: %d\n", perfectCount);
    printf("> ���~: %d\n\n", lostCount);
    printf("+-------------------------------------------+\n\n");
    for (int y = 0; y <= 9; y++) {
        for(int x = 0; x <= 3; x++){
            printf("%c    ", map[y][x]);
        }
        printf("\n");
    }
}

void alphabetGenerator(char map[10][4], int round, int time) {
    char alphabet;
    int chance = rand() % 100;
    int pos = rand() % 3;

    if (time == 0) {
        for (int y = 0; y <= 8; y++) {
            int randNum = rand() % 4, chance = rand() % 100;
            if (chance > 50) {
                alphabet = 'A';
                alphabet += rand() % 26;
            } else {
                alphabet = 'a';
                alphabet += rand() % 26;
            }
            map[y][randNum] = alphabet;
        }
    } else {
        int j = 0;
        for (int i = 0; i <= 3; i++) {
            if (map[0][i] != '*') {
                j++;
            }
        }
        if (j == 0) {
            if (chance > 50) {
                alphabet = 'A';
                alphabet += rand() % 26;
            } else {
                alphabet = 'a';
                alphabet += rand() % 26;
            }
            map[0][pos] = alphabet;
        }
    }
}