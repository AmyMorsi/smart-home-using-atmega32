#ifndef GateControl_H_
#define GateControl_H_

#define ClosedGate   0
#define OpenedGate   1


void SetGateState(u8 U8GateStateCopy);
u8 GetGateState(void);
void OpenGate(void);
void CloseGate(void);

#endif /* GateControl_H_ */
