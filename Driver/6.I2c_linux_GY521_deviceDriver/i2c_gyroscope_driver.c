/***************************************************************************//**
 *  \file       i2c-gyroscope_driver.c
 *
 *  \details    Simple I2C driver explanation (gyroscope Interface)-
 *  
 *  \IC---MPU6050
 *
 *  \author   sachin
 *
 *  \Tested with Linux raspberrypi 5.1.51-v7l+
 *
 * *******************************************************************************/


#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define I2C_BUS_AVAILABLE   (  1  )              // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME   ( "ETX_MPU6050")         // Device and Driver Name
#define MPU6050_SLAVE_ADDR  (  0x68 )              // MPU6050  Slave Address

#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40
#define REG_PWR_MGMT_1 0x6B
#define REG_ACCEL_CONFIG 0x1C
#define REG_SMPRT_DIV 0x19
#define REG_CONFIG 0x1A
#define REG_FIFO_EN 0x23
#define REG_USER_CTRL 0x6A
#define REG_FIFO_COUNT_L 0x72
#define REG_FIFO_COUNT_H 0x73
#define REG_FIFO 0x74
#define REG_WHO_AM_I 0x75

static struct i2c_adapter *etx_i2c_adapter     = NULL;  // I2C Adapter Structure
static struct i2c_client  *etx_i2c_client_mpu6050 = NULL;  // I2C Cient Structure (In our case it is mpu6050- gyroscope)

static void MPU6050_Sensor_Write(bool is_cmd, unsigned char data);
static int MPU6050_GyroInit(void);
static void mpu6050_temperature(void);
static void mpu6050_accelerometer(void);
static void mpu6050_gyroscope(void);
/*
 ** This function writes the data into the I2C client
 **
 **  Arguments:
 **      buff -> buffer to be sent
 **      len  -> Length of the data
 **   
 */

static int I2C_Write(unsigned char *buf, unsigned int len)
{
	/*
	 ** Sending Start condition, Slave address with R/W bit, 
	 ** ACK/NACK and Stop condtions will be handled internally.
	 */ 
	int ret = i2c_master_send(etx_i2c_client_mpu6050, buf, len);

	return ret;
}

/*
 ** This function reads one byte of the data from the I2C client
 **
 **  Arguments:
 **      out_buff -> buffer wherer the data to be copied
 **      len      -> Length of the data to be read
 ** 
 */
static int I2C_Read(unsigned char *out_buf, unsigned int len)
{
	/*
	 ** Sending Start condition, Slave address with R/W bit, 
	 ** ACK/NACK and Stop condtions will be handled internally.
	 */ 
	int ret = i2c_master_recv(etx_i2c_client_mpu6050, out_buf, len);

	return ret;
}

/*
 ** This function is specific to the gyroscope.
 ** This function sends the command/data to the .
 **
 **  Arguments:
 **      is_cmd -> true = command, flase = data
 **      data   -> data to be written
 ** 
 */
static void MPU6050_Sensor_Write_cmd_byte(unsigned char is_cmd, unsigned char data)
{
	unsigned char buf[2] = {0};
	int ret;

	buf[0] = is_cmd;
	buf[1] = data;

	ret = I2C_Write(buf, 2);
}
/* This function read the temperature data*/
static void mpu6050_temperature(void)
{
	u8 j=0,addr;
	u8 command=0x3B; 			//reading from ACCEL_XOUT_H
	char kbuff[20];
	printk("In read function\n");

   	struct i2c_client *client = etx_i2c_client_mpu6050;

	i2c_smbus_write_byte_data (client,0x6B,0x00);			//configuring PWR_MGMT_1 register

	addr=i2c_smbus_read_byte_data (client,0x75);			//reading WHO_AM_I register
	printk("who am I register slave address=%x\n",addr);
	memset(kbuff,'\0',20);
	while(j<15)
	{
	kbuff[j]=i2c_smbus_read_byte_data (client,command++);		//SMBUS read command
        printk("data at %d-%d\n",j,kbuff[j]);
        j++;
	}
}

/*This function read the acceleromete data*/
static void mpu6050_accelerometer(void)
{

}

/*this function read the Gyroscope  data*/
static void mpu6050_gyroscope(void)
{

}

