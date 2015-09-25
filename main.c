/***********************************************************
 *  ファイル名： main.c
 * 　作成日時： 2015/08/29
 * 　　　機能： FreeRTOS動作確認テスト用メインファイル
 ***********************************************************/

/***********************************************************
 * ヘッダファイル
 ***********************************************************/
#include <xc.h>
#include "./FreeRTOS_Source/include/FreeRTOS.h"
#include "./FreeRTOS_Source/include/task.h"

/***********************************************************
 * コンフィギュレーション設定
 ***********************************************************/
/* Fosc = 7.37[MHz]
 * Fcy  = Fosc / 4
 *      = 1.8425[MHz]
 */
// FOSC
#pragma config FOSFPR = FRC             // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_27         // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

/***********************************************************
 * 関数プロトタイプ
 ***********************************************************/
void vTask1( void *pvParameters);
void vTask2( void *pvParameters);
void vTask3( void *pvParameters);

/***********************************************************
 * メイン関数
 ***********************************************************/
int main(void){
    /* IO設定 */
    TRISF = 0x00;   /* すべてのRFポートを出力に */
    PORTF = 0x00;   /* PORTFを初期化 */
    LATF  = 0x38;   /* RF3、4、5消灯 */
    

    /* タスク作成 */
    xTaskCreate( vTask1, "T1", 100, NULL, 1, NULL );
    xTaskCreate( vTask2, "T2", 100, NULL, 1, NULL );
    xTaskCreate( vTask3, "T3", 100, NULL, 1, NULL );
    vTaskStartScheduler();
    
    while(1){
    }

    return 0;
}

/***********************************************************
 * タスク1関数
 ***********************************************************/
void vTask1( void *pvParameters){
    while(1){
        LATFbits.LATF3 = ~LATFbits.LATF3;
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

/***********************************************************
 * タスク2関数
 ***********************************************************/

void vTask2( void *pvParameters){
    while(1){
        LATFbits.LATF4 = ~LATFbits.LATF4;
        vTaskDelay(200 / portTICK_RATE_MS);
    }
}

/***********************************************************
 * タスク3関数
 ***********************************************************/

void vTask3( void *pvParameters){
    while(1){
        LATFbits.LATF5 = ~LATFbits.LATF5;
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}
