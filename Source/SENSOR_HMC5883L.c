/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: E-COMPASS
     File Name		: SENSOR_HMC5883L.c
     Function		: SENSOR_HMC5883L
     Create Date	: 2017/04/27
---------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <delay.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_HMC5883L.h>



#define HMC5883L_DEBUG		(0)		/* set "1" to printf debug message */


/********************************************* SYSTEM **************************************************/
/*--------------------------------------------------------------------------------------------------*/
/* Reg Addr : 0x0A ~ 0x0C*/
/* ID1 : ASCII 'H'	(0x48)*/
/* ID2 : ASCII '4'	(0x34)*/
/* ID3 : ASCII '3'	(0x33)*/
CHAR8S HMC5883L_GET_ID(HMC5883L_ID_DATA *DATA)
{
	CHAR8S status = 0;
	CHAR8U buffer[3]={0};

		/* read HMC5883L ID */
		status = i2c_read_n_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_IDA,3,&buffer[0]);
		if(status !=1)
		{
			DATA->ID1 = 0;
			DATA->ID2 = 0;
			DATA->ID3 = 0;
			return -1 ;	/* read fail ; error!*/
		}
		else
		{
			DATA->ID1 = buffer[0];
			DATA->ID2 = buffer[1];
			DATA->ID3 = buffer[2];
			return 0 ;	/*read success!*/
		}
		
}
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
CHAR8S HMC5883L_SET_CONFIG_A(CHAR8U *CONFIG_A,CHAR8U RW)
{
	CHAR8S flag = 0;
       CHAR8U DATA = 0;

		if(RW !=0 && RW!=1) 
		{
			return -1; 		/*error R/W flag*/
		}
		
		if(RW == 0)
		{
			DATA = *CONFIG_A;
			flag = i2c_write_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_CONFIGA,DATA);
			delay_us(20);		/*after set must be delay .*/
			if(flag!=1)
			{
				return -1 ; 	/* write fail ; error!*/
			}
			else
			{
				return 0 ; 	/*write success!*/
			}
		}

		if(RW == 1)
		{
			flag = i2c_read_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_CONFIGA,&DATA);
			delay_us(20); 	/*after set must be delay .*/
			if(flag !=1)
			{
				return -1 ;	/*read fail ; error!*/
			}
			else
			{
				*CONFIG_A = DATA;
				return 0 ;	/*read success!*/
			}
		}

}
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*
	Reg Addr : 0x01
	bit7 ~ bit5 : setting the device gain.
	    bit 7      bit 6     bit 5       GAIN
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
CHAR8S HMC5883L_SET_CONFIG_B(CHAR8U *CONFIG_B,CHAR8U RW)
{
	CHAR8S flag = 0;
       CHAR8U DATA = 0;

		if(RW !=0 && RW!=1) 
		{
			return -1;	/*error R/W flag*/
		}

		if(RW == 0)
		{
			DATA = *CONFIG_B;
			flag = i2c_write_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_CONFIGB,DATA);
			delay_us(20);	/*after set must be delay .*/
			if(flag!=1)
			{
				return -1 ;	/* write fail ; error!*/
			}
			else
			{
				return 0 ;	/* write success!*/
			}
		}

		if(RW == 1)
		{
			flag = i2c_read_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_CONFIGB,&DATA);
			delay_us(20);	/*after set must be delay .*/
			if(flag !=1)
			{
				return -1 ; /*read fail ; error!*/
			}
			else
			{
				*CONFIG_B = DATA;
				return 0 ; /*read success!*/
			}
		}

}
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
			1		1			Idle Mode -2.
