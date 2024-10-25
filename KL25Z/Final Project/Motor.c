#include "Constants.h"

void ConfigureRemoteXY(){
	uint8_t motorControls = serialData & 0b1111; // keep lower 4 bits
	uint8_t checkFB = motorControls & 0b11;
	uint8_t checkLR = (motorControls >> 2) & 0b11;
	uint8_t gearControls = serialData >> 4;
	
	// set all control variables
	g_controls.forward = (checkFB == 1) ? 1:0;
	g_controls.backward = (checkFB == 2) ? 1:0;
	g_controls.left = (checkLR == 1) ? 1:0;
	g_controls.right = (checkLR == 2)? 1:0;
	g_controls.forwardGear = gearControls & 0b11;
	g_controls.turnGear = (gearControls >> 2) & 0b11;
	g_controls.forwardSpeed = GEAR_SPEED[g_controls.forwardGear];
	g_controls.turnSpeed = GEAR_SPEED[g_controls.turnGear];
	g_controls.stop = (motorControls == 0) ? 1:0;
	g_controls.complete = (motorControls == 0b1111) ? 1:0;
}

void SetMotorSpeed(const MotorWire *MOTOR_WIRE, int speed){
	*(MOTOR_WIRE->channelValue) = (uint32_t)((speed / 100.0) * MOTOR_MOD_VALUE);
}

uint8_t MoveForward(){
	if (g_controls.forward == 1){
		int leftMotorSpeed = (int)(MAX_MOTOR_SPEED * ((float)g_controls.forwardSpeed / 100)
											 *	(1 - ((float)(g_controls.turnSpeed) / 100) * g_controls.left));
		int rightMotorSpeed = (int)(MAX_MOTOR_SPEED * ((float)g_controls.forwardSpeed / 100)
												*	(1 - ((float)(g_controls.turnSpeed) / 100) * g_controls.right));
		SetMotorSpeed(&MOTOR_WIRE[LEFT_RED], leftMotorSpeed);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_RED], rightMotorSpeed);
		SetMotorSpeed(&MOTOR_WIRE[LEFT_BLACK], 0);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_BLACK], 0);
		return 1;
	}
	return 0;
}

uint8_t MoveBackward(){
	if (g_controls.backward == 1){
		int leftMotorSpeed = (int)(MAX_MOTOR_SPEED * ((float)g_controls.forwardSpeed / 100)
											 *	(1 - ((float)(g_controls.turnSpeed) / 100) * g_controls.left));
		int rightMotorSpeed = (int)(MAX_MOTOR_SPEED * ((float)g_controls.forwardSpeed / 100)
												*	(1 - ((float)(g_controls.turnSpeed) / 100) * g_controls.right));
		SetMotorSpeed(&MOTOR_WIRE[LEFT_BLACK], leftMotorSpeed);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_BLACK], rightMotorSpeed);
		SetMotorSpeed(&MOTOR_WIRE[LEFT_RED], 0);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_RED], 0);
		return 1;
	}
	return 0;
}

uint8_t RotateLeft(){
	if (g_controls.left == 1) {
		int speed = (int)(MAX_MOTOR_SPEED * (float)(g_controls.turnSpeed) / 100); 
		SetMotorSpeed(&MOTOR_WIRE[LEFT_BLACK], speed);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_RED], speed);
		SetMotorSpeed(&MOTOR_WIRE[LEFT_RED], 0);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_BLACK], 0);
		return 1;
	}
	return 0;
}

uint8_t RotateRight(){
	if (g_controls.right == 1) {
		int speed = (int)(MAX_MOTOR_SPEED * (float)(g_controls.turnSpeed) / 100); 
		SetMotorSpeed(&MOTOR_WIRE[LEFT_RED], speed);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_BLACK], speed);
		SetMotorSpeed(&MOTOR_WIRE[LEFT_BLACK], 0);
		SetMotorSpeed(&MOTOR_WIRE[RIGHT_RED], 0);
		return 1;
	}
	return 0;
}

uint8_t Stop(){
	for (uint8_t i = 0; i < 4; i++){
		SetMotorSpeed(&MOTOR_WIRE[i], 0);
	}
	return 1;
}

uint8_t HandleMovement(){
	return MoveForward() || MoveBackward() || RotateLeft() || RotateRight() || Stop();
}

void InitMotor() {
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
  SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	for (int i = 0; i < 4; i++){
		PORTC->PCR[MOTOR_WIRE[i].pin] &= ~PORT_PCR_MUX_MASK;
		PORTC->PCR[MOTOR_WIRE[i].pin] |= (i<2) ? PORT_PCR_MUX(4) : PORT_PCR_MUX(3);
	}
	
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
  TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
  TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(TIMER_PRESCALER) | TPM_SC_TOIE_MASK);
  TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	for (int i = 0; i < 4; i++){
		*(MOTOR_WIRE[i].channelStatusControl) &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
		*(MOTOR_WIRE[i].channelStatusControl) |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
		Stop();
	}	
	
	TPM0->MOD = MOTOR_MOD_VALUE;
}
