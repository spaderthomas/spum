//------------------------------------------------------------------------------
//  clear-sapp.c
//------------------------------------------------------------------------------
#define SOKOL_GFX_IMPL
#include "sokol_gfx.h"
#define SOKOL_APP_IMPL
#include "sokol_app.h"
#define SOKOL_LOG_IMPL
#include "sokol_log.h"
#define SOKOL_GLUE_IMPL
#include "sokol_glue.h"
// #include "dbgui/dbgui.h"

sg_pass_action pass_action;

void init(void) {
    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });
    pass_action = (sg_pass_action) {
        .colors[0] = {
            .load_action = SG_LOADACTION_CLEAR,
            .clear_value = { 1.0f, 0.0f, 0.0f, 1.0f }
        }
    };
    // __dbgui_setup(sapp_sample_count());
}

void frame(void) {
    float g = pass_action.colors[0].clear_value.g + 0.01f;
    pass_action.colors[0].clear_value.g = (g > 1.0f) ? 0.0f : g;
    sg_begin_pass(&(sg_pass){ .action = pass_action, .swapchain = sglue_swapchain() });
    // __dbgui_draw();
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    // __dbgui_shutdown();
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        // .event_cb = __dbgui_event,
        .width = 400,
        .height = 300,
        .window_title = "Clear (sokol app)",
        .icon.sokol_default = true,
        .logger.func = slog_func,
    };
}