*/
CHAR8S HMC5883L_SET_MODE(CHAR8U MODE)
{
	CHAR8S status = 0;
	CHAR8U DATA = 0;

		/* read mode */
		status = i2c_write_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_MODE,DATA);
		
		delay_us(20); 	/*after set must be delay .*/
		
		if(status!=1)
		{
			return -1 ;	/* write fail ; error!*/
		}
		else
		{
			return 0 ; 	/*write success!*/
		}
	


}
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
*/
CHAR8S HMC5883L_GET_MODE(CHAR8U *MODE)
{
	CHAR8S status = 0;
       CHAR8U data = 0;

		/* read mode register */
		status = i2c_read_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_MODE,&data);
				
		delay_us(20); /*after set must be delay .*/
		if(status !=1)
		{
			return -1 ;	/*read fail ; error!*/
		}
		else
		{
			*MODE = data;
			return 0 ; 	/*read success!*/
		}


}
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* Reg Addr : 0x03 ~ 0x08*/
/* X-AXIS : 0x03(MSB) , 0x04(LSB)*/
/* Z-AXIS : 0x05(MSB) , 0x06(LSB)*/
/* Y-AXIS : 0x07(MSB) , 0x08(LSB)*/
CHAR8S HMC5883L_GET_3AXIS_DATA(AXIS_DATA  *DATA)
{
	CHAR8S status = 0;
	CHAR8U buffer[6]={0};
	CHAR8U data =0;

		/* read status to check the data ready */
		status = HMC5883L_GET_STATUS(&data);
		if(status!=0)
		{
			return -1;	/* read status fail */
		}	
		
		#if HMC5883L_DEBUG
		printf("status reg 0x%x\r\n",data);
		#endif		
		
		if(status!=0)
		{	
		
			#if HMC5883L_DEBUG
			printf("data not ready\r\n");
			#endif
		
			return -1;	/* check fail*/
		}
		
		if( data | 0x01 )	/*check RDY flag ; if "1" ready , "0" not ready.*/
		{

			/*read 3 -axis data X,Y,Z */
			status = i2c_read_n_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_X_MSB,6,&buffer[0]);
			
			delay_us(20); /*after set must be delay .*/
			
			if(status !=1)
			{
				DATA->X_AXIS = 0 ;
				DATA->Z_AXIS = 0 ;
				DATA->Y_AXIS = 0 ;
				
				return -1; /* read fail ; error!*/
			}
			else
			{
				DATA->X_AXIS = (INT16S)(buffer[0]<<8) | (INT16S)(buffer[1]) ;
				DATA->Z_AXIS = (INT16S)(buffer[2]<<8) | (INT16S)(buffer[3]) ;
				DATA->Y_AXIS = (INT16S)(buffer[4]<<8) | (INT16S)(buffer[5]) ;
				
				#if HMC5883L_DEBUG
				printf("X = %d , Y = %d , Z = %d \r\n",DATA->X_AXIS,DATA->Y_AXIS,DATA->Z_AXIS);
				#endif
			
				return 0; /* read success!*/
			}
		}
		else
		{
			return -1; /* the RDY bit not Ready!!*/
		}
}
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*
	Reg Addr : 0x09
	bit 7 ~ bit 2 : Reserved
	bit 1 : Data output register lock ; when set "1" lock , until read all axis register(3-axis) , change the mode or change config
	bit 0 : Ready Bit. ; when set "1" -> data ready ;  When RDY bit is clear it shall remain cleared for a 250us.
		this flag can replace the DRY pin,or DRY pin replace this flag.
