/*-----------------------------------------------------------------------
     Creator		: Morris chiou	 
     Sensor		: E-COMPASS
     File Name		: SENSOR_HMC5883L.h
     Function		: SENSOR_HMC5883L
     Create Date	: 2020/06/06
---------------------------------------------------------------------- */
#ifndef __HMC5883L_HEADER__ 
#define __HMC5883L_HEADER__ 

/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/
#define HMC5883L_SLAVE_ADDRESS 		(0x3C)
/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/


/* ------------- DEFINE HMC5883L REGISTER  ------------*/
/*NOTE :   R-> Read only , W-> Write only , R/W ->Read / Write*/
#define HMC5883L_REG_CONFIGA			(0x00)	/*R/W*/
#define HMC5883L_REG_CONFIGB			(0x01)	/*R/W*/
#define HMC5883L_REG_MODE				(0x02)	/*R/W*/
#define HMC5883L_REG_X_MSB				(0x03)	/*R*/
#define HMC5883L_REG_X_LSB				(0x04)	/*R*/
#define HMC5883L_REG_Z_MSB				(0x05)	/*R*/
#define HMC5883L_REG_Z_LSB				(0x06)	/*R*/
#define HMC5883L_REG_Y_MSB				(0x07)	/*R*/
#define HMC5883L_REG_Y_LSB				(0x08)	/*R*/
#define HMC5883L_REG_STATUS			(0x09)	/*R*/
#define HMC5883L_REG_IDA					(0x0A)	/*R*/	/*data must be : 0x48 */
#define HMC5883L_REG_IDB					(0x0B)	/*R*/	/*data must be : 0x34 */
#define HMC5883L_REG_IDC					(0x0C)	/*R*/	/*data must be : 0x33 */
/* ------------- DEFINE HMC5883L REGISTER  ------------*/

/* ------------- DEFINE HMC5883L PARAMETER  ------------*/
/*---- register: 0x00[Configuration Register A] parameters ------*/
/* note: bit7 always 0 */
#define HMC5883L_SAMPLE_AVER_1		(0x00<<5)	/* number of samples average 1 time. */
#define HMC5883L_SAMPLE_AVER_2		(0x01<<5)	/* number of samples average 2 time. */
#define HMC5883L_SAMPLE_AVER_4		(0x10<<5)	/* number of samples average 4 time. */
#define HMC5883L_SAMPLE_AVER_8		(0x11<<5)	/* number of samples average 8 time. */

#define HMC5883L_MEA_CNT_0_75HZ		(0x00<<2)	/* continous measurement mode , data rate :0.75 HZ */
#define HMC5883L_MEA_CNT_1_5HZ		(0x01<<2)	/* continous measurement mode , data rate :1.5 HZ */
#define HMC5883L_MEA_CNT_3HZ			(0x02<<2)	/* continous measurement mode , data rate :3 HZ */
#define HMC5883L_MEA_CNT_7_5HZ		(0x03<<2)	/* continous measurement mode , data rate :7.5 HZ */
#define HMC5883L_MEA_CNT_15HZ			(0x04<<2)	/* continous measurement mode , data rate :15 HZ */ /* default */
#define HMC5883L_MEA_CNT_30HZ			(0x05<<2)	/* continous measurement mode , data rate :30 HZ */
#define HMC5883L_MEA_CNT_75HZ			(0x06<<2)	/* continous measurement mode , data rate :75 HZ */

#define HMC5883L_MEA_MODE_NORMAL	(0x00<<0)	/* Normal measurement mode */
#define HMC5883L_MEA_MODE_POS_BIAS	(0x01<<0)	/* Positive bais configuration for X,Y,Z */
#define HMC5883L_MEA_MODE_NEG_BIAS	(0x02<<0)	/* Negative bais configuration for X,Y,Z */
/*---- register: 0x00[Configuration Register A] parameters ------*/

