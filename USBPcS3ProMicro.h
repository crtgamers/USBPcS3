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

#ifndef _USBPCS3PROMICRO_H_
#define _USBPCS3PROMICRO_H_

	/* Incluidos: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>


	/* Tipo Definiciones: */
	/** Escriba definir para la estructura de informes HID del joystick, para crear y enviar informes HID a la PC host.
	* Esto refleja el diseño descrito para el host en el descriptor del informe HID, en Descriptors.c.
	*/
		typedef struct
		{
			// botones digitales, 0 = off, 1 = on

			uint8_t square_btn : 1;
			uint8_t cross_btn : 1;
			uint8_t circle_btn : 1;
			uint8_t triangle_btn : 1;

			uint8_t l1_btn : 1;
			uint8_t r1_btn : 1;
			uint8_t l2_btn : 1;
			uint8_t r2_btn : 1;

			uint8_t select_btn : 1;
			uint8_t start_btn : 1;
			uint8_t l3_btn : 1;
			uint8_t r3_btn : 1;
			uint8_t ps_btn : 1;
			uint8_t : 3;

			// dirección digital, use las constantes dir_ * (enum)
			// 8 = centro, 0 = arriba, 1 = arriba / derecha, 2 = derecha, 3 = derecha / abajo
			// 4 = abajo, 5 = abajo / izquierda, 6 = izquierda, 7 = izquierda / arriba

			uint8_t direction;

			// joysticks analógicos izquierdo y derecho, 0x00 izquierda / arriba, 0x80 medio, 0xff derecha / abajo

			uint8_t l_x_axis;
			uint8_t l_y_axis;
			uint8_t r_x_axis;
			uint8_t r_y_axis;

			uint8_t unknown[4];

			// eje del botón, 0x00 = sin presionar, 0xff = completamente presionado

			uint8_t triangle_axis;
			uint8_t circle_axis;
			uint8_t cross_axis;
			uint8_t square_axis;

			uint8_t l1_axis;
			uint8_t r1_axis;
			uint8_t l2_axis;
			uint8_t r2_axis;

		} USB_JoystickReport_Data_t;

		extern USB_JoystickReport_Data_t gamepad_state;

	/* Prototipos de funciones: */
		void vs_reset_pad_status(void);
		void vs_init(bool watchdog);
		void vs_reset_watchdog(void);
		void vs_send_pad_state(void);
		void vs_set_connect_callback(void (*callbackPtr)(void));
		void vs_set_disconnect_callback(void (*callbackPtr)(void));

#endif

