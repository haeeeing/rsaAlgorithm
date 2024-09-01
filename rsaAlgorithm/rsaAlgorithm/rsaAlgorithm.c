#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void selectPQ(int* p, int* q) { //p, q 생성
    srand(time(NULL));
    int random = rand() % 100; // 난수 발생 범위 0-99
    int save = 0;

    for (int i = random; 1; i++) { // 난수를 i에 넣고 소수 2개가 정해질때까지 반복
        for (int j = 2; j < i / 2 + 1; j++) { // j를 통해 i가 1이 아닌 수로 나눠지는지 확인
            if (i % j == 0) { // 1 이외의 약수가 있음 -> save = 1
                save = 1;
                break;
            }
            save = 0; // 소수임 -> save = 0;
        }
        if (save == 0 && *p != 0) { // i가 소수이고, p에 들어간 숫자가 있음 -> q생성
            *q = i;
            break;
        }
        if (save == 0 && *p == 0) { // i가 소수이고, p에 들어간 숫자가 없음 -> p생성
            *p = i;
        }
    }
} // 소수 2개를 골라 p, q로 사용


// 오일러 함수(n) = (p-1)*(q-1)를 구하고 1과 오일러 함수 (n) 사이에 있고,
// 오일러 함수(n)과 서로소인 e를 정해줍니다
void selectE(int f, int* e) { // 공개키에 사용될 e
    int save = 1;

    for (int i = 2; i < f; i++) { // 1 < e < f
        for (int j = 1; j <= i; j++) { // 서로소 = 공약수가 1뿐
            if (i % j == 0 && f % j == 0) save = j; // 공약수가 있음 -> tmp가 1이 아니게 됨
        }
        if (save == 1) { // 공약수가 없음 -> e = i
            *e = i;
            break;
        }
        save = 1;
    }
}

void selectD(int e, int f, int* d) { // 개인키에 사용될 d, d는 e*d를 f로 나눴을때 나머지가 1
    for (int i = 2; i < f; i++) { // i를 늘려가면서 식에 넣어 확인
        if (((e * i) % f) == 1) *d = i;
    }
}


int main(void) {
    int p = 0, q = 0; // 두 소수
    selectPQ(&p, &q); // p, q에 2개의 소수를 골라서 넣는 함수

    int n, e, d, f;
    n = p * q;
    f = (p - 1) * (q - 1);
    selectE(f, &e); // e를 구하는 함수, e랑 f는 서로소, 1 < e < f

    selectD(e, f, &d); // d를 구하는 함수

    // 소수에 따라 자동 계산된 변수 값
    printf("p\tq\tn\te\td\tf\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", p, q, n, e, d, f);

    long long sum = 1; // 계산하기 위한 변수
    long long C[501] = { 0, }; // 암호문
    char M[501] = { 0, }; // 원문
    char M2[501] = { 0, };
    printf("원문 : ");
    fgets(M, sizeof(M), stdin);

    // 암호화 과정
    for (int i = 0; i < strlen(M); i++) {
        for (int j = 0; j < e; j++) {
            sum *= (int)M[i]; // C = M^e mod n
            sum %= n;
        }
        C[i] = sum;
        sum = 1;
    }

    printf("암호문 : ");
    for (int i = 0; i < strlen(M); i++) {
        printf(" %d ", C[i]);
    }

    // 복호화 과정
    long long word;
    for (int i = 0; i < strlen(M); i++) {
        word = C[i];
        for (int j = 0; j < d; j++) {
            sum *= word; // M = C^d mod n
            sum %= n;
        }
        M2[i] = (char)sum;
        sum = 1;
    }

    printf("\n해독결과 : %s", M2);

}

