void AddBook(BTree t, result r);
int menu(BTree p, result res);
void deleteBook(BTree p);
KeyType splitWhiteSpace(char str[]);
result SearchBook(BTree t);
void ReadAllBookUI();
void ReadAllBook(BTree p);
void BorrorBook(BTree p);
void QueryStuBook(BTree p);
void ReturnBook(BTree p);
void over();
void AfterAddWriteInFile(result res, int isTheSame);
//char *ConcatStr(result r);
/**
* function:ϵͳѡ��˵���
* params:
*/
int menu(BTree p, result res) {   //�˵�
//	do
//	{
		system("cls");  //����
		char t;
		printf("   ͼ���ѯ����ϵͳ\n");
		printf("|     1.ͼ�����      |\n\n");
		printf("|     2.����ͼ��      |\n\n");
		printf("|     3.ɾ��ͼ��      |\n\n");
		printf("|     4.ͼ���ѯ      |\n\n");
		printf("|     5.ͼ������      |\n\n");
		printf("|     6.���Ĳ鿴      |\n\n");
		printf("|     7.�黹ͼ��      |\n\n");
		printf("|     8.�˳����      |\n\n");
//	}while(1);
        t = getchar();
        switch(t) {
            case '1':AddBook(p, res);break;
		    case '2':BorrorBook(p);break;
		    case '3':deleteBook(p);break;
		    case '4':res = SearchBook(p);break;
		    case '5':ReadAllBook(p);break;
		    case '6':QueryStuBook(p);break;
		    case '7':ReturnBook(p);break;
            case '8':return 0; break;
		    default :break;
        }
        return 1;
}

