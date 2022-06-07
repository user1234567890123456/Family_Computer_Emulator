#include "FC.h"


FC::FC(const char* rom_filename, Key* key) : key(key) {
	memset(fc_ram.ram, 0, RAM_SIZE);
	memset(fc_vram.vram, 0, VRAM_SIZE);

	if (readrom(rom_filename) == -1) {
		goto fc_init_error;
	}

	if (init_chr() == -1) {
		goto fc_init_error;
	}

	Main::ROM_loaded_flag = true;

	//debug_chr1_image_print(16*2 + 2);
	//M_debug_printf("################################\n");
	//debug_chr2_image_print(16*2 + 2);


	cpu_init();


	M_debug_printf("################################\n");
	M_debug_printf("FC::FC() Succeed!\n");
	M_debug_printf("################################\n");

	return;

fc_init_error:
	M_debug_printf("################################\n");
	M_debug_printf("FC::FC() Failed......\n");
	M_debug_printf("################################\n");

	MessageBox(NULL, _T("ROMの初期化の際にエラーが発生しました"), _T("ERROR"), MB_OK | MB_ICONERROR);

	FATAL_ERROR_FLAG = true;
}

FC::~FC() {
	free(pgm_rom_data);
	free(chr_rom_data);
	free(chr1_image_data);
	free(chr2_image_data);
}

int FC::readrom_header(const char* filename) {
	FILE* rom_fp;
	if (fopen_s(&rom_fp, filename, "rb") != 0) {
		return -1;
	}

	uint8_t header[4];
	if (fread(header, sizeof(uint8_t), 4, rom_fp) != 4) {
		goto read_rom_error;
	}
	if (header[0] != 0x4E ||
		header[1] != 0x45 ||
		header[2] != 0x53 ||
		header[3] != 0x1A)
	{
		goto read_rom_error;
	}

	if (fread(&pgm_page16kb_num, sizeof(uint8_t), 1, rom_fp) != 1) {
		goto read_rom_error;
	}
	if (fread(&chr_page8kb_num, sizeof(uint8_t), 1, rom_fp) != 1) {
		goto read_rom_error;
	}

	Main::PGM_size = pgm_page16kb_num * 16;
	Main::CHR_size = chr_page8kb_num * 8;

	uint8_t tmp_buf_1;
	uint8_t tmp_buf_2;
	uint8_t tmp1;

	if (fread(&tmp_buf_1, sizeof(uint8_t), 1, rom_fp) != 1) {
		goto read_rom_error;
	}
	if (fread(&tmp_buf_2, sizeof(uint8_t), 1, rom_fp) != 1) {
		goto read_rom_error;
	}

	tmp1 = tmp_buf_1 & 0b00000001;
	if (tmp1 == 0) {
		mirror_type = MIRROR_TYPE::HORIZONTAL;

		Main::Mirror = 0;
	}
	else {
		mirror_type = MIRROR_TYPE::VERTICAL;

		Main::Mirror = 1;
	}

	tmp1 = (tmp_buf_1 & 0b00000010) >> 1;
	sram_flag = (tmp1 == 0) ? false : true;

	tmp1 = (tmp_buf_1 & 0b00000100) >> 2;
	trainer_flag = (tmp1 == 0) ? false : true;

	tmp1 = (tmp_buf_1 & 0b00001000) >> 3;
	four_screen_flag = (tmp1 == 0) ? false : true;

	mapper_num = (tmp_buf_1 & 0b11110000) >> 4;
	mapper_num |= (tmp_buf_2 & 0b11110000);

	Main::Mapper = mapper_num;

	tmp1 = tmp_buf_2 & 0b00000001;
	unisystem_flag = (tmp1 == 0) ? false : true;

	M_debug_printf("################################\n");
	M_debug_printf("pgm_page16kb_num = %d\n", pgm_page16kb_num);
	M_debug_printf("chr_page8kb_num = %d\n", chr_page8kb_num);
	M_debug_printf("mirror_type = %s\n", (mirror_type == MIRROR_TYPE::HORIZONTAL) ? "HORIZONAL" : "VERTICAL");
	M_debug_printf("sram_flag = %s\n", (sram_flag == true) ? "true" : "false");
	M_debug_printf("trainer_flag = %s\n", (trainer_flag == true) ? "true" : "false");
	M_debug_printf("four_screen_flag = %s\n", (four_screen_flag == true) ? "true" : "false");
	M_debug_printf("mapper_num = %d\n", mapper_num);
	M_debug_printf("unisystem_flag = %s\n", (unisystem_flag == true) ? "true" : "false");
	M_debug_printf("################################\n");

	fclose(rom_fp);

	return 0;

read_rom_error:
	fclose(rom_fp);

	return -1;
}

