LIST P = 18F8722
#include <p18f8722.inc>
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

i1 udata 0x20
i1
i2 udata 0x21
i2
i3 udata 0x22
i3
flag udata 0x23
flag
flagRA4 udata 0x24
flagRA4
flagRE3 udata 0x25
flagRE3
flagRE4 udata 0x26
flagRE4
 
ORG     0x00
goto    init

init:
    ;BCF  INTCON2,7 ; Pull-up Enables
    CLRF    PORTA
    CLRF    LATA
    MOVLW   0Fh
    MOVWF   ADCON1
    MOVLW   b'00010000' ; RA4 is input
    MOVWF   TRISA
    
    CLRF    PORTB
    CLRF    LATB
    CLRF    TRISB
    
    CLRF    PORTC
    CLRF    LATC
    CLRF    TRISC
    
    CLRF    PORTD
    CLRF    LATD
    CLRF    TRISD
    
    CLRF    PORTE
    CLRF    LATE
    MOVLW   b'00011000' ; RE3 and RE4 are inputs
    MOVWF   TRISE
    
main:  
    GOTO state0
      
OPENLED_A
    BTFSC   PORTA, 3
    return
    BTFSC   PORTA, 0  
    RLNCF    LATA, F
    INCF    LATA, F
    return
CLOSELED_A
    BTFSS   PORTA, 0
    return
    DECF    LATA, F
    RRNCF    LATA, F
    return
OPENLED_B
    BTFSC   PORTB, 3
    return
    BTFSC   PORTB, 0
    RLNCF    LATB, F
    INCF    LATB, F
    return    
CLOSELED_B
    BTFSS   PORTB, 0
    return
    DECF    LATB, F
    RRNCF    LATB, F
    return
OPENLED_C
    BTFSC   PORTC, 3
    return
    BTFSC   PORTC, 0
    RLNCF    LATC, F
    INCF    LATC, F
    return    
CLOSELED_C
    BTFSS   PORTC, 0
    return
    DECF    LATC, F
    RRNCF    LATC, F
    return
OPENLED_D
    BTFSC   PORTD, 3
    return
    BTFSC   PORTD, 0
    RLNCF    LATD, F
    INCF    LATD, F
    return    
CLOSELED_D
    BTFSS   PORTD, 0
    return
    DECF    LATD, F
    RRNCF    LATD, F
    return

DELAY_ONESEC	
    MOVLW   d'130'
    MOVWF   i3
    outer1:
	MOVLW	d'160'
	MOVWF	i2
    middle1:
	MOVLW	d'159'
	MOVWF	i1
    inner1:
	DECFSZ	i1, F  
	GOTO	inner1
	DECFSZ	i2, F
	GOTO	middle1
	DECFSZ	i3, F
	GOTO	outer1
    return
    
DELAY_HALFSEC	
    MOVLW d'61'
    MOVWF i3
    outer:	
	MOVLW	d'89'
	MOVWF	i2
    middle:
	MOVLW	d'102'
	MOVWF	i1
    inner:
	;do nothing
    initRA4:
	BTFSS	PORTA,4
	GOTO	noPressRA4
	BSF	flagRA4, 0
	GOTO	innerLast
    noPressRA4:
	BTFSS	flagRA4, 0
	GOTO	innerLast    
    pressAndReleaseRA4:
	BCF	flagRA4, 0
	;stop led movements and wait RE3/RE4
    initRE3:
	BTFSS	PORTE,3
	GOTO	noPressRE3
	BSF	flagRE3, 0
	GOTO	initRE4
    noPressRE3:
	BTFSS	flagRE3, 0
	GOTO	initRE4
    pressAndReleaseRE3:
	BCF	flagRE3, 0
	CLRF flag
	RETURN	
    initRE4:
	BTFSS	PORTE,4
	GOTO	noPressRE4
	BSF	flagRE4, 0
	GOTO	pressAndReleaseRA4
    noPressRE4:
	BTFSS	flagRE4, 0
	GOTO	pressAndReleaseRA4
    pressAndReleaseRE4:
	BCF	flagRE4, 0
	COMF flag,1
	RETURN
    innerLast:
	DECFSZ	i1,F  
	GOTO	inner 
	DECFSZ	i2,F
	GOTO	middle
	DECFSZ	i3,F
	GOTO	outer
    return
    
state0:
    MOVLW   b'00001111'
    MOVWF   LATA
    CALL    DELAY_ONESEC
    CALL    DELAY_ONESEC    
    CLRF    LATA
    CALL    DELAY_ONESEC
    
state1:
    ;do nothing    

openLeds_A:   ; flag = 0
    BTFSC   PORTA,3
    GOTO    openLeds_B
    CALL    OPENLED_A
    CALL    DELAY_HALFSEC
    BTFSS   flag,0  
    GOTO    openLeds_A
    GOTO    closeLeds_A    
closeLeds_A: ; flag = 1
    BTFSS   PORTA, 0
    GOTO    allClosed
    CALL    CLOSELED_A
    CALL    DELAY_HALFSEC
    BTFSS   flag,0
    GOTO    openLeds_A
    GOTO    closeLeds_A
    
openLeds_B:   ; flag = 0
    BTFSC   PORTB,3
    GOTO    openLeds_C
    CALL    OPENLED_B
    CALL    DELAY_HALFSEC
    BTFSS   flag,0  
    GOTO    openLeds_B
    GOTO    closeLeds_B    
closeLeds_B: ; flag = 1
    BTFSS   PORTB, 0
    GOTO    closeLeds_A
    CALL    CLOSELED_B
    CALL    DELAY_HALFSEC
    BTFSS   flag,0
    GOTO    openLeds_B
    GOTO    closeLeds_B
    
openLeds_C:   ; flag = 0
    BTFSC   PORTC,3
    GOTO    openLeds_D
    CALL    OPENLED_C
    CALL    DELAY_HALFSEC
    BTFSS   flag,0  
    GOTO    openLeds_C
    GOTO    closeLeds_C    
closeLeds_C: ; flag = 1
    BTFSS   PORTC, 0
    GOTO    closeLeds_B
    CALL    CLOSELED_C
    CALL    DELAY_HALFSEC
    BTFSS   flag,0
    GOTO    openLeds_C
    GOTO    closeLeds_C    

openLeds_D:   ; flag = 0
    BTFSC   PORTD,3
    GOTO    allOpened
    CALL    OPENLED_D
    CALL    DELAY_HALFSEC
    BTFSS   flag,0  
    GOTO    openLeds_D
    GOTO    closeLeds_D    
closeLeds_D: ; flag = 1
    BTFSS   PORTD, 0
    GOTO    closeLeds_C
    CALL    CLOSELED_D
    CALL    DELAY_HALFSEC
    BTFSS   flag,0
    GOTO    openLeds_D
    GOTO    closeLeds_D    
    
allOpened:
    CALL    DELAY_HALFSEC
    BTFSS   flag, 0   
    GOTO    allOpened
    GOTO    closeLeds_D
    
allClosed:
    CALL    DELAY_HALFSEC
    BTFSC   flag, 0   
    GOTO    allClosed
    GOTO    openLeds_A
    
END    



