/* Includes ------------------------------------------------------------------*/
#include <stdlib.h> 
#include "main.h"
#include "leds.h" 
#include "midi_lowlevel.h" 
#include "mm_midimsgbuilder.h" 
#include "mm_midirouter_standard.h" 
#include "afl.h"
#include "fuzzing.h"
#include "McuASAN.h"




#define MIDI_MSG_DEBUG 
#define NUM_MIDI_MSGS 10 

extern char midiBuffer[MIDI_BUF_SIZE];                  /* for debugging */ //buffer
extern MIDIMsgBuilder midiMsgBuilder;                   //buffers
extern MIDI_Router_Standard midiRouter;                 //buffers

extern MIDIMsgBuilder_State_t lastState; //global variable

#if DUALCOREFUZZ == 0
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif


void MIDI_note_on_do(void *data, MIDIMsg *msg)
{
    if ((MIDIMSG_GET_CHANNEL(msg->data[0]) == 1)
            && (msg->data[1] == 60)) {
        LEDs_greenSet();
    }
    if ((MIDIMSG_GET_CHANNEL(msg->data[0]) == 1)
            && (msg->data[1] == 67)) {
        LEDs_redSet();
    }
    MIDIMsg_free(msg); //Bug identified by DICE
    //free(msg);
}

void MIDI_note_off_do(void *data, MIDIMsg *msg)
{
    if ((MIDIMSG_GET_CHANNEL(msg->data[0]) == 1)
            && (msg->data[1] == 60)) {
        LEDs_greenReset();
    }
    if ((MIDIMSG_GET_CHANNEL(msg->data[0]) == 1)
            && (msg->data[1] == 67)) {
        LEDs_redReset();
    }
    MIDIMsg_free(msg); //Bug identified by DICE
    //free(msg);
}

int main_midi(void)
{
	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


    int dummy;


	/* Initialize MIDI Message builder */
	MIDIMsgBuilder_init(&midiMsgBuilder);
    
    /* Initialize the MIDI router */
    MIDI_Router_Standard_init(&midiRouter);
    MIDI_Router_addCB(&midiRouter.router, MIDIMSG_NOTE_ON, 1, MIDI_note_on_do, &dummy); 
    MIDI_Router_addCB(&midiRouter.router, MIDIMSG_NOTE_OFF, 1, MIDI_note_off_do, &dummy); 

    /* Enable LEDs so we can toggle them */

    //LEDs_Init();
    
    /* Set up midi */
    MIDI_low_level_setup_nolib();  // initialize USART with DMA RX
    xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,2,1,eSetValueWithOverwrite); //notify the fuzzer task the target is ready

    while (1) {

        MIDI_process_buffer();
        xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,0,FAULT_NONE_RTOS,eSetValueWithOverwrite);//notify that the test finished
    }
}






void do_stuff_with_msg(MIDIMsg *msg)
{
    MIDI_Router_handleMsg(&midiRouter.router, msg);
}

void MIDI_process_byte(char byte)
{

	switch (MIDIMsgBuilder_update(&midiMsgBuilder,byte)) {

        case MIDIMsgBuilder_Action_NONE:
            break;
        case MIDIMsgBuilder_Action_MSG_COMPLETE:
            do_stuff_with_msg(midiMsgBuilder.msg);
            MIDIMsgBuilder_init(&midiMsgBuilder); /* reset builder */
            break;
        default:
            break;
    }
    //lastState = midiMsgBuilder.state;
}
