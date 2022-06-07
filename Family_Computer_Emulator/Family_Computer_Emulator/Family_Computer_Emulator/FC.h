#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "DebugUtility.h"
#include "MyDirectXSystem.h"
#include "MyDirectXDraw.h"
#include "Key.h"
#include "Main.h"

#define INSTRUCTION_NUM 256

class FC
{
private:
	bool FATAL_ERROR_FLAG = false;//ロードなどで続行不能なエラーが発生したか


	uint16_t sprite_image_data_8x8___for0spritehit[8 * 8];

	Key* key;

	void (FC::*cpu_instruction_table[INSTRUCTION_NUM])() = {
			&FC::cpu_fnc_BRK, //0x00
			&FC::cpu_fnc_ORA_INDEX_INDIRECT_X, //0x01
			&FC::UNOFFICIAL_cpu_fnc_NOP__02, //0x02
			&FC::UNOFFICIAL_cpu_fnc_SLO_INDEX_INDIRECT_X, //0x03
			&FC::UNOFFICIAL_cpu_fnc_NOPD__04, //0x04
			&FC::cpu_fnc_ORA_ZEROPAGE, //0x05
			&FC::cpu_fnc_ASL_ZEROPAGE, //0x06
			&FC::UNOFFICIAL_cpu_fnc_SLO_ZEROPAGE, //0x07
			&FC::cpu_fnc_PHP, //0x08
			&FC::cpu_fnc_ORA_IMMEDIATE, //0x09
			&FC::cpu_fnc_ASL_ACCUMULATOR, //0x0a
			&FC::cpu_fnc_GARBAGE, //0x0b
			&FC::UNOFFICIAL_cpu_fnc_NOPI__0C, //0x0c
			&FC::cpu_fnc_ORA_ABSOLUTE, //0x0d
			&FC::cpu_fnc_ASL_ABSOLUTE, //0x0e
			&FC::UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE, //0x0f
			&FC::cpu_fnc_BPL, //0x10
			&FC::cpu_fnc_ORA_INDIRECT_INDEX_Y, //0x11
			&FC::UNOFFICIAL_cpu_fnc_NOP__12, //0x12
			&FC::UNOFFICIAL_cpu_fnc_SLO_INDIRECT_INDEX_Y, //0x13
			&FC::UNOFFICIAL_cpu_fnc_NOPD__14, //0x14
			&FC::cpu_fnc_ORA_ZEROPAGE_X, //0x15
			&FC::cpu_fnc_ASL_ZEROPAGE_X, //0x16
			&FC::UNOFFICIAL_cpu_fnc_SLO_ZEROPAGE_X, //0x17
			&FC::cpu_fnc_CLC, //0x18
			&FC::cpu_fnc_ORA_ABSOLUTE_Y, //0x19
			&FC::UNOFFICIAL_cpu_fnc_NOP__1A, //0x1a
			&FC::UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE_Y, //0x1b
			&FC::UNOFFICIAL_cpu_fnc_NOPI__1C, //0x1c
			&FC::cpu_fnc_ORA_ABSOLUTE_X, //0x1d
			&FC::cpu_fnc_ASL_ABSOLUTE_X, //0x1e
			&FC::UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE_X, //0x1f
			&FC::cpu_fnc_JSR, //0x20
			&FC::cpu_fnc_AND_INDEX_INDIRECT_X, //0x21
			&FC::UNOFFICIAL_cpu_fnc_NOP__22, //0x22
			&FC::UNOFFICIAL_cpu_fnc_RLA_INDEX_INDIRECT_X, //0x23
			&FC::cpu_fnc_BIT_ZEROPAGE, //0x24
			&FC::cpu_fnc_AND_ZEROPAGE, //0x25
			&FC::cpu_fnc_ROL_ZEROPAGE, //0x26
			&FC::UNOFFICIAL_cpu_fnc_RLA_ZEROPAGE, //0x27
			&FC::cpu_fnc_PLP, //0x28
			&FC::cpu_fnc_AND_IMMEDIATE, //0x29
			&FC::cpu_fnc_ROL_ACCUMULATOR, //0x2a
			&FC::cpu_fnc_GARBAGE, //0x2b
			&FC::cpu_fnc_BIT_ABSOLUTE, //0x2c
			&FC::cpu_fnc_AND_ABSOLUTE, //0x2d
			&FC::cpu_fnc_ROL_ABSOLUTE, //0x2e
			&FC::UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE, //0x2f
			&FC::cpu_fnc_BMI, //0x30
			&FC::cpu_fnc_AND_INDIRECT_INDEX_Y, //0x31
			&FC::UNOFFICIAL_cpu_fnc_NOP__32, //0x32
			&FC::UNOFFICIAL_cpu_fnc_RLA_INDIRECT_INDEX_Y, //0x33
			&FC::UNOFFICIAL_cpu_fnc_NOPD__34, //0x34
			&FC::cpu_fnc_AND_ZEROPAGE_X, //0x35
			&FC::cpu_fnc_ROL_ZEROPAGE_X, //0x36
			&FC::UNOFFICIAL_cpu_fnc_RLA_ZEROPAGE_X, //0x37
			&FC::cpu_fnc_SEC, //0x38
			&FC::cpu_fnc_AND_ABSOLUTE_Y, //0x39
			&FC::UNOFFICIAL_cpu_fnc_NOP__3A, //0x3a
			&FC::UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE_Y, //0x3b
			&FC::UNOFFICIAL_cpu_fnc_NOPI__3C, //0x3c
			&FC::cpu_fnc_AND_ABSOLUTE_X, //0x3d
			&FC::cpu_fnc_ROL_ABSOLUTE_X, //0x3e
			&FC::UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE_X, //0x3f
			&FC::cpu_fnc_RTI, //0x40
			&FC::cpu_fnc_EOR_INDEX_INDIRECT_X, //0x41
			&FC::UNOFFICIAL_cpu_fnc_NOP__42, //0x42
			&FC::UNOFFICIAL_cpu_fnc_SRE_INDEX_INDIRECT_X, //0x43
			&FC::UNOFFICIAL_cpu_fnc_NOPD__44, //0x44
			&FC::cpu_fnc_EOR_ZEROPAGE, //0x45
			&FC::cpu_fnc_LSR_ZEROPAGE, //0x46
			&FC::UNOFFICIAL_cpu_fnc_SRE_ZEROPAGE, //0x47
			&FC::cpu_fnc_PHA, //0x48
			&FC::cpu_fnc_EOR_IMMEDIATE, //0x49
			&FC::cpu_fnc_LSR_ACCUMULATOR, //0x4a
			&FC::cpu_fnc_GARBAGE, //0x4b
			&FC::cpu_fnc_JMP_ABSOLUTE, //0x4c
			&FC::cpu_fnc_EOR_ABSOLUTE, //0x4d
			&FC::cpu_fnc_LSR_ABSOLUTE, //0x4e
			&FC::UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE, //0x4f
			&FC::cpu_fnc_BVC, //0x50
			&FC::cpu_fnc_EOR_INDIRECT_INDEX_Y, //0x51
			&FC::UNOFFICIAL_cpu_fnc_NOP__52, //0x52
			&FC::UNOFFICIAL_cpu_fnc_SRE_INDIRECT_INDEX_Y, //0x53
			&FC::UNOFFICIAL_cpu_fnc_NOPD__54, //0x54
			&FC::cpu_fnc_EOR_ZEROPAGE_X, //0x55
			&FC::cpu_fnc_LSR_ZEROPAGE_X, //0x56
			&FC::UNOFFICIAL_cpu_fnc_SRE_ZEROPAGE_X, //0x57
			&FC::cpu_fnc_CLI, //0x58
			&FC::cpu_fnc_EOR_ABSOLUTE_Y, //0x59
			&FC::UNOFFICIAL_cpu_fnc_NOP__5A, //0x5a
			&FC::UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE_Y, //0x5b
			&FC::UNOFFICIAL_cpu_fnc_NOPI__5C, //0x5c
			&FC::cpu_fnc_EOR_ABSOLUTE_X, //0x5d
			&FC::cpu_fnc_LSR_ABSOLUTE_X, //0x5e
			&FC::UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE_X, //0x5f
			&FC::cpu_fnc_RTS, //0x60
			&FC::cpu_fnc_ADC_INDEX_INDIRECT_X, //0x61
			&FC::UNOFFICIAL_cpu_fnc_NOP__62, //0x62
			&FC::UNOFFICIAL_cpu_fnc_RRA_INDEX_INDIRECT_X, //0x63
			&FC::UNOFFICIAL_cpu_fnc_NOPD__64, //0x64
			&FC::cpu_fnc_ADC_ZEROPAGE, //0x65
			&FC::cpu_fnc_ROR_ZEROPAGE, //0x66
			&FC::UNOFFICIAL_cpu_fnc_RRA_ZEROPAGE, //0x67
			&FC::cpu_fnc_PLA, //0x68
			&FC::cpu_fnc_ADC_IMMEDIATE, //0x69
			&FC::cpu_fnc_ROR_ACCUMULATOR, //0x6a
			&FC::cpu_fnc_GARBAGE, //0x6b
			&FC::cpu_fnc_JMP_INDIRECT, //0x6c
			&FC::cpu_fnc_ADC_ABSOLUTE, //0x6d
			&FC::cpu_fnc_ROR_ABSOLUTE, //0x6e
			&FC::UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE, //0x6f
			&FC::cpu_fnc_BVS, //0x70
			&FC::cpu_fnc_ADC_INDIRECT_INDEX_Y, //0x71
			&FC::UNOFFICIAL_cpu_fnc_NOP__72, //0x72
			&FC::UNOFFICIAL_cpu_fnc_RRA_INDIRECT_INDEX_Y, //0x73
			&FC::UNOFFICIAL_cpu_fnc_NOPD__74, //0x74
			&FC::cpu_fnc_ADC_ZEROPAGE_X, //0x75
			&FC::cpu_fnc_ROR_ZEROPAGE_X, //0x76
			&FC::UNOFFICIAL_cpu_fnc_RRA_ZEROPAGE_X, //0x77
			&FC::cpu_fnc_SEI, //0x78
			&FC::cpu_fnc_ADC_ABSOLUTE_Y, //0x79
			&FC::UNOFFICIAL_cpu_fnc_NOP__7A, //0x7a
			&FC::UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE_Y, //0x7b
			&FC::UNOFFICIAL_cpu_fnc_NOPI__7C, //0x7c
			&FC::cpu_fnc_ADC_ABSOLUTE_X, //0x7d
			&FC::cpu_fnc_ROR_ABSOLUTE_X, //0x7e
			&FC::UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE_X, //0x7f
			&FC::UNOFFICIAL_cpu_fnc_NOPD__80, //0x80
			&FC::cpu_fnc_STA_INDEX_INDIRECT_X, //0x81
			&FC::UNOFFICIAL_cpu_fnc_NOPD__82, //0x82
			&FC::UNOFFICIAL_cpu_fnc_SAX_INDEX_INDIRECT_X, //0x83
			&FC::cpu_fnc_STY_ZEROPAGE, //0x84
			&FC::cpu_fnc_STA_ZEROPAGE, //0x85
			&FC::cpu_fnc_STX_ZEROPAGE, //0x86
			&FC::UNOFFICIAL_cpu_fnc_SAX_ZEROPAGE, //0x87
			&FC::cpu_fnc_DEY, //0x88
			&FC::UNOFFICIAL_cpu_fnc_NOPD__89, //0x89
			&FC::cpu_fnc_TXA, //0x8a
			&FC::cpu_fnc_GARBAGE, //0x8b
			&FC::cpu_fnc_STY_ABSOLUTE, //0x8c
			&FC::cpu_fnc_STA_ABSOLUTE, //0x8d
			&FC::cpu_fnc_STX_ABSOLUTE, //0x8e
			&FC::UNOFFICIAL_cpu_fnc_SAX_ABSOLUTE, //0x8f
			&FC::cpu_fnc_BCC, //0x90
			&FC::cpu_fnc_STA_INDIRECT_INDEX_Y, //0x91
			&FC::UNOFFICIAL_cpu_fnc_NOP__92, //0x92
			&FC::cpu_fnc_GARBAGE, //0x93
			&FC::cpu_fnc_STY_ZEROPAGE_X, //0x94
			&FC::cpu_fnc_STA_ZEROPAGE_X, //0x95
			&FC::cpu_fnc_STX_ZEROPAGE_Y, //0x96
			&FC::UNOFFICIAL_cpu_fnc_SAX_ZEROPAGE_Y, //0x97
			&FC::cpu_fnc_TYA, //0x98
			&FC::cpu_fnc_STA_ABSOLUTE_Y, //0x99
			&FC::cpu_fnc_TXS, //0x9a
			&FC::cpu_fnc_GARBAGE, //0x9b
			&FC::cpu_fnc_GARBAGE, //0x9c
			&FC::cpu_fnc_STA_ABSOLUTE_X, //0x9d
			&FC::cpu_fnc_GARBAGE, //0x9e
			&FC::cpu_fnc_GARBAGE, //0x9f
			&FC::cpu_fnc_LDY_IMMEDIATE, //0xa0
			&FC::cpu_fnc_LDA_INDEX_INDIRECT_X, //0xa1
			&FC::cpu_fnc_LDX_IMMEDIATE, //0xa2
			&FC::UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_INDEX_INDIRECT_X, //0xa3
			&FC::cpu_fnc_LDY_ZEROPAGE, //0xa4
			&FC::cpu_fnc_LDA_ZEROPAGE, //0xa5
			&FC::cpu_fnc_LDX_ZEROPAGE, //0xa6
			&FC::UNOFFICIAL_cpu_fnc_LAX_ZEROPAGE, //0xa7
			&FC::cpu_fnc_TAY, //0xa8
			&FC::cpu_fnc_LDA_IMMEDIATE, //0xa9
			&FC::cpu_fnc_TAX, //0xaa
			&FC::cpu_fnc_GARBAGE, //0xab
			&FC::cpu_fnc_LDY_ABSOLUTE, //0xac
			&FC::cpu_fnc_LDA_ABSOLUTE, //0xad
			&FC::cpu_fnc_LDX_ABSOLUTE, //0xae
			&FC::UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE, //0xaf
			&FC::cpu_fnc_BCS, //0xb0
			&FC::cpu_fnc_LDA_INDIRECT_INDEX_Y, //0xb1
			&FC::UNOFFICIAL_cpu_fnc_NOP__B2, //0xb2
			&FC::UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_INDIRECT_INDEX_Y, //0xb3
			&FC::cpu_fnc_LDY_ZEROPAGE_X, //0xb4
			&FC::cpu_fnc_LDA_ZEROPAGE_X, //0xb5
			&FC::cpu_fnc_LDX_ZEROPAGE_Y, //0xb6
			&FC::UNOFFICIAL_cpu_fnc_LAX_ZEROPAGE_Y, //0xb7
			&FC::cpu_fnc_CLV, //0xb8
			&FC::cpu_fnc_LDA_ABSOLUTE_Y, //0xb9
			&FC::cpu_fnc_TSX, //0xba
			&FC::cpu_fnc_GARBAGE, //0xbb
			&FC::cpu_fnc_LDY_ABSOLUTE_X, //0xbc
			&FC::cpu_fnc_LDA_ABSOLUTE_X, //0xbd
			&FC::cpu_fnc_LDX_ABSOLUTE_Y, //0xbe
			&FC::UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_Y, //0xbf
			&FC::cpu_fnc_CPY_IMMEDIATE, //0xc0
			&FC::cpu_fnc_CMP_INDEX_INDIRECT_X, //0xc1
			&FC::UNOFFICIAL_cpu_fnc_NOPD__C2, //0xc2
			&FC::UNOFFICIAL_cpu_fnc_DCP_INDEX_INDIRECT_X, //0xc3
			&FC::cpu_fnc_CPY_ZEROPAGE, //0xc4
			&FC::cpu_fnc_CMP_ZEROPAGE, //0xc5
			&FC::cpu_fnc_DEC_ZEROPAGE, //0xc6
			&FC::UNOFFICIAL_cpu_fnc_DCP_ZEROPAGE, //0xc7
			&FC::cpu_fnc_INY, //0xc8
			&FC::cpu_fnc_CMP_IMMEDIATE, //0xc9
			&FC::cpu_fnc_DEX, //0xca
			&FC::cpu_fnc_GARBAGE, //0xcb
			&FC::cpu_fnc_CPY_ABSOLUTE, //0xcc
			&FC::cpu_fnc_CMP_ABSOLUTE, //0xcd
			&FC::cpu_fnc_DEC_ABSOLUTE, //0xce
			&FC::UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE, //0xcf
			&FC::cpu_fnc_BNE, //0xd0
			&FC::cpu_fnc_CMP_INDIRECT_INDEX_Y, //0xd1
			&FC::UNOFFICIAL_cpu_fnc_NOP__D2, //0xd2
			&FC::UNOFFICIAL_cpu_fnc_DCP_INDIRECT_INDEX_Y, //0xd3
			&FC::UNOFFICIAL_cpu_fnc_NOPD__D4, //0xd4
			&FC::cpu_fnc_CMP_ZEROPAGE_X, //0xd5
			&FC::cpu_fnc_DEC_ZEROPAGE_X, //0xd6
			&FC::UNOFFICIAL_cpu_fnc_DCP_ZEROPAGE_X, //0xd7
			&FC::cpu_fnc_CLD, //0xd8
			&FC::cpu_fnc_CMP_ABSOLUTE_Y, //0xd9
			&FC::UNOFFICIAL_cpu_fnc_NOP__DA, //0xda
			&FC::UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE_Y, //0xdb
			&FC::UNOFFICIAL_cpu_fnc_NOPI__DC, //0xdc
			&FC::cpu_fnc_CMP_ABSOLUTE_X, //0xdd
			&FC::cpu_fnc_DEC_ABSOLUTE_X, //0xde
			&FC::UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE_X, //0xdf
			&FC::cpu_fnc_CPX_IMMEDIATE, //0xe0
			&FC::cpu_fnc_SBC_INDEX_INDIRECT_X, //0xe1
			&FC::UNOFFICIAL_cpu_fnc_NOPD__E2, //0xe2
			&FC::UNOFFICIAL_cpu_fnc_ISB_INDEX_INDIRECT_X, //0xe3
			&FC::cpu_fnc_CPX_ZEROPAGE, //0xe4
			&FC::cpu_fnc_SBC_ZEROPAGE, //0xe5
			&FC::cpu_fnc_INC_ZEROPAGE, //0xe6
			&FC::UNOFFICIAL_cpu_fnc_ISB_ZEROPAGE, //0xe7
			&FC::cpu_fnc_INX, //0xe8
			&FC::cpu_fnc_SBC_IMMEDIATE, //0xe9
			&FC::cpu_fnc_NOP, //0xea
			&FC::UNOFFICIAL_cpu_fnc_SBC_IMMEDIATE, //0xeb
			&FC::cpu_fnc_CPX_ABSOLUTE, //0xec
			&FC::cpu_fnc_SBC_ABSOLUTE, //0xed
			&FC::cpu_fnc_INC_ABSOLUTE, //0xee
			&FC::UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE, //0xef
			&FC::cpu_fnc_BEQ, //0xf0
			&FC::cpu_fnc_SBC_INDIRECT_INDEX_Y, //0xf1
			&FC::UNOFFICIAL_cpu_fnc_NOP__F2, //0xf2
			&FC::UNOFFICIAL_cpu_fnc_ISB_INDIRECT_INDEX_Y, //0xf3
			&FC::UNOFFICIAL_cpu_fnc_NOPD__F4, //0xf4
			&FC::cpu_fnc_SBC_ZEROPAGE_X, //0xf5
			&FC::cpu_fnc_INC_ZEROPAGE_X, //0xf6
			&FC::UNOFFICIAL_cpu_fnc_ISB_ZEROPAGE_X, //0xf7
			&FC::cpu_fnc_SED, //0xf8
			&FC::cpu_fnc_SBC_ABSOLUTE_Y, //0xf9
			&FC::UNOFFICIAL_cpu_fnc_NOP__FA, //0xfa
			&FC::UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE_Y, //0xfb
			&FC::UNOFFICIAL_cpu_fnc_NOPI__FC, //0xfc
			&FC::cpu_fnc_SBC_ABSOLUTE_X, //0xfd
			&FC::cpu_fnc_INC_ABSOLUTE_X, //0xfe
			&FC::UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE_X, //0xff
	};

#define UNOFFICIAL_INSTRUCTION_NOP_CLOCK 2
#define UNOFFICIAL_INSTRUCTION_NOPD_CLOCK 2
#define UNOFFICIAL_INSTRUCTION_NOPI_CLOCK 4

