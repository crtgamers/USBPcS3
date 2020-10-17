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

/**Archivo
  *
  * Descriptores de dispositivo USB, para uso de la biblioteca en el modo de dispositivo USB. Los descriptores son especiales
  * estructuras legibles por computadora que el host solicita al enumerar el dispositivo, para determinar
  * las capacidades y funciones del dispositivo.
  */

#include "Descriptors.h"

/** Descriptor de informe de clase HID. Este es un descriptor especial construido con valores del
 * Especificación de clase USBIF HID para describir los informes y las capacidades del dispositivo HID. Esta
 * El host analiza el descriptor y su contenido se utiliza para determinar qué datos (y en qué codificación)
 * el dispositivo enviará y lo que puede ser enviado desde el host. Consulte la especificación HID para
 * más detalles sobre los descriptores de informes HID.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport[] =
{
		0x05, 0x01, // USAGE_PAGE (Generic Desktop)
		0x09, 0x05, // USAGE (Gamepad)
		0xa1, 0x01, // COLLECTION (Application)
		0x15, 0x00, //   LOGICAL_MINIMUM (0)
		0x25, 0x01, //   LOGICAL_MAXIMUM (1)
		0x35, 0x00, //   PHYSICAL_MINIMUM (0)
		0x45, 0x01, //   PHYSICAL_MAXIMUM (1)
		0x75, 0x01, //   REPORT_SIZE (1)
		0x95, 0x0d, //   REPORT_COUNT (13)
		0x05, 0x09, //   USAGE_PAGE (Button)
		0x19, 0x01, //   USAGE_MINIMUM (Button 1)
		0x29, 0x0d, //   USAGE_MAXIMUM (Button 13)
		0x81, 0x02, //   INPUT (Data,Var,Abs)
		0x95, 0x03, //   REPORT_COUNT (3)
		0x81, 0x01, //   INPUT (Cnst,Ary,Abs)
		0x05, 0x01, //   USAGE_PAGE (Generic Desktop)
		0x25, 0x07, //   LOGICAL_MAXIMUM (7)
		0x46, 0x3b, 0x01, //   PHYSICAL_MAXIMUM (315)
		0x75, 0x04, //   REPORT_SIZE (4)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x65, 0x14, //   UNIT (Eng Rot:Angular Pos)
		0x09, 0x39, //   USAGE (Hat switch)
		0x81, 0x42, //   INPUT (Data,Var,Abs,Null)
		0x65, 0x00, //   UNIT (None)
		0x95, 0x01, //   REPORT_COUNT (1)
		0x81, 0x01, //   INPUT (Cnst,Ary,Abs)
		0x26, 0xff, 0x00, //   LOGICAL_MAXIMUM (255)
		0x46, 0xff, 0x00, //   PHYSICAL_MAXIMUM (255)
		0x09, 0x30, //   USAGE (X)
		0x09, 0x31, //   USAGE (Y)
		0x09, 0x32, //   USAGE (Z)
		0x09, 0x35, //   USAGE (Rz)
		0x75, 0x08, //   REPORT_SIZE (8)
		0x95, 0x04, //   REPORT_COUNT (4)
		0x81, 0x02, //   INPUT (Data,Var,Abs)
		0x06, 0x00, 0xff, //   USAGE_PAGE (Vendor Specific)
		0x09, 0x20, //   Unknown
		0x09, 0x21, //   Unknown
		0x09, 0x22, //   Unknown
		0x09, 0x23, //   Unknown
		0x09, 0x24, //   Unknown
		0x09, 0x25, //   Unknown
		0x09, 0x26, //   Unknown
		0x09, 0x27, //   Unknown
		0x09, 0x28, //   Unknown
		0x09, 0x29, //   Unknown
		0x09, 0x2a, //   Unknown
		0x09, 0x2b, //   Unknown
		0x95, 0x0c, //   REPORT_COUNT (12)
		0x81, 0x02, //   INPUT (Data,Var,Abs)
		0x0a, 0x21, 0x26, //   Unknown
		0x95, 0x08, //   REPORT_COUNT (8)
		0xb1, 0x02, //   FEATURE (Data,Var,Abs)
		0xc0, // END_COLLECTION
};

/** Estructura del descriptor de dispositivo. Este descriptor, ubicado en la memoria FLASH, describe el
 * características del dispositivo, incluida la versión USB compatible, el tamaño del terminal de control y el
 * número de configuraciones de dispositivo. El host USB lee el descriptor cuando la enumeración
 * comienza el proceso.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(1,1,0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x054c,
	.ProductID              = 0x0268,
	.ReleaseNumber          = VERSION_BCD(1,0,0),

	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Estructura del descriptor de configuración. Este descriptor, ubicado en la memoria FLASH, describe el uso
 * del dispositivo en una de sus configuraciones admitidas, incluida información sobre las interfaces de cualquier dispositivo
 * y puntos finales. El host USB lee el descriptor durante el proceso de enumeración al seleccionar
 * una configuración para que el host pueda comunicarse correctamente con el dispositivo USB.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = USB_CONFIG_ATTR_RESERVED,

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x00,
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_JoystickHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(JoystickReport)
		},

	.HID_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x01
		}
};

/** Estructura del descriptor de idioma. Este descriptor, ubicado en la memoria FLASH, se devuelve cuando el host solicita
 * el descriptor de cadena con índice 0 (el primer índice). En realidad, es una matriz de enteros de 16 bits, que indican
 * a través de la tabla de ID de idiomas disponible en USB.org, qué idiomas admite el dispositivo para sus descriptores de cadena.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Cadena de descriptor del fabricante. Esta es una cadena Unicode que contiene los detalles del fabricante en legible por humanos
 * formulario, y se lee en voz alta a petición del host cuando se solicita la ID de cadena adecuada, que se enumera en el dispositivo
 * Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(12), .Type = DTYPE_String},

	.UnicodeString          = L"crtgamers.cl"
};

/** Cadena de descriptor de producto. Esta es una cadena Unicode que contiene los detalles del producto en forma legible por humanos,
 * y se lee a pedido del host cuando se solicita el ID de cadena apropiado, que se enumera en el Dispositivo
 * Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(81), .Type = DTYPE_String},

	.UnicodeString          = L"CRT GAMERS - 0 Delay USB Joystick Professional Plus Plus 2002 UM Champion Edition"
};

/** La biblioteca llama a esta función cuando está en modo dispositivo y debe anularse (consulte la biblioteca "Descriptores USB"
 * documentación) por el código de la aplicación para que se pueda dar la dirección y el tamaño de un descriptor solicitado
 * a la biblioteca USB. Cuando el dispositivo recibe una solicitud Get Descriptor en el punto final de control, esta función
 * se llama para que los detalles del descriptor se puedan devolver y el descriptor apropiado se envíe de vuelta al
 *  Puerto USB.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}

			break;
		case DTYPE_HID:
			Address = &ConfigurationDescriptor.HID_JoystickHID;
			Size    = sizeof(USB_HID_Descriptor_HID_t);
			break;
		case DTYPE_Report:
			Address = &JoystickReport;
			Size    = sizeof(JoystickReport);
			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