int FC::readrom(const char* filename) {
	if (readrom_header(filename) == -1) {
		return -1;
	}

	const int PGM_SIZE = 1024 * 16 * pgm_page16kb_num;
	const int CHR_SIZE = 1024 * 8 * chr_page8kb_num;
	pgm_rom_data = (uint8_t*)malloc(PGM_SIZE);
	if (pgm_rom_data == NULL) {
		return -1;
	}
	chr_rom_data = (uint8_t*)malloc(CHR_SIZE);
	if (chr_rom_data == NULL) {
		return -1;
	}
	memset(pgm_rom_data, 0, PGM_SIZE);
	memset(chr_rom_data, 0, CHR_SIZE);

	FILE* rom_fp;
	if (fopen_s(&rom_fp, filename, "rb") != 0) {
		return -1;
	}

	uint8_t skip_16byte[16];
	if (fread(skip_16byte, sizeof(uint8_t), 16, rom_fp) != 16) {
		goto read_rom_error;
	}

	if (fread(pgm_rom_data, sizeof(uint8_t), PGM_SIZE, rom_fp) != PGM_SIZE) {
		goto read_rom_error;
	}

	if (fread(chr_rom_data, sizeof(uint8_t), CHR_SIZE, rom_fp) != CHR_SIZE) {
		goto read_rom_error;
	}


	memcpy(fc_vram.pattern_table_low, chr_rom_data, 0x2000);

	//memcpy((uint8_t*)(fc_ram.ram + 0x8000), pgm_rom_data, PGM_SIZE);
	memcpy(fc_ram.ROM_low, pgm_rom_data, PGM_SIZE);
	
	if (pgm_page16kb_num == 1) {//PGMが16KBだったとき
		memcpy((uint8_t*)(fc_ram.ram + 0x8000 + PGM_SIZE), pgm_rom_data, PGM_SIZE);
	}

	fclose(rom_fp);

	return 0;

read_rom_error:
	fclose(rom_fp);
	return -1;
}

int FC::init_chr() {
	const int CHR1_IMAGE_SIZE = 8 * 8 * 256;
	chr1_image_data = (uint8_t*)malloc(CHR1_IMAGE_SIZE);
	if (chr1_image_data == NULL) {
		return -1;
	}
	const int CHR2_IMAGE_SIZE = 8 * 8 * 256;
	chr2_image_data = (uint8_t*)malloc(CHR2_IMAGE_SIZE);
	if (chr2_image_data == NULL) {
		return -1;
	}
	memset(chr1_image_data, 0, CHR1_IMAGE_SIZE);
	memset(chr2_image_data, 0, CHR2_IMAGE_SIZE);


	//CHR1
	for (int i = 0; i < 256; i++) {
		uint8_t tmp_read_buffer[16];
		for (int j = 0; j < 16; j++) {
			tmp_read_buffer[j] = chr_rom_data[i * 16 + j];
		}

		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++) {
				chr1_image_data[8 * 8 * i + 8 * k + l] =
					((tmp_read_buffer[k] & (0b10000000 >> l)) >> (7 - l)) | (((tmp_read_buffer[k + 8] & (0b10000000 >> l)) >> (7 - l)) << 1);
			}
		}
	}


	//CHR2
	for (int i = 0; i < 256; i++) {
		uint8_t tmp_read_buffer[16];
		for (int j = 0; j < 16; j++) {
			tmp_read_buffer[j] = chr_rom_data[0x1000 + i * 16 + j];
		}

		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++) {
				chr2_image_data[8 * 8 * i + 8 * k + l] =
					((tmp_read_buffer[k] & (0b10000000 >> l)) >> (7 - l)) | (((tmp_read_buffer[k + 8] & (0b10000000 >> l)) >> (7 - l)) << 1);
			}
		}
	}
	
	return 0;
}

