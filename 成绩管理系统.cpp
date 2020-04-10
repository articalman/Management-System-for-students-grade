
#include <bits/stdc++.h> // 万能头文件
using namespace std;
int amount = 0; // 人数
struct student{
    string name; //姓名
    double num; //学号
    double Math;
    double Chineses;
    double English;
    double Major; // 专业课成绩
    double sum;   // 新增sum字段 ， 返回成绩和
    student *next;
};

void InitList(student *&L); // 链表初始化
inline void Next(student *&p, student *&pr);
// 内联函数，方便重复使用链表遍历的代码
inline void forDelete(student *&p , student *&pr , int &flag);
// 内联函数，为删除函数提供删除多样性
void Ins(student *&L, int n);       // 插入函数
void Display(student *L);           // 输出函数
void Destroy(student *&L);          // 析构函数，回收结点，避免空间浪费
void Delete(student *&L, double num , int n);    // 删除函数，根据学号/成绩
void Delete(student *&L, string s);    //删除函数重载，根据姓名删除
void show(student *p); //配合modify函数，显示修改后的结果
void modify(student *&L, double n);    // 修改函数，用于修改记录的值
void IsExcellent(student *&L);    // 查找各科>90的优秀学生 并输出
void PassOrnot(student *&L);     // 显示补考名单并输出
void exchange(student *&p, student *&pr);  // 交换函数，搭配sort函数使用 
void Sort(student *&L, int n); // 排序函数（按总分排序）n=1升序 n=0降序
void Menu();  // 打印系统界面
void about();  //显示关于页面

int main(){
    student *head;
    InitList(head);
    system("title 学生成绩管理系统V2.0");//设置控制台标题
    system("color 0B");// 设置控制台颜色，背景黑色，字体蓝色
    int n, m;
    
    while (1){ //进入系统，执行操作
        Menu();
        cout << "请输入您要进行的操作：";
        cin >> m;
        switch (m){
            case 0:{
                system("cls");
                about();
                break;
            }
            case 1:{
                system("cls");
                cout << "请输入新增人数： ";
                cin >> n;
                if (n < 0){
                    cout << "\n人数有误！\n";
                }else{
                    Ins(head, n);
                    cout << "\n录入后结果" << endl;
                    Display(head);
                }
                break;
            }
            case 2:{ // 新增选择删除的方式
                system("cls");
                cout << "请选择删除的方式：\n";
                cout << "1.姓名\n";
                cout << "2.学号\n";
                cout << "3.语文\n";
                cout << "4.数学\n";
                cout << "5.英语\n";
                cout << "6.专业课\n";
                cout << "7.总成绩" << endl;
                cin >> n;
                if(n == 1){ // name是string类型的，需要函数重载
                    string s; 
                    cout << "好的，需要您输入对应的学生姓名：";
                    cin >> s;
                    Delete(head,s);
                }else if(n > 1 && n <= 6){
                    double n1;
                    cout << "好的，需要您输入对应的学生学号或成绩：";
                    cin >> n1;
                    Delete(head,n1,n);
                }else{
                    cout << "\n删除失败，请输入有效的数据\n";
                }
                cout << "删除后结果为：" << endl;
                Display(head);
                break;
            }
            case 3:{
                system("cls");
                cout << "请输入要修改的学生学号：";
                cin >> n;
                modify(head, n);
                break;
            }
            case 4:{
                system("cls");
                Display(head);
                break;
            }
            case 5:{
                system("cls");
                PassOrnot(head);
                break;
            }
            case 6:{
                system("cls");
                IsExcellent(head);
                break;
            }
            case 7:{
                system("cls");
                cout << "请输入排序方式：\n";
                cout << "1升序 0降序\n";
                cin >> n;
                if(n != 0 && n != 1)
                    break;
                Sort(head,n);
                Display(head);
                break;
            }
            default:{
                exit(0);
            }
        }
        char ch;
        cout << endl;
        cout << "----------------------------------------------------------\n";
        cout << "                      是否继续(y/n)：";
        cin >> ch;
        if (ch == 'y'){
            system("cls");
            continue;
        }
        else
            exit(0); // 退出循环，程序结束
    }
    Destroy(head);
    system("pause");
    return 0;
}

