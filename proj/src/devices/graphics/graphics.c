#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include "graphics.h"

vbe_mode_info_t mode_info;
uint8_t* video_mem;

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
    mr.mr_limit = mr.mr_base + vram_size;

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
        printf("sys_privctl failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if (video_mem == NULL) {
        printf("vm_map_phys failed inside %s", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x > mode_info.XResolution) return EXIT_FAILURE;  
    if (y > mode_info.YResolution) return EXIT_FAILURE;

    unsigned int bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    uint8_t* pixel_pos = video_mem + ((y * mode_info.XResolution + x) * bytes_per_pixel);
    
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
            vg_draw_pixel(x + j, y + i, *aux);
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