#ifdef FC_EMU_DEBUG
void FC::debug_chr1_image_print(uint8_t number) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			M_debug_printf("%d ", chr1_image_data[8*8*number + i*8 + j]);
		}
		M_debug_printf("\n");
	}
}

void FC::debug_chr2_image_print(uint8_t number) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			M_debug_printf("%d ", chr2_image_data[8 * 8 * number + i * 8 + j]);
		}
		M_debug_printf("\n");
	}
}
#endif

void FC::cpu_init() {
	fc_register.a = 0;
	fc_register.x = 0;
	fc_register.y = 0;
	fc_register.s = 0xFD;
	//fc_register.s = 0;
	//fc_register.p = 0;
	fc_register.p_R = 1;
	fc_register.p_I = 1;
	//fc_register.pc = 0;
	//fc_register.pc = 0x8000;
	//fc_register.pc = 0xC000;
	fc_register.pc = (read_fc_RAM(0xFFFC)) | (read_fc_RAM(0xFFFD) << 8);
	M_debug_printf("FC::cpu_init()... fc_register.pc = 0x%04x\n", fc_register.pc);
}

void FC::execute_all(MyDirectXSystem* myDirectXSystem) {
	//M_debug_printf("FC::execute()!!!!!!!!!!!!!!\n");
	execute_fc_machine(myDirectXSystem);
}

void FC::execute_fc_machine(MyDirectXSystem* myDirectXSystem) {
	NMI_First_Flag = false;

	controller_register_init();

	set_0_sprite_hit(false);

	draw_pixel_x = 0;
	draw_pixel_y = 0;

	/*
	毎フレームあらかじめ0スプライトの情報を取得しておく
	*/
	uint8_t sprite_x___for0spritehit;//使わない
	uint8_t sprite_y___for0spritehit;//使わない
	bool low_priority_flag___for0spritehit;//使わない
	get_draw_sprite_data__calc_reverse_hv(0, &sprite_x___for0spritehit, &sprite_y___for0spritehit, &low_priority_flag___for0spritehit, sprite_image_data_8x8___for0spritehit);

	for (;;) {
		uint8_t instruction = fc_ram.ram[fc_register.pc];

		fc_register.pc++;
		(this->*(cpu_instruction_table[instruction]))();

		uint32_t instruction_clock = instruction_clock_table[instruction];
		if (instruction_clock == 0xDEADBEEF) {
			M_debug_printf("[命令番号:0x%02x] FC::execute_fc_machine()... error\n", instruction);

			MessageBox(NULL, _T("定義されていない命令を実行しました"), _T("ERROR"), MB_OK | MB_ICONERROR);

			FATAL_ERROR_FLAG = true;
		}

		if (SPRITE_RAM_DMA_ACCESS_FLAG == true) {
			instruction_clock += SPRITE_DMA_ACCESS_CPU_CLOCK;

			SPRITE_RAM_DMA_ACCESS_FLAG = false;
		}

		//cpuの1クロックの間にppuは3クロック(3ピクセル)処理する
		fc_draw_backbuffer(instruction_clock * 3);

		/*
		TODO 余ったXを考慮するのか考える
		余ったCPUクロック = ((余ったX) / 3)
		*/
		if (262 <= draw_pixel_y) {
			set_Vblank_flag(false);
			fc_draw_backbuffer_2x2();//この時に背景の256*2*240*2のバッファーのイメージを作成しておく
			break;
		}
	}

//#ifdef FC_EMU_DEBUG
//	_debug_fc_draw_screen__2x2(myDirectXSystem);
//#endif

	if (is_BG_draw() == false) {//BGを描画しないときは黒く塗りつぶす
		memset(fc_screen_backbuffer, 0x0F, FC_WIDTH * FC_HEIGHT);//0x0Fは黒
	}
	if (is_SPRITE_draw() == true) {
		fc_draw_sprite_backbuffer();
	}
	fc_draw_screen(myDirectXSystem);

	if (Main::draw_screen_up_down_flag == true) {
		draw_screen_up_down_black_band(myDirectXSystem);
	}

	/*
	TODO
	音を実装する
	*/
	/*
	音はまだ未実装
	*/
	//if (is_APU_SQUARE_CH1_enable() == true) {
	//
	//}
	//if (is_APU_SQUARE_CH2_enable() == true) {
	//
	//}
	//if (is_APU_TRIANGLE_enable() == true) {
	//
	//}
	//if (is_APU_NOISE_enable() == true) {
	//
	//}
	//if (is_APU_DPCM_enable() == true) {
	//
	//}

}

