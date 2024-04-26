#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 30
#define MAX_DROPS 30

typedef struct {
    int x;
    int y;
} Drop;

int main() {
    int playerX = WIDTH / 2;
    int playerY = HEIGHT - 1;
    int dx = 0;
    int delay = 100;
    int score = 0;
    int running = 1;
    Drop drops[MAX_DROPS];

    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].x = rand() % WIDTH;
        drops[i].y = -i * 3; // 각 똥들이 겹치지 않게 초기 위치 조절
    }

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
            default:
                break;
            }
        }

        // 플레이어 이동
        playerX += dx;
        if (playerX < 0) playerX = 0;
        if (playerX >= WIDTH) playerX = WIDTH - 1;

        // 똥들 떨어뜨리기
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

        // 맵 끝에 닿으면 죽음 확인
        if (playerY == HEIGHT - 1 && (playerX == 0 || playerX == WIDTH - 1)) {
            running = 0;
        }

        // 게임 화면 출력
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == playerY && j == playerX) {
                    printf("O");
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

        // 잠시 멈추기
        Sleep(delay);
    }

    system("cls");
    printf("Game Over! Your score: %d\n", score);

    return 0;
}