/***************************************************
 *                    Preprocessor
 ***************************************************/
/*  using uCOS-II to manage tasks */
#include <ucos_ii.h>

#define   LED_OUT     12      
#define   task1_prio  (INT8U)11
#define   task2_prio  (INT8U)34

/***************************************************
 *                    Globals
 ***************************************************/

OS_STK    TASK1_STK[64];
OS_STK    TASK2_STK[64];

OS_EVENT  *sema;                                                       /* Semaphore Event Kernel Object */
int       max_blink  = 524700;
int       blink      = 0;

/***************************************************
 *                    Prototypes
 ***************************************************/

void      LED_ON(void);                                                /* TASK, Led Off */
void      LED_OFF(void);                                               /* TASK, Led On  */

/***************************************************
 *                    Main
 ***************************************************/

void setup() {
    Serial.begin(9600);                                                /* Use serial port for control (board rate : 9600) */
    pinMode(LED_OUT, OUTPUT);                                          /* set Digital Pin to output */
    Serial.println("[DBG] : Initiailize uCOS");
    OSInit();                                                          /* initialize uCOS */
    Serial.println("[DBG] : Create two tasks");
    OSTaskCreate(LED_ON, NULL,TASK1_STK,task1_prio);                   /* create led_on task */
    OSTaskCreate(LED_OFF,NULL,TASK2_STK,task2_prio);                   /* create led_off task */
    Serial.println("[DBG] : Done. OS starts now.");
    OSStart();                                                         /* start uCOS */
    Serial.println("[DBG] : Shutdown");
}

/***************************************************
 *                    Functions
 ***************************************************/

void LED_ON(void *arg){
    INT8U err = 0;
    sema = OSSemCreate(1);                                            /* create Semaphore (in high priority task) */
    while(1){
        OSSemPend(sema,5000,&err);                                    /* wait until semaphore gets */
        Serial.println("[DBG] : get semaphore at led_on");
        digitalWrite(LED_OUT, HIGH);
        OSSemPost(sema);                                              /* return semaphore to OS */
        OSTimeDlyHMSM(0,0,5,0);
        if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {      /* check whether the task is requested shutdown */
            Serial.println("[DBG] : task1 shutdown");
            OSTaskDelReq(task2_prio);                                 /* 더이상 OFF 시킬 필요 없으므로 led_off task 종료 */
            OSTaskDel(OS_PRIO_SELF);}
   }
}

void LED_OFF(void *arg){
    INT8U err = 0;
    while(1){
        OSSemPend(sema,5000,&err);                                     /* wait until semaphore gets */
        Serial.print("[DBG] : get semaphore at led_off >> Rest count :");
        Serial.println(max_blink-blink);                               /* available counts */
        digitalWrite(LED_OUT, LOW);
        blink++;
        if(blink >= max_blink){                                        /* if no-available count, */
          OSTaskDelReq(task1_prio);                                    /* request shutdown to LED ON TASK */
          if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {
              Serial.println("[DBG] : task2 shutdown");                /* state : LED OFF       */
              OSSemPost(sema);                                         /* return semaphore before shutdown    */
              OSTaskDel(OS_PRIO_SELF);}                                /* Here, shutdown LED_OFF Task   */
          Serial.println("[DBG] : send a request to led_on task");
        }
        OSSemPost(sema);                                               /* return semaphore to OS */
        OSTimeDlyHMSM(0,0,5,0);
   }
}

/***************************************************
 *                    Fin
***************************************************/
void loop() {/* do nothing */}
