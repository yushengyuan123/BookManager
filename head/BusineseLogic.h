void AddBook(BTree t, result r);
void menu(BTree p, result res);
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
//		    case '3':del_book();break;
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
	printf("�����������");
	getch();//�����Ժ���
}

/**
* function:����ͼ�顣
* params:B��,�������
*/
void AddBook(BTree t, result r) {
    int bookSerial;

    KeyType book;

    system("cls");
    printf("������ͼ��ı��,����,����(�м�ʹ�ö��Ÿ���)\n");

    scanf("%d %s %s", &book.bookNum, book.bookName, book.bookAuthor);
    printf("%s", book.bookAuthor);

    book.allStock = 1;
    book.presentStock = 1;
    //��ʱ�ȸ������ȥ����
    SearchBTree(t, book.bookNum, r);
    //���tagΪ0˵��ͼ�鲻����,���ʱӦ�ò���ͼ��
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        printf("��ӳɹ�,����󷵻�\n");
        Sleep(2000);
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

    printf("��������Ҫ����������:");
    scanf("%d", &bookSerial);
    if(bookSerial <= 0) {
        //��������س������Ϣ
        res.pt = NULL;
        res.i = 0;
    } else {
        if(SearchBTree(t, bookSerial, res)) {
            printf("���ҳɹ�\n");
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
    return res;
}