/*
背景色を考慮してSPRITEのパレットから選択する
*/
uint8_t FC::get_sprite_tile__palette(uint8_t* tile_palette_ptr, uint8_t palette_no) {
	uint8_t bg_color = fc_vram.bg_palette_table[0];//透明色を取得する
	
	if (palette_no == 0) {
		return bg_color;
	}

	return tile_palette_ptr[palette_no];
}

/*
背景色を考慮してBGのパレットから選択する
*/
uint8_t FC::get_bg_tile__palette(uint8_t* tile_palette_ptr, uint8_t palette_no) {
	uint8_t bg_color = fc_vram.bg_palette_table[0];//透明色を取得する
	
	if (palette_no == 0) {
		return bg_color;
	}

	return tile_palette_ptr[palette_no];
}

uint8_t* FC::get_bg_tile_palette_ptr(uint8_t* ppu_attribute_table_ptr, int tile_x, int tile_y) {
	int palette_x = tile_x / 4;
	int palette_y = tile_y / 4;

	uint8_t palette_block_no = 0;

	if ((tile_x % 4) >= 2) {
		palette_block_no |= 0b00000001;
	}
	if ((tile_y % 4) >= 2) {
		palette_block_no |= 0b00000010;
	}

	int attribute_no = palette_y * (FC_WIDTH / 8 / 4) + palette_x;

	uint8_t palette_no = ppu_attribute_table_ptr[attribute_no];
	uint8_t tile_palette_no = ((palette_no >> (palette_block_no * 2)) & 0b00000011);

	return &(fc_vram.bg_palette_table[tile_palette_no * 4]);
}

void FC::fc_draw_backbuffer_2x2() {
	uint8_t* bg_chr_image_data_ptr = get_bg_chr_table_address();

	uint8_t* ppu_name_table_1_ptr = fc_vram.name_table_1;
	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 32; x++) {
			uint8_t* tile_palette_ptr = get_bg_tile_palette_ptr(fc_vram.attribute_table_1, x, y);

			uint8_t tile_no = ppu_name_table_1_ptr[x + y * 32];
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					uint8_t palette_no = bg_chr_image_data_ptr[8 * 8 * tile_no + i * 8 + j];
					fc_screen_backbuffer_2x2[(y * 8 + i) * (FC_WIDTH * 2) + x * 8 + j] = get_bg_tile__palette(tile_palette_ptr, palette_no);
				}
			}
		}
	}

	/*
	
	HORIZONAL


		 (0,0)     (256,0)     (511,0)
		   +-----------+-----------+
		   |           |           |
		   |           |           |
		   |     1     |     1     |
		   |           |           |
		   |           |           |
	(0,240)+-----------+-----------+(511,240)
		   |           |           |
		   |           |           |
		   |     2     |     2     |
		   |           |           |
		   |           |           |
		   +-----------+-----------+
		 (0,479)   (256,479)   (511,479)
	*/

	/*
	
	VERTICAL


		 (0,0)     (256,0)     (511,0)
		   +-----------+-----------+
		   |           |           |
		   |           |           |
		   |     1     |     2     |
		   |           |           |
		   |           |           |
	(0,240)+-----------+-----------+(511,240)
		   |           |           |
		   |           |           |
		   |     1     |     2     |
		   |           |           |
		   |           |           |
		   +-----------+-----------+
		 (0,479)   (256,479)   (511,479)
	*/

	
	if (mirror_type == MIRROR_TYPE::HORIZONTAL) {
		uint8_t* ppu_name_table_3_ptr = fc_vram.name_table_3;
		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 32; x++) {
				uint8_t* tile_palette_ptr = get_bg_tile_palette_ptr(fc_vram.attribute_table_3, x, y);

				uint8_t tile_no = ppu_name_table_3_ptr[x + y * 32];
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						uint8_t palette_no = bg_chr_image_data_ptr[8 * 8 * tile_no + i * 8 + j];
						fc_screen_backbuffer_2x2[(FC_WIDTH * 2 * FC_HEIGHT) + (y * 8 + i) * (FC_WIDTH * 2) + x * 8 + j] = get_bg_tile__palette(tile_palette_ptr, palette_no);
					}
				}
			}
		}

		for (int k = 0; k < (FC_HEIGHT * 2); k++) {
			memcpy((uint8_t*)(fc_screen_backbuffer_2x2 + (FC_WIDTH * 2) * k + FC_WIDTH), (uint8_t*)(fc_screen_backbuffer_2x2 + (FC_WIDTH * 2) * k), FC_WIDTH);
		}
	}
	else {
		uint8_t* ppu_name_table_2_ptr = fc_vram.name_table_2;
		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 32; x++) {
				uint8_t* tile_palette_ptr = get_bg_tile_palette_ptr(fc_vram.attribute_table_2, x, y);

				uint8_t tile_no = ppu_name_table_2_ptr[x + y * 32];
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						uint8_t palette_no = bg_chr_image_data_ptr[8 * 8 * tile_no + i * 8 + j];
						fc_screen_backbuffer_2x2[(y * 8 + i) * (FC_WIDTH * 2) + x * 8 + j + FC_WIDTH] = get_bg_tile__palette(tile_palette_ptr, palette_no);
					}
				}
			}
		}

		const int COPY_SIZE = (FC_WIDTH * 2) * FC_HEIGHT;
		memcpy((uint8_t*)(fc_screen_backbuffer_2x2 + COPY_SIZE), fc_screen_backbuffer_2x2, COPY_SIZE);
	}
}

