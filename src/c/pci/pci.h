
#ifndef __AQUA__PCI_PCI_H
	#define __AQUA__PCI_PCI_H
	
	#include "../types.h"
	#include "../io/ports.h"
	#include "../common/print.h"
	#include "../common/extern.h"
	
	#define PCI_DATA_PORT 0xCFC//0xCF8 // PCI_CONFIG_ADDRESS
	#define PCI_COMMAND_PORT 0xCF8//0xCFC // PCI_CONFIG_DATA
	
	#define PCI_STATUS_COMMAND 0x04
	
	typedef struct {
		uint8_t bus;
		uint8_t slot;
		uint8_t flags;
		
	} pci_device_t;
	
	typedef struct {
		uint32_t port_base;
		uint32_t interrupt;
		
		uint16_t bus;
		uint16_t device;
		uint16_t function;
		
		uint16_t vendor_id;
		uint16_t device_id;
		
		uint8_t class_id;
		uint8_t subclass_id;
		uint8_t interface_id;
		
		uint8_t revision;
		
	} pci_device_descriptor_t;
	
	typedef enum pci_bar_enum_t {
		memory_mapping = 0,
		input_output = 1
		
	} pci_bar_enum_t;
	
	typedef struct {
		uint8_t prefetchable;
		uint8_t* address;
		uint32_t size;
		pci_bar_enum_t type;
		
	} pci_bar_t;
	
	typedef struct {
		uint8_t unknown; // unavailable is probably a better description
		pci_device_descriptor_t device;
		
		char* vendor_name;
		char* device_name;
		
		char* device_type;
		char* device_subtype;
		char* device_interface_type;
		
	} pci_driver_descriptor_t;
	
	uint16_t pci_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
	uint32_t pci_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
	
	void pci_write_word(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset, uint16_t data);
	void pci_write_dword(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset, uint32_t data);
	
	uint16_t get_pci_vendor(uint8_t bus, uint8_t slot, uint8_t function);
	pci_device_t get_pci_device(uint8_t tclass, uint8_t tsub_class, uint8_t tprog_if);
	
	uint32_t pci_make_addr(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset);
	void pci_write_long(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset, uint32_t data);
	
	void pci_debug(void);
	void pci_analyse(void);
	
	void print_pci_class_code(uint8_t class_code, uint8_t sub_class, uint8_t prog_if);
	uint32_t get_pci_id(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset);
	
	uint32_t pci_read(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset);
	void pci_write(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset, uint32_t value);
	uint8_t pci_device_has_functions(uint16_t bus, uint16_t device);
	
	pci_device_descriptor_t pci_get_device_descriptor(uint16_t bus, uint16_t device, uint16_t function);
	pci_bar_t pci_get_bar(uint16_t bus, uint16_t device, uint16_t function, uint16_t bar);
	pci_driver_descriptor_t pci_get_driver(pci_device_descriptor_t device);
	
	// USB stuff
	
	#define MAX_USB_CONTROLLER_COUNT 16
	
	uint8_t ohci_controller_count;
	uint8_t uhci_controller_count;
	uint8_t ehci_controller_count;
	uint8_t xhci_controller_count;
	
	pci_driver_descriptor_t ohci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t uhci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t ehci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t xhci_controller[MAX_USB_CONTROLLER_COUNT];
	
#endif
