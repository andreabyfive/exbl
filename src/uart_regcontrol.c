#include "en675.h"
#include "reg.h"

//*************************************************************************************************
// 4. COMM
//-------------------------------------------------------------------------------------------------
// Tx header
// Eyenix Protocol
#define	PC_STX		0x02			// STX

	//						gbRxStg :  0   1   CMD
	#define PC_CMD_REGW		0x10	// STX CMD ADH ADL DAH DA1 DA2 DAL ETX	: ISP Reg. Write
	#define PC_CMD_REGR		0x20	// STX CMD ADH ADL ETX					: ISP Reg. Read
	#define PC_CMD_KEY		0x30	// STX CMD KEY ETX						: KEY
	//#define PC_CMD_CHA		0x40	// STX CMD CHA ETX						: gbWinChar	- Not Used

	#define PC_CMD_PARW 	0x50 		// Cmd : Write parameter in F/W. 			2 addr, 1 data.
	#define PC_CMD_PARR 	0x58 		// Cmd : Read paramter in F/W. 				2 addr, 1 data.
	#define PC_CMD_EEPW 	0x60 		// Cmd : Write paramter from F/W to EEP.
	#define PC_CMD_EEPR 	0x61 		// Cmd : Read paramter from EEP to F/W.
	//#define PC_CMD_EEPD 	0x62 		// Cmd : Write / Read for EEPROM is done.
	#define PC_CMD_PARK		0x68		// Cmd : Enable Parameter					4 data

	//#define PC_CMD_SENW 	0x70 		// Cmd : Write register in Sensor. 			2 addr, 4 data
	//#define PC_CMD_SENR 	0x78 		// Cmd : Read register from Sensor.

#if model_I2cSlave == 1	|| model_I2cSlave == 2
	#define I2C_CMD_MENUW 	/*0x50*/	// STX CMD ADH ADL WDH WDL ETX : Menu parameter write
	#define I2C_CMD_MENUR	/*0x60*/	// STX CMD ADH ADL RDH RDL ETX : Menu parameter read
	#define I2C_CMD_CLOCK	/*0x70*/	// Cmd : Internet Standard Time
#endif

	#define PD_STG			0x80	// xFF ADD CMD CMD DAT DAT CRC			: Pelco-D
	#define PP_STG			0x90	// xA0 ADD DAT DAT DAT DAT xAF CRC		: Pelco-P

	#define PC_CMD_AWBI 	0xaa	// STX CMD ETX							: InitAwbOdmCap()

	#define	PC_CMD_STR		0xb0	// TxStr()
	#define	PC_CMD_GRP		0xc0	// TxGrp()
	#define	PC_CMD_ERR		0xd0	// TxErr()

	#define	PC_CMD_INI		0xe0	// STX CMD ETX							: UartRstQue()	- ?
	#define	PC_CMD_ACK		0xf0	// STX CMD ETX							: TxAck()		- ?

	#define PC_CMD_DOWN		0xf8	// STX CMD ETX							: Uart Download request Rx

#if (model_Lens==1)
		// System
	#define TMC_TABLEREAD			0x01
	#define TMC_TABLEWRITE			0x02 // Data 부분이 4Byte * 11 = 총 44Byte입니다.
	#define TMC_LENSINITIALIZATION	0x03 // Write Command로 보내며, Data는 4Byte로 TRUE(1)를 보냅니다.
	#define TMC_CALIBRATIONSTART	0x04 // Write Command로 보내며, Data는 4Byte로 TRUE(1)를 보냅니다.

		// Zoom
	#define TMC_ZOOM_TOTALSTEP		0x10
	#define TMC_ZOOM_STARTPOSITION	0x11
	#define TMC_ZOOM_ENDPOSITION	0x12
	#define TMC_ZOOM_SPEED			0x13
	#define TMC_ZOOM_MINRATIO		0x14
	#define TMC_ZOOM_MAXRATIO		0x15

		// Focus
	#define TMC_FOCUS_TOTALSTEP		0x20
	#define TMC_FOCUS_STARTPOSITION	0x21
	#define TMC_FOCUS_ENDPOSITION	0x22
	#define TMC_FOCUS_SPEED			0x23
	#define TMC_FOCUS_MODE			0x24
	#define TMC_FOCUS_DnNFILTER		0x25