#define PPU_1LINE_CLOCK_NUM 341
void FC::fc_draw_backbuffer(uint32_t draw_pixel_number) {
	for (int i = 0; i < draw_pixel_number; i++) {
		if (draw_pixel_x < FC_WIDTH && draw_pixel_y < FC_HEIGHT) {
			fc_draw_backbuffer_1pixel();


			/*
			================================================================================
			================================================================================
			================================================================================
			*/
			/*
			 TODO
			 Sprite0衝突をより正確に直す
			*/

			uint8_t sprite_0_x = ppu_info.sprite_RAM[3];
			uint8_t sprite_0_y = ppu_info.sprite_RAM[0];
			uint8_t real_draw_sprite_y = sprite_0_y + 1;//スプライトは実際のy座標+1に描画される仕様(理由は謎)
			uint8_t sprite_attribute_flag = ppu_info.sprite_RAM[2];
			bool low_priority_flag = false;
			if ((sprite_attribute_flag & 0b00100000) != 0) {
				low_priority_flag = true;
			}
			
			if ((sprite_0_x <= draw_pixel_x && draw_pixel_x < (sprite_0_x + 8)) &&
				(real_draw_sprite_y <= draw_pixel_y && draw_pixel_y < (real_draw_sprite_y + 8))) {
				uint8_t sprite_image_data_index_x = draw_pixel_x - sprite_0_x;
				uint8_t sprite_image_data_index_y = draw_pixel_y - real_draw_sprite_y;
			
				
				if (sprite_image_data_8x8___for0spritehit[sprite_image_data_index_x + sprite_image_data_index_y * 8] != 0xFFFF) {//パレット番号が0でないとき
					//sprite0hit
					set_0_sprite_hit(true);
				}
			}

			/*
			================================================================================
			================================================================================
			================================================================================
			*/

		}

		draw_pixel_x++;
		if (PPU_1LINE_CLOCK_NUM <= draw_pixel_x) {
			draw_pixel_x = 0;
			draw_pixel_y++;

			if (FC_HEIGHT <= draw_pixel_y) {
				if (NMI_First_Flag == false && get_NMI_flag() == true) {//初めての時はNMI割り込みを行う
					NMI_process();

					NMI_First_Flag = true;
				}

				set_Vblank_flag(true);
			}
		}
	}
}

