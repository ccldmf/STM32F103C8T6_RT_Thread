/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(B, 12)

#define THREAD_PRIORITY     25
#define THREAD_STACK_SIZE   512
#define THREAD_TIMESLICE    5

rt_thread_t tid1, tid2;

static void thread1_entry(void *parameter)
{
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(50);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(50);
    }
}

static void thread1_cleanup(struct rt_thread *tid)
{
    if (tid != tid1)
    {
        return ;
    }
    rt_kprintf("thread1 end\n");
    tid1 = RT_NULL;
}

static void thread2_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1)
   {
       //rt_kprintf("thread2 count: %d\n", count ++);
       count ++;
       rt_thread_mdelay(50);
   }
}

static void thread2_cleanup(struct rt_thread *tid)
{
    if (tid != tid2)
    {
        return ;
    }
    rt_kprintf("thread2 end\n");
    tid2 = RT_NULL;
}


void thread_sample_init()
{

    tid1 = rt_thread_create("t1",                                                   /* 线程1的名称是t1 */
                            thread1_entry, RT_NULL,                                 /* 入口是thread1_entry，参数是RT_NULL */
                            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);  /* 优先级为 25 */

    if (tid1 != RT_NULL)                                                            /* 如果获得线程控制块，启动这个线程 */
    {
        tid1->cleanup = thread1_cleanup;                                            /*thread1_cleanup在线程1退出后执行*/
        rt_thread_startup(tid1);
    }

    /* 创建线程2 */
    tid2 = rt_thread_create("t2",                                                   /* 线程2的名称是t2 */
                            thread2_entry, RT_NULL,                                 /* 入口是thread2_entry，参数是RT_NULL */
                            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)                                                            /* 如果获得线程控制块，启动这个线程 */
    {
        tid2->cleanup = thread2_cleanup;
        rt_thread_startup(tid2);
    }
}

int main(void)
{
    thread_sample_init();

    return RT_EOK;
}
