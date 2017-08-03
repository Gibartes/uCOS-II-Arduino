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

OS_EVENT  *sema;                                                         /* Semaphore Event Kernel Object */
int       max_blink  = 524700;
int       blink      = 0;

/***************************************************
 *                    Prototypes
 ***************************************************/

void      LED_ON(void);                                                 /* Led Off시키는 Task */
void      LED_OFF(void);                                                /* Led On시키는  Task */

/***************************************************
 *                    Main
 ***************************************************/

void setup() {
    Serial.begin(9600);                                                /* Use serial port for control (board rate : 9600) */
    pinMode(LED_OUT, OUTPUT);                                           /* Digital Pin 출력 설정 */
    Serial.println("[DBG] : Initiailize uCOS");
    OSInit();                                                           /* uCOS 초기화 */
    Serial.println("[DBG] : Create two tasks");
    OSTaskCreate(LED_ON, NULL,TASK1_STK,task1_prio);                    /* led_on  task 생성 */
    OSTaskCreate(LED_OFF,NULL,TASK2_STK,task2_prio);                    /* led_off task 생성 */
    Serial.println("[DBG] : Done. OS starts now.");
    OSStart();                                                          /* uCOS 시작  */
    Serial.println("[DBG] : Shutdown");
}

/***************************************************
 *                    Functions
 ***************************************************/

void LED_ON(void *arg){
    INT8U err = 0;
    sema = OSSemCreate(1);                                              /* 세마포어 생성 */
    while(1){
        OSSemPend(sema,5000,&err);                                    /* 세마포어 획득시까지 대기 */
        Serial.println("[DBG] : get semaphore at led_on");
        digitalWrite(LED_OUT, HIGH);
        OSSemPost(sema);                                              /* 세마포어 반납 */
        OSTimeDlyHMSM(0,0,5,0);
        if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {      /* 종료 요청받았는지 확인 */
            Serial.println("[DBG] : task1 shutdown");
            OSTaskDelReq(task2_prio);                                 /* 더이상 OFF 시킬 필요 없으므로 led_off task 종료 */
            OSTaskDel(OS_PRIO_SELF);}
   }
}

void LED_OFF(void *arg){
    INT8U err = 0;
    while(1){
        OSSemPend(sema,5000,&err);                                    /* 세마포어 획득시까지 대기 */
        Serial.print("[DBG] : get semaphore at led_off >> Rest count :");
        Serial.println(max_blink-blink);                             /* 남은 카운트 */
        digitalWrite(LED_OUT, LOW);
        blink++;
        if(blink >= max_blink){                                      /* max_blink만큼 blink 하면 ... */
          OSTaskDelReq(task1_prio);                                  /* LED ON TASK 종료요청 */
          if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ) {
              Serial.println("[DBG] : task2 shutdown");             /* LED는 꺼진 상태로 종료       */
              OSSemPost(sema);                                       /* 종료전 세마포어 자원 반납    */
              OSTaskDel(OS_PRIO_SELF);}                              /* 여기서 LED_OFF Task 종료됨   */
          Serial.println("[DBG] : send a request to led_on task");
        }
        OSSemPost(sema);                                             /* 세마포어 반납 */
        OSTimeDlyHMSM(0,0,5,0);
   }
}

/***************************************************
 *                    Fin
***************************************************/
void loop() {/* do nothing */}
