#include<stdio.h>
#include "seqstack1.h"
typedef struct QueueBy2Stack
{
    SeqStact input;
    SeqStact output;
}QueueBy2Stack;

void QueueInit(QueueBy2Stack* q)
{
    if(q == NULL)
    {
        //非法操作
        return;
    }
    SeqStactInit(&q->input);
    SeqStactInit(&q->output);
}

void QueuePush(QueueBy2Stack* q,SeqStactType value)
{
    if(q == NULL)
    {
        //非法操作
        return;
    }
    //若output棧不为空，则需要将output棧中的元素全部出棧到input棧中，然后再进行后续操作
    while(1)
    {
        SeqStactType top;
        int ret=SeqStactTop(&q->output,&top);
        if(ret == 0)//空棧
        {
            break;
        }
        SeqStactPop(&q->output);
        SeqStactPush(&q->input,top);
       //SeqStactPop(&q->input);
    }
    SeqStactPush(&q->output,value);
    return;
}

void QueuePop(QueueBy2Stack* q)
{
    if(q == NULL)
    {
        //非法操作
        return;
    }
    while(1)
    {
        SeqStactType top;
        int ret=SeqStactTop(&q->input,&top);
        if(ret == 0)
        {
            break;
        }
        SeqStactPop(&q->input);
        SeqStactPush(&q->output,top);
    }
    SeqStactPop(&q->output);
}

int QueueTop(QueueBy2Stack* q,SeqStactType* value)
{
    if(q == NULL || value == NULL)
    {
        //非法操作
        return 0;
    } 
    while(1)
    {
        SeqStactType top;
        int ret=SeqStactTop(&q->input,&top);
        if(ret == 0)
        {
            break;
        }
        SeqStactPop(&q->input);
        SeqStactPush(&q->output,top);
    }
    return SeqStactTop(&q->output,value);
}

/***
 *
 *以下为测试代码

 *****/
#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void Test()
{
    TEST_HEADER;
    QueueBy2Stack queue;
    QueueInit(&queue);
    QueuePush(&queue,'a');
    QueuePush(&queue,'b');
    QueuePush(&queue,'c');
    QueuePush(&queue,'d');
    SeqStactType value;
    int ret;
    ret=QueueTop(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected a,actuall %c\n",value);
    QueuePop(&queue);
    QueuePop(&queue);
    ret=QueueTop(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected c,actuall %c\n",value);
    QueuePop(&queue);
    QueuePop(&queue);
    ret = QueueTop(&queue,&value);
    printf("ret expected 0,actuall %d\n",ret);
}
int main()
{
    Test();
    return 0;
}
