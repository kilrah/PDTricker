#include "stdio.h"
#include "CH552.H"

#include "Public\TIMER.H"
#include "Public\ADC.H"
#include "Public\GPIO.H"
#include "Public\DEBUG.H"

void led_all_set();    
void led_off(UINT8 value);
void led_set(UINT8 value, UINT8 blink);
UINT16 adc_read();
int pd_verify(UINT8 value);

enum {
    PD_5V = 0,
    PD_9V,
    PD_12V,
    PD_15V,
    PD_20V,
    PD_MAX,
};

unsigned int x=0;

sbit  KEY = P1^0;

sbit LED_5V  = P3^2;
sbit LED_9V  = P1^4;
sbit LED_12V = P1^5;
sbit LED_15V = P1^6;
sbit LED_20V = P1^7;

sbit CFG_1 = P3^3;
sbit CFG_2 = P3^4;
sbit CFG_3 = P3^5;


/* TX:  P3.1/PWM2/TXD */
/* RX:  P3.0/PWM1/RXD */
int pd_set(UINT8 value)
{
    switch (value) {
        case (PD_5V):
            CFG_1 = 1;
            CFG_2 = 0;
            CFG_3 = 0;
            break;
        case (PD_9V):
            CFG_1 = 0;
            CFG_2 = 0;
            CFG_3 = 0;
            break;
        case (PD_12V):
            CFG_1 = 0;
            CFG_2 = 0;
            CFG_3 = 1;
            break;
        case (PD_15V):
            CFG_1 = 0;
            CFG_2 = 1;
            CFG_3 = 1;
            break;
        case (PD_20V):
            CFG_1 = 0;
            CFG_2 = 1;
            CFG_3 = 0;
            break;
        default:
            break;
    }

    pd_verify(value);
    
    return 0;    
}


    
 /* compare with adc value */
int pd_verify(UINT8 value)
{
    UINT8 r = 0;

    /* 100K 510K */
    UINT16 adc_value;
    adc_value = adc_read();

    //printf("ADC_VALUE: %d (%ld mV)\n",(UINT16)adc_value, (((UINT32)(adc_value) * 20130)) / 256);

    switch (value) {
        case (PD_5V):
            if (adc_value >= 57 && adc_value <= 69) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case (PD_9V):
            if (adc_value >= 108 && adc_value <= 120) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case (PD_12V):
            if (adc_value >= 146 && adc_value <= 158) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case (PD_15V):
            if (adc_value >= 184 && adc_value <= 197) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case (PD_20V):
            if (adc_value >= 247 && adc_value <= 260) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        default:            
            break;
    }
    
    led_set(value, r);
    return r;
}

UINT16 count = 0;
UINT8 blink = 0;
UINT8 blink_value = PD_5V;

void led_all_set(BOOL value)
{
    LED_5V  = value;
    LED_9V  = value;
    LED_12V = value;
    LED_15V = value;
    LED_20V = value;
}

void led_off(UINT8 value)
{
    switch (value) {
        case (PD_5V):
            LED_5V = 0;
            break;
        case (PD_9V):
            LED_9V = 0;
            break;
        case (PD_12V):
            LED_12V = 0;
            break;
        case (PD_15V):
            LED_15V = 0;
            break;
        case (PD_20V):
            LED_20V = 0;
            break;
        default:
            break;
    }    
}

void led_set(UINT8 value, UINT8 mode)
{

    
    if (mode == 0) {
#if 0            
        LED_5V  = 0;
        LED_9V  = 0;
        LED_12V = 0;
        LED_15V = 0;
        LED_20V = 0;
#endif
        
        blink = 0;

        switch (value) {
            case (PD_5V):
                LED_5V = 1;
                break;
            case (PD_9V):
                LED_9V = 1;
                break;
            case (PD_12V):
                LED_12V = 1;
                break;
            case (PD_15V):
                LED_15V = 1;
                break;
            case (PD_20V):
                LED_20V = 1;
                break;
            default:
                break;
        }
    } else {
        blink = 1;
        blink_value = value;
    }
}

UINT16 adc_read()
{
    UINT16 v;

    //printf("AIN%02x ",(UINT16)i);		
    ADC_ChannelSelect( 0 );
    ADC_START = 1;
    while(ADC_START);
    //printf("DATA: %d\n",(UINT16)ADC_DATA);
    v = (UINT16)ADC_DATA;
    return v;
}