/*---- register: 0x01[Configuration Register B] parameters ------*/
/* data output range 0xf800(-2048)~0x7fff)(2047) */
#define HMC5883L_SAMPLE_GAIN1370		(0x00<<5)	/* gain : 1370 ; Resolution : 0.73 */
#define HMC5883L_SAMPLE_GAIN1090		(0x01<<5)	/* gain : 1090 ; Resolution : 0.92 */
#define HMC5883L_SAMPLE_GAIN820		(0x02<<5)	/* gain : 820 ; Resolution : 1.22 */
#define HMC5883L_SAMPLE_GAIN660		(0x03<<5)	/* gain : 660 ; Resolution : 1.52 */
#define HMC5883L_SAMPLE_GAIN440		(0x04<<5)	/* gain : 440 ; Resolution : 2.27 */
#define HMC5883L_SAMPLE_GAIN390		(0x05<<5)	/* gain : 390 ; Resolution : 2.56 */
#define HMC5883L_SAMPLE_GAIN330		(0x06<<5)	/* gain : 330 ; Resolution : 3.03 */
#define HMC5883L_SAMPLE_GAIN230		(0x07<<5)	/* gain : 230 ; Resolution : 4.35 */
/* bit 5~0 must be 0 */
/*---- register: 0x01[Configuration Register B] parameters ------*/

/*---- register: 0x02[Mode] parameters ------*/
#define HMC5883L_HS						(0x01<<7)	/*set I2C speedup to 3.4MHz */
#define HMC5883L_MODE_CNT				(0x00<0)	/*set continous measurement mode */
#define HMC5883L_MODE_SINGLE			(0x01<0)	/*set single measurement mode */
#define HMC5883L_MODE_IDLE				(0x02<0)	/*set IDLE mode */ /* or 0x03 alse IDLE mode */
/*---- register: 0x02[Mode] parameters ------*
/* ------------- DEFINE HMC5883L PARAMETER  ------------*/



/* ------------- DEFINE HMC5883L SET  ------------*/
#define HMC5883L_CFG_A_SET				(HMC5883L_SAMPLE_AVER_4 | HMC5883L_MEA_CNT_7_5HZ |HMC5883L_MEA_MODE_NORMAL)		/*set the register 0x00 [configuration register A]*/
#define HMC5883L_CFG_B_SET				(HMC5883L_SAMPLE_GAIN1370)			/*set the register 0x00 [configuration register B]*/
#define HMC5883L_MODE_SET				(HMC5883L_MODE_SINGLE)			/*set MODE register */
/* ------------- DEFINE HMC5883L SET  ------------*/



/*  ------------- DEFINE HMC5883L VALUE  ------------*/
/* -------------------------------*/
/* 3 - AXIS data*/
typedef struct HMC5883L_AXIS_INFO
{
	INT16S X_AXIS;
	INT16S Y_AXIS;
	INT16S Z_AXIS;
}AXIS_DATA;
/*-------------------------------*/
/*-------------------------------*/
/* DEVICE ID */
typedef struct HMC5883L_ID
{
	CHAR8U ID1;
	CHAR8U ID2;
	CHAR8U ID3;
}HMC5883L_ID_DATA;
/*-------------------------------*/
/* ------------- DEFINE HMC5883L VALUE  ------------*/


/********************************************* SYSTEM **************************************************/
/*--------------------------------------------------------------------------------------------------*/
/* Reg Addr : 0x0A ~ 0x0C*/
/* ID1 : ASCII 'H'	(0x48)*/
/* ID2 : ASCII '4'	(0x34)*/
/* ID3 : ASCII '3'	(0x33)*/
CHAR8S HMC5883L_GET_ID(HMC5883L_ID_DATA *DATA);	/*READ ONLY*/
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*
		Reg Addr : 0x00
		bit 7 alway set "0" , must be "0"
		bit 6 ~ bit 5 : sample averaged(1~8) per measurement output
		bit 6     bit 5         sample averaged
		0           0               1
		0           1               2
		1           0               4
		1           1               8  (default)
	---------------------------------------------------
	bit 4 ~ bit 2 : set Data output rate. all three data register .
	    bit 4    bit 3      bit2       HZ
		0		0		0		0.75	
	   	0		0		1		1.5
		0		1		0		3	
		0		1		1		7.5
		1		0		0		15	(default)
		1		0		1		30		
		1		1		0		75
		1		1		1		no use
	---------------------------------------------------
	 bit 1 ~ bit 0 : set Measurement Mode
	   bit 0      bit 1        		 Mode
	      0          0		Normal Measurement mode (default)
	      0          1		Positive bias configuration for X, Y, and Z axes.
	      1          0		Negative bias configuration for X, Y and Z axes.
	      1          1		Reserved
	---------------------------------------------------
	RW = 0 or 1  ;  write "0" , read "1"