	uint32_t instruction_clock_table[INSTRUCTION_NUM] = {
				7, //0x00
				6, //0x01
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x02
				8, //0x03
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x04
				3, //0x05
				5, //0x06
				5, //0x07
				3, //0x08
				2, //0x09
				2, //0x0a
				0xDEADBEEF, //0x0b
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0x0c
				4, //0x0d
				6, //0x0e
				6, //0x0f
				2, //0x10
				5, //0x11
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x12
				8, //0x13
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x14
				4, //0x15
				6, //0x16
				6, //0x17
				2, //0x18
				4, //0x19
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x1a
				7, //0x1b
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0x1c
				4, //0x1d
				7, //0x1e
				7, //0x1f
				6, //0x20
				6, //0x21
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x22
				8, //0x23
				3, //0x24
				3, //0x25
				5, //0x26
				5, //0x27
				4, //0x28
				2, //0x29
				2, //0x2a
				0xDEADBEEF, //0x2b
				4, //0x2c
				4, //0x2d
				6, //0x2e
				6, //0x2f
				2, //0x30
				5, //0x31
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x32
				8, //0x33
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x34
				4, //0x35
				6, //0x36
				6, //0x37
				2, //0x38
				4, //0x39
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x3a
				7, //0x3b
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0x3c
				4, //0x3d
				7, //0x3e
				7, //0x3f
				6, //0x40
				6, //0x41
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x42
				8, //0x43
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x44
				3, //0x45
				5, //0x46
				5, //0x47
				3, //0x48
				2, //0x49
				2, //0x4a
				0xDEADBEEF, //0x4b
				3, //0x4c
				4, //0x4d
				6, //0x4e
				6, //0x4f
				2, //0x50
				5, //0x51
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x52
				8, //0x53
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x54
				4, //0x55
				6, //0x56
				6, //0x57
				2, //0x58
				4, //0x59
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x5a
				7, //0x5b
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0x5c
				4, //0x5d
				7, //0x5e
				7, //0x5f
				6, //0x60
				6, //0x61
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x62
				8, //0x63
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x64
				3, //0x65
				5, //0x66
				5, //0x67
				4, //0x68
				2, //0x69
				2, //0x6a
				0xDEADBEEF, //0x6b
				5, //0x6c
				4, //0x6d
				6, //0x6e
				6, //0x6f
				2, //0x70
				5, //0x71
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x72
				8, //0x73
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x74
				4, //0x75
				6, //0x76
				6, //0x77
				2, //0x78
				4, //0x79
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x7a
				7, //0x7b
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0x7c
				4, //0x7d
				7, //0x7e
				7, //0x7f
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x80
				6, //0x81
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x82
				6, //0x83
				3, //0x84
				3, //0x85
				3, //0x86
				3, //0x87
				2, //0x88
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0x89
				2, //0x8a
				0xDEADBEEF, //0x8b
				4, //0x8c
				4, //0x8d
				4, //0x8e
				4, //0x8f
				2, //0x90
				6, //0x91
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0x92
				0xDEADBEEF, //0x93
				4, //0x94
				4, //0x95
				4, //0x96
				4, //0x97
				2, //0x98
				5, //0x99
				2, //0x9a
				0xDEADBEEF, //0x9b
				0xDEADBEEF, //0x9c
				5, //0x9d
				0xDEADBEEF, //0x9e
				0xDEADBEEF, //0x9f
				2, //0xa0
				6, //0xa1
				2, //0xa2
				6, //0xa3
				3, //0xa4
				3, //0xa5
				3, //0xa6
				3, //0xa7
				2, //0xa8
				2, //0xa9
				2, //0xaa
				0xDEADBEEF, //0xab
				4, //0xac
				4, //0xad
				4, //0xae
				4, //0xaf
				2, //0xb0
				5, //0xb1
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0xb2
				5, //0xb3
				4, //0xb4
				4, //0xb5
				4, //0xb6
				4, //0xb7
				2, //0xb8
				4, //0xb9
				2, //0xba
				0xDEADBEEF, //0xbb
				4, //0xbc
				4, //0xbd
				4, //0xbe
				4, //0xbf
				2, //0xc0
				6, //0xc1
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0xc2
				8, //0xc3
				3, //0xc4
				3, //0xc5
				5, //0xc6
				5, //0xc7
				2, //0xc8
				2, //0xc9
				2, //0xca
				0xDEADBEEF, //0xcb
				4, //0xcc
				4, //0xcd
				6, //0xce
				6, //0xcf
				2, //0xd0
				5, //0xd1
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0xd2
				8, //0xd3
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0xd4
				4, //0xd5
				6, //0xd6
				6, //0xd7
				2, //0xd8
				4, //0xd9
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0xda
				7, //0xdb
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0xdc
				4, //0xdd
				7, //0xde
				7, //0xdf
				2, //0xe0
				6, //0xe1
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0xe2
				8, //0xe3
				3, //0xe4
				3, //0xe5
				5, //0xe6
				5, //0xe7
				2, //0xe8
				2, //0xe9
				2, //0xea
				2, //0xeb
				4, //0xec
				4, //0xed
				6, //0xee
				6, //0xef
				2, //0xf0
				5, //0xf1
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0xf2
				8, //0xf3
				UNOFFICIAL_INSTRUCTION_NOPD_CLOCK, //0xf4
				4, //0xf5
				6, //0xf6
				6, //0xf7
				2, //0xf8
				4, //0xf9
				UNOFFICIAL_INSTRUCTION_NOP_CLOCK, //0xfa
				7, //0xfb
				UNOFFICIAL_INSTRUCTION_NOPI_CLOCK, //0xfc
				4, //0xfd
				7, //0xfe
				7, //0xff
	};