#endif

#define	PC_ETX		0x03			// ETX

// Pelco D Protocol
#define PD_STX		0xFF

// Pelco P Protocol
#define PP_STX		0xA0
#define PP_ETX		0xAF

// I2C Protocol
#define	I2C_STX		PC_STX
#define I2C_ETX		PC_ETX

#define I2C_STX_SIZ		1
#define I2C_CMD_SIZ		1
#define I2C_ADR_SIZ		2
#define I2C_DAT_SIZ		2
#define I2C_ETX_SIZ		1

#define I2C_ALL_SIZ		(I2C_STX_SIZ+I2C_CMD_SIZ+I2C_ADR_SIZ+I2C_DAT_SIZ+I2C_ETX_SIZ)

//-------------------------------------------------------------------------------------------------
// Snatch logic address (Regulate with logic address .CAUTION)
#define	BASE_SENS			0x4000		// 0x300 ea 		sensor control
#define BASE_SENS_OV		0x4800
#define BASE_EN331			0x5000
#define BASE_EEPROM			0x6000
#define BASE_MICOM_PAR		0x8000

//-------------------------------------------------------------------------------------------------
// Debug Graph channel
union uFLOAT{
	float	m_float;
	UINT	m_UINT;
};

#define	GRP0			(gnTxGrp[0].m_UINT)
#define	GRP1			(gnTxGrp[1].m_UINT)
#define	GRP2			(gnTxGrp[2].m_UINT)
#define	GRP3			(gnTxGrp[3].m_UINT)
#define	GRP4			(gnTxGrp[4].m_UINT)
#define	GRP5			(gnTxGrp[5].m_UINT)
#define	GRP6			(gnTxGrp[6].m_UINT)
#define	GRP7			(gnTxGrp[7].m_UINT)

#define	GRP0F			(gnTxGrp[0].m_float)
#define	GRP1F			(gnTxGrp[1].m_float)
#define	GRP2F			(gnTxGrp[2].m_float)
#define	GRP3F			(gnTxGrp[3].m_float)
#define	GRP4F			(gnTxGrp[4].m_float)
#define	GRP5F			(gnTxGrp[5].m_float)
#define	GRP6F			(gnTxGrp[6].m_float)
#define	GRP7F			(gnTxGrp[7].m_float)

//-------------------------------------------------------------------------------------------------
// Debug Parameter channel
#define	PAR00			(gnRxPar[ 0])
#define	PAR01			(gnRxPar[ 1])
#define	PAR02			(gnRxPar[ 2])
#define	PAR03			(gnRxPar[ 3])
#define	PAR04			(gnRxPar[ 4])
#define	PAR05			(gnRxPar[ 5])
#define	PAR06			(gnRxPar[ 6])
#define	PAR07			(gnRxPar[ 7])
#define	PAR08			(gnRxPar[ 8])
#define	PAR09			(gnRxPar[ 9])
#define	PAR0A			(gnRxPar[10])
#define	PAR0B			(gnRxPar[11])
#define	PAR0C			(gnRxPar[12])
#define	PAR0D			(gnRxPar[13])
#define	PAR0E			(gnRxPar[14])
#define	PAR0F			(gnRxPar[15])
#define	PAR10			(gnRxPar[16])
#define	PAR11			(gnRxPar[17])
#define	PAR12			(gnRxPar[18])
#define	PAR13			(gnRxPar[19])
#define	PAR14			(gnRxPar[20])
#define	PAR15			(gnRxPar[21])
#define	PAR16			(gnRxPar[22])
#define	PAR17			(gnRxPar[23])
#define	PAR18			(gnRxPar[24])
#define	PAR19			(gnRxPar[25])
#define	PAR1A			(gnRxPar[26])
#define	PAR1B			(gnRxPar[27])
#define	PAR1C			(gnRxPar[28])
#define	PAR1D			(gnRxPar[29])
#define	PAR1E			(gnRxPar[30])
#define	PAR1F			(gnRxPar[31])