/*
 ** This function sends the commands that need to used to Initialize the MPU6050 Gyro sensor.
 **
 **  Arguments:
 **      none
 ** 
 */
static int MPU6050_GyroInit(void)
{

	pr_info("!!!!!!!........MPU6050 Init.....!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	struct i2c_client *client = etx_i2c_client_mpu6050;
	msleep(100);               // delay

	printk("WHO M I=%x\n",i2c_smbus_read_byte_data(client, 0x75));				//Slave address=0x68

//	i2c_smbus_write_byte_data(client,0x6B,0x02);
	MPU6050_Sensor_Write_cmd_byte(0x6B,0x02);
	printk("power management register=%d\n",i2c_smbus_read_byte_data(client,0x6B));

//	i2c_smbus_write_byte_data(client,0x19,0x07);
	MPU6050_Sensor_Write_cmd_byte(0x19,0x07);
	printk("SMPLRT_DIV register=%d\n",i2c_smbus_read_byte_data(client,0x19));

//	i2c_smbus_write_byte_data(client,0x1B,0x08);
	MPU6050_Sensor_Write_cmd_byte(0x1B,0x08);
	printk("GYRO_CONFIG register=%d\n",i2c_smbus_read_byte_data(client,0x1B));

//	i2c_smbus_write_byte_data(client,0x1C,0x00);
	MPU6050_Sensor_Write_cmd_byte(0x1C,0x00);
	printk("ACCEL_CONFIG register=%d\n",i2c_smbus_read_byte_data(client,0x1C));

	int i =0;
	while( i<5)
	{
	msleep(2000);
	mpu6050_temperature();
	i++;
	}
	return 0;
}


/*
 ** This function getting called when the slave has been found
 ** Note : This will be called only once when we load the driver.
 */

static int etx_mpu6050_probe(struct i2c_client *client, const struct i2c_device_id *id)
{

	pr_info("!!!!!!!........MPU6050 Probed.........!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	dev_info(&client->dev, "MPU6050 device probed"); 

	/*mpu6050 init function*/
	MPU6050_GyroInit();

	return 0;
}

/*
 ** This function getting called when the slave has been removed
 ** Note : This will be called only once when we unload the driver.
 */

static int etx_mpu6050_remove(struct i2c_client *client)
{   

	pr_info("!!!!!!!!!!!......MPU6050 Removed.......!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return 0;
}

/*
 ** Structure that has slave device id
 */

static const struct i2c_device_id etx_mpu6050_id[] = {
	{ SLAVE_DEVICE_NAME, 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, etx_mpu6050_id);

/*
 ** I2C driver Structure that has to be added to linux
 */

static struct i2c_driver etx_mpu6050_driver = {
	.driver = {
		.name   = SLAVE_DEVICE_NAME,
		.owner  = THIS_MODULE,
	},
	.probe          = etx_mpu6050_probe,
	.remove         = etx_mpu6050_remove,
	.id_table       = etx_mpu6050_id,
};

/*
 ** I2C Board Info strucutre
 */

static struct i2c_board_info mpu6050_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, MPU6050_SLAVE_ADDR)
};

/*
 ** Module Init function
 */

static int __init etx_driver_init(void)
{
	int ret = -1;
	etx_i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);

	if(etx_i2c_adapter != NULL)
	{
		etx_i2c_client_mpu6050 = i2c_new_client_device(etx_i2c_adapter, &mpu6050_i2c_board_info);

		if( etx_i2c_client_mpu6050 != NULL )
		{
			i2c_add_driver(&etx_mpu6050_driver);
			ret = 0;
		}

		i2c_put_adapter(etx_i2c_adapter);
	}

	pr_info("\n!!!!!!!!!!!!...........Driver Added.....!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return ret;
}
//module_i2c_driver(etx_mpu6050_driver);
/*
 ** Module Exit function
 */
static void __exit etx_driver_exit(void)
{
	i2c_unregister_device(etx_i2c_client_mpu6050);
	i2c_del_driver(&etx_mpu6050_driver);
	pr_info("!!!!!!!!.....Driver Removed Sucessfully..........!!!!!!!!!!!!!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(" Sachin ");
MODULE_DESCRIPTION("Simple I2C driver explanation (MPU6050 gyroscope, Accelerometer, temperature Interface)");
MODULE_VERSION("1.00");
