#ifndef __DEVICE_H
#define __DEVICE_H

#define DEVICE_NAME_MAXLEN 64

typedef struct device {
    char name[DEVICE_NAME_MAXLEN];
    struct device *next;
} dev_t;

int device_register(dev_t *dev);
void device_unregister(dev_t *dev);
dev_t *get_device_by_name(const char *name);

#endif