*/
CHAR8S HMC5883L_GET_STATUS(CHAR8U  *read_data)
{

	CHAR8S status = 0;
	CHAR8U data = 0;

		/* read status register */
		status = i2c_read_1_byte_data(HMC5883L_SLAVE_ADDRESS,HMC5883L_REG_STATUS,&data);
		
		delay_us(20); /*after set must be delay .*/
		
		if(status !=1)
		{
			return -1 ;	/* read fail ; error!*/
		}
		else
		{
			*read_data = data & 0x3;	/*0x3:mask */
			return 0 ;	/*read success!*/
		}
}
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
CHAR8S HMC5883L_SELF_TEST(void)
{
	CHAR8S status = 0;
	CHAR8U data = 0;
	CHAR8U success_cnt =0,fail_cnt=0,dummy_cnt=0;
	AXIS_DATA	self_test_xyz_data;


		printf("self test start !!\r\n");
	
		/*==================== Positive bias test  ====================*/
		printf("Positive bias test start !!\r\n");
		/* step 1:  set config A */
		data = (HMC5883L_SAMPLE_AVER_8 | HMC5883L_MEA_CNT_15HZ | HMC5883L_MEA_MODE_POS_BIAS);
		status = HMC5883L_SET_CONFIG_A(&data,0);
		if(status!=0)
		{
			printf("read HMC5883L set CFG A fail\r\n");
			return -1;
		}		

		/* step 2: set config B , GAIN =5*/
		data = HMC5883L_SAMPLE_GAIN390;
		status = HMC5883L_SET_CONFIG_B(&data,0);
		if(status!=0)
		{
			printf("read HMC5883L set CFG B fail\r\n");
			return -1;
		}


		/* step 3: SET measurement -> Continous mode */
		status = HMC5883L_SET_MODE(HMC5883L_MODE_SET);
		if(status!=0)
		{
			printf("read HMC5883L set continous mode fail\r\n");
			return -1;
		}


		/* dummy read , wait data stable */
		dummy_cnt=0;
		while(1)
		{

			delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
			/* read X,Y,Z axis data */
			status=HMC5883L_GET_3AXIS_DATA(&self_test_xyz_data);
			dummy_cnt++;
			if(dummy_cnt>10)
			{
				break ;
			}
		}

		/*check every axis are limit in 243 ~575 */
		/*check 10 times */
		success_cnt=0;
		fail_cnt=0;
		while(1)
		{

			delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
			/* read X,Y,Z axis data */
			status=HMC5883L_GET_3AXIS_DATA(&self_test_xyz_data);
			if(status!=0)
			{
				printf("read HMC5883L XYZdata fail\r\n");
				return -1;
			}
			else
			{
				/*check every axis are limit in 243 ~575 */
				if( (self_test_xyz_data.X_AXIS>=243) &&(self_test_xyz_data.X_AXIS<=575) /
					(self_test_xyz_data.Y_AXIS>=243) &&(self_test_xyz_data.Y_AXIS<=575) /
					(self_test_xyz_data.Z_AXIS>=243) &&(self_test_xyz_data.Z_AXIS<=575))
				{
					success_cnt++;
					printf("x:%d , y:%d , z:%d ,pass time = %d\r\n",self_test_xyz_data.X_AXIS,self_test_xyz_data.Y_AXIS,self_test_xyz_data.Z_AXIS,success_cnt);	
					if((success_cnt + fail_cnt)>=10)
					{
						break;
					}
				}
				else
				{

					fail_cnt++;
					printf("x:%d , y:%d , z:%d ,fail time = %d\r\n",self_test_xyz_data.X_AXIS,self_test_xyz_data.Y_AXIS,self_test_xyz_data.Z_AXIS,fail_cnt);	
					if((success_cnt + fail_cnt)>=10)
					{
						break;
					}
				}

				if(fail_cnt>0)
				{
					printf("Self test Positive bias fail !!!\r\n");	
				}
				else
				{
					printf("Self test Positive bias success !!!\r\n");	
				}
			}

		}

		/*==================== Positive bias test  ====================*/

		/*==================== Negative bias test  ====================*/
		printf("Negative bias test start !!\r\n");
		
		/* step 1:  set config A to Negative bais mode*/
		data = (HMC5883L_SAMPLE_AVER_8 | HMC5883L_MEA_CNT_15HZ | HMC5883L_MEA_MODE_NEG_BIAS);
		status = HMC5883L_SET_CONFIG_A(&data,0);
		if(status!=0)
		{
			printf("read HMC5883L set CFG A fail\r\n");
			return -1;
		}		
		
		/* dummy read , wait data stable */
		dummy_cnt=0;
		while(1)
		{
			delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
			/* read X,Y,Z axis data */
			status=HMC5883L_GET_3AXIS_DATA(&self_test_xyz_data);
			dummy_cnt++;
			if(dummy_cnt>10)
			{
				break ;
			}
		}

		/*check every axis are limit in -243 ~-575 */
		/*check 10 times */
		success_cnt=0;
		fail_cnt=0;
		while(1)
		{

			delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
			/* read X,Y,Z axis data */
			status=HMC5883L_GET_3AXIS_DATA(&self_test_xyz_data);
			if(status!=0)
			{
				printf("read HMC5883L XYZdata fail\r\n");
				return -1;
			}
			else
			{
				/*check every axis are limit in -243 ~-575 */
				if( (self_test_xyz_data.X_AXIS<= -243) &&(self_test_xyz_data.X_AXIS>= -575) /
					(self_test_xyz_data.Y_AXIS<= -243) &&(self_test_xyz_data.Y_AXIS>= -575) /
					(self_test_xyz_data.Z_AXIS<= -243) &&(self_test_xyz_data.Z_AXIS>= -575))
				{
					success_cnt++;
					printf("x:%d , y:%d , z:%d ,pass time = %d\r\n",self_test_xyz_data.X_AXIS,self_test_xyz_data.Y_AXIS,self_test_xyz_data.Z_AXIS,success_cnt);	
					if((success_cnt + fail_cnt)>=10)
					{
						break;
					}
				}
				else
				{

					fail_cnt++;
					printf("x:%d , y:%d , z:%d ,fail time = %d\r\n",self_test_xyz_data.X_AXIS,self_test_xyz_data.Y_AXIS,self_test_xyz_data.Z_AXIS,fail_cnt);	
					if((success_cnt + fail_cnt)>=10)
					{
						break;
					}
				}

				if(fail_cnt>0)
				{
					printf("Self test Negative bias fail !!!\r\n");	
				}
				else
				{
					printf("Self test Negative bias success !!!\r\n");	
				}
			}

		}

		printf("Self test Pass!!!!!!!\r\n");	

		/*==================== Negative bias test  ====================*/		
}
/*--------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* simple calculate */
/* calculate the HMC5883L azimuth*/
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
FLOAT HMC5883L_GET_AZIMUTH(AXIS_DATA data)
{
	FLOAT x_data,y_data,result_data,cal;
	
		/* calculate the azimuth */
		result_data =atan2((FLOAT)data.Y_AXIS,(FLOAT)data.X_AXIS)*180.0/3.14159 +180.0;			
		return result_data;

}
/*------------------------------------------------------------------------------------------------------*/
/********************************************* SYSTEM **************************************************/
