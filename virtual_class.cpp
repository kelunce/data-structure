// 64位下
#include <stdio.h>

typedef int(*VirtualFun)(void);

class B1{
    public:
        int b1;
        // 虚函数表的地址就存在该类对象内存的开始处
        // 所以会影响b1成员在内存处于Vtable指针的后边
        // 不管有多少个，只有一个函数表指针
        virtual int  B1_FUN1() {printf("B1_FUN1\n");}; // 要求偏移是8个字节（起始地址为8N）
        virtual int  B1_FUN2() {printf("B1_FUN2\n");};
        // 静态的成员，或者普通的成员函数不占对象内存
        int B1_NORMAL_FUN(){printf("B1_NORMAL_FUN\n");};
        char b11;
};

typedef int(B1::*B1VirtualFun)(void);

class B2{
    int b2;
    virtual int  B2_FUN1(){ printf("B2_FUN1\n");};
    virtual int  B2_FUN2(){ printf("B2_FUN2\n");};
};

class B3: public B1,B2{
    int b3;
    // 有两个基类，有两个虚函数表(如基数没有虚函数，就不会有对应的表)
    virtual int  B1_FUN1() {printf("B3 B1_FUN1\n");};
    virtual int  B2_FUN2() {printf("B3 B2_FUN2\n");};
};

//虽然是不同的对象实例，但是指向的函数是同一个。无论是否虚函数
void testFuncAddr(B1 *b1)
{
    B1VirtualFun pfunc = &B1::B1_NORMAL_FUN;
    printf("虚函数表起始地址：%p, B1_NORMAL_FUN地址:%p\n", b1, pfunc);
    (b1->*pfunc)();
    
    for(int i = 0;i < 2; i++){
        VirtualFun fun = (VirtualFun)*((long long*)*(long long*)b1 + i); 
        printf("B1 virtual func idx:%d addr:%p\n", i, fun);
        fun();
    }
}

int main()
{    
    printf("size ptr=%d, sizeof(B1)=%d, sizeof(B2)=%d, sizeof(B3)=%d \n", sizeof(int*), sizeof(B1), sizeof(B2), sizeof(B3));
    B1 *b1 = new B1();
    testFuncAddr(b1);
    printf("B1::b1 的内存偏移量:%d\n", (long long)&(b1->b1) - (long long)b1);
    printf("B1::B11的内存偏移量:%d\n", (long long)&(b1->b11) - (long long)b1);

    B1 *b11 = new B1();
    testFuncAddr(b11);
    printf("------------------\n");
    B1 *b3 = new B3();
    b3->B1_FUN1();// B3 B1_FUN1
    VirtualFun b3fun = (VirtualFun)(*(long long*)*((long long*)b3+2));
    b3fun();
    return 0;
}