	uint8_t FC_COLOR_LIST[64][3] = {
		{0x80, 0x80, 0x80}, {0x00, 0x3D, 0xA6}, {0x00, 0x12, 0xB0}, {0x44, 0x00, 0x96},
		{0xA1, 0x00, 0x5E}, {0xC7, 0x00, 0x28}, {0xBA, 0x06, 0x00}, {0x8C, 0x17, 0x00},
		{0x5C, 0x2F, 0x00}, {0x10, 0x45, 0x00}, {0x05, 0x4A, 0x00}, {0x00, 0x47, 0x2E},
		{0x00, 0x41, 0x66}, {0x00, 0x00, 0x00}, {0x05, 0x05, 0x05}, {0x05, 0x05, 0x05},
		{0xC7, 0xC7, 0xC7}, {0x00, 0x77, 0xFF}, {0x21, 0x55, 0xFF}, {0x82, 0x37, 0xFA},
		{0xEB, 0x2F, 0xB5}, {0xFF, 0x29, 0x50}, {0xFF, 0x22, 0x00}, {0xD6, 0x32, 0x00},
		{0xC4, 0x62, 0x00}, {0x35, 0x80, 0x00}, {0x05, 0x8F, 0x00}, {0x00, 0x8A, 0x55},
		{0x00, 0x99, 0xCC}, {0x21, 0x21, 0x21}, {0x09, 0x09, 0x09}, {0x09, 0x09, 0x09},
		{0xFF, 0xFF, 0xFF}, {0x0F, 0xD7, 0xFF}, {0x69, 0xA2, 0xFF}, {0xD4, 0x80, 0xFF},
		{0xFF, 0x45, 0xF3}, {0xFF, 0x61, 0x8B}, {0xFF, 0x88, 0x33}, {0xFF, 0x9C, 0x12},
		{0xFA, 0xBC, 0x20}, {0x9F, 0xE3, 0x0E}, {0x2B, 0xF0, 0x35}, {0x0C, 0xF0, 0xA4},
		{0x05, 0xFB, 0xFF}, {0x5E, 0x5E, 0x5E}, {0x0D, 0x0D, 0x0D}, {0x0D, 0x0D, 0x0D},
		{0xFF, 0xFF, 0xFF}, {0xA6, 0xFC, 0xFF}, {0xB3, 0xEC, 0xFF}, {0xDA, 0xAB, 0xEB},
		{0xFF, 0xA8, 0xF9}, {0xFF, 0xAB, 0xB3}, {0xFF, 0xD2, 0xB0}, {0xFF, 0xEF, 0xA6},
		{0xFF, 0xF7, 0x9C}, {0xD7, 0xE8, 0x95}, {0xA6, 0xED, 0xAF}, {0xA2, 0xF2, 0xDA},
		{0x99, 0xFF, 0xFC}, {0xDD, 0xDD, 0xDD}, {0x11, 0x11, 0x11}, {0x11, 0x11, 0x11},
	};

	uint8_t* pgm_rom_data;//プログラムのロムデータ
	uint8_t* chr_rom_data;//画像のロムデータ

	uint8_t pgm_page16kb_num;//プログラムの16kbのページ数
	uint8_t chr_page8kb_num;//画像データの8kbのページ数

	/*
	|   1    |  1   | ROM Control Byte #1                      |
    |        |      |   %####vTsM                              |
    |        |      |    |  ||||+- 0=Horizontal Mirroring      |
    |        |      |    |  ||||   1=Vertical Mirroring        |
    |        |      |    |  |||+-- 1=SRAM enabled              |
    |        |      |    |  ||+--- 1=512-byte trainer present  |
    |        |      |    |  |+---- 1=Four-screen VRAM layout   |
    |        |      |    |  |                                  |
    |        |      |    +--+----- Mapper # (lower 4-bits)     |
    |   2    |  1   | ROM Control Byte #2                      |
    |        |      |   %####0000                              |
    |        |      |    |  |                                  |
    |        |      |    +--+----- Mapper # (upper 4-bits)     |
	*/
	enum class MIRROR_TYPE {
		HORIZONTAL,
		VERTICAL,
	};
	MIRROR_TYPE mirror_type;
	bool sram_flag;
	bool trainer_flag;
	bool four_screen_flag;

	uint8_t mapper_num;

	bool unisystem_flag;

	int readrom_header(const char* filename);
	int readrom(const char* filename);
	uint8_t* chr1_image_data;
	uint8_t* chr2_image_data;
	int init_chr();
#ifdef FC_EMU_DEBUG
	void debug_chr1_image_print(uint8_t number);
	void debug_chr2_image_print(uint8_t number);
#endif

