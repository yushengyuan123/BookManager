void AddBook(BTree t, result r);
void menu(BTree p, result res);
void deleteBook(BTree p);
result SearchBook(BTree t);
/**
* function:系统选择菜单。
* params:
*/
void menu(BTree p, result res) {   //菜单
//	do
//	{
		system("cls");  //清屏
		char t;
		printf(" 图书查询管理系统\n");
		printf("|     1.图书入库      |\n");
		printf("|     2.修改信息      |\n");
		printf("|     3.删除信息      |\n");
		printf("|     4.图书查询      |\n");
		printf("|     5.图书总览      |\n");
		printf("|     6.退出软件      |\n");
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
* function:图书总览UI。
* params:
*/
void ReadSomeBookInfo(result res)   //图书总览
{
    system("cls");
	printf("--------------------------------------------------------------------\n");
	printf("书编号        书名        作者名        当前数量        总数量\n");
	printf("--------------------------------------------------------------------\n");
//	if(head==NULL)
//	{
//		printf("书库暂时没有书哦~赶快去添加几本吧^_^(按任意键返回)");
//		getch();
//		menu();
//	}
    printf("  %d           %s         %s           %d               %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);
}

/**
* function:向文件中增加图书。
* params:搜索结果
*/
void wirteFile(result res) {
    FILE *out;
    out = fopen("bookList.txt","a+");
    if(out == NULL){
        printf("文件打开失败\n");
        Sleep(3000);
    }

    fprintf(out,"%d %s %s %d %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);

    fclose(out);
}

/**
* function:向文件中读取图书列表。
* params:搜索结果
*/
char *ReadFile() {
    FILE *fin = fopen("bookList.txt", "r"); /*假设文件名为file.txt*/
    int flag = 0, file_row = 0, count = 0;
    //获取文件中的行数
    while(!feof(fin))
    {
        flag = fgetc(fin);
        if(flag == '\n')
            if()
        count++;
    }
    file_row = count + 1; //加上最后一行
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
* function:增加图书。
* params:B树,搜索结果
*/
void AddBook(BTree t, result r) {
    int bookSerial;

    KeyType book;

    system("cls");
    printf("请输入图书的编号:");
    scanf("%d", &book.bookNum);
    printf("请输入图书的书名:");
    fflush(stdin);
    gets(book.bookName);
    printf("请输入图书的作者:");
    fflush(stdin);
    gets(book.bookAuthor);
    book.allStock = 1;
    book.presentStock = 1;
    printf("编号:%d\n书名:%s\n作者:%s\n",book.bookNum,book.bookName, book.bookAuthor);
    //暂时先根据序号去搜索
    SearchBTree(t, book.bookNum, r);
    //如果tag为0说明图书不存在,则此时应该插入图书
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        wirteFile(r);
        printf("添加成功,按任意键返回\n");
        getch();//不回显函数
    } else {
        //图书的数目加1
    }
}

/**
* function:查找图书。
* params:B树,图书的序列号
*/
result SearchBook(BTree t) {
    int bookSerial;
    result res;

    system("cls");
    printf("请输入你要查找书的序号:");
    scanf("%d", &bookSerial);
    if(bookSerial <= 0) {
        //输入出错返回出错的信息
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
            printf("查找失败\n");
        }

//        printf("%s", res.pt->key[res.i].bookName);
    }
    printf("按任意键返回");
	getch();//不回显函数
    return res;
}


/**
* function:删除图书。
* params:B树
*/
void deleteBook(BTree p) {
    int bookSerial;
    result res;

    system("cls");
    printf("请输入你要删除书的序号:");
    scanf("%d", &bookSerial);
    system("cls");
    if(bookSerial <= 0) {
        //输入出错返回出错的信息
        res.pt = NULL;
        res.i = 0;
        printf("你的输入有误\n");
        Sleep(5000);
    } else {
        if(SearchBTree(p, bookSerial, res)) {
            DeleteKey(p, res.i);
            printf("你删除的图书序号为:%d,书籍名称为:%s\n", res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName);
            printf("删除成功\n");
        } else {
            printf("很抱歉你输入的书籍不存在\n");
        }
    }
    printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:图书总览。
* params:B树
*/
void ReadAllBook() {

}


