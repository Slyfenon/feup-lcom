#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "devices/kbc/keyboard.h"
#include "devices/kbc/mouse.h"
#include "devices/graphics/graphics.h"
#include "event_handler.h"
#include "game/sprite.h"

struct mousePacket mouse_packet;
uint8_t keyboard_scancode[2];
enum State state = GAME;


int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  if (lcf_start(argc, argv)) return 1;

  lcf_cleanup();

  return 0;
}

int (proj_main_loop)(int argc, char **argv) {
  uint8_t keyboard_irq_set, mouse_irq_set;

  if (set_graphics_mode(DIRECT_COLOR_WITH_32BITS) != OK) return EXIT_FAILURE;
  if (set_frame_buffer(DIRECT_COLOR_WITH_32BITS) != OK) return EXIT_FAILURE;

  if (kbc_subscribe_int(&keyboard_irq_set) != OK) return EXIT_FAILURE;
  if (mouse_enable_scrolling() != OK) return EXIT_FAILURE;
  if (mouse_enable_data_reporting_mine() != OK) return EXIT_FAILURE;
  if (mouse_subscribe_int(&mouse_irq_set) != OK) return EXIT_FAILURE;

  load_sprites();
  draw_sprite(aim, 200, 300);

  message msg;
  int ipc_status, r;
  while (keyboard_scancode[0] != 0x81) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source == HARDWARE)) {

      if (msg.m_notify.interrupts & BIT(mouse_irq_set)){
        mouse_ih();
        if (mouse_packet_is_done()){
          mouse_get_packet(&mouse_packet);
          handle_mouse(state, &mouse_packet);
        }
      }

      if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) {
        kbc_ih();
        if (kbc_scancode_is_done()) {
          kbc_get_scancode(keyboard_scancode);
        }
      }
    }
  }

  if (mouse_unsubscribe_int() != OK) return EXIT_FAILURE;
  if (mouse_disable_data_reporting() != OK) return EXIT_FAILURE;
  if (kbc_unsubscribe_int() != OK) return EXIT_FAILURE;
  if (vg_exit() != OK) return EXIT_FAILURE;

  return 0;
}