	struct FC_Register {
		uint8_t a;
		uint8_t x;
		uint8_t y;
		uint8_t s;
		union {
			uint8_t p;
			struct {
				uint8_t p_C : 1;
				uint8_t p_Z : 1;
				uint8_t p_I : 1;
				uint8_t p_D : 1;
				uint8_t p_B : 1;
				uint8_t p_R : 1;
				uint8_t p_V : 1;
				uint8_t p_N : 1;
			};
		};
		uint16_t pc;
	};
	FC_Register fc_register;

	/*
	$0000-$07FF 	RAM
	$0800-$1FFF 	RAM ミラー
	$2000-$2007 	PPU I/O レジスタ
	$2008-$3FFF 	PPU I/O レジスタ ミラー
	$4000-$4017 	APU/OAMDMA/コントローラ I/O レジスタ
	$4018-$401F 	没機能レジスタ (通常は無効)
	$4020-$FFFF 	カートリッジ側で構成 
	*/
#define RAM_SIZE 0x10000
	union FC_RAM {
		uint8_t ram[RAM_SIZE];
		struct {
			uint8_t zero_page[0x100];
			uint8_t stack[0x100];
			uint8_t other_mem[0x600];
			uint8_t unused_1[0x1800];//$0000-$07FFのミラー
			uint8_t ppu_io_port[0x8];
			uint8_t unused_2[0x1ff8];//$2000-$2007のミラー
			uint8_t apu_io_port[0x20];
			uint8_t extend_RAM[0x1fe0];
			uint8_t backup_RAM[0x2000];
			uint8_t ROM_low[0x4000];
			uint8_t ROM_high[0x4000];
		};
	};
	FC_RAM fc_ram;

	/*
	|アドレス 		|内容 							|ミラーアドレス
	|---------------|-------------------------------|---------------------
	|$0000-$0FFF 	|パターンテーブル LOW 			|
	|$1000-$1FFF 	|パターンテーブル HIGH 			|
	|$2000-$23BF 	|画面1 ネームテーブル 			|
	|$23C0-$23FF 	|画面1 属性テーブル 			|
	|$2400-$27BF 	|画面2 ネームテーブル 			|
	|$27C0-$27FF 	|画面2 属性テーブル 			|
	|$2800-$2BBF 	|画面3 ネームテーブル 			|$2000-$23BF
	|$2BC0-$2BFF 	|画面3 属性テーブル 			|$23C0-$23FF
	|$2C00-$2FBF 	|画面4 ネームテーブル 			|$2400-$27BF
	|$2FC0-$2FFF 	|画面4 属性テーブル 			|$27C0-$2FFF
	|$3000-$3EFF 	|未使用 						|$2000-$2EFF
	|$3F00-$3F0F 	|BGパレットテーブル 			|
	|$3F10-$3F1F 	|スプライトパレットテーブル 	|
	|$3F20-$3FFF 	|未使用 						|$3F00-$3F1F
	|$4000-$FFFF 	|未使用 						|$0000-$3FFF
	*/
#define VRAM_SIZE 0x10000
	union FC_VRAM {
		uint8_t vram[VRAM_SIZE];
		struct {
			uint8_t pattern_table_low[0x1000];
			uint8_t pattern_table_high[0x1000];
			uint8_t name_table_1[0x3C0];
			uint8_t attribute_table_1[0x40];
			uint8_t name_table_2[0x3C0];
			uint8_t attribute_table_2[0x40];
			uint8_t name_table_3[0x3C0];
			uint8_t attribute_table_3[0x40];
			uint8_t name_table_4[0x3C0];
			uint8_t attribute_table_4[0x40];
			uint8_t unused_1[0xF00];
			uint8_t bg_palette_table[0x10];
			uint8_t sprite_palette_table[0x10];
			uint8_t unused_2[0xE0];
			uint8_t unused_3[0xC000];
		};
	};
	FC_VRAM fc_vram;

#define SPRITE_DMA_ACCESS_CPU_CLOCK 514
	/*
	false=何もない
	true=SPRITE_RAMにDMAのアクセスがあった
	*/
	bool SPRITE_RAM_DMA_ACCESS_FLAG = false;

	struct PPU_Info{
		uint8_t sprite_RAM[0x100] = { 0 };

		/*
		位置 	内容 	クリア時 	セット時
		7 		VBlank時にNMI割込の発生 	オフ 	オン
		6 		PPUの選択 	マスター 	スレーブ
		5 		スプライトサイズ 	8x8 	8x16
		4 		BG用CHRテーブル 	$0000 	$1000
		3 		スプライト用CHRテーブル 	$0000 	$1000
		2 		VRAM入出力時のアドレス変化 	+1 	+32
		1-0 	メインスクリーン 	0=$2000 , 1=$2400 , 2=$2800 , 3=$2C00
		*/
		uint8_t PPU_REGISTER_1__2000 = 0;

		/*
		位置 	内容 	クリア時 	セット時
		7 		赤色を強調 	オフ 	オン
		6 		緑色を強調 	オフ 	オン
		5 		青色を強調 	オフ 	オン
		4 		スプライトの表示 	オフ 	オン
		3 		BGの表示 	オフ 	オン
		2 		画面左端8ドットのスプライト 	クリップ 	表示
		1 		画面左端8ドットのBG 	クリップ 	表示
		0 		色設定 	カラー 	モノクロ
		*/
		uint8_t PPU_REGISTER_2__2001 = 0;

		/*
		位置 	内容 	クリア時 	セット時
		7 		スクリーンの描画状況 	描画中 	VBlank中
		6 		描画ラインの0番スプライト 	衝突しない 	衝突した
		5 		描画ラインスプライト数 	8個以下 	9個以上
		4		VRAM状態 	書き込み可能 	書き込み不可
		3-0 	未使用
		*/
		uint8_t PPU_REGISTER_3__2002 = 0;

		uint8_t sprite_address__2003 = 0;

		bool PPUADDR_2nd_flag___2005_2006 = false;//$2005,$2006の値を一度書き込んだか($2005,$2006で共有する)

		uint8_t scroll_x = 0;
		uint8_t scroll_y = 0;
		//bool PPUADDR_2nd_flag__2005 = false;//Xのスクロールをすでに書き込んだか

		uint16_t PPUADDR_address__2006 = 0x0000;
		//bool PPUADDR_2nd_flag__2006 = false;//すでに一回書き込んだか

		uint8_t PPUADDR_read_buffer_2007 = 0x00;//内部バッファー

	};
	PPU_Info ppu_info;

	struct APU_Info {
		uint8_t APU_SQUARE_CH1__4000;
		uint8_t APU_SQUARE_CH1__4001;
		uint8_t APU_SQUARE_CH1__4002;
		uint8_t APU_SQUARE_CH1__4003;

		uint8_t APU_SQUARE_CH2__4004;
		uint8_t APU_SQUARE_CH2__4005;
		uint8_t APU_SQUARE_CH2__4006;
		uint8_t APU_SQUARE_CH2__4007;

		uint8_t APU_TRIANGLE__4008;
		uint8_t APU_TRIANGLE__400A;
		uint8_t APU_TRIANGLE__400B;

		uint8_t APU_NOISE__400C;
		uint8_t APU_NOISE__400E;
		uint8_t APU_NOISE__400F;

		uint8_t APU_DPCM__4010;
		uint8_t APU_DPCM__4011;
		uint8_t APU_DPCM__4012;
		uint8_t APU_DPCM__4013;

		uint8_t APU_SETTING__4015;
	};
	APU_Info apu_info;

	bool is_APU_SQUARE_CH1_enable() {
		if ((apu_info.APU_SETTING__4015 & 0b00000001) != 0) {
			return true;
		}

		return false;
	}

	bool is_APU_SQUARE_CH2_enable() {
		if ((apu_info.APU_SETTING__4015 & 0b00000010) != 0) {
			return true;
		}

		return false;
	}

	bool is_APU_TRIANGLE_enable() {
		if ((apu_info.APU_SETTING__4015 & 0b00000100) != 0) {
			return true;
		}

		return false;
	}

	bool is_APU_NOISE_enable() {
		if ((apu_info.APU_SETTING__4015 & 0b00001000) != 0) {
			return true;
		}

		return false;
	}

	bool is_APU_DPCM_enable() {
		if ((apu_info.APU_SETTING__4015 & 0b00010000) != 0) {
			return true;
		}

		return false;
	}

	uint8_t get_duty_cycle__SQUARE_CH1() {
		return (apu_info.APU_SQUARE_CH1__4000 >> 6);
	}
	uint8_t get_duty_cycle__SQUARE_CH2() {
		return (apu_info.APU_SQUARE_CH2__4004 >> 6);
	}


	uint8_t get_main_screen_type() {
		return (ppu_info.PPU_REGISTER_1__2000 & 0b00000011);
	}

	struct Controller_Info {
		uint8_t IO_REGISTER_read_counter__4016_4017 = 0;

		uint8_t IO_REGISTER_CONTROLLER_1P_read_counter__4016 = 0;
		uint8_t IO_REGISTER_CONTROLLER_2P_read_counter__4017 = 0;
	};
	Controller_Info controller_info;

	void controller_register_init() {
		controller_info.IO_REGISTER_read_counter__4016_4017 = 0;

		controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 = 0;
		controller_info.IO_REGISTER_CONTROLLER_2P_read_counter__4017 = 0;
	}

	uint8_t* get_bg_chr_table_address() {
		if ((ppu_info.PPU_REGISTER_1__2000 & 0b00010000) == 0) {
			return chr1_image_data;
		}

		return chr2_image_data;
	}

	uint8_t* get_sprite_chr_table_address() {
		if ((ppu_info.PPU_REGISTER_1__2000 & 0b00001000) == 0) {
			return chr1_image_data;
		}

		return chr2_image_data;
	}

