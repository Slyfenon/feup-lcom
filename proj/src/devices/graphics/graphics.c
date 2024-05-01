#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include "graphics.h"

vbe_mode_info_t mode_info;
uint8_t* buffers[3];
int indexArrayBuffers = 0;

int (set_graphics_mode)(uint16_t mode) {
    reg86_t reg;
    memset(&reg, 0, sizeof(reg));

    reg.intno = VIDEO_SERVICES;
    reg.ax = SET_VBE_MODE;
    reg.bx = mode | LINEAR_BIT;

    if(sys_int86(&reg) != OK) {
        printf("sys_int86 failed inside %s", __func__);
        return EXIT_FAILURE;
    }    

    return EXIT_SUCCESS;
}

int (set_frame_buffer)(uint16_t mode) {
    memset(&mode_info, 0, sizeof(mode_info));

    if (vbe_get_mode_info(mode, &mode_info) != OK) {
        printf("vbe_get_mode_info failed inside %s", __func__);
        return EXIT_FAILURE;
    }    

    int vram_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);

    struct minix_mem_range mr;
    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + (vram_size * 3);

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
        printf("sys_privctl failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 3; i++) {
        buffers[i] = vm_map_phys(SELF, (void *)(mr.mr_base + (vram_size * i)), vram_size);
        memset(buffers[indexArrayBuffers], 0, vram_size);

        if (buffers[indexArrayBuffers] == NULL) {
            printf("vm_map_phys failed inside %s", __func__);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x > mode_info.XResolution) return OK;  
    if (y > mode_info.YResolution) return OK;

    unsigned int bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    uint8_t* pixel_pos = buffers[indexArrayBuffers] + ((y * mode_info.XResolution + x) * bytes_per_pixel);
    
    if (memcpy(pixel_pos, &color, bytes_per_pixel) == NULL) {
        printf("memcpy failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int (vg_size_xpm)(xpm_map_t xpm) {
    xpm_image_t img;
    xpm_load(xpm, XPM_INDEXED, &img);

    return img.height * img.width;
}

int (vg_load_xpm)(xpm_map_t xpm, uint8_t** map, xpm_image_t* img) {
    *map = xpm_load(xpm, XPM_INDEXED, img);
    if (map == NULL) {
        printf("xpm_load failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int (vg_draw_xpm)(uint8_t** map, xpm_image_t* img, uint16_t x, uint16_t y) {
    uint8_t* aux = *map;

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            if (vg_draw_pixel(x + j, y + i, *aux) != 0) {
                printf("vg_draw_pixel failed inside %s", __func__);
                return EXIT_FAILURE;
            }
            aux++;
        }
    }

    return EXIT_SUCCESS;
}

int (vg_load_and_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
    uint8_t* map = malloc(vg_size_xpm(xpm));
    xpm_image_t img;

    if (vg_load_xpm(xpm, &map, &img) != OK) {
        printf("vg_load_xpm failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    if (vg_draw_xpm(&map, &img, x, y) != OK) {
        printf("vg_draw_xpm failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    free(map);

    return EXIT_SUCCESS;
}

uint32_t (R)(uint32_t color) {
    return (color >> mode_info.RedFieldPosition) & (BIT(mode_info.RedMaskSize) - 1);
}

uint32_t (G)(uint32_t color) {
    return (color >> mode_info.GreenFieldPosition) & (BIT(mode_info.GreenMaskSize) - 1);
}

uint32_t (B)(uint32_t color) {
    return (color >> mode_info.BlueFieldPosition) & (BIT(mode_info.BlueMaskSize) - 1);
}

int (vg_page_flipping)() {
    reg86_t reg;
    memset(&reg, 0, sizeof(reg));

    reg.intno = VIDEO_SERVICES;
    reg.ax = SET_VBE_DISPLAY_START;
    reg.bl = VERTICAL_RETRACE;
    reg.cx = 0;
    reg.dx = 0;

    if(sys_int86(&reg) != 0) {
        printf("sys_int86 failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    indexArrayBuffers = (indexArrayBuffers + 1) % 3;

    return EXIT_SUCCESS;
}