void FC::fc_draw_backbuffer_1pixel() {
	fc_screen_backbuffer[draw_pixel_y * FC_WIDTH + draw_pixel_x] = get_2x2screen_pixel_data_XY(draw_pixel_x, draw_pixel_y);
}

uint8_t FC::get_2x2screen_pixel_data_XY(int x, int y) {
	uint8_t main_screen_type = get_main_screen_type();

	uint32_t x__2x2 = x + ppu_info.scroll_x;
	uint32_t y__2x2 = y + ppu_info.scroll_y;

	if ((main_screen_type & 0b00000001) != 0) {
		x__2x2 += 256;
	}
	if ((main_screen_type & 0b00000010) != 0) {
		y__2x2 += 240;
	}

	while ((256 * 2) <= x__2x2) {
		x__2x2 -= (256 * 2);
	}

	//if ((240 * 2) <= y__2x2) {
	while ((240 * 2) <= y__2x2) {
		y__2x2 -= (240 * 2);
	}

	return fc_screen_backbuffer_2x2[y__2x2 * (FC_WIDTH * 2) + x__2x2];
}

void FC::get_draw_sprite_data__calc_reverse_hv(uint8_t sprite_number, uint8_t* ret_sprite_x_ptr, uint8_t* ret_sprite_y_ptr, bool* ret_low_priority_flag_ptr, uint16_t* ret_sprite_image_data_ptr_8x8) {
	uint8_t* sprite_chr_image_data_ptr = get_sprite_chr_table_address();

	/*
	１バイト目 Ｙ座標

	２バイト目 タイルインデクス番号 （sprファイルの何番目のスプライトを表示するか）

	３バイト目　8ビットのビットフラグです。スプライトの属性を指定します。
	bit7:垂直反転(１で反転)
	bit6:水平反転(１で反転)
	bit5:BGとの優先順位(0:手前、1:奥)
	bit0-1:パレットの上位2bit
	(他のビットは0に)

	４バイト目　Ｘ座標
	*/
	uint8_t sprite_y = ppu_info.sprite_RAM[sprite_number * 4];
	uint8_t sprite_no = ppu_info.sprite_RAM[sprite_number * 4 + 1];
	uint8_t sprite_attribute_flag = ppu_info.sprite_RAM[sprite_number * 4 + 2];
	bool reverse_vertical_flag = false;
	bool reverse_horizonal_flag = false;
	bool low_priority_flag = false;
	uint8_t palette_kind_no = (sprite_attribute_flag & 0b00000011);
	if ((sprite_attribute_flag & 0b10000000) != 0) {
		reverse_vertical_flag = true;
	}
	if ((sprite_attribute_flag & 0b01000000) != 0) {
		reverse_horizonal_flag = true;
	}
	if ((sprite_attribute_flag & 0b00100000) != 0) {
		low_priority_flag = true;
	}
	uint8_t sprite_x = ppu_info.sprite_RAM[sprite_number * 4 + 3];

	uint8_t* sprite_palette_ptr = &(fc_vram.sprite_palette_table[palette_kind_no * 4]);

	uint16_t bef_sprite_image_data[8 * 8];//反転する前のデータ(反転するときに使用する)
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			uint8_t palette_no = sprite_chr_image_data_ptr[8 * 8 * sprite_no + i * 8 + j];
			if (palette_no == 0) {//パレット番号が0のときはそのピクセルは描画しない
				bef_sprite_image_data[i * 8 + j] = 0xFFFF;
			}
			else {
				bef_sprite_image_data[i * 8 + j] = get_sprite_tile__palette(sprite_palette_ptr, palette_no);
			}
		}
	}

	uint16_t bef_sprite_image_data__copy[8 * 8];//反転する前のデータのコピー
	if (reverse_vertical_flag == true) {//垂直反転するとき
		memcpy(bef_sprite_image_data__copy, bef_sprite_image_data, 8 * 8 * sizeof(uint16_t));
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bef_sprite_image_data[(7 - i) * 8 + j] = bef_sprite_image_data__copy[i * 8 + j];
			}
		}
	}
	if (reverse_horizonal_flag == true) {//水平反転するとき
		memcpy(bef_sprite_image_data__copy, bef_sprite_image_data, 8 * 8 * sizeof(uint16_t));
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bef_sprite_image_data[i * 8 + (7 - j)] = bef_sprite_image_data__copy[i * 8 + j];
			}
		}
	}

	*ret_sprite_x_ptr = sprite_x;
	*ret_sprite_y_ptr = sprite_y;
	*ret_low_priority_flag_ptr = low_priority_flag;
	memcpy(ret_sprite_image_data_ptr_8x8, bef_sprite_image_data, sizeof(uint16_t) * 8 * 8);
}

