#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 10
#define MAX_DROPS 5

int levelDelays[] = { 100, 80, 60 }; // 레벨에 따른 떨어지는 속도

typedef struct {
    int x;
    int y;
} Drop;

void initializeDrops(Drop drops[]) {
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].x = rand() % WIDTH;
        drops[i].y = -i * 3; // 각 물방울들이 겹치지 않게 초기 위치 설정
    }
}

void printGameScreen(int playerX, int playerY, Drop drops[], int score) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == playerY && j == playerX) {
                printf("P");
            }
            else {
                int isDropPrinted = 0;
                for (int k = 0; k < MAX_DROPS; k++) {
                    if (i == drops[k].y && j == drops[k].x) {
                        printf("*");
                        isDropPrinted = 1;
                        break;
                    }
                }
                if (!isDropPrinted) {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

int main() {
    int playerX = WIDTH / 2;
    int playerY = HEIGHT - 1;
    int dx = 0;
    int delay = 100;
    int score = 0;
    int level = 1;
    int running = 1;
    Drop drops[MAX_DROPS];

    while (running) {
        system("cls");

        // 레벨에 따른 딜레이 설정
        delay = levelDelays[level - 1];

        initializeDrops(drops);

        while (running) {
            system("cls");

            // 키 입력 처리
            if (_kbhit()) {
                char ch = _getch();
                switch (ch) {
                case 'a':
                    dx = -1;
                    break;
                case 'd':
                    dx = 1;
                    break;
                case 'q':
                    running = 0; // q를 누르면 게임 종료
                    break;
                default:
                    break;
                }
            }

            // 플레이어 이동
            playerX += dx;
            if (playerX < 0) playerX = 0;
            if (playerX >= WIDTH) playerX = WIDTH - 1;

            // 물방울 떨어뜨리기
            for (int i = 0; i < MAX_DROPS; i++) {
                drops[i].y++;
                if (drops[i].y >= HEIGHT) {
                    drops[i].y = 0;
                    drops[i].x = rand() % WIDTH;
                    score++;
                }

                // 충돌 확인
                if (playerX == drops[i].x && playerY == drops[i].y) {
                    running = 0;
                }
            }

            // 맵 끝에 닿았는지 확인
            if (playerY == HEIGHT - 1 && (playerX == 0 || playerX == WIDTH - 1)) {
                running = 0;
            }

            printGameScreen(playerX, playerY, drops, score);

            // 잠시 멈추기
            Sleep(delay);
        }

        system("cls");
        printf("Game Over! Your score: %d\n", score);

        if (level < sizeof(levelDelays) / sizeof(levelDelays[0])) {
            printf("Press 'Enter' to continue to the next level, or 'q' to quit.\n");
            char ch = _getch();
            if (ch == 'q') {
                break; // 게임 종료
            }
            else if (ch == '\r') { // 엔터 키 입력
                playerX = WIDTH / 2; // 플레이어 위치 초기화
                score = 0; // 점수 초기화
                level++; // 다음 레벨로 이동
            }
        }
        else {
            printf("Congratulations! You've completed all levels!\n");
            printf("Press 'q' to quit.\n");
            char ch = _getch();
            if (ch == 'q') {
                break; // 게임 종료
            }
        }
    }

    return 0;
}