/**
* function:��ĳһ��ͼ��UI��
* params:
*/
void ReadSomeBookInfo(result res)   //ͼ������
{
    system("cls");
    printf("************************ͼ����Ϣ************************************\n");
	printf("--------------------------------------------------------------------\n");
	printf("����        ������        �ɽ�����        ������        ����\n");
	printf("--------------------------------------------------------------------\n");
//	if(head==NULL)
//	{
//		printf("�����ʱû����Ŷ~�Ͽ�ȥ��Ӽ�����^_^(�����������)");
//		getch();
//		menu();
//	}
    printf("  %d         %s           %d         %d         %s\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock, res.pt->key[res.i].bookName);
}


/**
* function:ͼ������UI��
* params:
*/
void ReadAllBookUI() {
    system("cls");
    printf("************************ͼ������************************************\n");
	printf("--------------------------------------------------------------------\n");
	printf("����      ������       �ɽ�����           ������       ����\n");
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
    for(i = 0; i < file_row; i++) {
        SearchBTree(p, bookList[i].bookNum, res);
        if(res.tag == 1) {
             printf("  %d         %s           %d               %d            %s\n\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock, res.pt->key[res.i].bookName);
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
* function:�Ƚ������ַ����Ƿ���ͬ��
* params:�ַ���1,�ַ���2
*/
int CompareStr(char *str1, char *str2) {
    if (strcmp(str1, str2) == 0) {
	    return 1;
	}
	return 0;
}


/**
* function:ͼ����⡣
* params:B��,�������
*/
void AddBook(BTree t, result r) {
    int bookSerial;

    KeyType book;

    system("cls");
    printf("************************ͼ�����************************************\n");
    printf("������ͼ��ı��:");
    scanf("%d", &book.bookNum);
    fflush(stdin);
    printf("������ͼ�������:");
    fflush(stdin);
    book.bookName = (char *)malloc(sizeof(char) * 50);
    gets(book.bookName);
    printf("������ͼ�������:");
    book.bookAuthor = (char *)malloc(sizeof(char) *50);
    fflush(stdin);
    gets(book.bookAuthor);
    book.allStock = 1;
    book.presentStock = 1;
    printf("���������Ϣ:���:%d  ����:%s  ����:%s\n",book.bookNum,book.bookName, book.bookAuthor);
    //��ʱ�ȸ������ȥ����
    SearchBTree(t, book.bookNum, r);
    //���tagΪ0˵��ͼ�鲻����,���ʱӦ�ò���ͼ��
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        printf("��ӳɹ�\n");
        //������д���ļ�
        AfterAddWriteInFile(r, 0);
    } else {
        //��ʱ˵���Ȿ����λ���Ѿ�����,��Ŀ��1
        if(CompareStr(book.bookName, r.pt->key[r.i].bookName) && CompareStr(book.bookAuthor, r.pt->key[r.i].bookAuthor)) {
            r.pt->key[r.i].allStock++;
            r.pt->key[r.i].presentStock++;
            printf("��ӳɹ�\n");
            //������д���ļ�
//            AfterAddWriteInFile(r, 1);
        } else {
            printf("����ʧ��,�����������鼮��Ϣ��ƥ��\n");
        }
    }
    printf("�����������");
	getch();//�����Ժ���
}

/**
* function:�����ͼ�黹Ҫд���ļ��С�
* params:B��,�������
*/
void AfterAddWriteInFile(result r, int isTheSame) {
    FILE *out;
    int i;
    int line, c, c1, cnt;
    out = fopen("bookList.txt","a+");
    char str1[60];
//    char *temp = ConcatStr(r);

    //��ȡĿ���ַ������к�
//    while(fgets(temp,sizeof(temp),out))//����ѭ����ȡ�ļ���ֱ���ļ�����
//	{
//		line++;
//		if(strstr(temp,temp))  //����ַ����Ƿ��ڸ����У�����ڣ����������
//		{
//		    printf("Ŀ���ַ���������Ϊ:%d\n",line);
//            break;
//		}
//	}

    if(out == NULL){
        exit(-1);
    }
    if(isTheSame == 0) {
        fprintf(out,"\n%d %s %s %d %d", r.pt->key[r.i].bookNum, r.pt->key[r.i].bookName, r.pt->key[r.i].bookAuthor, r.pt->key[r.i].presentStock, r.pt->key[r.i].allStock);
    } else {
//        //��ȡĿ���ַ������к�
//        while(fgets(temp,sizeof(temp),out))//����ѭ����ȡ�ļ���ֱ���ļ�����
//        {
//            line++;
//            if(strstr(temp,temp))  //����ַ����Ƿ��ڸ����У�����ڣ����������
//            {
//                printf("Ŀ���ַ���������Ϊ:%d\n",line);
//                break;
//            }
//        }
//
//        //��⵽ָ���п�ͷ��ָ��λ�ã����丳ֵ��c
//        c = ftell(out);
//        //����һ��Ŀ���У�ȷ�����г��ȣ�ͬʱforѭ������ʱc1Ϊ����ĩβ��ָ��λ��
//        while(fgetc(out)!='\n')
//        {
//            c1=ftell(out);
//        }
//        //���ļ�ָ���Ƶ�Ŀ���е�����
//        fseek(out,c,SEEK_SET);
//        //�õ�Ŀ���еĳ���
//        cnt=c1-c;
//        //forѭ��������Ҫ�޸ĵ�����
//        for(i=0;i<cnt;i++)
//        {
//            fputc(temp,out);
//        }

    }

    fclose(out);
}

/**
* function:�����ؽ��ƴ�ӳ��ַ�����
* params:�������
*/
//char *ConcatStr(result r) {
//    printf("�ҽ�����\n");
//    char num[20]; itoa(r.pt->key[r.i].bookNum, num, 10);
//
//    char *name = r.pt->key[r.i].bookName;
//    char *author = r.pt->key[r.i].bookAuthor;
//    char presentStock[20]; itoa(r.pt->key[r.i].presentStock, presentStock, 10);
//    char allStock[20]; itoa(r.pt->key[r.i].allStock, allStock, 10);
//    char *concanStr = (char *) malloc(strlen(num) + strlen(name) + strlen(author) + strlen(presentStock) + strlen(allStock));
//printf("$s,%d\n", name,num);
//    strcpy(concanStr, num);
//    strcpy(concanStr, name);
//    strcpy(concanStr, author);
//    strcpy(concanStr, presentStock);
//    strcpy(concanStr, allStock);
//    printf("����ַ���Ϊ:%s\n", concanStr);
//    return concanStr;
//}

/**
* function:ɾ���ļ��е�ĳһ�С�
* params:��
*/
//void deleteFile(result r) {
//    FILE* fp = fopen("bookList.txt", "r");
//    char *targetStr = (char *)malloc(sizeof(char)); strcpy(targetStr, "2 JavaScript ����� 1 1");
//    char *scanfStr = ConcatStr(r);
//    if(!fp)
//    {
//       exit(-1);
//    }
//    printf("fuck");
//    FILE* fp2 = fopen("temp.txt", "w");
//    while(fscanf(fp, "%s", scanfStr))
//    {
//        if(strcmp(scanfStr, targetStr))
//            fprintf(fp2, "%s\n", targetStr);
//    }
//    fclose(fp);
//    fclose(fp2);
//}

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
    printf("************************ͼ��ɾ��************************************\n");
    printf("��������Ҫɾ��������:");
    scanf("%d", &bookSerial);
    if(bookSerial <= 0) {
        //��������س������Ϣ
        res.pt = NULL;
        res.i = 0;
        printf("�����������\n");
    } else {
        if(SearchBTree(p, bookSerial, res)) {
            printf("--------------------------------------------------------------------\n");
            printf("����             ����\n");
            printf("--------------------------------------------------------------------\n");
            printf("%d                %s\n", res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName);
            DeleteKey(res.pt, res.i);
            printf("ɾ���ɹ�\n");
//            deleteFile(res);
        } else {
            printf("�ܱ�Ǹ��������鼮������\n");
        }
    }
    printf("�����������");
	getch();//�����Ժ���
}


/**
* function:����ͼ�顣
* params:B��
*/
void BorrorBook(BTree p) {
    int bookSerial;
    result r;
    char *studentName;
    int deadline;

    system("cls");
    printf("************************ͼ�����************************************\n");
    printf("���������ͼ������:");
    scanf("%d", &bookSerial);
    printf("����������˵�����:");
    fflush(stdin);
    studentName = (char *)malloc(sizeof(char) * 50);
    gets(studentName);
    printf("��������ĵ�����:");
    scanf("%d", &deadline);

    printf("���������Ϣ:�����鼮���:%d  ����������:%s  ��������:%d\n", bookSerial, studentName, deadline);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("����ʧ��,��Ǹ����ĵ�ͼ�鲻����\n");
    } else if(r.pt->key[r.i].presentStock == 0){
        printf("����ʧ��,��Ǹͼ���Ѿ���������\n");
    } else {
        //���ĳɹ�,Ŀǰ������ȥ1
        int present = --(r.pt->key[r.i].presentStock);
        int all = r.pt->key[r.i].allStock;
        //��¼ѧ����������
        r.pt->stu[r.i].deadline[all - present] = deadline;
        r.pt->stu[r.i].StudentName[all - present] = (char *)malloc(sizeof(char) * 10);
        strcpy(r.pt->stu[r.i].StudentName[all - present], studentName);
        SearchBTree(p, bookSerial, r);
        printf("���ĳɹ�");
    }
    printf("�����������");
	getch();//�����Ժ���
}

/**
* function:�鿴����ѧ������ͼ�顣
* params:B��
*/
void QueryStuBook(BTree p) {
    int bookSerial;
    result r;
    int k;

    system("cls");
    printf("************************���Ĳ�ѯ************************************\n");
    printf("���������ͼ������:");
    scanf("%d", &bookSerial);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("��ѯʧ��,��Ǹ���ѯ��ͼ�鲻����\n");
    } else if(r.pt->key[r.i].allStock == r.pt->key[r.i].presentStock){
        printf("��ѯ�ɹ�,Ŀǰ��ͼ����δ���˽���\n");
    } else {
        printf("�����鼮:%s\n", r.pt->key[r.i].bookName);
        for(k = 1; k < r.pt->key[r.i].allStock - r.pt->key[r.i].presentStock + 1; k++) {
            printf("����������:%s,��������:%d\n", r.pt->stu[r.i].StudentName[k], r.pt->stu[r.i].deadline[k]);
        }
    }
    printf("�����������");
	getch();//�����Ժ���
}

/**
* function:�黹ͼ�顣
* params:B��
*/
void ReturnBook(BTree p) {
    int bookSerial;
    char *Name;
    result r;
    int k;

    system("cls");
    printf("************************ͼ��黹************************************\n");
    printf("������黹�˵�����:");
    fflush(stdin);
    Name = (char *)malloc(sizeof(char) * 20);
    gets(Name);
    printf("\n������黹ͼ������:");
    scanf("%d", &bookSerial);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("�黹ʧ��,��Ǹ��黹��ͼ�鲻����\n");
    } else if(r.pt->key[r.i].allStock == r.pt->key[r.i].presentStock){
        printf("��ѯʧ��,Ŀǰ��ͼ����δ�н��ļ�¼\n");
    } else {
        printf("�黹�鼮:%s\n", r.pt->key[r.i].bookName);
        int present = ++(r.pt->key[r.i].presentStock);
        int all = r.pt->key[r.i].allStock;
        r.pt->stu[r.i].StudentName[all - present] = NULL;
        r.pt->stu[r.i].deadline[all - present] = 0;
        printf("�黹�ɹ�");

    }
    printf("�����������");
	getch();//�����Ժ���
}




