void AddBook(BTree t, result r);
void menu(BTree p, result res);
void deleteBook(BTree p);
KeyType splitWhiteSpace(char str[]);
result SearchBook(BTree t);
void ReadAllBookUI();
void ReadAllBook(BTree p);
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
		    case '5':ReadAllBook(p);break;
//		    case '6':over();break;
//		    default :break;
        }
}

/**
* function:��ĳһ��ͼ��UI��
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
* function:ͼ������UI��
* params:
*/
void ReadAllBookUI() {
    system("cls");
	printf("--------------------------------------------------------------------\n");
	printf("����        ����        ������        ��ǰ����        ������\n");
	printf("--------------------------------------------------------------------\n");
}

/**
* function:��ʼ����⡣
* params:�������
*/
void InitBookLibray(BTree &p) {
    FILE *out;
    char temp[30];
    int i;
    int flag = 0, file_row = 0, count = 0;
    result r;
    KeyType bookList[50];
    out = fopen("bookList.txt","r");
    if(out == NULL){
        printf("�ļ���ʧ��\n");
        Sleep(3000);
    }
    while(!feof(out))
    {
        flag = fgetc(out);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //�������һ��
    rewind(out);
    for(i = 0; i < file_row; i++) {
        fgets (temp, 60, out);
        bookList[i] = splitWhiteSpace(temp);
    }
    for(i = 0; i < file_row; i++) {
        SearchBTree(p, bookList[i].bookNum, r);
        InsertBTree(p, bookList[i], r.pt, r.i);
    }
    fclose(out);
}

/**
* function:ͼ��������
* params:B��
*/
void ReadAllBook(BTree p) {
    result res;
    FILE *out;
    char temp[30];
    int i;
    int flag = 0, file_row = 0, count = 0;
    result r;
    KeyType bookList[50];
    out = fopen("bookList.txt","r");
    if(out == NULL){
        printf("�ļ���ʧ��\n");
        Sleep(3000);
    }
    while(!feof(out))
    {
        flag = fgetc(out);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //�������һ��
    rewind(out);

    for(i = 0; i < file_row; i++) {
        fgets (temp, 60, out);
        bookList[i] = splitWhiteSpace(temp);
    }
    fclose(out);
    ReadAllBookUI();
    printf("asdasdas%d", p->key[2].bookNum);
    for(i = 0; i < file_row; i++) {
        SearchBTree(p, bookList[i].bookNum, res);
        printf("��%d��%d���%d", i, res.tag, bookList[i].bookNum);
        if(res.tag == 1) {
            printf("  %d           %s         %s           %d               %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);
        }
    }
    printf("�����������");
	getch();//�����Ժ���
}

/**
* function:�����ո��п���
*/
KeyType splitWhiteSpace(char *str) {
    KeyType book;
    int index = 0;
    char delims[] = " ";
    char *result = NULL;
    result = strtok( str, delims );
    while( result != NULL ) {
        if(index == 0) {
            book.bookNum = atoi(result);
        } else if(index == 1) {
            book.bookName = (char *)malloc(sizeof(char)*50);
            strcpy(book.bookName, result);
        } else if(index == 2) {
            book.bookAuthor = (char *)malloc(sizeof(char)*50);
            strcpy(book.bookAuthor, result);
        } else if(index == 3) {
            book.presentStock = atoi(result);
        } else if(index == 4) {
            book.allStock = atoi(result);
        }
        index++;
        result = strtok( NULL, delims );
    }

    return book;
}


/**
* function:���ļ��ж�ȡͼ���б���Ŵ���������(����ͼ������)��
* params:�������
*/
char *ReadSerial() {
    FILE *fin = fopen("bookSerial.txt", "r"); /*�����ļ���Ϊfile.txt*/
    int flag = 0, file_row = 0, count = 0;
    //��ȡ�ļ��е�����
    while(!feof(fin))
    {
        flag = fgetc(fin);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //�������һ��
    printf("row = %d\n", file_row);
    rewind(fin);
    char str[file_row][20];
    int i;

    for(i = 0; i < file_row; i++) {
        fscanf(fin, "%s", str[i]);
    }
    fclose(fin);

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