	uint16_t calc_valid_RAM_address(uint16_t address) {
		uint16_t valid_address = address;
		if (0x0800 <= address && address <= 0x1fff) {
			valid_address -= 0x0800;
		}
		else if (0x2008 <= address && address <= 0x3fff) {
			M_debug_printf("FC::calc_valid_RAM_address() error\n");
			M_debug_printf("address = 0x%04x\n", address);

			MessageBox(NULL, _T("不正なアドレスの操作が行われました"), _T("ERROR"), MB_OK | MB_ICONERROR);
		}
		else if (pgm_page16kb_num == 1) {//PGMが16KBだったとき
			if (0xC000 <= address && address <= 0xffff) {
				valid_address -= 0x4000;
			}
		}

		return valid_address;
	}
	uint8_t read_fc_RAM(uint16_t address) {
		uint16_t valid_address = calc_valid_RAM_address(address);

		uint8_t read_val = 0;

		if (0x2000 <= valid_address && valid_address <= 0x2007) {//I/Oポート (PPU)
			if (valid_address == 0x2002) {
				/*
				位置 	内容 	クリア時 	セット時
				7 		スクリーンの描画状況 	描画中 	VBlank中
				6 		描画ラインの0番スプライト 	衝突しない 	衝突した
				5 		描画ラインスプライト数 	8個以下 	9個以上
				4 		VRAM状態 	書き込み可能 	書き込み不可
				3-0 	未使用
				*/
				read_val = ppu_info.PPU_REGISTER_3__2002;

				set_Vblank_flag(false);

				ppu_info.PPUADDR_2nd_flag___2005_2006 = false;
				//ppu_info.PPUADDR_2nd_flag__2005 = false;
				

				/*
				* ===================================================
				書き込み状態のみリセットするので不要
				* ===================================================
				*/
//				//ppu_info.scroll_x = 0;
//				//ppu_info.scroll_y = 0;
//				//ppu_info.PPUADDR_address__2006 = 0x0000;
 

				//ppu_info.PPUADDR_2nd_flag__2006 = false;
			}
			else if (valid_address == 0x2007) {
				read_val = ppu_info.PPUADDR_read_buffer_2007;
				ppu_info.PPUADDR_read_buffer_2007 = fc_vram.vram[ppu_info.PPUADDR_address__2006];

				if ((ppu_info.PPU_REGISTER_1__2000 & 0b00000100) == 0) {
					ppu_info.PPUADDR_address__2006++;
				}
				else {
					ppu_info.PPUADDR_address__2006 += 32;
				}
			}
		}
		else if (0x4000 <= valid_address && valid_address <= 0x401f) {//I/Oポート (APU, etc)
			if (valid_address == 0x4016) {//1Pコントローラー
				if (controller_info.IO_REGISTER_read_counter__4016_4017 >= 2) {
					if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 0) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_A)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 1) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_B)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 2) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_SELECT)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 3) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_START)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 4) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_UP)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 5) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_DOWN)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 6) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_LEFT)) {
							read_val = 0b00000001;
						}
					}
					else if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 7) {
						if (1 <= key->get_input_state__FC__(INPUT_MY_ID_RIGHT)) {
							read_val = 0b00000001;
						}
					}
					else {
						//M_debug_printf("0x4016レジスタの読み出しエラーが発生しました[カウント=%d]\n", controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016);

						read_val = 0;
					}

					controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016++;

					if (controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 == 8) {
						//一応内部カウンターを0に戻す
						controller_info.IO_REGISTER_CONTROLLER_1P_read_counter__4016 = 0;
					}
				}
				//else {
				//	M_debug_printf("0x4016レジスタの読み出しエラーが発生しました\n");
				//}
			}
			else if (valid_address == 0x4017) {//2Pコントローラー
				if (controller_info.IO_REGISTER_read_counter__4016_4017 >= 2) {
					read_val = 0;//(まだ実装しない)
				}
			}
		}
		else {//その他(通常読み込み)
			read_val = fc_ram.ram[valid_address];
		}

		return read_val;
	}
	void write_fc_RAM(uint16_t address, uint8_t value) {
		uint16_t valid_address = calc_valid_RAM_address(address);

		if (0x2000 <= valid_address && valid_address <= 0x2007) {//I/Oポート (PPU)
			if (valid_address == 0x2000) {
				ppu_info.PPU_REGISTER_1__2000 = value;
			}
			else if (valid_address == 0x2001) {
				ppu_info.PPU_REGISTER_2__2001 = value;
			}
			else if (valid_address == 0x2003) {
				ppu_info.sprite_address__2003 = value;
			}
			else if (valid_address == 0x2004) {
				ppu_info.sprite_RAM[ppu_info.sprite_address__2003] = value;
				ppu_info.sprite_address__2003++;
			}
			else if (valid_address == 0x2005) {
				if (ppu_info.PPUADDR_2nd_flag___2005_2006 == false) {//X座標の書き込みのとき
					ppu_info.scroll_x = value;
				}
				else {//Y座標の書き込みのとき
					ppu_info.scroll_y = value;
				}

				ppu_info.PPUADDR_2nd_flag___2005_2006 = !ppu_info.PPUADDR_2nd_flag___2005_2006;
			}
			else if (valid_address == 0x2006) {
				if (ppu_info.PPUADDR_2nd_flag___2005_2006 == false) {//一回目の書き込みのとき
					ppu_info.PPUADDR_address__2006 &= 0b0000000011111111;
					ppu_info.PPUADDR_address__2006 |= (value << 8);
				}
				else {//二回目の書き込みのとき
					ppu_info.PPUADDR_address__2006 &= 0b1111111100000000;
					ppu_info.PPUADDR_address__2006 |= value;
				}
				
				ppu_info.PPUADDR_2nd_flag___2005_2006 = !ppu_info.PPUADDR_2nd_flag___2005_2006;
			}
			else if (valid_address == 0x2007) {
				//パレットの指定のときはミラーを考慮する
				if (ppu_info.PPUADDR_address__2006 == 0x3f10 ||
					ppu_info.PPUADDR_address__2006 == 0x3f14 ||
					ppu_info.PPUADDR_address__2006 == 0x3f18 ||
					ppu_info.PPUADDR_address__2006 == 0x3f1C)
				{
					//ミラー先のアドレスにも書き込む
					fc_vram.vram[ppu_info.PPUADDR_address__2006 - 0x10] = value;
				}

				fc_vram.vram[ppu_info.PPUADDR_address__2006] = value;

				if ((ppu_info.PPU_REGISTER_1__2000 & 0b00000100) == 0) {
					ppu_info.PPUADDR_address__2006++;
				}
				else {
					ppu_info.PPUADDR_address__2006 += 32;
				}
			}
		}
		else if (0x4000 <= valid_address && valid_address <= 0x401f) {//I/Oポート (APU, etc)

			if (valid_address == 0x4000) {
				apu_info.APU_SQUARE_CH1__4000 = value;
			}
			else if (valid_address == 0x4001) {
				apu_info.APU_SQUARE_CH1__4001 = value;
			}
			else if (valid_address == 0x4002) {
				apu_info.APU_SQUARE_CH1__4002 = value;
			}
			else if (valid_address == 0x4003) {
				apu_info.APU_SQUARE_CH1__4003 = value;
			}
			else if (valid_address == 0x4004) {
				apu_info.APU_SQUARE_CH2__4004 = value;
			}
			else if (valid_address == 0x4005) {
				apu_info.APU_SQUARE_CH2__4005 = value;
			}
			else if (valid_address == 0x4006) {
				apu_info.APU_SQUARE_CH2__4006 = value;
			}
			else if (valid_address == 0x4007) {
				apu_info.APU_SQUARE_CH2__4007 = value;
			}
			else if (valid_address == 0x4008) {
				apu_info.APU_TRIANGLE__4008 = value;
			}
			else if (valid_address == 0x400A) {
				apu_info.APU_TRIANGLE__400A = value;
			}
			else if (valid_address == 0x400B) {
				apu_info.APU_TRIANGLE__400B = value;
			}
			else if (valid_address == 0x400C) {
				apu_info.APU_NOISE__400C = value;
			}
			else if (valid_address == 0x400E) {
				apu_info.APU_NOISE__400E = value;
			}
			else if (valid_address == 0x400F) {
				apu_info.APU_NOISE__400F = value;
			}
			else if (valid_address == 0x4010) {
				apu_info.APU_DPCM__4010 = value;
			}
			else if (valid_address == 0x4011) {
				apu_info.APU_DPCM__4011 = value;
			}
			else if (valid_address == 0x4012) {
				apu_info.APU_DPCM__4012 = value;
			}
			else if (valid_address == 0x4013) {
				apu_info.APU_DPCM__4013 = value;
			}
			else if (valid_address == 0x4015) {
				apu_info.APU_SETTING__4015 = value;
			}
			else if (valid_address == 0x4014) {
				/*
				この処理はCPUの514クロック分かかる
				*/
				uint16_t address_from = 0x100 * value;
				memcpy(ppu_info.sprite_RAM, (uint8_t*)(fc_ram.ram + address_from), 0x100);

				SPRITE_RAM_DMA_ACCESS_FLAG = true;
			}
			else if (valid_address == 0x4016) {
				if (controller_info.IO_REGISTER_read_counter__4016_4017 == 0) {
					//if (value == 1) {
						controller_info.IO_REGISTER_read_counter__4016_4017++;
					//}
				}
				else if (controller_info.IO_REGISTER_read_counter__4016_4017 == 1) {
					//if (value == 0) {
						controller_info.IO_REGISTER_read_counter__4016_4017++;
					//}
				}
			}
		}
		else {//その他(通常書き込み)
			fc_ram.ram[valid_address] = value;
		}
	}

	void cpu_init();

	void execute_fc_machine(MyDirectXSystem* myDirectXSystem);

	uint8_t fc_screen_backbuffer_2x2[FC_WIDTH * 2 * FC_HEIGHT * 2];
	uint8_t fc_screen_backbuffer[FC_WIDTH * FC_HEIGHT];
	uint32_t draw_pixel_x;
	uint32_t draw_pixel_y;

#ifdef FC_EMU_DEBUG
	void _debug_fc_draw_screen__2x2(MyDirectXSystem* myDirectXSystem);