void InitList(student *&L){
    L = new student;
    L->next = NULL;
}
inline void Next(student *&p, student *&pr){
    pr = p; // 内联函数，方便重复使用链表遍历的代码
    p = p->next;
}
inline void forDelete(student *&p , student *&pr ,int &flag){
    pr->next = p->next; // 将后一个结点连接到前一个结点
    //delete[]p;
    amount--;
    flag = 1;
}
void Ins(student *&L, int n){         // 采用尾插法实现
    student *p = L->next, *pr = L; //pr赋初值，避免插入首结点的时候循环不会执行
    while (p != NULL){
        Next(p, pr);
    } // 定位到链表末尾
    while (n--){
        student *p1 = new student;
        string name;
        double chinese, math, english, major,num;
        cout << "请输入学生信息 ：" << endl;
        cout << "姓名    学号    语文    数学    英语   专业课" << endl;
        cin >> name >> num >> chinese >> math >> english >> major;
        if (chinese < 0 || chinese > 100 || math < 0 || math > 100 ||
            english < 0 || english > 100 || major < 0 || major > 100)
        {  // 增加输入限定条件 0<成绩<100 
            cout << "\n请确保插入数据的正确性！\n";
            break;
        }
        amount++;

        p1->name = name;
        p1->num = num;
        p1->Chineses = chinese;
        p1->English = english;
        p1->Math = math;
        p1->Major = major;
        p1->sum = p1->Chineses + p1->English + p1->Major + p1->Math;

        pr->next = p1; // 和前面的节点相连
        //pr = p1;   // 指向当前节点
        pr = pr->next; //指向后继结点
        p1->next = NULL;
        puts(""); //输出换行控制格式
    }
}
void Display(student *L){
    if (L->next == NULL){
        cout << "成绩管理系统为空" << endl;
    }
    while (L->next != NULL){
        L = L->next;
        cout << "姓名    学号    语文    数学    英语   专业课    总成绩" << endl;
        cout << L->name;
        printf("\t%.lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t\n", L->num, L->Chineses, L->Math, L->English, L->Major,L->sum);
    }
    cout << "\n表中人数共计：" << amount << "人\n";
}
void Destroy(student *&L){
    student *p = L->next, *pr = L;
    while (p != NULL){
        Next(p, pr);
        delete[] pr;
    }
    //delete[] p;
}
void Delete(student *&L, double num , int n){
    // num表示数据的值  根据n来选择执行哪步判断
    student *p = L->next, *pr = L;
    int flag = 0; // 判断标志
    if (p == NULL)
        cout << "\n学生表中没有任何学生记录！\n";
    else{
        while (p != NULL){
            switch (n){
                case 2:{
                    if (p->num == num){  
                        forDelete(p,pr,flag);
                        break; // break只能在表达式内，不能放入内联函数
                    }
                }
                case 3:{
                    if (p->Chineses == num){
                        forDelete(p,pr,flag);
                        break; 
                    }
                }
                case 4:{
                    if (p->Math == num){
                        forDelete(p, pr,flag);
                        break;
                    }
                }
                case 5:{
                    if (p->English == num){
                        forDelete(p, pr, flag);
                        break;
                    }
                }
                case 6:{
                    if (p->Major == num){
                        forDelete(p, pr, flag);
                        break;
                    }
                }
                case 7:{
                    if (p->sum == num){
                        forDelete(p , pr , flag);
                        break;
                    }
                }
                default:{ //其实在参数传进函数前就已经判断过了，可以不用写
                    break;
                }
            }
            Next(p, pr); // 继续指向后继节点
        }
    }
    if (p == NULL && flag == 0)
        cout << "抱歉，查无此人" << endl;
}
void Delete(student *&L, string s){
    student *p = L->next, *pr = L;
    if (p == NULL)
        cout << "\n学生表中没有任何学生记录！\n";
    else
    {
        while (p != NULL)
        {
            if (p->name == s)
            {
                pr->next = p->next; // 将后一个结点连接到前一个结点
                //delete[]p;
                amount--;
                break;
            }
            Next(p, pr); // 继续指向后继节点
        }
    }
    if (p == NULL)
        cout << "抱歉，查无此人" << endl;
}
void show(student *p){ // 打印修改后的结果
    cout << "\n修改成功!\n修改后的成绩为：" << endl;
    cout << "姓名    学号    语文    数学    英语   专业课    总成绩" << endl;
    cout << p->name;
    printf("\t%.lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t\n", p->num, p->Chineses, p->Math, p->English, p->Major,p->sum);
}
void modify(student *&L, double n){
    student *p = L->next, *pr = L;
    while (p != NULL){
        if (p->num == n){
            cout << "\n学号——>n\nChinese——>c\nMath——>m\nEnglish——>e\nMajor——>M" << endl;
            cout << "\n请选择修改的属性：";
            char ch;
            double grade,num;
            cin >> ch;
            cout << "请输入修改后的成绩/学号：";
            if (ch == 'n'){
                cin >> num;
            }else{
                cin >> grade;
            }
            switch (ch){
                case 'n':{
                    p->num = num;
                    show(p);
                    break;
                }
                case 'c':{
                    p->Chineses = grade;
                    show(p); //调用函数打印修改后的结果
                    break;
                }
                case 'm':{
                    p->Math = grade;
                    show(p);
                    break;
                }
                case 'e':{
                    p->English = grade;
                    show(p);
                    break;
                }
                case 'M':{
                    p->Major = grade;
                    show(p);
                    break;
                }
                default:{
                    cout << "\n修改失败，请输入有效的键值！" << endl;
                    break;
                }
            }
        }
        Next(p, pr);
    }
}
void IsExcellent(student *&L){
    student *p = L->next, *pr = L;
    int flag = 0;
    while(p != NULL){
        if(p->Chineses >= 90 && p->English >= 90 && p->Major >= 90 && p->Math >= 90){
            cout << "学号为" << p->num << "的" << p->name << "同学是一个尖子生\n";
            printf("语文：%.2lf\t数学：%.2lf\t英语：%.2lf\t专业课：%.2lf\t总成绩:%.2lf\t\n", p->Chineses, p->Math, p->English, p->Major,p->sum);
            flag = 1;
        }
        Next(p,pr);
    }
    if(flag == 0)
        cout << "一个都没有吗？这届学生也太难带了吧\n";
}
void PassOrnot(student *&L){
    student *p = L->next, *pr = L;
    int flag = 1; // 判断学生不及格的标记
    while(p != NULL){
        if(p->Chineses < 60){
            flag = 0;
            cout << p->name << "的语文成绩是：" << p->Chineses << ",不合格\n";
        }
        if(p->English < 60){
            flag = 0;
            cout << p->name << "的英语成绩是：" << p->English << ",不合格\n";
        }
        if(p->Major < 60){
            flag = 0;
            cout << p->name << "的专业课成绩是：" << p->Major << ",不合格\n";
        }
        if(p->Math < 60){
            flag = 0;
            cout << p->name << "的数学成绩是：" << p->Math << ",不合格\n";
        }
        Next(p, pr);
    }
    if(p == NULL && flag == 1)
        cout << "这批学生都很优秀，再接再励！\n";
}
void exchange(student *&p , student *&pr){
    student *t = new student;
    t->next = NULL;
    t->Chineses = p->Chineses;
    t->English = p->English;
    t->Major = p->Major;
    t->Math = p->Math;
    t->name = p->name;
    t->num = p->num;
    t->sum = p->sum;

    p->Chineses = pr->Chineses;
    p->English = pr->English;
    p->Major = pr->Major;
    p->Math = pr->Math;
    p->name = pr->name;
    p->num = pr->num;
    p->sum = pr->sum;

    pr->Chineses = t->Chineses;
    pr->English = t->English;
    pr->Major = t->Major;
    pr->Math = t->Math;
    pr->name = t->name;
    pr->num = t->num;
    pr->sum = t->sum;

    //delete [] t; t已经指向了别的地方，会由系统释放，手动释放会造成多次释放导致出错
}
void Sort(student *&L , int n){  // 采用冒泡排序
    student *pr = L->next , *p; //跳过头节点，从首节点开始
    while(pr != NULL){
        p = pr->next; // p始终指向pr的下个节点 
        while (p != NULL){  //依次和后继节点比较
            if(n == 1){   // 升序
                if(pr->sum > p->sum){
                    exchange(pr,p);
                }
            }else if(n == 0){ //降序
                if(pr->sum < p->sum){
                    exchange(pr,p);
                }
            }
            p = p->next;
        }
        pr = pr->next;
    }
}
void Menu(){
    cout << "\n\n";
    cout << "\t\t\t\t欢迎使用成绩管理系统\n";
    cout << "\t*******************************************************************\n";
    cout << "\t*                        1.成绩录入                               *\n";
    cout << "\t*                        2.删除学生记录                           *\n";
    cout << "\t*                        3.修改学生记录                           *\n";
    cout << "\t*                        4.打印记录                               *\n";
    cout << "\t*                        5.显示补考名单                           *\n";
    cout << "\t*                        6.查找优秀学生                           *\n";
    cout << "\t*                        7.按成绩排序                             *\n";
    cout << "\t*                        *.退出系统                               *\n";
    cout << "\t*                        0.关于                                   *\n";
    cout << "\t*                                                                 *\n";
    cout << "\t*                                   								 *\n";
    cout << "\t*******************************************************************\n";
    cout << "请选择输入的方式" << endl;
    cout << "1.手动输入    2.文件输入\n";
    int f;
    cin >> f;
    if (f == 2) //如果输入2，从1.txt的文本中读入输入结果(需提前准备)
        freopen("1.txt", "r", stdin);
}

