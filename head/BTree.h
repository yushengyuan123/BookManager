#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define m 3
typedef int Status;
//书号、书名、著者、现存量和总库存量等五项。
typedef struct KeyType {
    char bookName[10];
    int bookNum;
    char bookAuthor[3];
    int presentStock;
    int allStock;
}KeyType;

typedef struct Record {

}Record;

typedef struct BTNode {
    int keynum;//结点当前的关键字个数
    KeyType key[m+1];//关键字数组
    struct BTNode *parent;//双亲结点指针数组
    struct BTNode *ptr[m+1];//孩子结点指针数组
    Record *recptr[m+1];//记录指针向量,0号单元未用
}BTNode, *BTree;

typedef struct result{
    BTree pt;//指向找到的结点
    int i;//1<=i<=m,在结点中的关键字位序
    int tag;//1:查找成功,0:查找失败
}result;


/**
* function:初始化B树。
* params:队列
*/
Status InitBTree(BTree &t) {
    int i;
    t = (BTree)malloc(sizeof(BTNode));
    if(t == NULL) {
        printf("初始化失败\n");
        return 0;
    }
    //关键字数组没有东西
    t->keynum = 0;
    t->parent = NULL;
    for(i = 0; i < m + 1; i++) {
        t->ptr[i] = NULL;
    }
    return 1;
}

/**
* function:在关键字数组中查找关键字所在位置。
* params:B树,传入关键字
*/
int Search(BTree p, int k) {
    int i = 1;
    while(i <= p->keynum && k > p->key[i].bookNum) {
       i++;
    }
    return i;
}

/**
* function:B树结点查询操作。
* params:B树，查找的关键字, 查找结果
*/
Status SearchBTree(BTree t, int k, result &r) {
    int i = 0, found = 0;
    BTree p = t, q = NULL;
    while(p != NULL && found == 0) {
        i = Search(p, k);
        if(i <= p->keynum && p->key[i].bookNum == k)
            found = 1;
        else {
            q = p;
            p = p->ptr[i-1];
        }
    }
    if(found == 1){
        r.pt = p;
        r.i = i;
        r.tag = 1;
    } else {
        //如果没有找到则r的BTree域会指向它应该插入的位置
        r.pt = q;
        r.i = i;
        r.tag = 0;
        return 0;
    }
    return 1;
}

/**
* function:当结点关键字超过m时切割关键字。
* params:B树,传入关键字
*/
void split(BTree &q, int s, BTree &ap) {
    int i, j , n = q->keynum;
    ap = (BTNode *)malloc(sizeof(BTNode));
    ap->ptr[0] = q->ptr[s];
    for(i = s+1, j = 1; i <= n; i++, j++) {
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
    }
    ap->keynum = n - s;
    ap->parent = q->parent;
    for(i = 0; i < n - s; i++) {
        if(ap->ptr[i] != NULL) {
            ap->ptr[i]->parent = ap;
        }
    }
    q->keynum = s - 1;
}

void newRoot(BTree &t, BTree p, KeyType x, BTree ap) {
    t = (BTNode *)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = x;
    if(p != NULL){
        p->parent  = t;
    }
    if(ap != NULL) {
        ap->parent = t;
    }
    t->parent = NULL;
}

void Insert(BTree &q, int i, KeyType x, BTree ap) {
    int j,n = q->keynum;
    for(j = n; j >= i; j--) {
        q->key[j+1] = q->key[j];
        q->ptr[j+1] = q->ptr[j];
    }
    q->key[i] = x;
    q->ptr[i] = ap;
    if(ap != NULL) {
        ap->parent = q;
    }
    q->keynum++;
}

/**
* function:B树的插入操作。
* params:B树,传入关键字
*/
void InsertBTree(BTree &t ,KeyType k, BTree q, int i) {
    int s, finished = 0, needNewRoot = 0;
    KeyType x;
    BTree ap;
    if(q == NULL) {
        newRoot(t, NULL, x, NULL);//假如连根结点都没有的时候就会触发这条语句生成根结点
    } else {
        x = k, ap = NULL;
        while(0 == needNewRoot && finished == 0) {
            Insert(q, i, x, ap);
            if(q->keynum < m) {
                finished = 1;
            } else {
                s = (m + 1) / 2;
                split(q, s, ap);
                x = q->key[s];
                if(q->parent != NULL){
                    q = q->parent;
                    i = Search(q, x.bookNum);
                } else {
                    needNewRoot = 1;
                }
            }
        }
        if(1 == needNewRoot) {
            newRoot(t, q, x, ap);
        }
    }
}

/**
* function:B树删除结点。
* params:B树，查找的关键字, 查找结果
*/
void DeleteBTree(BTree p, int i) {
    //删除B树上结点的第i个关键字
    if(p->ptr[i] != NULL) {
        Successor(p, i);
        DeleteBTree(p, 1);
    } else {
        Remove(p, i);
        if(p->keynum < (m - 1) / 2) {
            Restore(p, i);
        }
    }
}
