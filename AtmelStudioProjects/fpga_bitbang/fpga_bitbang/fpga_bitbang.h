/*
 * fpga_bitbang.h
 *
 * Created: 26.11.2022 09:29:17
 *  Author: Matthias Musch
 */ 


#ifndef FPGA_BITBANG_H_
#define FPGA_BITBANG_H_

/**
* xxx
* ...xxx
*
* Implemented in assembly
*
* @param control xxx
* @param data xxx
*/

#ifdef __cplusplus
extern "C" {
	void init_io_for_bitbang();
}
#else
extern void init_io_for_bitbang();
#endif

/**
* xxx
* ...xxx
*
* Implemented in assembly
*
* @param control xxx
* @param data xxx
*/

#ifdef __cplusplus
extern "C" {
	void send_bytes_via_bitbang(uint8_t control, uint8_t data);
}
#else
extern void send_bytes_via_bitbang(uint8_t control, uint8_t data);
#endif



#endif /* FPGA_BITBANG_H_ */