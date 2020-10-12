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
/**\Archivo
 *
 * Archivo de encabezado para Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Tipo Deficiones: */
	/** Type define para la estructura del descriptor de configuración del dispositivo. Esto debe definirse en el
	*código de aplicación, ya que el descriptor de configuración contiene varios subdescriptores que
	*varían entre dispositivos y describen el uso del dispositivo al host.
	*/
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			// Interfaz HID de joystick
			USB_Descriptor_Interface_t            HID_Interface;
			USB_HID_Descriptor_HID_t              HID_JoystickHID;
	        USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

	/* Macros: */
		/** Dirección de punto final del punto final IN de informes HID de Joystick. */
		#define JOYSTICK_EPADDR           (ENDPOINT_DIR_IN | 1)

		/** Tamaño en bytes del punto final IN de informes HID de Joystick. */
		#define JOYSTICK_EPSIZE           64

		/** Valor del tipo de encabezado del descriptor, para indicar un descriptor HID de clase HID. */
		#define DTYPE_HID                 0x21

		/** Valor del tipo de encabezado del descriptor, para indicar un descriptor de informe HID de clase HID. */
		#define DTYPE_Report              0x22

	/* Función Prototipos: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

