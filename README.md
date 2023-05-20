PDTricker
-----------

Fork of https://github.com/wuxx/PDTricker/, original readme below

The PDTricker board is a very nice PD trigger board, but the fact that the voltage selection button is always "live" made it too unsafe to my liking, easy to bump it by mistake during use and unexpectedly send higher voltages out to something.

This firmware alleviates that with these changes:
- Changing voltage setting requires holding the button down while applying power
- After 3 seconds without input the current selection is locked and stored to EEPROM (all LEDs blink once to confirm)
- The stored voltage setting is recalled on subsequent power-ups

## Flashing
- Download and install WCHISPTool_Setup.exe from https://www.wch.cn/products/CH552.html
- Bridge the 2 contacts closest to the VOUT pad of the 4-pad header on the underside of the board
- Launch WCHISPStudio, click the bottom blue button, select chip model CH552, select the software\PDTricker-fw.hex file as "Object File 1"
- Connect the output-side port of the board to a USB port (make sure no input is connected!)
- The board should be detected, click "Download"
- Remove the bridge from the pads

![Flasher](https://github.com/kilrah/PDTricker/blob/master/doc/wchisp.png)

## Building

Should you want to make further modifications:
- Download and Install Keil uVision for C51 from https://www.keil.com/download/product/
- Open software/CH552.uvproj
- Hit F7 to build
- The new .hex is generated for flashing as described above

Note that the serial debug output from the original firmware has been disabled as keeping it in exceeded uVision's max code size for the demo version.

---

# Original readme

[中文](./README_cn.md)
* [PDTricker Introduce](#PDTricker-Introduce) 
* [Product Link](#Product-Link)
* [Reference](#Reference)


# PDTricker Introduce
PDTricker is a simple PD trigger tool build with wch ch224k and ch552t, it support PD3.0/2.0,can config output 5V/9V/12V/15V/20V voltage, use the button to dynamically adjust the output voltage at any time. the software is open source, you can also modify the source code to customize the output. 

<div align=center>
<img src="https://github.com/kilrah/PDTricker/blob/master/doc/PDTricker-1.jpg" width = "400" alt="" align=center />
<img src="https://github.com/kilrah/PDTricker/blob/master/doc/PDTricker-2.jpg" width = "400" alt="" align=center />
</div>

# Product Link
- aliexpress
[PDTricker Board](https://www.aliexpress.com/item/1005004835450194.html?spm=a2g0o.productlist.0.0.79e27651KZikpg&algo_pvid=ef2d20e1-8533-4ab6-935f-0eff28aba869&algo_exp_id=ef2d20e1-8533-4ab6-935f-0eff28aba869-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000030671927494%22%7D&pdp_npi=2%40dis%21USD%215.0%215.0%21%21%21%21%21%402132f35016691733010651616ea925%2112000030671927494%21sea&curPageLogUid=ZTLDfY8k539M&gatewayAdapt=4itemAdapt)
- tindie
[PDTricker Board](https://www.tindie.com/products/johnnywu/pdtricker-fast-charge-deception-tool/)

# Reference
### wch
http://www.wch.cn/
