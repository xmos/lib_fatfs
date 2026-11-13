// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
/* Format a RAM disk, write a file and read it back. */
#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "diskio.h"

#define SECTORS 128
static BYTE disk[SECTORS][512];

/* Disk I/O callbacks required by FatFs. A real application talks to its
 * storage device here instead. */
DSTATUS disk_initialize(BYTE drive) { return drive ? STA_NOINIT : 0; }
DSTATUS disk_status(BYTE drive) { return drive ? STA_NOINIT : 0; }

DRESULT disk_read(BYTE drive, BYTE *buffer, LBA_t sector, UINT count)
{
    if (drive || sector >= SECTORS || count > SECTORS - sector) return RES_PARERR;
    memcpy(buffer, disk[sector], count * 512);
    return RES_OK;
}

DRESULT disk_write(BYTE drive, const BYTE *buffer, LBA_t sector, UINT count)
{
    if (drive || sector >= SECTORS || count > SECTORS - sector) return RES_PARERR;
    memcpy(disk[sector], buffer, count * 512);
    return RES_OK;
}

DRESULT disk_ioctl(BYTE drive, BYTE command, void *buffer)
{
    if (drive) return RES_PARERR;
    switch (command) {
    case CTRL_SYNC: return RES_OK;
    case GET_SECTOR_COUNT: *(LBA_t *)buffer = SECTORS; return RES_OK;
    case GET_SECTOR_SIZE: *(WORD *)buffer = 512; return RES_OK;
    case GET_BLOCK_SIZE: *(DWORD *)buffer = 1; return RES_OK;
    default: return RES_PARERR;
    }
}

/* Timestamp for new files: 2026-01-01. */
DWORD get_fattime(void) { return ((DWORD)(2026 - 1980) << 25) | (1 << 21) | (1 << 16); }

int main(void)
{
    static FATFS fs;
    static FIL file;
    static BYTE work[FF_MAX_SS];
    const char message[] = "Hello from lib_fatfs!";
    char text[sizeof(message)] = {0};
    UINT bytes;
    MKFS_PARM options = {FM_FAT | FM_SFD, 0, 0, 0, 0};

    if (f_mkfs("0:", &options, work, sizeof(work)) != FR_OK ||
        f_mount(&fs, "0:", 1) != FR_OK ||
        f_open(&file, "HELLO.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK ||
        f_write(&file, message, sizeof(message) - 1, &bytes) != FR_OK ||
        f_close(&file) != FR_OK ||
        f_open(&file, "HELLO.TXT", FA_READ) != FR_OK ||
        f_read(&file, text, sizeof(text) - 1, &bytes) != FR_OK ||
        f_close(&file) != FR_OK) {
        printf("FatFs error\n");
        return 1;
    }
    printf("HELLO.TXT: %s\n", text);
    f_unmount("0:");
    return 0;
}