#endif

	uint8_t get_sprite_tile__palette(uint8_t* tile_palette_ptr, uint8_t palette_no);

	uint8_t get_bg_tile__palette(uint8_t* tile_palette_ptr, uint8_t palette_no);

	uint8_t* get_bg_tile_palette_ptr(uint8_t* ppu_attribute_table_ptr, int tile_x, int tile_y);
	void fc_draw_backbuffer_2x2();
	void fc_draw_backbuffer(uint32_t draw_pixel_number);
	void fc_draw_backbuffer_1pixel();
	uint8_t get_2x2screen_pixel_data_XY(int x, int y);

	void get_draw_sprite_data__calc_reverse_hv(uint8_t sprite_number, uint8_t* ret_sprite_x_ptr, uint8_t* ret_sprite_y_ptr, bool* ret_low_priority_flag_ptr, uint16_t* ret_sprite_image_data_ptr_8x8);
	void fc_draw_sprite_backbuffer();
	void fc_draw_screen(MyDirectXSystem* myDirectXSystem);

	void draw_screen_up_down_black_band(MyDirectXSystem* myDirectXSystem);

	bool is_BG_draw() {
		if ((ppu_info.PPU_REGISTER_2__2001 & 0b00001000) != 0) {
			return true;
		}

		return false;
	}

	bool is_SPRITE_draw() {
		if ((ppu_info.PPU_REGISTER_2__2001 & 0b00010000) != 0) {
			return true;
		}

		return false;
	}

	void set_Vblank_flag(bool flag) {
		if (flag == true) {
			ppu_info.PPU_REGISTER_3__2002 |= 0b10000000;
		}
		else {
			ppu_info.PPU_REGISTER_3__2002 &= 0b01111111;
		}
	}

	bool get_Vblank_flag() {
		if ((ppu_info.PPU_REGISTER_3__2002 & 0b10000000) != 0) {
			return true;
		}

		return false;
	}

	void set_0_sprite_hit(bool flag) {
		if (flag == true) {
			ppu_info.PPU_REGISTER_3__2002 |= 0b01000000;
		}
		else {
			ppu_info.PPU_REGISTER_3__2002 &= 0b10111111;
		}
	}

	bool get_0_sprite_hit_flag() {
		if ((ppu_info.PPU_REGISTER_3__2002 & 0b01000000) != 0) {
			return true;
		}

		return false;
	}

	bool NMI_First_Flag = false;//NMI割り込みを初めて行うときの識別用

	bool get_NMI_flag() {
		if ((ppu_info.PPU_REGISTER_1__2000 & 0b10000000) != 0) {
			return true;
		}

		return false;
	}

	void NMI_process() {
		uint16_t ret_address = fc_register.pc;
		uint8_t pc_1 = (uint8_t)(ret_address >> 8);
		uint8_t pc_2 = (uint8_t)(ret_address & 0b11111111);

		fc_register.p_B = 0;

		fc_ram.stack[fc_register.s] = pc_1;
		fc_register.s--;
		fc_ram.stack[fc_register.s] = pc_2;
		fc_register.s--;

		fc_ram.stack[fc_register.s] = fc_register.p;
		fc_register.s--;

		fc_register.p_I = 1;

		fc_register.pc = (read_fc_RAM(0xFFFA)) | (read_fc_RAM(0xFFFB) << 8);
	}

