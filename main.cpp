#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>
#include "./head/BTree.h"
#include "./head/BusineseLogic.h"

int main() {
    //记录用户在菜单的选择项目
    int i;
    char t;
    BTree p = NULL;
    result res;
    InitBookLibray(p);
    for(i = 0; i < 100; i++) {
        menu(p, res);
    }
}

