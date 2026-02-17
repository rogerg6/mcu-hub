#include "device.h"
#include "def.h"
#include "platform.h"
#include <string.h>

/**
 * @brief 全局设备链表
 * 每个成员都是静态定义，无动态分配
 */
struct device *g_devices = NULL;

int device_register(dev_t *dev) {
    if (!dev)
        return ERR;

    g_devices = dev;
    dev->next = g_devices;

    return OK;
}

void device_unregister(dev_t *dev) {
    if (!dev)
        return;

    dev_t *cur_dev;
    dev_t **nextp = &g_devices;
    while (NULL != (cur_dev = *nextp)) {
        if (!strcmp(cur_dev->name, dev->name)) {
            *nextp =cur_dev->next;
        }
        nextp = &cur_dev->next;
    }
}

dev_t *get_device_by_name(const char *name) {
    if (!name)
        return NULL;

    dev_t *dev = g_devices;
    while (dev) {
        if (!strcmp(dev->name, name))
            return dev;
        dev = dev->next;
    }
    return NULL;
}

