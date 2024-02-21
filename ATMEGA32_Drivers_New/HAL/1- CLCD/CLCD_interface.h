/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : CLCD_interface.h *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef CLCH_INTERFACE_H_
#define CLCH_INTERFACE_H_

void CLCD_voidSendCmd(uint8 Copy_u8Cmd);

void CLCD_voidSendData (uint8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_vodDisplayClear(void);

NULL_PTR_Error_State_t CLCD_u8SendString (const char* Copy_pcharString);

void CLCD_voidSendNumber(sint32 Copy_s32Number);

void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos);

void CLCD_voidSendSpecialCharacter(uint8 *Copy_u8Pattern,uint8 Copy_u8PatternNumber, uint8 Copy_u8XPos, uint8 Copy_u8YPos);

enum CLCD_Y_Position
{
	CLCD_Y_ROW_0 = 0u,
	CLCD_Y_ROW_1 = 1u,
};


enum CLCD_X_Position
{
	CLCD_X_POSITION_0 = 0u,
	CLCD_X_POSITION_1	  ,
	CLCD_X_POSITION_2	  ,
	CLCD_X_POSITION_3	  ,
	CLCD_X_POSITION_4	  ,
	CLCD_X_POSITION_5	  ,
	CLCD_X_POSITION_6	  ,
	CLCD_X_POSITION_7	  ,
	CLCD_X_POSITION_8	  ,
	CLCD_X_POSITION_9	  ,
	CLCD_X_POSITION_10	  ,
	CLCD_X_POSITION_11	  ,
	CLCD_X_POSITION_12	  ,
	CLCD_X_POSITION_13	  ,
	CLCD_X_POSITION_14	  ,
	CLCD_X_POSITION_15	  ,
	CLCD_X_POSITION_16	  ,
	CLCD_X_POSITION_17	  ,
	CLCD_X_POSITION_18	  ,
	CLCD_X_POSITION_19	  ,
	CLCD_X_POSITION_20	  ,
	CLCD_X_POSITION_21	  ,
	CLCD_X_POSITION_22	  ,
	CLCD_X_POSITION_23	  ,
	CLCD_X_POSITION_24	  ,
	CLCD_X_POSITION_25	  ,
	CLCD_X_POSITION_26	  ,
	CLCD_X_POSITION_27	  ,
	CLCD_X_POSITION_28	  ,
	CLCD_X_POSITION_29	  ,
	CLCD_X_POSITION_30	  ,
	CLCD_X_POSITION_31	  ,
	CLCD_X_POSITION_32	  ,
	CLCD_X_POSITION_33	  ,
	CLCD_X_POSITION_34	  ,
	CLCD_X_POSITION_35	  ,
	CLCD_X_POSITION_36	  ,
	CLCD_X_POSITION_37	  ,
	CLCD_X_POSITION_38	  ,
	CLCD_X_POSITION_39	  ,
	CLCD_X_POSITION_40	  ,
	CLCD_X_POSITION_41	  ,
	CLCD_X_POSITION_42	  ,
	CLCD_X_POSITION_43	  ,
	CLCD_X_POSITION_44	  ,
	CLCD_X_POSITION_45	  ,
	CLCD_X_POSITION_46	  ,
	CLCD_X_POSITION_47	  ,
	CLCD_X_POSITION_48	  ,
	CLCD_X_POSITION_49	  ,
	CLCD_X_POSITION_50	  ,
	CLCD_X_POSITION_51	  ,
	CLCD_X_POSITION_52	  ,
	CLCD_X_POSITION_53	  ,
	CLCD_X_POSITION_54	  ,
	CLCD_X_POSITION_55	  ,
	CLCD_X_POSITION_56	  ,
	CLCD_X_POSITION_57	  ,
	CLCD_X_POSITION_58	  ,
	CLCD_X_POSITION_59	  ,
	CLCD_X_POSITION_60	  ,
	CLCD_X_POSITION_61	  ,
	CLCD_X_POSITION_62	  ,
	CLCD_X_POSITION_63	  ,
	CLCD_X_POSITION_64	  ,
	CLCD_X_POSITION_65	  ,
	CLCD_X_POSITION_66	  ,
	CLCD_X_POSITION_67	  ,
};

#endif
