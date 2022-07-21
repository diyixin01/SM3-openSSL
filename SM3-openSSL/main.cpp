#include <iostream>
#include "sm3/sm3.h"
#include <time.h>
using namespace std;
typedef unsigned char uchar;
void print_Hashvalue(unsigned char buf[],int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%02x",*(buf + i));
    }
    printf("\n");
}

void timetest()
{
    clock_t start,end;//定义clock_t变量
    uchar input[64] = {0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
                        0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
                        0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
                        0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
                        0xaa,0xaa,0xaa,0xaa};
    int64_t t = 1000000; 
    SM3_CTX SMC;
    ossl_sm3_init(&SMC);
    unsigned char md[SM3_DIGEST_LENGTH] = { 0 };
    start = clock();  //开始时间
    for(int i=0;i<t;i++)
    {
        ossl_sm3_update(&SMC, input, 64);
        ossl_sm3_final(md, &SMC);
    }
    end = clock();   //结束时间
    cout<<"对64字节的数据做"<<t<<"次SM3，花费时间：time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;  //输出时间（单位：ｓ）
    cout<<"平均每秒做"<<t/(double(end-start)/CLOCKS_PER_SEC)<<"次SM3"<<endl;
}

int main()
{
    timetest();
    SM3_CTX SMC;
    ossl_sm3_init(&SMC);
    unsigned char md[SM3_DIGEST_LENGTH] = { 0 };

    // const unsigned char Data[1024] = "Hello World";
    // printf("input message:%s\n",Data);
    // ossl_sm3_update(&SMC, Data, strlen((const char *) Data));
    // ossl_sm3_final(md, &SMC);
    // printf("output hash value:");
    // for (int i = 0; i < SM3_DIGEST_LENGTH; i++) {
    //     printf("%02x ", *(md + i));
    // }
#  define HOST_c2l(c,l)  (l =(((unsigned long)(*((c)++)))<<24),          \
                         l|=(((unsigned long)(*((c)++)))<<16),          \
                         l|=(((unsigned long)(*((c)++)))<< 8),          \
                         l|=(((unsigned long)(*((c)++)))    )           )
#  define HOST_l2c(l,c)  (*((c)++)=(unsigned char)(((l)>>24)&0xff),      \
                         *((c)++)=(unsigned char)(((l)>>16)&0xff),      \
                         *((c)++)=(unsigned char)(((l)>> 8)&0xff),      \
                         *((c)++)=(unsigned char)(((l)    )&0xff),      \
                         l)

    // unsigned char a[4]={0x12,0x34,0x56,0x78};
    // unsigned char* data = a;
    // unsigned int b;
    // (void)HOST_c2l(data,b); 
    // char* p =(char*)&b;
    // printf("%x\n",b);
    // printf("%x %x %x %x\n",*(p),*(p+1),*(p+2),*(p+3));
    // data = a;
    // b= *(int*)a;
    // printf("%x\n",b);
    // unsigned char a[4]={0x12,0x34,0x56,0x78};
    // unsigned char* data = a;
    // unsigned int b= 0x12345678;
    // (void)HOST_l2c(b,data); 
    // printf("%x %x %x %x\n",*(data),*(data-1),*(data-2),*(data-3));
    // string myinput;
    // getline(cin,myinput);
    // cout<<myinput.c_str()<<endl;

    // ossl_sm3_update(&SMC, myinput.c_str(), myinput.length());
    // ossl_sm3_final(md, &SMC);

    // print_Hashvalue(md,SM3_DIGEST_LENGTH);
    return 0;
}