void FC::fc_draw_sprite_backbuffer() {
	//スプライトの描画をする
	for (int k = 0; k < 64; k += 1) {
		uint8_t sprite_x;
		uint8_t sprite_y;
		bool low_priority_flag;
		uint16_t sprite_image_data_8x8[8 * 8];
		get_draw_sprite_data__calc_reverse_hv(k, &sprite_x, &sprite_y, &low_priority_flag, sprite_image_data_8x8);

		uint8_t real_draw_sprite_y = sprite_y + 1;//スプライトは実際のy座標+1に描画される仕様(理由は謎)

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				//uint8_tに一部分キャストしないと上か下にはみ出したときに描画されないときがある

				if (FC_WIDTH <= (sprite_x + j)) {//X座標で画面外のピクセルは描画しない
					continue;
				}

				if (FC_HEIGHT <= (real_draw_sprite_y + i)) {//Y座標画面外のピクセルは描画しない
					continue;
				}

				uint32_t screen_buffer_index = (uint8_t)(real_draw_sprite_y + i) * FC_WIDTH + sprite_x + j;

				if (is_BG_draw() == true) {//背景を描画していないときはとばさない
					if (low_priority_flag == true) {//スプライトが奥に描画されているとき
						if (fc_screen_backbuffer[screen_buffer_index] != fc_vram.bg_palette_table[0]) {//BGのピクセルが背景色でないときはとばす
							continue;
						}
					}
				}

				if (sprite_image_data_8x8[i * 8 + j] == 0xFFFF) {//透明部分はとばす
					continue;
				}

				fc_screen_backbuffer[screen_buffer_index] = sprite_image_data_8x8[i * 8 + j];
			}
		}
	}
}

void FC::fc_draw_screen(MyDirectXSystem* myDirectXSystem) {
	LPDIRECT3DTEXTURE9 pTexture;
	if (FAILED(myDirectXSystem->get_pDevice3D()->CreateTexture(FC_WIDTH, FC_HEIGHT, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture, NULL))) {
		return;
	}
	D3DLOCKED_RECT lockedRect;
	pTexture->LockRect(0, &lockedRect, NULL, 0);
	DWORD* pTextureBuffer = (DWORD*)lockedRect.pBits;

	for (int y = 0; y < FC_HEIGHT; y++) {
		for (int x = 0; x < FC_WIDTH; x++) {
			uint8_t palette_no = fc_screen_backbuffer[y * FC_WIDTH + x];
			DWORD color = GET_COLOR_ALPHA255(FC_COLOR_LIST[palette_no][0], FC_COLOR_LIST[palette_no][1], FC_COLOR_LIST[palette_no][2]);

			pTextureBuffer[y * FC_WIDTH + x] = color;
		}
	}

	pTexture->UnlockRect(0);

	//MyDirectXDraw::draw_texture_base_leftup(myDirectXSystem, pTexture, (float)FC_WIDTH, (float)FC_HEIGHT, 0, 0);
	MyDirectXDraw::draw_texture_base_leftup_enable_size(myDirectXSystem, pTexture, (float)FC_WIDTH, (float)FC_HEIGHT, 0, 0, 2.0);

	pTexture->Release();
}

void FC::draw_screen_up_down_black_band(MyDirectXSystem* myDirectXSystem) {
	MyDirectXDraw::draw_box_leftup(myDirectXSystem, 0, 0, WINDOW_WIDTH, 8 * 2, 0xFF000000);
	MyDirectXDraw::draw_box_leftup(myDirectXSystem, 0, WINDOW_HEIGHT - (8 * 2), WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);
}