void blink_handler()
{

    switch (blink_value) {
        case (PD_5V):
            LED_5V = !LED_5V;
            break;
        case (PD_9V):
            LED_9V = !LED_9V;
            break;
        case (PD_12V):
            LED_12V = !LED_12V;
            break;
        case (PD_15V):
            LED_15V = !LED_15V;
            break;
        case (PD_20V):
            LED_20V = !LED_20V;
            break;
        default:
            break;
    }
}

void timer0_int_handler()
{
    if (blink) {
        blink_handler();
    }    
}

void timer1_int_handler()
{
    if (blink) {
        blink_handler();
    }
}

UINT16 key_read()
{
    UINT16 k;
    
    /* 1: release; 0: pressed */
    k = (UINT16)(KEY == 0 ? 0 : 1);

    //printf("KEY: %02x\r\n", k);
    return k;    
}

UINT8 WriteDataFlash(UINT8 addr, UINT8* buf, UINT8 len) {
	UINT8 i;
	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;

	GLOBAL_CFG |= bDATA_WE;

	SAFE_MOD = 0;

	ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
	addr <<= 1;

	for (i = 0; i < len; i++) {
		ROM_ADDR_L = addr + i * 2;
		ROM_DATA_L = *(buf + i);
		if (ROM_STATUS & bROM_ADDR_OK) {
			ROM_CTRL = ROM_CMD_WRITE;
		}
		if ((ROM_STATUS ^ bROM_ADDR_OK) > 0) {
			return i;
		}
	}

	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;
	GLOBAL_CFG &= ~bDATA_WE;
	SAFE_MOD = 0;

	return i;
}

UINT8 ReadDataFlash(UINT8 addr, UINT8* buf, UINT8 len) {
	UINT8 i;

	ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
	addr <<= 1;
	for (i = 0; i < len; i++) {
		ROM_ADDR_L = addr + i * 2;
		ROM_CTRL = ROM_CMD_READ;
		*(buf + i) = ROM_DATA_L;
	}
	return i;
}

/* uart-0 baudrate: 57600 */
main()
{
    UINT16 i, curr_key, prev_key;
    UINT16 curr_pd = PD_5V;
    UINT32 loop = 0;
	UINT16 changeTimeout = 0;
	UINT8  blinkSpeed = 20;
	BOOL   enableChange = FALSE;

	CfgFsys();	

#if 0
	mInitSTDIO();
    printf("\r\nPDTricker system buildtime [" __TIME__ " " __DATE__ "] " "rev     1.0\r\n");
    printf("T0 Test ...\n"); 
    mTimer0Clk12DivFsys();	                                                   // 12MHz / 12 = 1MHz
    mTimer_x_ModInit(0,2);                                                     // timer-0, mode-2
    mTimer_x_SetData(0,0xc8c8);	                                               // timer-0 data timer interrupt freq: 1MHz / 0xc8 = 5KHz, every 0.2ms
    mTimer0RunCTL(1);                                                          // timer-0 start
    ET0 = 1;                                                                   // 
    EA = 1;
#endif

	Port1Cfg(0, 0);
    ADCInit( 0 );
		
	if (!key_read()) {
		enableChange = TRUE;
		led_all_set(TRUE);
		while(!key_read());
	}

    prev_key = curr_key = 1;
    led_all_set(FALSE);
	ReadDataFlash(0, &curr_pd, 2);
	if (curr_pd >= PD_MAX) {
		curr_pd = PD_5V;
		WriteDataFlash(0, &curr_pd, 2);
	}
    pd_set(curr_pd);

    i = 0;
    
	while ( 1 ) {
        prev_key = curr_key;
        curr_key = key_read();

		if(enableChange) {
			if (prev_key == 1 && curr_key == 0) {
				changeTimeout = 0;
				led_off(curr_pd);
				curr_pd++;
				if (curr_pd == PD_MAX) {
					curr_pd = PD_5V;
				}

				//printf("pd_set %d\n", curr_pd);
				pd_set(curr_pd);
			}
		}
				
        pd_verify(curr_pd);

		if(enableChange)
			blinkSpeed = 10; // 100ms
		else
			blinkSpeed = 20; // 200ms
					
        if (loop % blinkSpeed == 0) {
            if (blink) {
                blink_handler();
            }
        }
		
		if(enableChange) {
			if(++changeTimeout>=300) {  // 3 secs
				enableChange = FALSE;
				WriteDataFlash(0, &curr_pd, 2);
				led_all_set(TRUE);
				mDelaymS(500);
				led_all_set(FALSE);
			}
		}

        mDelaymS(10);
        loop++;
	}
}