*/
CHAR8S HMC5883L_SET_CONFIG_A(CHAR8U *CONFIG_A,CHAR8U RW);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*
	Reg Addr : 0x01
	bit7 ~ bit5 : setting the device gain.
	    bit 7      	bit 6     	bit 5       	GAIN 
		0		0		0		 see spec	
	    	0		0		1		 see spec (default)		
		0		1		0		 see spec			
		0		1		1		 see spec		
		1		0		0		 see spec		
		1		0		1		 see spec				
		1		1		0		 see spec		
		1		1		1		 see spec		
	---------------------------------------------------
	bit4 ~ bit0 : alway set "0" , must be "0"
	RW = 0 or 1  ;  write "0" , read "1"
*/
CHAR8S HMC5883L_SET_CONFIG_B(CHAR8U *CONFIG_B,CHAR8U RW);
/*--------------------------------------------------------------------------------------------------*/
/*
	Reg Addr : 0x02
	bit 7 ~ bit 2 : set  alway set "0"
	bit 7 ->  is set "1" internally after each single-measurement operation.
	   bit 1     bit 0      			MODE
		0		0			Continuous-Measurement Mode.
		0		1			Single-Measurement Mode (Default).
		1		0			Idle Mode.
		1		1			Idle Mode2.
-*/
CHAR8S HMC5883L_SET_MODE(CHAR8U MODE);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*
	Reg Addr : 0x02
	bit 7 ~ bit 2 : set  alway set "0"
	bit 7 ->  is set "1" internally after each single-measurement operation.
	   bit 1     bit 0      			MODE
		0		0			Continuous-Measurement Mode.
		0		1			Single-Measurement Mode (Default).
		1		0			Idle Mode.
		1		1			Idle Mode2.
-*/
CHAR8S HMC5883L_GET_MODE(CHAR8U *MODE);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* Reg Addr : 0x03 ~ 0x08*/
/* X-AXIS : 0x03(MSB) , 0x04(LSB)*/
/* Z-AXIS : 0x05(MSB) , 0x06(LSB)*/
/* Y-AXIS : 0x07(MSB) , 0x08(LSB)*/
CHAR8S HMC5883L_GET_3AXIS_DATA(AXIS_DATA  *DATA);			/*READ ONLY*/
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* 
	Reg Addr : 0x09
	bit 7 ~ bit 2 : Reserved
	bit 1 : Data output register lock ; when set "1" lock , until read all axis register(3-axis) , change the mode or change config
	bit 0 : Ready Bit. ; when set "1" -> data ready ;  When RDY bit is clear it shall remain cleared for a 250us.
		 this flag can replace the DRY pin,or DRY pin replace this flag.
*/
CHAR8S HMC5883L_GET_STATUS(CHAR8U  *STATUS);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* test the Positive bias */
/* only test the */
/* 
	this part set Gain =5 , 
	The Positvie bias test range : 243 ~ 575
	The Negative bias test range : -243 ~ -575
       other Gain range see spec self test page.
*/
CHAR8S HMC5883L_SELF_TEST(void);
/*--------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* simple calculate */
/*calculate the HMC5883L azimuth*/
/* return degree */
/* the coordinates is 

			y
			^
			|     /
                   	|    /
			|   /  
                   	|  /		
			| /     degree
                   	|/  
			------------> x

     and point to South
*/
FLOAT HMC5883L_GET_AZIMUTH(AXIS_DATA data);
/*------------------------------------------------------------------------------------------------------*/
/********************************************* SYSTEM **************************************************/

#endif		/*#ifndef __HMC5883L_HEADER__ */