#ifdef FC_EMU_DEBUG
void FC::_debug_fc_draw_screen__2x2(MyDirectXSystem* myDirectXSystem) {
	LPDIRECT3DTEXTURE9 pTexture;
	if (FAILED(myDirectXSystem->get_pDevice3D()->CreateTexture(FC_WIDTH * 2, FC_HEIGHT * 2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture, NULL))) {
		return;
	}
	D3DLOCKED_RECT lockedRect;
	pTexture->LockRect(0, &lockedRect, NULL, 0);
	DWORD* pTextureBuffer = (DWORD*)lockedRect.pBits;

	uint8_t* ppu_name_table_1_ptr = fc_vram.name_table_1;
	uint8_t* ppu_attribute_table_1_ptr = fc_vram.attribute_table_1;
	uint8_t* ppu_bg_palette_table_ptr = fc_vram.bg_palette_table;

	for (int y = 0; y < FC_HEIGHT * 2; y++) {
		for (int x = 0; x < FC_WIDTH * 2; x++) {
			uint8_t pixel_no = fc_screen_backbuffer_2x2[y * (FC_WIDTH * 2) + x];

			DWORD color = GET_COLOR_ALPHA255(FC_COLOR_LIST[pixel_no][0], FC_COLOR_LIST[pixel_no][1], FC_COLOR_LIST[pixel_no][2]);
			pTextureBuffer[y * (FC_WIDTH * 2) + x] = color;
		}
	}

	pTexture->UnlockRect(0);

	MyDirectXDraw::draw_texture_base_leftup(myDirectXSystem, pTexture, (float)(FC_WIDTH * 2), (float)(FC_HEIGHT * 2), (float)(FC_WIDTH * 2), 0);

	pTexture->Release();
}
#endif

void FC::cpu_fnc_GARBAGE() {
	M_debug_printf("FC::cpu_fnc_GARBAGE()......................\n");

	MessageBox(NULL, _T("定義されていない命令を実行しました"), _T("ERROR"), MB_OK | MB_ICONERROR);
}

void FC::cpu_fnc_TAX() {
	fc_register.x = fc_register.a;
	calc_N_flag(fc_register.x);
	calc_Z_flag(fc_register.x);
}

void FC::cpu_fnc_TXA() {
	fc_register.a = fc_register.x;
	calc_N_flag(fc_register.a);
	calc_Z_flag(fc_register.a);
}

void FC::cpu_fnc_TAY() {
	fc_register.y = fc_register.a;
	calc_N_flag(fc_register.y);
	calc_Z_flag(fc_register.y);
}

void FC::cpu_fnc_TYA() {
	fc_register.a = fc_register.y;
	calc_N_flag(fc_register.a);
	calc_Z_flag(fc_register.a);
}

void FC::cpu_fnc_TXS() {
	fc_register.s = fc_register.x;
}

void FC::cpu_fnc_TSX() {
	fc_register.x = fc_register.s;
	calc_N_flag(fc_register.x);
	calc_Z_flag(fc_register.x);
}

void FC::cpu_fnc_PHA() {
	fc_ram.stack[fc_register.s] = fc_register.a;

	fc_register.s--;
}

void FC::cpu_fnc_PLA() {
	fc_register.s++;

	fc_register.a = fc_ram.stack[fc_register.s];

	calc_N_flag(fc_register.a);
	calc_Z_flag(fc_register.a);
}

void FC::cpu_fnc_PHP() {
	fc_register.p_B = 1;

	fc_ram.stack[fc_register.s] = fc_register.p;

	fc_register.s--;
}

void FC::cpu_fnc_PLP() {
	fc_register.s++;

	fc_register.p = fc_ram.stack[fc_register.s];

	//fc_register.p_B = 0;
	fc_register.p_R = 1;
}

void FC::cpu_fnc_CLC() {
	fc_register.p_C = 0;
}

void FC::cpu_fnc_CLD() {
	fc_register.p_D = 0;
}

void FC::cpu_fnc_CLI() {
	fc_register.p_I = 0;
}

void FC::cpu_fnc_CLV() {
	fc_register.p_V = 0;
}

void FC::cpu_fnc_SEC() {
	fc_register.p_C = 1;
}

void FC::cpu_fnc_SED() {
	fc_register.p_D = 1;
}

void FC::cpu_fnc_SEI() {
	fc_register.p_I = 1;
}

void FC::cpu_fnc_NOP() {
}
