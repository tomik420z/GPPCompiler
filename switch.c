#include "stdio.h"
int g() {
    return 0;
}

int main() {
    int x = 10;
    int y;
    switch (x)
    {
    case 12:
        y = 10;
        g();
    default:
    }
}