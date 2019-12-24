void AddBook(BTree t, result r);
void menu(BTree p, result res);
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
//		    case '3':del_book();break;
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
	printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:增加图书。
* params:B树,搜索结果
*/
void AddBook(BTree t, result r) {
    int bookSerial;

    KeyType book;

    system("cls");
    printf("请输入图书的编号,书名,作者(中间使用逗号隔开)\n");

    scanf("%d %s %s", &book.bookNum, book.bookName, book.bookAuthor);
    printf("%s", book.bookAuthor);

    book.allStock = 1;
    book.presentStock = 1;
    //暂时先根据序号去搜索
    SearchBTree(t, book.bookNum, r);
    //如果tag为0说明图书不存在,则此时应该插入图书
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        printf("添加成功,两秒后返回\n");
        Sleep(2000);
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

    printf("请输入你要查找书的序号:");
    scanf("%d", &bookSerial);
    if(bookSerial <= 0) {
        //输入出错返回出错的信息
        res.pt = NULL;
        res.i = 0;
    } else {
        if(SearchBTree(t, bookSerial, res)) {
            printf("查找成功\n");
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
    return res;
}


