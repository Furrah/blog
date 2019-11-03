---
title: "FPGA I2C Wishbone Interface and Testing "
date: 2019-10-27T20:04:40+01:00
tags: ["FPGA", "I2C", "wishbone", "interface", "verilog", "VHDL"]
type: "E"
draft: false
---


### Requirements 
* Lua 5.14+ (recommended 5.15) (https://github.com/rjpcomputing/luaforwindows/releases/tag/v5.1.5-52)
* wbgen2 https://www.ohwr.org/project/wishbone-gen
* MCP2221A USB2.0 to I2C/UART Protocol Converter with GPIO
 * Any USB to I2C device will work.

# Creating an I2C wishbone interface for FPGA

The wishbone interface acts as a bridge between the FPGA and external signals containing a master and a slave. In this example the FPGA will be acting as an I2C slave with two registers;

* 1 read/write
* 1 read only.




#### Create the .wb file for the I2C slave
 * documentation found at https://ohwr.org/project/wishbone-gen/wikis/wbgen2-reg

The .wb defines the registers for the I2C slave. Here we define two registers <br>

* one the I2C master can read and write from 
* one to be read only by the I2C master

Save as I2C_Slave.wb 

```systemverilog

peripheral {
	name ="I2C_Slave"; 
	prefix="i2cslave"; 
	hdl_entity="I2C_Slave"; // generally make the hdl entity the same as the name  and save the file with name + .wb
	
// register for read/writing.
	reg {
		prefix = "test_rw";
		name = "test_rw";
		decription = "A read/write test register";
		
		field {
			name = "val";
			prefix = "val";
			type = SLV; // std_logic_vector
			size = 32; // always a 32 bit register 
			access_bus = READ_WRITE; // master can read and write from this register 
			access_dev = READ_ONLY; // FPGA can only read from this register 
		};
	};


// register for read only 
	reg {
		prefix = "test_ro";
		name = "test_ro";
		decription = "A read test register";
		
		field {
			name = "val";
			prefix = "val";
			type = SLV;
			size = 32;
			access_bus = READ_ONLY;
			access_dev = WRITE_ONLY;
		};
	};
};
```


#### Generate I2C_Slave.vhd file using wbgen2 

```bash
lua wbgen2 -V I2C_Slave.vhd -D I2C_Slave.html I2C_Slave.wb
```


This can be made easier using a .bat file. example below. @pause stops the application exiting - useful for compiler errors.  

```bat
lua C:\Users\jospence\Downloads\wishbone-gen\wbgen2 -V I2C_Slave.vhd -D I2C_Slave.html I2C_Slave.wb
@pause
```

#### Add I2C_Slave.vhd to project

doesn't matter if you are using VHDL or Verilog. 

#### Add wb_i2c_bridge.vhd to project from general core modules

(https://ohwr.org/project/general-cores) 
NOTE there will be many more files required - all of which are found in general cores and will be flagged by the compiler 

#### Connect ports to the wb_i2c_bridge
```systemverilog
wire        wb_stb;
wire        wb_cyc;
wire  [3:0] wb_sel_b4;
wire        wb_we;
wire [31:0] wb_dat_i_b32;
wire [31:0] wb_dat_o_b32;
wire [31:0] wb_adr_b32;
wire        wb_ack;
wire        wb_rty;
wire        wb_err;

wire        Scl_o, Scl_en_o;
wire        Sda_o, Sda_en_o;

assign Scl_io = (Scl_en_o) ? Scl_o : 1'bZ; // when I2C not enabled make pins high impedance 
assign Sda_io = (Sda_en_o) ? Sda_o : 1'bZ; // when I2C not enabled make pins high impedance 
```
```systemverilog
// # is how parameters are passe din verilog - .g_fsm_wdt(480000) this is the watchdog time out. 
wb_i2c_bridge #(.g_fsm_wdt(480000)) i_wb_i2c_bridge (
    .clk_i      (Clk_ik), // system clock - external crystal  
    .rst_n_i    (!Reset_r), // system reset 

    .scl_i      (Scl_io), 
    .scl_o      (Scl_o),
    .scl_en_o   (Scl_en_o),
    .sda_i      (Sda_io),
    .sda_o      (Sda_o),
    .sda_en_o   (Sda_en_o),

    .i2c_addr_i (7'b1000000), // address of I2C device hex value 0x40

    .tip_o      (),
    .err_p_o    (),
    .wdto_p_o   (),

    .wbm_stb_o  (wb_stb),
    .wbm_cyc_o  (wb_cyc),
    .wbm_sel_o  (wb_sel_b4),
    .wbm_we_o   (wb_we),
    .wbm_dat_i  (wb_dat_o_b32), // Notice wb_dat_o_b32 is given to wbm_dat_i and wb_dat_i_b32 given to wbm_dat_o.
    .wbm_dat_o  (wb_dat_i_b32),
    .wbm_adr_o  (wb_adr_b32),
    .wbm_ack_i  (wb_ack),
    .wbm_rty_i  (wb_rty),
    .wbm_err_i  (wb_err)
);
```


#### Connect ports to I2C_Slave 

```systemverilog
I2C_Slave i_I2C_Slave (
    .rst_n_i    (!Reset_r),
    .clk_sys_i  (Clk_ik),
    .wb_adr_i   (wb_adr_b32),
    .wb_dat_i   (wb_dat_i_b32),
    .wb_dat_o   (wb_dat_o_b32),
    .wb_cyc_i   (wb_cyc),
    .wb_sel_i   (wb_sel_b4),
    .wb_stb_i   (wb_stb),
    .wb_we_i    (wb_we),
    .wb_ack_o   (wb_ack),
    .wb_err_o   (wb_err),
    .wb_rty_o   (wb_rty),
    .wb_stall_o (),
    .i2cslave_test_rw_val_o(TestReg_b32),   // addr=0x00
    .i2cslave_test_ro_val_i(32'hDEADBEEF)   // addr=0x01
);
```


# Testing

To communicate with the FPGA we will be using the MCP2221A chip which conveniently has a python library built for it and can be installed with pip.

```bash
pip install PyMCP2221A
```

**one of the  nuances with the wishbone interface is that the registers require 16-bit addresses, opposed to other chips requiring 8-bit register addresses.**

Python script.
First lets initialise our device and create a couple of functions for reading and writing to our I2C slave. The pyMCP22221A library recommends creating the object, resetting and then creating it again. I don't know why.

Second, remember that the address of our FPGA is at 0x40 which can be found in wb_i2c_bridge.v

```python

def Read_I2C(device,addr,register,num_bytes):
	device.I2C_Write_No_Stop(addr, [0x00, register])
	read = list(device.I2C_Read_Repeated(addr, num_bytes))
	read.reverse() #endian reversal
	return read

def Write_FPGA(device,addr,register,data):
	device.I2C_Write(addr, ([0x00, register] + data )) #first element in array - compensation for 16 bit address


mcp2221 = PyMCP2221A.PyMCP2221A()
mcp2221.Reset()
mcp2221 = PyMCP2221A.PyMCP2221A()
mcp2221.I2C_Init()


Write_FPGA(device = mcp2221, addr = 0x40, register = 0x00, data = [0xFF, 0xFF, 0xFF, 0xFF])
print(Read_I2C(device = mcp2221, addr = 0x40, register = 0x00, 4))
```

The result of this should be - [0xFF, 0xFF, 0xFF, 0xFF]

