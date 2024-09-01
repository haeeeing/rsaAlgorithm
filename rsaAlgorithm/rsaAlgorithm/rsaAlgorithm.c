#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void selectPQ(int* p, int* q) { //p, q ����
    srand(time(NULL));
    int random = rand() % 100; // ���� �߻� ���� 0-99
    int save = 0;

    for (int i = random; 1; i++) { // ������ i�� �ְ� �Ҽ� 2���� ������������ �ݺ�
        for (int j = 2; j < i / 2 + 1; j++) { // j�� ���� i�� 1�� �ƴ� ���� ���������� Ȯ��
            if (i % j == 0) { // 1 �̿��� ����� ���� -> save = 1
                save = 1;
                break;
            }
            save = 0; // �Ҽ��� -> save = 0;
        }
        if (save == 0 && *p != 0) { // i�� �Ҽ��̰�, p�� �� ���ڰ� ���� -> q����
            *q = i;
            break;
        }
        if (save == 0 && *p == 0) { // i�� �Ҽ��̰�, p�� �� ���ڰ� ���� -> p����
            *p = i;
        }
    }
} // �Ҽ� 2���� ��� p, q�� ���


// ���Ϸ� �Լ�(n) = (p-1)*(q-1)�� ���ϰ� 1�� ���Ϸ� �Լ� (n) ���̿� �ְ�,
// ���Ϸ� �Լ�(n)�� ���μ��� e�� �����ݴϴ�
void selectE(int f, int* e) { // ����Ű�� ���� e
    int save = 1;

    for (int i = 2; i < f; i++) { // 1 < e < f
        for (int j = 1; j <= i; j++) { // ���μ� = ������� 1��
            if (i % j == 0 && f % j == 0) save = j; // ������� ���� -> tmp�� 1�� �ƴϰ� ��
        }
        if (save == 1) { // ������� ���� -> e = i
            *e = i;
            break;
        }
        save = 1;
    }
}

void selectD(int e, int f, int* d) { // ����Ű�� ���� d, d�� e*d�� f�� �������� �������� 1
    for (int i = 2; i < f; i++) { // i�� �÷����鼭 �Ŀ� �־� Ȯ��
        if (((e * i) % f) == 1) *d = i;
    }
}


int main(void) {
    int p = 0, q = 0; // �� �Ҽ�
    selectPQ(&p, &q); // p, q�� 2���� �Ҽ��� ��� �ִ� �Լ�

    int n, e, d, f;
    n = p * q;
    f = (p - 1) * (q - 1);
    selectE(f, &e); // e�� ���ϴ� �Լ�, e�� f�� ���μ�, 1 < e < f

    selectD(e, f, &d); // d�� ���ϴ� �Լ�

    // �Ҽ��� ���� �ڵ� ���� ���� ��
    printf("p\tq\tn\te\td\tf\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", p, q, n, e, d, f);

    long long sum = 1; // ����ϱ� ���� ����
    long long C[501] = { 0, }; // ��ȣ��
    char M[501] = { 0, }; // ����
    char M2[501] = { 0, };
    printf("���� : ");
    fgets(M, sizeof(M), stdin);

    // ��ȣȭ ����
    for (int i = 0; i < strlen(M); i++) {
        for (int j = 0; j < e; j++) {
            sum *= (int)M[i]; // C = M^e mod n
            sum %= n;
        }
        C[i] = sum;
        sum = 1;
    }

    printf("��ȣ�� : ");
    for (int i = 0; i < strlen(M); i++) {
        printf(" %d ", C[i]);
    }

    // ��ȣȭ ����
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

    printf("\n�ص���� : %s", M2);

}

