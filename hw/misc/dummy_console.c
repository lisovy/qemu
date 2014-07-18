#include "hw/hw.h"
#include "hw/sysbus.h"
#include "exec/address-spaces.h"


typedef struct {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
} DummyConsoleState;

static uint64_t dummy_console_control_read(void *opaque, hwaddr offset,
                                           unsigned size)
{
    printf("Read operation is not implemented\n");
    return 0;
}

static void dummy_console_control_write(void *opaque, hwaddr offset,
                                        uint64_t value, unsigned size)
{
    printf("%c", (char)value);
}

static const MemoryRegionOps dummy_console_control_ops = {
    .read = dummy_console_control_read,
    .write = dummy_console_control_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void dummy_console_control_init(Object *obj)
{
    SysBusDevice *sd = SYS_BUS_DEVICE(obj);
    DummyConsoleState *s =
		OBJECT_CHECK(DummyConsoleState, (obj), "dummy_console");

    memory_region_init_io(&s->iomem, NULL, &dummy_console_control_ops,
                          NULL, "dummy_console", 0x1000000);
    sysbus_init_mmio(sd, &s->iomem);
}

static const TypeInfo dummy_console_info = {
    .name          = "dummy_console",
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(DummyConsoleState),
    .instance_init = dummy_console_control_init,
};

static void dummy_console_register_types(void)
{
    type_register_static(&dummy_console_info);
}

type_init(dummy_console_register_types)
