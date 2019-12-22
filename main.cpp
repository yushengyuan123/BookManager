#include <stdio.h>
#include <stdlib.h>
typedef int Status;
//��š����������ߡ��ִ������ܿ���������
typedef struct KeyType {
    char bookName[10];
    char bookNum[10];
    char bookAuthor[3];
    int presentStock;
    int allStock;
}KeyType;

typedef struct Record {

}Record;

typedef struct BTNode {
    int keynum;//��㵱ǰ�Ĺؼ��ָ���
    KeyType key[m+1];//�ؼ�������
    struct BTNode *parent;//˫�׽��ָ������
    struct BTNode *ptr[m+1];//���ӽ��ָ������
    Record *recptr[m+1]//��¼ָ������,0�ŵ�Ԫδ��
}BTNode, *BTree;

/**
* function:��ʼ�����С�
* params:����
*/
Status SearchBTree(BTree t, int k, result &r) {
    int i = 0, found = 0;
    BTree p = t, q = NULL;
    while(p != NULL && found == 0) {
        i == Search(p, k);
        if(i <= p->keynum && p->key[i] == k)
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
        r.pt = q;
        r.i = i;
        r.tag = 0;
    }
    return 1;

}

/**
* function:�ڹؼ��������в��ҹؼ�������λ�á�
* params:B��,����ؼ���
*/
int Serach(BTree p, int k) {
    int i = 1;
    while(i <=p->keynum && k > p->key[i]) {
       i++;
    }
    return i;
}

/**
* function:B���Ĳ��������
* params:B��,����ؼ���
*/
void InsertBTree(BTree &t ,int k, BTree q, int i) {
    int x, s,finished = 0, needNewRoot = 0;
    BTree ap;
    if(q == NULL) {
        NewRoot(t, NULL, k, NULL);
    } else {
        x = k, ap = NULL;
        while(o == needNewRoot && finished == 0) {
            Insert(q, i, x, ap);
            if(q->keynum < m) {
                finished = 1;
            } else {
                s = (m + 1) / 2;
                split(q, s, ap);
                x = q->key[s];
                if(q->parent != NULL){
                    q = q->parent;
                    i = Search(q, x);
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
* function:�����ؼ��ֳ���mʱ�и�ؼ��֡�
* params:B��,����ؼ���
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

void newRoot(BTree &t, BTree p, int x, BTree ap) {

}

