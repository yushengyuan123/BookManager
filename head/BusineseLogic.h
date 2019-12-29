void AddBook(BTree t, result r);
void menu(BTree p, result res);
void deleteBook(BTree p);
KeyType splitWhiteSpace(char str[]);
result SearchBook(BTree t);
void ReadAllBookUI();
void ReadAllBook(BTree p);
void BorrorBook(BTree p);
void QueryStuBook(BTree p);
void ReturnBook(BTree p);
//void AfterAddWriteInFile(result res, int isTheSame);
//char *ConcatStr(result r);
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
		printf("|     2.借阅图书      |\n");
		printf("|     3.删除图书      |\n");
		printf("|     4.图书查询      |\n");
		printf("|     5.图书总览      |\n");
		printf("|     6.借阅查看      |\n");
		printf("|     7.归还图书      |\n");
		printf("|     8.退出软件      |\n");
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
//            case '8':over();break;
//		    default :break;
        }
}

/**
* function:看某一本图书UI。
* params:
*/
void ReadSomeBookInfo(result res)   //图书总览
{
    system("cls");
	printf("--------------------------------------------------------------------\n");
	printf("书编号        书名        作者名        可借数量        总数量\n");
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
* function:图书总览UI。
* params:
*/
void ReadAllBookUI() {
    system("cls");
	printf("--------------------------------------------------------------------\n");
	printf("书编号        书名        作者名        可借数量        总数量\n");
	printf("--------------------------------------------------------------------\n");
}

/**
* function:初始化书库。
* params:搜索结果
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
        printf("文件打开失败\n");
        Sleep(3000);
    }
    while(!feof(out))
    {
        flag = fgetc(out);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //加上最后一行
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
* function:图书总览。
* params:B树
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
        printf("文件打开失败\n");
        Sleep(3000);
    }
    while(!feof(out))
    {
        flag = fgetc(out);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //加上最后一行
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
            printf("  %d           %s         %s           %d               %d\n",res.pt->key[res.i].bookNum, res.pt->key[res.i].bookName, res.pt->key[res.i].bookAuthor, res.pt->key[res.i].presentStock, res.pt->key[res.i].allStock);
        }
    }
    printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:遇到空格切开。
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
* function:向文件中读取图书列表序号存入数组中(用于图书总览)。
* params:搜索结果
*/
char *ReadSerial() {
    FILE *fin = fopen("bookSerial.txt", "r"); /*假设文件名为file.txt*/
    int flag = 0, file_row = 0, count = 0;
    //获取文件中的行数
    while(!feof(fin))
    {
        flag = fgetc(fin);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1; //加上最后一行
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
* function:比较两个字符串是否相同。
* params:字符串1,字符串2
*/
int CompareStr(char *str1, char *str2) {
    if (strcmp(str1, str2) == 0) {
	    return 1;
	}
	return 0;
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
    book.bookName = (char *)malloc(sizeof(char) * 50);
    gets(book.bookName);
    printf("请输入图书的作者:");
    book.bookAuthor = (char *)malloc(sizeof(char) *50);
    fflush(stdin);
    gets(book.bookAuthor);
    book.allStock = 1;
    book.presentStock = 1;
    printf("你输入的信息:编号:%d  书名:%s  作者:%s\n",book.bookNum,book.bookName, book.bookAuthor);
    //暂时先根据序号去搜索
    SearchBTree(t, book.bookNum, r);
    //如果tag为0说明图书不存在,则此时应该插入图书
    if(r.tag == 0) {
        InsertBTree(t, book, r.pt, r.i);
        printf("添加成功\n");
        //添加完后写入文件
//        AfterAddWriteInFile(r, 0);
    } else {
        //此时说明这本树的位序已经有了,数目加1
        if(CompareStr(book.bookName, r.pt->key[r.i].bookName) && CompareStr(book.bookAuthor, r.pt->key[r.i].bookAuthor)) {
            r.pt->key[r.i].allStock++;
            r.pt->key[r.i].presentStock++;
            printf("添加成功\n");
            //添加完后写入文件
//            AfterAddWriteInFile(r, 1);
        } else {
            printf("插入失败,输入与已有书籍信息不匹配\n");
        }
    }
    printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:添加完图书还要写入文件中。
* params:B树,搜索结果
*/
//void AfterAddWriteInFile(result r, int isTheSame) {
//    FILE *out;
//    int i;
//    int line, c, c1, cnt;
//    out = fopen("bookList.txt","r+");
//    char str1[60];
////    char *temp = ConcatStr(r);
//
//    //获取目标字符串的行号
//    while(fgets(temp,sizeof(temp),out))//逐行循环读取文件，直到文件结束
//	{
//		line++;
//		if(strstr(temp,temp))  //检查字符串是否在该行中，如果在，则输出该行
//		{
//		    printf("目标字符串所在行为:%d\n",line);
//            break;
//		}
//	}
//
//    if(out == NULL){
//        exit(-1);
//    }
//    if(isTheSame == 0) {
//        fprintf(out,"\n%d %s %s %d %d", r.pt->key[r.i].bookNum, r.pt->key[r.i].bookName, r.pt->key[r.i].bookAuthor, r.pt->key[r.i].presentStock, r.pt->key[r.i].allStock);
//    } else {
////        //获取目标字符串的行号
////        while(fgets(temp,sizeof(temp),out))//逐行循环读取文件，直到文件结束
////        {
////            line++;
////            if(strstr(temp,temp))  //检查字符串是否在该行中，如果在，则输出该行
////            {
////                printf("目标字符串所在行为:%d\n",line);
////                break;
////            }
////        }
////
////        //检测到指定行开头的指针位置，将其赋值给c
////        c = ftell(out);
////        //遍历一遍目标行，确定该行长度，同时for循环结束时c1为该行末尾的指针位置
////        while(fgetc(out)!='\n')
////        {
////            c1=ftell(out);
////        }
////        //将文件指针移到目标行的行首
////        fseek(out,c,SEEK_SET);
////        //得到目标行的长度
////        cnt=c1-c;
////        //for循环插入想要修改的内容
////        for(i=0;i<cnt;i++)
////        {
////            fputc(temp,out);
////        }
//
//    }
//
//    fclose(out);
//}

/**
* function:将返回结果拼接成字符串。
* params:搜索结果
*/
//char *ConcatStr(result r) {
//    printf("我进来了\n");
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
//    printf("这个字符串为:%s\n", concanStr);
//    return concanStr;
//}

/**
* function:删除文件中的某一行。
* params:无
*/
//void deleteFile(result r) {
//    FILE* fp = fopen("bookList.txt", "r");
//    char *targetStr = (char *)malloc(sizeof(char)); strcpy(targetStr, "2 JavaScript 黄煜淇 1 1");
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
//            deleteFile(res);
        } else {
            printf("很抱歉你输入的书籍不存在\n");
        }
    }
    printf("按任意键返回");
	getch();//不回显函数
}


/**
* function:借阅图书。
* params:B树
*/
void BorrorBook(BTree p) {
    int bookSerial;
    result r;
    char *studentName;
    int deadline;

    system("cls");
    printf("请输入借阅图书的序号:");
    scanf("%d", &bookSerial);
    printf("请输入借阅人的姓名:");
    fflush(stdin);
    studentName = (char *)malloc(sizeof(char) * 50);
    gets(studentName);
    printf("请输入借阅的天数:");
    scanf("%d", &deadline);

    printf("你输入的信息:借阅书籍编号:%d  借书人姓名:%s  借阅天数:%d\n", bookSerial, studentName, deadline);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("借阅失败,抱歉你借阅的图书不存在\n");
    } else if(r.pt->key[r.i].presentStock == 0){
        printf("借阅失败,抱歉图书已经被借阅完\n");
    } else {
        //借阅成功,目前存量减去1
        int present = --(r.pt->key[r.i].presentStock);
        int all = r.pt->key[r.i].allStock;
        //记录学生借阅日期
        r.pt->stu[r.i].deadline[all - present] = deadline;
        r.pt->stu[r.i].StudentName[all - present] = (char *)malloc(sizeof(char) * 10);
        strcpy(r.pt->stu[r.i].StudentName[all - present], studentName);
        SearchBTree(p, bookSerial, r);
        printf("借阅成功");
    }
    printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:查看借阅学生借阅图书。
* params:B树
*/
void QueryStuBook(BTree p) {
    int bookSerial;
    result r;
    int k;

    system("cls");

    printf("请输入借阅图书的序号:");
    scanf("%d", &bookSerial);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("查询失败,抱歉你查询的图书不存在\n");
    } else if(r.pt->key[r.i].allStock == r.pt->key[r.i].presentStock){
        printf("查询成功,目前该图书尚未有人借阅\n");
    } else {
        printf("借阅书籍:%s\n", r.pt->key[r.i].bookName);
        for(k = 1; k < r.pt->key[r.i].allStock - r.pt->key[r.i].presentStock + 1; k++) {
            printf("借阅人姓名:%s,借阅天数:%d\n", r.pt->stu[r.i].StudentName[k], r.pt->stu[r.i].deadline[k]);
        }
    }
    printf("按任意键返回");
	getch();//不回显函数
}

/**
* function:归还图书。
* params:B树
*/
void ReturnBook(BTree p) {
    int bookSerial;
    char *Name;
    result r;
    int k;

    system("cls");
    printf("请输入归还人的名字:");
    fflush(stdin);
    Name = (char *)malloc(sizeof(char) * 20);
    gets(Name);
    printf("\n请输入归还图书的序号:");
    scanf("%d", &bookSerial);

    SearchBTree(p, bookSerial, r);
    if(r.tag == 0) {
        printf("归还失败,抱歉你归还的图书不存在\n");
    } else if(r.pt->key[r.i].allStock == r.pt->key[r.i].presentStock){
        printf("查询失败,目前该图书尚未有借阅记录\n");
    } else {
        printf("归还书籍:%s\n", r.pt->key[r.i].bookName);
        int present = ++(r.pt->key[r.i].presentStock);
        int all = r.pt->key[r.i].allStock;
        r.pt->stu[r.i].StudentName[all - present] = NULL;
        r.pt->stu[r.i].deadline[all - present] = 0;
        printf("归还成功");

    }
    printf("按任意键返回");
	getch();//不回显函数
}



