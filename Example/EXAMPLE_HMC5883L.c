/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: E-COMPASS
     File Name		: EXAMPLE_HMC5883L.c
     Function		: EXAMPLE_HMC5883L
     Create Date	: 2020/06/06
---------------------------------------------------------------------- */

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <i2c.h>
#include <alcd.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_HMC5883L.h>



#define ENABLE_SEFT_TEST 					(1)		/*enable self test */
#define HMC5883L_GET_RAW_DATA_ONLY		(0)		/* enable print data to UART TX only */

void  EXAMPLE_HMC5883L(void);

void  EXAMPLE_HMC5883L(void)
{

	CHAR8U check_data;
	CHAR8S status = 0 ; 
    	CHAR8U lcd_char_data[3][4]={0}; 
	CHAR8U write_cfg_data;	
	FLOAT x_data,y_data,result_data,cal;
	CHAR8U	lcd_char_angle_data[5]={0};

 	HMC5883L_ID_DATA id_data;
	AXIS_DATA xyz_data;
	
			printf("-------------------- E-COMPASS HMC5883L --------------------\r\n");
               	/*E-COMPASS HMC5883L*/


			/* read HMC5883L ID */
			status = HMC5883L_GET_ID(&id_data);
			if(status!=0)
			{
				printf("read HMC5883L ID fail\r\n");
			}
			else
			{
				printf(" HMC5883L ID1 =0x%x; ID2 =0x%x; ID3 =0x%x\r\n",id_data.ID1,id_data.ID2,id_data.ID3);
			}


#if ENABLE_SEFT_TEST
			/* self test */
			status =HMC5883L_SELF_TEST();
			if(status!=0)
			{
				printf("MHC5883L self test fail\r\n");
			}
#endif

			/* set configuration A */
			write_cfg_data = HMC5883L_CFG_A_SET;
			status = HMC5883L_SET_CONFIG_A(&write_cfg_data,0);
			if(status!=0)
			{
				printf("read HMC5883L set CFG A fail\r\n");
			}
			else
			{
				printf("read HMC5883L set CFG A success\r\n");
			}

			/* set configuration B */
			write_cfg_data = HMC5883L_CFG_B_SET;
			status = HMC5883L_SET_CONFIG_B(&write_cfg_data,0);
			if(status!=0)
			{
				printf("read HMC5883L set CFG B fail\r\n");
			}
			else
			{
				printf("read HMC5883L set CFG B success\r\n");
			}

			/* if mode is continous measurment mode , set the mode */
			if((HMC5883L_MODE_SET&0x03) == HMC5883L_MODE_CNT)
			{
				/*set HMC5883L continous measurement */
				status = HMC5883L_SET_MODE(HMC5883L_MODE_SET);
				if(status!=0)
				{
					printf("read HMC5883L set continous mode fail\r\n");
				}
				else
				{
					printf("read HMC5883L set continous mode success\r\n");
				}
			}



#if(HMC5883L_GET_RAW_DATA_ONLY==1)

		while(1)
		{
			/* if mode is single measurment mode , set the mode */
				if((HMC5883L_MODE_SET&0x03) == HMC5883L_MODE_SINGLE)
				{
					/*set HMC5883L single measurement */
					status = HMC5883L_SET_MODE(HMC5883L_MODE_SET);
					if(status!=0)
					{
					//	printf("read HMC5883L set mode fail\r\n");
					}
					else
					{
					//	printf("read HMC5883L set mode success\r\n");
					}
				}

				delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
				/* read X,Y,Z axis data */
				status=HMC5883L_GET_3AXIS_DATA(&xyz_data);

				
				delay_ms(1);	/* tiny delay */
				

		

				#if 0
				/*print x,y,z */
				printf("%d %d %d\r\n",xyz_data.X_AXIS,xyz_data.Y_AXIS,xyz_data.Z_AXIS);
				#endif


				#if 1
				/*print x,y only */
				printf("%d %d \r\n",xyz_data.X_AXIS,xyz_data.Y_AXIS);
				#endif
				
				delay_ms(30); /* tiny delay */
		}
	
#endif









			while(1)
			{
			
				/* if mode is single measurment mode , set the mode */
				if((HMC5883L_MODE_SET&0x03) == HMC5883L_MODE_SINGLE)
				{
					/*set HMC5883L single measurement */
					status = HMC5883L_SET_MODE(HMC5883L_MODE_SET);
					if(status!=0)
					{
						printf("read HMC5883L set mode fail\r\n");
					}
					else
					{
						printf("read HMC5883L set mode success\r\n");
					}
				}

				delay_ms(7);	/* SPEC page8 ,say wait 6mS  */
				
				/* read X,Y,Z axis data */
				status=HMC5883L_GET_3AXIS_DATA(&xyz_data);
				if(status!=0)
				{
					printf("read HMC5883L XYZdata fail\r\n");
				}
				
				delay_ms(1);	/* tiny delay */
				
				status = HMC5883L_GET_STATUS(&check_data);
				if(status==0)
				{
					printf("check status 0x%x \r\n",check_data);
				}
					

				/* calculate X,Y,Z data for display */
	                     /* X AXIS*/
	                     lcd_char_data[0][0]=(INT32U)(xyz_data.X_AXIS/1000)%10;
	                     lcd_char_data[0][1]=(INT32U)(xyz_data.X_AXIS/100)%10;   
	                     lcd_char_data[0][2]=(INT32U)(xyz_data.X_AXIS/10)%10;  
	                     lcd_char_data[0][3]=(INT32U)(xyz_data.X_AXIS)%10;   
	                     
	                     /* Y AXIS*/   
	                     lcd_char_data[1][0]=(INT32U)(xyz_data.Y_AXIS/1000)%10;
	                     lcd_char_data[1][1]=(INT32U)(xyz_data.Y_AXIS/100)%10;   
	                     lcd_char_data[1][2]=(INT32U)(xyz_data.Y_AXIS/10)%10;  
	                     lcd_char_data[1][3]=(INT32U)(xyz_data.Y_AXIS)%10;         
	                     
	                     
	                     /* Z AXIS*/   
	                     lcd_char_data[2][0]=(INT32U)(xyz_data.Z_AXIS/1000)%10;
	                     lcd_char_data[2][1]=(INT32U)(xyz_data.Z_AXIS/100)%10;   
	                     lcd_char_data[2][2]=(INT32U)(xyz_data.Z_AXIS/10)%10;  
	                     lcd_char_data[2][3]=(INT32U)(xyz_data.Z_AXIS)%10;         


	                     /* SHOW X axis DATA */                    
	            		lcd_gotoxy(0,0);
	            		lcd_putsf("X axis:");     
	            		if(xyz_data.X_AXIS<0)
	            		{
	            			lcd_putchar(45);		/* LCD show "-"  mean negative */
				}                             
	           		else
				{
					lcd_putchar(32);		/* LCD show " "  mean positive */
				}   
					
				/* show X axis data on LCD */
				lcd_putchar(48+lcd_char_data[0][0]);
				lcd_putchar(48+lcd_char_data[0][1]);
				lcd_putchar(48+lcd_char_data[0][2]);
				lcd_putchar(48+lcd_char_data[0][3]);

				/* SHOW Y axis DATA */    
				lcd_gotoxy(0,1);
				lcd_putsf("Y axis:"); 
	             		if(xyz_data.Y_AXIS<0)
	           		{
	           			lcd_putchar(45);		/* LCD show "-"  mean negative */
				}                             
	            		else
				{
					lcd_putchar(32);		/* LCD show " "  mean positive */
				}   


				/* show Y axis data on LCD */
	                 	lcd_putchar(48+lcd_char_data[1][0]);
	                	lcd_putchar(48+lcd_char_data[1][1]);
	                 	lcd_putchar(48+lcd_char_data[1][2]);
	                 	lcd_putchar(48+lcd_char_data[1][3]);
	                    
				/* SHOW Z axis DATA */    
	            		lcd_gotoxy(0,2);
	            		lcd_putsf("Z axis:"); 
	           		if(xyz_data.Z_AXIS<0)
	            		{
	            			lcd_putchar(45);
				}                             
	            		else
				{
					lcd_putchar(32);
				}
					   
				/* show Y axis data on LCD */
	                 	lcd_putchar(48+lcd_char_data[2][0]);
	                 	lcd_putchar(48+lcd_char_data[2][1]);
	                 	lcd_putchar(48+lcd_char_data[2][2]);
	                 	lcd_putchar(48+lcd_char_data[2][3]);



				/* calculate the azimuth group */
				{
					/* simple calculate */
					/* calculate the azimuth */
					result_data =HMC5883L_GET_AZIMUTH(xyz_data);
						
					if((result_data < 22.5) || (result_data > 337.5 ))
					{
						printf("\r\nSouth\r\n");
					}
					else if((result_data > 22.5) && (result_data < 67.5 ))
					{
						printf("\r\nSouth-West\r\n");
					}
					else if((result_data > 67.5) && (result_data < 112.5 ))
					{
						printf("\r\nWest\r\n");
					}
					else if((result_data > 112.5) && (result_data < 157.5 ))
					{
						printf("\r\nNorth-West\r\n");
					}
					else if((result_data > 157.5) && (result_data< 202.5 ))
					{
						printf("\r\nNorth\r\n");
					}
					else if((result_data > 202.5) && (result_data < 247.5 ))
					{
						printf("\r\nNorthEast\r\n");
					}
					else if((result_data > 247.5) && (result_data < 292.5 ))
					{
						printf("\r\nEast\r\n");
					}
					else if((result_data > 292.5) && (result_data < 337.5 ))
					{
						printf("\r\nSouthEast\r\n");
					}

					/* SHOW Angle DATA */    
					lcd_gotoxy(0,3);
					lcd_putsf("Ang:"); 
								
					/* calculate azimuth DATA */   
					lcd_char_angle_data[0]=(INT32U)((INT32U)result_data/1000)%10;
					lcd_char_angle_data[1]=(INT32U)((INT32U)result_data/100)%10;   
					lcd_char_angle_data[2]=(INT32U)((INT32U)result_data/10)%10;  
					lcd_char_angle_data[3]=(INT32U)((INT32U)result_data)%10;         
					lcd_char_angle_data[4]=(INT32U)(result_data*10)%10;      

									   
					/* SHOW azimuth DATA */  
					lcd_putchar(48+lcd_char_angle_data[0]);
					lcd_putchar(48+lcd_char_angle_data[1]);			 		
					lcd_putchar(48+lcd_char_angle_data[2]);		
					lcd_putchar(48+lcd_char_angle_data[3]);
					lcd_putchar(46);    /* print "."  */ 	
					lcd_putchar(48+lcd_char_angle_data[4]);						 
			
				}		


				delay_ms(30);	/* tiny delay */
				
			}
			
			printf("-------------------- E-COMPASS HMC5883L --------------------\r\n");
}
