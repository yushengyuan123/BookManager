void AddBook(BTree t, result r);
void menu(BTree p, result res);
void deleteBook(BTree p);
result SearchBook(BTree t);
/**
* function:ϵͳѡ��˵���
* params:
*/
void menu(BTree p, result res) {   //�˵�
//	do
//	{
		system("cls");  //����
		char t;
		printf(" ͼ���ѯ����ϵͳ\n");
		printf("|     1.ͼ�����      |\n");
		printf("|     2.�޸���Ϣ      |\n");
		printf("|     3.ɾ����Ϣ      |\n");
		printf("|     4.ͼ���ѯ      |\n");
		printf("|     5.ͼ������      |\n");
		printf("|     6.�˳����      |\n");
//	}while(1);
        t = getchar();
        switch(t) {
            case '1':AddBook(p, res);break;
//		    case '2':amend_book();break;
		    case '3':deleteBook(p);break;
		    case '4':res = SearchBook(p);break;
//		    case '5':print_book();break;
//		    case '6':over();break;
//		    default :break;
        }
}

/**
* function:ͼ������UI��
* params:
*/
void ReadSomeBookInfo(result res)   //ͼ������
{
    system("cls");
	printf("--------------------------------------------------------------------\n");
	printf("����        ����        ������        ��ǰ����        ������\n");
	printf("--------------------------------------------------------------------\n");
//	if(head==NULL)
//	{
//		printf("�����ʱû����Ŷ~�Ͽ�ȥ��Ӽ�����^_^(�����������)");
//		getch();
//		menu();
//	}
    printf("  %d           %s         %s           %d               %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);
}

/**
* function:���ļ�������ͼ�顣
* params:�������
*/
void wirteFile(result res) {
    FILE *out;
    out = fopen("bookList.txt","a+");
    if(out == NULL){
        printf("�ļ���ʧ��\n");
        Sleep(3000);
    }

    fprintf(out,"%d %s %s %d %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);

    fclose(out);
}

/**
* function:���ļ��ж�ȡͼ���б�
* params:�������
*/
char *ReadFile() {
    FILE *fin = fopen("bookList.txt", "r"); /*�����ļ���Ϊfile.txt*/
    int flag = 0, file_row = 0, count = 0;
    //��ȡ�ļ��е�����
    while(!feof(fin))
    {
        flag = fgetc(fin);
        if(flag == '\n')
            if()
        count++;
    }
    file_row = count + 1; //�������һ��
    printf("row = %d\n", file_row);

    char a[file_row][20], i;

        fscanf(fin, "%s", &a[i]);



        printf("%s ", a);

    fclose(fin);

//    FILE *fp;
//    char *bookSerial
//	char buf[1024];
//	fp = fopen("bookList.txt", "r");
//	if (fp == NULL) {
//		printf("open error!\n");
//	}
//	else {
//		while (fgets(buf, sizeof(buf), fp) != NULL) {
//			printf(buf);
//		}
//	}

}


/**
* function:����ͼ�顣
* params:B��,�������
*/
void AddBook(BTree t, result r) {
    int bookSerial;

    KeyType book;

    system("cls");
    printf("������ͼ��ı��:");
    scanf("%d", &book.bookNum);
    printf("������ͼ�������:");
    fflush(stdin);
    gets(book.bookName);
    printf("������ͼ�������:");
    fflush(stdin);
    gets(book.bookAuthor);
    book.allStock = 1;
    book.presentStock = 1;
    printf("���:%d\n����:%s\n����:%s\n",book.bookNum,book.bookName, book.bookAuthor);
    //��ʱ�ȸ������ȥ����
    SearchBTree(t, book.bookNum, r);
    //���tagΪ0˵��ͼ�鲻����,���ʱӦ�ò���ͼ��
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        wirteFile(r);
        printf("��ӳɹ�,�����������\n");
        getch();//�����Ժ���
    } else {
        //ͼ�����Ŀ��1
    }
}

/**
* function:����ͼ�顣
* params:B��,ͼ������к�
*/
result SearchBook(BTree t) {
    int bookSerial;
    result res;

    system("cls");
    printf("��������Ҫ����������:");
    scanf("%d", &bookSerial);
    if(bookSerial <= 0) {
        //��������س������Ϣ
        res.pt = NULL;
        res.i = 0;
    } else {
        if(SearchBTree(t, bookSerial, res)) {
            ReadSomeBookInfo(res);
            printf("%d\n",  res.pt->keynum);
            printf("%d\n", res.i);
            printf("%s", res.pt->key[res.i].bookName);
            printf("%s", res.pt->key[res.i].bookAuthor);
            Sleep(5000);
        } else {
            printf("����ʧ��\n");
        }

//        printf("%s", res.pt->key[res.i].bookName);
    }
    printf("�����������");
	getch();//�����Ժ���
    return res;
}


/**
* function:ɾ��ͼ�顣
* params:B��
*/
void deleteBook(BTree p) {
    int bookSerial;
    result res;

    system("cls");
    printf("��������Ҫɾ��������:");
    scanf("%d", &bookSerial);
    system("cls");
    if(bookSerial <= 0) {
        //��������س������Ϣ
        res.pt = NULL;
        res.i = 0;
        printf("�����������\n");
        Sleep(5000);
    } else {
        if(SearchBTree(p, bookSerial, res)) {
            DeleteKey(p, res.i);
            printf("��ɾ����ͼ�����Ϊ:%d,�鼮����Ϊ:%s\n", res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName);
            printf("ɾ���ɹ�\n");
        } else {
            printf("�ܱ�Ǹ��������鼮������\n");
        }
    }
    printf("�����������");
	getch();//�����Ժ���
}

/**
* function:ͼ��������
* params:B��
*/
void ReadAllBook() {

}