//-------------------------------------------------------------------------------------------------

#define Case1(CMD,VAL)\
	case (CMD) :\
		(VAL) = bIn;\
		gbRxStg++;\
		break

#define Case2(CMD,VAL)\
	case (CMD)   :\
	case (CMD)+1 :\
		(VAL) = ((VAL)<<8) | bIn;\
		gbRxStg++;\
		break

#define Case4(CMD,VAL)\
	case (CMD)   :\
	case (CMD)+1 :\
	Case2((CMD)+2,VAL)

#define SetCase0(C,E,EC, ...)			case C : if(E) { EC } else goto err_proc; SetEnd(); break
#define SetCase1(C,E,EC,D0,D0n)			Case##D0n(C,D0);  SetCase0(C+D0n,E,EC)
#define SetCase2(C,E,EC,D0,D0n,...)		Case##D0n(C,D0);  SetCase1(C+D0n,E,EC,__VA_ARGS__)
#define SetCase3(C,E,EC,D0,D0n,...)		Case##D0n(C,D0);  SetCase2(C+D0n,E,EC,__VA_ARGS__)

#define SetCase(CMD,EndChk,EndCode,VAL_NUM,...)	SetCase##VAL_NUM(CMD,EndChk,EndCode,__VA_ARGS__)


//-------------------------------------------------------------------------------------------------
// Variables
BYTE	gbETX = 0;
BYTE	gbRxStg = 0;
WORD	gwRxAddr = 0;
UINT	gnRxData = 0;
BYTE	gbParOn = 0x0;

#define SetEnd() {\
		gbRxStg = 0;\
		gwRxAddr = 0;\
		gnRxData = 0;\
		gbETX = 0;\
	}

//BYTE gbWinChar = 0;													// Window character
union uFLOAT gnTxGrp[8] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };	// Graphic data

UINT gnRxPar[32] = {
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	// Parameter data (Regulate with logic address .CAUTION)
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
					};

//UINT gnDownOn = 0;										// PC_CMD_DOWNLOAD

UINT gnI2cOn = 0;

#define UNUSED_ARG(x)			((void)(x))
#define	_rd32(a)				(*((volatile UINT *)(a)))			//			"			- Always used for ISP Register Read
#define	_wr32(a,d)				(*((volatile UINT *)(a)) = (d))		//			"			- Always used for ISP Register Write
#define	GetIsp(anAddr)			(_rd32(ISP_REG_BASE+((UINT)(anAddr)<<2))                )	// Read from bridge(Isp,Aud)

#define ISP_CK_ADR0		0x0005	// PCLKI1_PD[31],FPCK_PD[30],PPCK_PD[29],PSCK_PD[28],PR_CK_PD[27],FN_CK_PD[26]
#define ISP_CK_ADR1     0x0006	// YCW_CK0_PD[24],YCW_CK1_PD[23],YCW_CK2_PD[22],IMD_CK_PD[21],JPGCK_PD[20],CDS0_PCK_PD[19],CDS1_PCK_PD[18],PIP_PPCK_PD[17],IBT_PCK_PD[16],IBT0_PCK_PD[15],BT_PCK_PD[14],BT0_PCK_PD[13],YCR_CK0_PD[12],PCKO0_ON[8],PCKO1_ON[7],PCKO_OEN[5],BT1120_PCK_PD[4],BT1120_PCK0_PD[3]

#define ISP_CK_MSK0		0x03FFFFFF
#define ISP_CK_MSK1     0xF7000E47

#define ISP_REG_BASE	0xa0020000	//	CPU0 | CPU1  OK