//#####################################################################
//#####################################################################
	void cpu_fnc_GARBAGE();//未定義の命令(ゴミ)

	//#####################################################################

	void cpu_fnc_LDA_IMMEDIATE() {
		fc_register.a = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.a = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.a = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.a = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.a = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		fc_register.a = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LDA_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void cpu_fnc_LDX_IMMEDIATE() {
		fc_register.x = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	void cpu_fnc_LDX_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.x = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	void cpu_fnc_LDX_ZEROPAGE_Y() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.y;
		fc_register.x = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	void cpu_fnc_LDX_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.x = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	void cpu_fnc_LDX_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.x = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	//#####################################################################

	void cpu_fnc_LDY_IMMEDIATE() {
		fc_register.y = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	void cpu_fnc_LDY_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.y = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	void cpu_fnc_LDY_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.y = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	void cpu_fnc_LDY_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.y = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	void cpu_fnc_LDY_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.y = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	//#####################################################################

	void cpu_fnc_STA_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, fc_register.a);
		fc_register.pc++;
	}

	void cpu_fnc_STA_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		write_fc_RAM(tmp_zero_addr, fc_register.a);
		fc_register.pc++;
	}

	void cpu_fnc_STA_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, fc_register.a);
		fc_register.pc += 2;
	}

	void cpu_fnc_STA_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		write_fc_RAM(tmp_16bit_addr, fc_register.a);
		fc_register.pc += 2;
	}

	void cpu_fnc_STA_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		write_fc_RAM(tmp_16bit_addr, fc_register.a);
		fc_register.pc += 2;
	}

	void cpu_fnc_STA_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		write_fc_RAM(tmp_16bit_addr, fc_register.a);
		fc_register.pc++;
	}

	void cpu_fnc_STA_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		write_fc_RAM(tmp_16bit_addr, fc_register.a);
		fc_register.pc++;
	}

	//#####################################################################

	void cpu_fnc_STX_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, fc_register.x);
		fc_register.pc++;
	}

	void cpu_fnc_STX_ZEROPAGE_Y() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.y;
		write_fc_RAM(tmp_zero_addr, fc_register.x);
		fc_register.pc++;
	}

	void cpu_fnc_STX_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, fc_register.x);
		fc_register.pc += 2;
	}

	//#####################################################################

	void cpu_fnc_STY_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, fc_register.y);
		fc_register.pc++;
	}

	void cpu_fnc_STY_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		write_fc_RAM(tmp_zero_addr, fc_register.y);
		fc_register.pc++;
	}

	void cpu_fnc_STY_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, fc_register.y);
		fc_register.pc += 2;
	}

	//#####################################################################

	void cpu_fnc_ADC_IMMEDIATE() {
		uint8_t bef_register_a = fc_register.a;
		uint8_t tmp_8bit = read_fc_RAM(fc_register.pc);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_ZEROPAGE() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint8_t tmp_8bit = read_fc_RAM(tmp_zero_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_ZEROPAGE_X() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint8_t tmp_8bit = read_fc_RAM(tmp_zero_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_ABSOLUTE() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_ABSOLUTE_X() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_ABSOLUTE_Y() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_INDEX_INDIRECT_X() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ADC_INDIRECT_INDEX_Y() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		uint16_t tmp_16bit = fc_register.a + tmp_8bit + fc_register.p_C;
		calc_C_flag(tmp_16bit);

		fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__add(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void cpu_fnc_AND_IMMEDIATE() {
		fc_register.a &= read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.a &= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.a &= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.a &= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.a &= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a &= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		fc_register.a &= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_AND_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a &= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void calc_C_flag_LSHIFT(uint8_t result) {
		if ((result & 0b10000000) != 0) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}
	}

	void cpu_fnc_ASL_ACCUMULATOR() {
		calc_C_flag_LSHIFT(fc_register.a);
		uint16_t register_a_16bit = (uint16_t)fc_register.a;
		register_a_16bit <<= 1;
		//calc_C_flag(register_a_16bit);

		fc_register.a = (uint8_t)(0b11111111 & register_a_16bit);

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ASL_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;
		//calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_ASL_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;
		//calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_ASL_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;
		//calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_ASL_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;
		//calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_BIT_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint8_t tmp_8bit = read_fc_RAM(tmp_zero_addr);

		if ((fc_register.a & tmp_8bit) == 0) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}

		if ((tmp_8bit & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}

		if ((tmp_8bit & 0b01000000) != 0) {
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}

		fc_register.pc++;
	}

	void cpu_fnc_BIT_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		if ((fc_register.a & tmp_8bit) == 0) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}

		if ((tmp_8bit & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}

		if ((tmp_8bit & 0b01000000) != 0) {
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}

		fc_register.pc += 2;
	}

	//#####################################################################

	void cmp_A_process(uint8_t cmp_mem_8bit) {
		if (fc_register.a == cmp_mem_8bit) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}

		if (fc_register.a >= cmp_mem_8bit) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}

		if (((fc_register.a - cmp_mem_8bit) & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}
	}

	void cpu_fnc_CMP_IMMEDIATE() {
		cmp_A_process(read_fc_RAM(fc_register.pc));
		fc_register.pc++;
	}

	void cpu_fnc_CMP_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		cmp_A_process(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_CMP_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.pc++;

		cmp_A_process(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_CMP_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.pc += 2;

		cmp_A_process(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_CMP_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.pc += 2;

		cmp_A_process(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_CMP_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.pc += 2;

		cmp_A_process(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_CMP_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		fc_register.pc++;

		cmp_A_process(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_CMP_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.pc++;

		cmp_A_process(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cmp_X_process(uint8_t cmp_mem_8bit) {
		if (fc_register.x == cmp_mem_8bit) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}

		if (fc_register.x >= cmp_mem_8bit) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}

		if (((fc_register.x - cmp_mem_8bit) & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}
	}

	void cpu_fnc_CPX_IMMEDIATE() {
		cmp_X_process(read_fc_RAM(fc_register.pc));
		fc_register.pc++;
	}

	void cpu_fnc_CPX_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		cmp_X_process(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_CPX_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.pc += 2;

		cmp_X_process(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cmp_Y_process(uint8_t cmp_mem_8bit) {
		if (fc_register.y == cmp_mem_8bit) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}

		if (fc_register.y >= cmp_mem_8bit) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}

		if (((fc_register.y - cmp_mem_8bit) & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}
	}

	void cpu_fnc_CPY_IMMEDIATE() {
		cmp_Y_process(read_fc_RAM(fc_register.pc));
		fc_register.pc++;
	}

	void cpu_fnc_CPY_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		cmp_Y_process(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_CPY_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.pc += 2;

		cmp_Y_process(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_DEC_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) - 1));
		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_DEC_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) - 1));
		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_DEC_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_DEC_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_DEX() {
		fc_register.x--;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	//#####################################################################

	void cpu_fnc_DEY() {
		fc_register.y--;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	//#####################################################################

	void cpu_fnc_EOR_IMMEDIATE() {
		fc_register.a ^= read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.a ^= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.a ^= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.a ^= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.a ^= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a ^= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		fc_register.a ^= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_EOR_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a ^= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void cpu_fnc_INC_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) + 1));
		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_INC_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) + 1));
		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_INC_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) + 1));
		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_INC_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) + 1));
		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_INX() {
		fc_register.x++;

		calc_N_flag(fc_register.x);
		calc_Z_flag(fc_register.x);
	}

	//#####################################################################

	void cpu_fnc_INY() {
		fc_register.y++;

		calc_N_flag(fc_register.y);
		calc_Z_flag(fc_register.y);
	}

	//#####################################################################

	void calc_C_flag_RSHIFT(uint8_t bef_8bit) {
		if ((bef_8bit & 0b00000001) != 0) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}
	}

	void cpu_fnc_LSR_ACCUMULATOR() {
		calc_C_flag_RSHIFT(fc_register.a);

		fc_register.a >>= 1;

		//calc_N_flag(fc_register.a);
		fc_register.p_N = 0;//ネガティブフラグは必ず0になる
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_LSR_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		calc_C_flag_RSHIFT(read_fc_RAM(tmp_zero_addr));
		write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) >> 1);

		fc_register.pc++;

		//calc_N_flag(read_fc_RAM(tmp_zero_addr));
		fc_register.p_N = 0;//ネガティブフラグは必ず0になる
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_LSR_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;

		calc_C_flag_RSHIFT(read_fc_RAM(tmp_zero_addr));
		write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) >> 1);

		fc_register.pc++;

		//calc_N_flag(read_fc_RAM(tmp_zero_addr));
		fc_register.p_N = 0;//ネガティブフラグは必ず0になる
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_LSR_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		
		calc_C_flag_RSHIFT(read_fc_RAM(tmp_16bit_addr));
		write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) >> 1);

		fc_register.pc += 2;

		//calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		fc_register.p_N = 0;//ネガティブフラグは必ず0になる
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_LSR_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;

		calc_C_flag_RSHIFT(read_fc_RAM(tmp_16bit_addr));
		write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) >> 1);

		fc_register.pc += 2;

		//calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		fc_register.p_N = 0;//ネガティブフラグは必ず0になる
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_ORA_IMMEDIATE() {
		fc_register.a |= read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		fc_register.a |= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		fc_register.a |= read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		fc_register.a |= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		fc_register.a |= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a |= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		fc_register.a |= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ORA_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		fc_register.a |= read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void cpu_fnc_ROL_ACCUMULATOR() {
		uint16_t register_a_16bit = (uint16_t)fc_register.a;
		register_a_16bit <<= 1;
		register_a_16bit |= fc_register.p_C;
		calc_C_flag(register_a_16bit);

		fc_register.a = (uint8_t)(0b11111111 & register_a_16bit);

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_ROL_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit |= fc_register.p_C;
		calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_ROL_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit |= fc_register.p_C;
		calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));
	}

	void cpu_fnc_ROL_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		tmp_mem_16bit <<= 1;
		tmp_mem_16bit |= fc_register.p_C;
		calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	void cpu_fnc_ROL_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		tmp_mem_16bit <<= 1;
		tmp_mem_16bit |= fc_register.p_C;
		calc_C_flag(tmp_mem_16bit);

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void cpu_fnc_ROR_ACCUMULATOR() {
		uint8_t bef_register_a = fc_register.a;

		fc_register.a >>= 1;
		if (fc_register.p_C != 0) {
			fc_register.a |= 0b10000000;
		}

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);

		calc_C_flag_RSHIFT(bef_register_a);
	}

	void cpu_fnc_ROR_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		uint8_t bef_mem_8bit = read_fc_RAM(tmp_zero_addr);

		write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) >> 1);
		if (fc_register.p_C != 0) {
			write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) | 0b10000000);
		}

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));

		calc_C_flag_RSHIFT(bef_mem_8bit);
	}

	void cpu_fnc_ROR_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;

		uint8_t bef_mem_8bit = read_fc_RAM(tmp_zero_addr);

		write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) >> 1);
		if (fc_register.p_C != 0) {
			write_fc_RAM(tmp_zero_addr, read_fc_RAM(tmp_zero_addr) | 0b10000000);
		}

		fc_register.pc++;

		calc_N_flag(read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(read_fc_RAM(tmp_zero_addr));

		calc_C_flag_RSHIFT(bef_mem_8bit);
	}

	void cpu_fnc_ROR_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);

		uint8_t bef_mem_8bit = read_fc_RAM(tmp_16bit_addr);

		write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) >> 1);
		if (fc_register.p_C != 0) {
			write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) | 0b10000000);
		}

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));

		calc_C_flag_RSHIFT(bef_mem_8bit);
	}

	void cpu_fnc_ROR_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;

		uint8_t bef_mem_8bit = read_fc_RAM(tmp_16bit_addr);

		write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) >> 1);
		if (fc_register.p_C != 0) {
			write_fc_RAM(tmp_16bit_addr, read_fc_RAM(tmp_16bit_addr) | 0b10000000);
		}

		fc_register.pc += 2;

		calc_N_flag(read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(read_fc_RAM(tmp_16bit_addr));

		calc_C_flag_RSHIFT(bef_mem_8bit);
	}

	//#####################################################################

	void cpu_fnc_SBC_IMMEDIATE() {
		uint8_t bef_register_a = fc_register.a;
		uint8_t tmp_8bit = read_fc_RAM(fc_register.pc);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_ZEROPAGE() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint8_t tmp_8bit = read_fc_RAM(tmp_zero_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_ZEROPAGE_X() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint8_t tmp_8bit = read_fc_RAM(tmp_zero_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_ABSOLUTE() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_ABSOLUTE_X() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_ABSOLUTE_Y() {
		uint8_t bef_register_a = fc_register.a;

		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_INDEX_INDIRECT_X() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void cpu_fnc_SBC_INDIRECT_INDEX_Y() {
		uint8_t bef_register_a = fc_register.a;

		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		uint8_t tmp_8bit = read_fc_RAM(tmp_16bit_addr);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void cpu_fnc_JMP_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		//fc_register.pc += 2;

		fc_register.pc = tmp_16bit_addr;
	}
	
	void cpu_fnc_JMP_INDIRECT() {
		uint16_t tmp_16bit_addr_1 = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint16_t tmp_16bit_addr_2 = (read_fc_RAM(tmp_16bit_addr_1)) | (read_fc_RAM((tmp_16bit_addr_1 & 0b1111111100000000) | ((uint8_t)(tmp_16bit_addr_1 + 1))) << 8);
		//fc_register.pc += 2;

		fc_register.pc = tmp_16bit_addr_2;
	}

	//#####################################################################

	void cpu_fnc_JSR() {
		uint16_t jmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);

		uint16_t ret_address = (fc_register.pc + 2) - 1;
		uint8_t pc_1 = (uint8_t)(ret_address >> 8);
		uint8_t pc_2 = (uint8_t)(ret_address & 0b11111111);

		fc_ram.stack[fc_register.s] = pc_1;
		fc_register.s--;
		fc_ram.stack[fc_register.s] = pc_2;
		fc_register.s--;

		fc_register.pc = jmp_16bit_addr;
	}

	void cpu_fnc_RTS() {
		uint16_t ret_16bit_addr;

		uint8_t pc_1;
		uint8_t pc_2;

		fc_register.s++;
		pc_2 = fc_ram.stack[fc_register.s];
		fc_register.s++;
		pc_1 = fc_ram.stack[fc_register.s];

		ret_16bit_addr = (pc_1 << 8) | pc_2;

		fc_register.pc = (ret_16bit_addr + 1);
	}

	//#####################################################################

	void FC::cpu_fnc_BRK() {
		M_debug_printf("BRK!!!!!\n");

		bool bef_I_flag = (fc_register.p_I == 0) ? false : true;

		fc_register.pc++;

		uint16_t ret_address = fc_register.pc;
		uint8_t pc_1 = (uint8_t)(ret_address >> 8);
		uint8_t pc_2 = (uint8_t)(ret_address & 0b11111111);

		fc_ram.stack[fc_register.s] = pc_1;
		fc_register.s--;
		fc_ram.stack[fc_register.s] = pc_2;
		fc_register.s--;

		fc_register.p_B = 1;

		fc_ram.stack[fc_register.s] = fc_register.p;
		fc_register.s--;

		fc_register.p_I = 1;

		if (bef_I_flag == false) {
			fc_register.pc = (read_fc_RAM(0xFFFE)) | (read_fc_RAM(0xFFFF) << 8);
		}

		fc_register.pc--;
	}

	void cpu_fnc_RTI() {
		uint16_t ret_16bit_addr;

		uint8_t pc_1;
		uint8_t pc_2;

		fc_register.s++;
		fc_register.p = fc_ram.stack[fc_register.s];
		fc_register.p_R = 1;

		fc_register.s++;
		pc_2 = fc_ram.stack[fc_register.s];
		fc_register.s++;
		pc_1 = fc_ram.stack[fc_register.s];
		ret_16bit_addr = (pc_1 << 8) | pc_2;

		fc_register.pc = ret_16bit_addr;
	}

	//#####################################################################

	void relative_jump(uint8_t relative_address) {
		if (relative_address > 127) {//相対アドレスが負数のとき
			fc_register.pc -= (0x100 - relative_address);
		}
		else {//相対アドレスが負数でないとき
			fc_register.pc += relative_address;
		}
	}

	void cpu_fnc_BCC() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_C == 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BCS() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_C != 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BEQ() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_Z != 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BMI() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_N != 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BNE() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_Z == 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BPL() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_N == 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BVC() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_V == 0) {
			relative_jump(relative_addr);
		}
	}

	void cpu_fnc_BVS() {
		uint8_t relative_addr = read_fc_RAM(fc_register.pc);
		fc_register.pc++;

		if (fc_register.p_V != 0) {
			relative_jump(relative_addr);
		}
	}

	//#####################################################################

	void cpu_fnc_TAX();
	void cpu_fnc_TXA();
	void cpu_fnc_TAY();
	void cpu_fnc_TYA();
	void cpu_fnc_TXS();
	void cpu_fnc_TSX();

	//#####################################################################

	void cpu_fnc_PHA();
	void cpu_fnc_PLA();
	void cpu_fnc_PHP();
	void cpu_fnc_PLP();

	//#####################################################################

	void cpu_fnc_CLC();
	void cpu_fnc_CLD();
	void cpu_fnc_CLI();
	void cpu_fnc_CLV();
	void cpu_fnc_SEC();
	void cpu_fnc_SED();
	void cpu_fnc_SEI();

	void cpu_fnc_NOP();
	//#####################################################################
	
	//NOP
	void UNOFFICIAL_NOP_PROCESS() {
	}

	void UNOFFICIAL_cpu_fnc_NOP__1A() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__3A() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__5A() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__7A() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__DA() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__FA() {
		UNOFFICIAL_NOP_PROCESS();
	}


	void UNOFFICIAL_cpu_fnc_NOP__02() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__12() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__22() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__32() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__42() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__52() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__62() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__72() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__92() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__B2() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__D2() {
		UNOFFICIAL_NOP_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOP__F2() {
		UNOFFICIAL_NOP_PROCESS();
	}

	//#####################################################################

	//NOP #8bit
	void UNOFFICIAL_NOPD_PROCESS() {
		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_NOPD__80() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__82() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__89() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__C2() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__E2() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__04() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__44() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__64() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__14() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__34() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__54() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__74() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__D4() {
		UNOFFICIAL_NOPD_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPD__F4() {
		UNOFFICIAL_NOPD_PROCESS();
	}

	//#####################################################################

	//NOP #8bit
	void UNOFFICIAL_NOPI_PROCESS() {
		fc_register.pc += 2;
	}

	void UNOFFICIAL_cpu_fnc_NOPI__0C() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__1C() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__3C() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__5C() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__7C() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__DC() {
		UNOFFICIAL_NOPI_PROCESS();
	}
	void UNOFFICIAL_cpu_fnc_NOPI__FC() {
		UNOFFICIAL_NOPI_PROCESS();
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_LAX_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		uint8_t read_mem_data = read_fc_RAM(tmp_zero_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_LAX_ZEROPAGE_Y() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.y;

		uint8_t read_mem_data = read_fc_RAM(tmp_zero_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		
		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_LAX_ABSOLUTE_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.a = read_mem_data;
		fc_register.x = read_mem_data;
		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_SAX_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, (fc_register.a & fc_register.x));
		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_SAX_ZEROPAGE_Y() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.y;
		write_fc_RAM(tmp_zero_addr, (fc_register.a & fc_register.x));
		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_SAX_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		write_fc_RAM(tmp_16bit_addr, (fc_register.a & fc_register.x));
		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_SAX_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, (fc_register.a & fc_register.x));
		fc_register.pc += 2;
	}


	//#####################################################################

	//公式のやつと同じ
	void UNOFFICIAL_cpu_fnc_SBC_IMMEDIATE() {
		uint8_t bef_register_a = fc_register.a;
		uint8_t tmp_8bit = read_fc_RAM(fc_register.pc);

		int16_t tmp_16bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		uint8_t tmp_8bit_2 = fc_register.a - tmp_8bit - ((fc_register.p_C == 0) ? 1 : 0);
		calc_C_flag__sub_2(tmp_16bit_2);

		fc_register.a = tmp_8bit_2;

		//fc_register.a = (uint8_t)(0b11111111 & tmp_16bit);
		//calc_V_flag(bef_register_a, fc_register.a);
		//calc_V_flag(tmp_8bit, fc_register.a);
		calc_V_flag__sub(bef_register_a, tmp_8bit, fc_register.a);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_DCP_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) - 1));
		fc_register.pc++;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_zero_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_zero_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		write_fc_RAM(tmp_zero_addr, (uint8_t)(read_fc_RAM(tmp_zero_addr) - 1));
		fc_register.pc++;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_zero_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_zero_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_zero_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc += 2;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc += 2;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc += 2;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;

		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc++;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
	}

	void UNOFFICIAL_cpu_fnc_DCP_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);

		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		write_fc_RAM(tmp_16bit_addr, (uint8_t)(read_fc_RAM(tmp_16bit_addr) - 1));
		fc_register.pc++;

		//calc_C_flag__sub(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_N_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
		calc_Z_flag(fc_register.a - read_fc_RAM(tmp_16bit_addr));
	}

	//#####################################################################

	void ISB_CALC_P_FLAGS(uint8_t target_mem_data, uint32_t result_32bit) {
		uint8_t result_8bit = (uint8_t)result_32bit;
		if (!(((fc_register.a ^ target_mem_data) & 0b10000000) != 0) &&
			(((fc_register.a ^ result_8bit) & 0b10000000) != 0))
		{
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}
		if (result_32bit > 0xFF) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}
		if ((result_8bit & 0b10000000) != 0) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}
		if (result_8bit == 0) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}
	}

	void UNOFFICIAL_cpu_fnc_ISB_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		uint8_t read_mem_data = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_zero_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;

		uint8_t read_mem_data = read_fc_RAM(tmp_zero_addr);
		fc_register.pc++;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_zero_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_16bit_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_16bit_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc += 2;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_16bit_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_16bit_addr, target_mem_data);
	}

	void UNOFFICIAL_cpu_fnc_ISB_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t read_mem_data = read_fc_RAM(tmp_16bit_addr);
		fc_register.pc++;

		uint8_t target_mem_data = read_mem_data + 1;
		uint32_t result_32bit = ((uint8_t)(~target_mem_data)) + fc_register.a + fc_register.p_C;
		ISB_CALC_P_FLAGS(target_mem_data, result_32bit);

		fc_register.a = (uint8_t)result_32bit;
		write_fc_RAM(tmp_16bit_addr, target_mem_data);
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_SLO_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SLO_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		uint16_t tmp_mem_16bit = read_fc_RAM(tmp_16bit_addr);

		calc_C_flag_LSHIFT((uint8_t)tmp_mem_16bit);
		tmp_mem_16bit <<= 1;

		fc_register.a |= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_RLA_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_zero_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_zero_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_16bit_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_16bit_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_16bit_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_16bit_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_RLA_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;
		uint16_t tmp_mem_16bit = (uint16_t)(read_fc_RAM(tmp_16bit_addr));
		tmp_mem_16bit <<= 1;
		tmp_mem_16bit += fc_register.p_C;

		calc_C_flag(tmp_mem_16bit);

		fc_register.a &= (uint8_t)tmp_mem_16bit;

		write_fc_RAM(tmp_16bit_addr, (uint8_t)(0b11111111 & tmp_mem_16bit));

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void UNOFFICIAL_cpu_fnc_SRE_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_zero_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_zero_addr, tmp_mem_8bit);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_zero_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_zero_addr, tmp_mem_8bit);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		
		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		
		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	void UNOFFICIAL_cpu_fnc_SRE_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		calc_C_flag_RSHIFT(tmp_mem_8bit);
		tmp_mem_8bit >>= 1;

		fc_register.a ^= tmp_mem_8bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc++;

		calc_N_flag(fc_register.a);
		calc_Z_flag(fc_register.a);
	}

	//#####################################################################

	void calc_V_flag__rra(uint8_t target, uint8_t aft) {
		//同じ符号同士の演算かつ計算結果の符号が元の符号と異なるとき
		if (((fc_register.a ^ target) & 0b10000000) == 0 && ((fc_register.a ^ aft) & 0b10000000) != 0) {
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}
	}

	void UNOFFICIAL_cpu_fnc_RRA_ZEROPAGE() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_zero_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_zero_addr, tmp_mem_8bit);

		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_RRA_ZEROPAGE_X() {
		uint8_t tmp_zero_addr = read_fc_RAM(fc_register.pc);
		tmp_zero_addr += fc_register.x;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_zero_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_zero_addr, tmp_mem_8bit);

		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		
		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;
	}

	void UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE_X() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.x;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;
	}

	void UNOFFICIAL_cpu_fnc_RRA_ABSOLUTE_Y() {
		uint16_t tmp_16bit_addr = (read_fc_RAM(fc_register.pc)) | (read_fc_RAM(fc_register.pc + 1) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc += 2;
	}

	void UNOFFICIAL_cpu_fnc_RRA_INDEX_INDIRECT_X() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		tmp_8bit_addr += fc_register.x;
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		
		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc++;
	}

	void UNOFFICIAL_cpu_fnc_RRA_INDIRECT_INDEX_Y() {
		uint8_t tmp_8bit_addr = read_fc_RAM(fc_register.pc);
		uint16_t tmp_16bit_addr = (read_fc_RAM(tmp_8bit_addr)) | (read_fc_RAM((uint8_t)(tmp_8bit_addr + 1)) << 8);
		tmp_16bit_addr += fc_register.y;

		uint8_t tmp_mem_8bit = read_fc_RAM(tmp_16bit_addr);
		bool mem8bit_C_flag = ((tmp_mem_8bit & 0b00000001) != 0) ? true : false;

		tmp_mem_8bit >>= 1;
		if (fc_register.p_C == 1) {
			tmp_mem_8bit |= 0b10000000;
		}

		uint16_t result_16bit = tmp_mem_8bit + fc_register.a;
		if (mem8bit_C_flag == true) {
			result_16bit += 1;
		}
		calc_V_flag__rra(tmp_mem_8bit, (uint8_t)result_16bit);

		calc_N_flag((uint8_t)result_16bit);
		calc_Z_flag((uint8_t)result_16bit);
		calc_C_flag(result_16bit);

		fc_register.a = (uint8_t)result_16bit;

		write_fc_RAM(tmp_16bit_addr, tmp_mem_8bit);

		fc_register.pc++;
	}

	//#####################################################################


