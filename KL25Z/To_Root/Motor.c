#include "MKL25Z4.h"     
#include "Constants.h"

void move_left_forward(uint8_t speed);
void move_left_reverse(uint8_t speed);
void move_right_forward(uint8_t speed);
void move_right_reverse(uint8_t speed);
/*
void InitMotor() {
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
  SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
  SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;

  PORTB->PCR[MOTOR_FRONT_LEFT] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[MOTOR_FRONT_LEFT] |= PORT_PCR_MUX(3);
	
  PORTB->PCR[MOTOR_FRONT_RIGHT] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[MOTOR_FRONT_RIGHT] |= PORT_PCR_MUX(3);
	
  PORTB->PCR[MOTOR_BACK_LEFT] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[MOTOR_BACK_LEFT] |= PORT_PCR_MUX(3);
	
  PORTB->PCR[MOTOR_BACK_RIGHT] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[MOTOR_BACK_RIGHT] |= PORT_PCR_MUX(3);
	
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
  TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
  TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(TIMER_PRESCALER));
  TPM1->SC &= ~(TPM_SC_CPWMS_MASK);

  TPM1_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
  TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
  TPM1_C1SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
  TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
  TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
  TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(TIMER_PRESCALER));
  TPM2->SC &= ~(TPM_SC_CPWMS_MASK);

  TPM2_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
  TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
	
  TPM2_C1SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
  TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
	
  TPM1->MOD = MOTOR_PERIOD_TICKS;
  TPM2->MOD = MOTOR_PERIOD_TICKS;
}
*/