#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define m 3
typedef int Status;
//��š����������ߡ��ִ������ܿ���������
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
    int keynum;//��㵱ǰ�Ĺؼ��ָ���
    KeyType key[m+1];//�ؼ�������
    struct BTNode *parent;//˫�׽��ָ������
    struct BTNode *ptr[m+1];//���ӽ��ָ������
    Record *recptr[m+1];//��¼ָ������,0�ŵ�Ԫδ��
}BTNode, *BTree;

typedef struct result{
    BTree pt;//ָ���ҵ��Ľ��
    int i;//1<=i<=m,�ڽ���еĹؼ���λ��
    int tag;//1:���ҳɹ�,0:����ʧ��
}result;


/**
* function:��ʼ��B����
* params:����
*/
Status InitBTree(BTree &t) {
    int i;
    t = (BTree)malloc(sizeof(BTNode));
    if(t == NULL) {
        printf("��ʼ��ʧ��\n");
        return 0;
    }
    //�ؼ�������û�ж���
    t->keynum = 0;
    t->parent = NULL;
    for(i = 0; i < m + 1; i++) {
        t->ptr[i] = NULL;
    }
    return 1;
}

/**
* function:�ڹؼ��������в��ҹؼ�������λ�á�
* params:B��,����ؼ���
*/
int Search(BTree p, int k) {
    int i = 1;
    while(i <= p->keynum && k > p->key[i].bookNum) {
       i++;
    }
    return i;
}

/**
* function:B������ѯ������
* params:B�������ҵĹؼ���, ���ҽ��
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
        //���û���ҵ���r��BTree���ָ����Ӧ�ò����λ��
        r.pt = q;
        r.i = i;
        r.tag = 0;
        return 0;
    }
    return 1;
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
* function:B���Ĳ��������
* params:B��,����ؼ���
*/
void InsertBTree(BTree &t ,KeyType k, BTree q, int i) {
    int s, finished = 0, needNewRoot = 0;
    KeyType x;
    BTree ap;
    if(q == NULL) {
        newRoot(t, NULL, x, NULL);//����������㶼û�е�ʱ��ͻᴥ������������ɸ����
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
* function:B��ɾ����㡣
* params:B�������ҵĹؼ���, ���ҽ��
*/
void DeleteBTree(BTree p, int i) {
    //ɾ��B���Ͻ��ĵ�i���ؼ���
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