//#####################################################################
//#####################################################################

	void calc_C_flag(uint16_t result) {
		if ((result >> 8) != 0) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}
	}
//	void calc_C_flag__sub(uint8_t result) {
//		//if (0x00 <= result && result <= 0x7F) {
//			//演算結果が0を下回らない（ボローなし）のとき
//		if (0x00 <= result) {
//			fc_register.p_C = 1;
//		}
//		else {
//			fc_register.p_C = 0;
//		}
//	}
	void calc_C_flag__sub_2(int16_t result) {
		if (0x00 <= result) {
			fc_register.p_C = 1;
		}
		else {
			fc_register.p_C = 0;
		}
	}
	void calc_Z_flag(uint8_t result) {
		if (result == 0) {
			fc_register.p_Z = 1;
		}
		else {
			fc_register.p_Z = 0;
		}
	}
//	void calc_I_flag();
//	void calc_D_flag();
//	void calc_B_flag();
//	void calc_R_flag();
	void calc_V_flag__add(uint8_t bef, uint8_t target, uint8_t aft) {
		//同じ符号同士の演算かつ計算結果の符号が元の符号と異なるとき
		if (((bef ^ target) & 0b10000000) == 0 && ((bef ^ aft) & 0b10000000) != 0) {
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}
	}
	void calc_V_flag__sub(uint8_t bef, uint8_t target, uint8_t aft) {
		//異なる符号同士の演算かつ計算結果の符号が 1 つ目の整数の符号と異なるとき
		if (((bef ^ target) & 0b10000000) != 0 && ((bef ^ aft) & 0b10000000) != 0) {
			fc_register.p_V = 1;
		}
		else {
			fc_register.p_V = 0;
		}
	}
	void calc_N_flag(uint8_t result) {
		if (result & 0b10000000) {
			fc_register.p_N = 1;
		}
		else {
			fc_register.p_N = 0;
		}
	}

public:
	FC(const char* rom_filename, Key* key);
	~FC();

	void execute_all(MyDirectXSystem* myDirectXSystem);

	bool get_FATAL_ERROR_FLAG() {
		return FATAL_ERROR_FLAG;
	}
};
