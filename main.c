/*
*
* USBPcS3: Interfaz USB que emula control de PS3 para Pro Micro originales o piratas 5V 16MHz | ATMega32u4
*
* Copyright (c) 2020
* Bruno Freitas - bruno@brunofreitas.com
* Jon Wilson    - degenatrons@gmail.com
* Kevin Mackett - kevin@sharpfork.com
* Bastian Aguirre - crtgamers.cl
*
* Este programa es software gratuito: puedes redistribuirlo y / o modificar
* bajo los términos de la Licencia Pública General GNU publicada por
* Free Software Foundation, ya sea la versión 3 de la Licencia, o
* (a su elección) cualquier versión posterior.
*
* Este programa se distribuye con la esperanza de que sea útil,
* pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
* COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver el
* Licencia pública general GNU para más detalles.
*
* Debería haber recibido una copia de la Licencia Pública General GNU
* junto con este programa. Si no, vea <http://www.gnu.org/licenses/>.
*/

#include "USBPcS3ProMicro.h"
#include "util.h"

void setup_pins(void);

static const uint8_t digital_dir_lookup[16] = {8, 2, 6, 8, 4, 3, 5, 8, 0, 1, 7, 8, 8, 8, 8, 8};

int main(void) {
	uint8_t pad_up, pad_down, pad_left, pad_right, pad_cross, pad_triangle, pad_circle, pad_square, pad_l2,
	pad_r2, pad_start, pad_select, pad_l3, pad_r3, pad_l1, pad_r1, pad_left_analog_x,
	pad_left_analog_y, pad_right_analog_x, pad_right_analog_y;

	// Ajuste el reloj a 16 Mhz
	CPU_PRESCALE(0);

	// Desactivar JTAG
	bit_set(MCUCR, 1 << JTD);
	bit_set(MCUCR, 1 << JTD);

	// Pines de inicio
	setup_pins();

	// Iniciar emulación del control de PS3
	vs_init(true);

	// Actualizaciones de estado de controles y encuestas
	for (;;) {
		vs_reset_watchdog();

		pad_up = !bit_check(PIND, 1);
		pad_down = !bit_check(PIND, 0);
		pad_left = !bit_check(PIND, 4);
		pad_right = !bit_check(PINC, 6);
		pad_triangle = !bit_check(PIND, 7);
		pad_circle = !bit_check(PINE, 6);
		pad_square = !bit_check(PINB, 4);
		pad_cross = !bit_check(PINB, 5);
		pad_l2 =  !bit_check(PINB, 6);
		pad_r2 =  !bit_check(PINB, 2);
		pad_start =  !bit_check(PIND, 2);
		pad_select =  !bit_check(PIND, 3);
		pad_l3 =  !bit_check(PINF, 6);
		pad_r3 =  !bit_check(PINF, 7);
		pad_l1 = !bit_check(PINB, 1);
		pad_r1 = !bit_check(PINB, 3);

		pad_left_analog_x = pad_left_analog_y = pad_right_analog_x = pad_right_analog_y = 0x7F;

		if(!bit_check(PINF, 4)) {
			pad_right_analog_y = 0x00;
		} else if(!bit_check(PINF, 5)) {
			pad_right_analog_y = 0xFF;
		}

		gamepad_state.cross_btn = pad_cross;
		gamepad_state.cross_axis = gamepad_state.cross_btn * 0xFF;
		gamepad_state.circle_btn = pad_circle;
		gamepad_state.circle_axis = gamepad_state.circle_btn * 0xFF;
		gamepad_state.square_btn = pad_square;
		gamepad_state.square_axis = gamepad_state.square_btn * 0xFF;
		gamepad_state.triangle_btn = pad_triangle;
		gamepad_state.triangle_axis = gamepad_state.triangle_btn * 0xFF;

		gamepad_state.l1_btn = pad_l1;
		gamepad_state.l1_axis = gamepad_state.l1_btn * 0xFF;
		gamepad_state.r1_btn = pad_r1;
		gamepad_state.r1_axis = gamepad_state.r1_btn * 0xFF;
		gamepad_state.l2_btn = pad_l2;
		gamepad_state.l2_axis = gamepad_state.l2_btn * 0xFF;
		gamepad_state.r2_btn = pad_r2;
		gamepad_state.r2_axis = gamepad_state.r2_btn * 0xFF;

		gamepad_state.direction = digital_dir_lookup[pad_up << 3 | pad_down << 2 |
				pad_left << 1 | pad_right];

		gamepad_state.start_btn = pad_start;
		gamepad_state.select_btn = pad_select;

		gamepad_state.ps_btn = pad_start && pad_select;

		gamepad_state.l3_btn = pad_l3;
		gamepad_state.r3_btn = pad_r3;

		gamepad_state.l_x_axis = pad_left_analog_x;
		gamepad_state.l_y_axis = pad_left_analog_y;
		gamepad_state.r_x_axis = pad_right_analog_x;
		gamepad_state.r_y_axis = pad_right_analog_y;

		vs_send_pad_state();
	}
}

void setup_pins(void) {

	// Pines de inicio
	bit_clear(DDRF, 1 << 7);
	bit_set(PORTF, 1 << 7);

	bit_clear(DDRF, 1 << 6);
	bit_set(PORTF, 1 << 6);

	bit_clear(DDRF, 1 << 5);
	bit_set(PORTF, 1 << 5);

	bit_clear(DDRF, 1 << 4);
	bit_set(PORTF, 1 << 4);

	bit_clear(DDRF, 1 << 1);
	bit_set(PORTF, 1 << 1);

	bit_clear(DDRF, 1 << 0);
	bit_set(PORTF, 1 << 0);

	bit_clear(DDRB, 1 << 3);
	bit_set(PORTB, 1 << 3);

	bit_clear(DDRB, 1 << 1);
	bit_set(PORTB, 1 << 1);

	bit_clear(DDRD, 1 << 6);
	bit_set(PORTD, 1 << 6);

	bit_clear(DDRB, 1 << 7);
	bit_set(PORTB, 1 << 7);

	bit_clear(DDRB, 1 << 6);
	bit_set(PORTB, 1 << 6);

	bit_clear(DDRB, 1 << 5);
	bit_set(PORTB, 1 << 5);

	bit_clear(DDRB, 1 << 4);
	bit_set(PORTB, 1 << 4);

	bit_clear(DDRE, 1 << 6);
	bit_set(PORTE, 1 << 6);

	bit_clear(DDRD, 1 << 7);
	bit_set(PORTD, 1 << 7);

	bit_clear(DDRC, 1 << 6);
	bit_set(PORTC, 1 << 6);

	bit_clear(DDRD, 1 << 4);
	bit_set(PORTD, 1 << 4);

	bit_clear(DDRD, 1 << 0);
	bit_set(PORTD, 1 << 0);

	bit_clear(DDRD, 1 << 1);
	bit_set(PORTD, 1 << 1);

	bit_clear(DDRD, 1 << 2);
	bit_set(PORTD, 1 << 2);

	bit_clear(DDRD, 1 << 3);
	bit_set(PORTD, 1 << 3);

	bit_clear(DDRB, 1 << 0);
	bit_set(PORTB, 1 << 0);

	bit_clear(DDRB, 1 << 2);
	bit_set(PORTB, 1 << 2);

	bit_clear(DDRC, 1 << 7);
	bit_set(PORTC, 1 << 7);
}