void SetIsp(UINT anAddr, UINT anData)
{
	UINT nAcept_Mask = 0;

	switch(anAddr) {

		case ISP_CK_ADR0 : nAcept_Mask = ISP_CK_MSK0;
		case ISP_CK_ADR1 : nAcept_Mask = ISP_CK_MSK1;
		default          : nAcept_Mask = 0;
	}

	if(nAcept_Mask) _wr32(ISP_REG_BASE+((UINT)(anAddr)<<2), (UINT)((anData&~nAcept_Mask)|((_rd32(ISP_REG_BASE+((UINT)(anAddr)<<2))&nAcept_Mask))));
	else            _wr32(ISP_REG_BASE+((UINT)(anAddr)<<2), (UINT)(anData));
}

void TxReg(UINT anAddr, UINT anData)
{
	Uart7_Tx(PC_STX);
	Uart7_Tx(PC_CMD_REGR);

	Uart7_Tx(anAddr>> 8);
	Uart7_Tx(anAddr>> 0);

	Uart7_Tx(anData>>24);
	Uart7_Tx(anData>>16);
	Uart7_Tx(anData>> 8);
	Uart7_Tx(anData>> 0);

	Uart7_Tx(PC_ETX);
}

void TxErr(void)
{
	Uart7_Tx(PC_STX);
	Uart7_Tx(PC_CMD_ERR);
	Uart7_Tx(PC_ETX);
}


void RxAddr(const int aiWrite)
{
	const int iRxAddr = gwRxAddr;

	#define SET_ADDR(ADDR_START, ADDR_END, WRITE_CMD, READ_CMD, READ_DATA)	\
		if((int)(ADDR_START) <= iRxAddr && iRxAddr < (int)(ADDR_END)) {\
			const WORD wAddr = iRxAddr - (ADDR_START);\
			UNUSED_ARG(wAddr);\
			if(aiWrite) { WRITE_CMD; }\
			READ_CMD\
			TxReg(iRxAddr, (READ_DATA));}


	SET_ADDR(0x0, BASE_SENS,				// ISP : 0x0000 ~ 0x3fff
		// ISP Write Code
		SetIsp(wAddr, gnRxData);

		GRP3 = wAddr;
		GRP4 = gnRxData;
		GRP7 = GetIsp(wAddr);
		,
		// ISP Read Code
		,
		GetIsp(wAddr))


}


void Comm(void)
{
	char bIn;

	if((bIn=Uart7_Rx()) != (char)-1){

		switch(gbRxStg){
		 //...............................................
		 // Start -> Command
		 			case 0x00 :
		 				switch(bIn){
		 					case PC_STX : gbRxStg++; break;
		 					case PD_STX : gbRxStg = PD_STG; break;
		 					case PP_STX : gbRxStg = PP_STG; break;
		 				}
		 				break;

		 			case 0x01 :
		 				switch(bIn){
		 					case PC_CMD_REGW :
		 					case PC_CMD_REGR :
		 					case PC_CMD_KEY  :
		 					//case PC_CMD_CHA  :

		 					case PC_CMD_AWBI :

		 					case PC_CMD_INI  :
		 					case PC_CMD_ACK  :

		 					case PC_CMD_PARW :
		 					case PC_CMD_PARR :
		 					case PC_CMD_EEPW :
		 					case PC_CMD_EEPR :
		 					case PC_CMD_PARK :

		 					case PC_CMD_DOWN :

		 					case PC_CMD_STR  :
		 						gbRxStg = bIn;
		 						break;

		 					default	:
		 						goto err_proc;
		 						break;
		 				}
		 				break;

		 //...............................................
		 // Reg write process : ISP register set
		 			SetCase(PC_CMD_REGW, bIn==PC_ETX, if(gnI2cOn==0) { RxAddr(1); }
		 					, 2, gwRxAddr,2, gnRxData,4);
		 //...............................................
		 // Reg read process : ISP register get
		 			SetCase(PC_CMD_REGR, bIn==PC_ETX, RxAddr(0);
		 					, 1, gwRxAddr,2);

		 			err_proc:
		 					default :
		 						TxErr();
		 						gbRxStg = 0;
		 						break;

		 }
	 }
}

