void enable_box_esp() {
    globals::g_box_esp = !globals::g_box_esp;
    std::cout << "Esp " << (globals::g_box_esp ? "enabled" : "disabled") << std::endl;
}

void enable_aimbot() {
    globals::g_aimbot = !globals::g_aimbot;
    std::cout << "Aimbot " << (globals::g_aimbot ? "enabled" : "disabled") << std::endl;
}

void aimbotkey() {
    aimkey = !aimkey;  // Toggle the value of aimkey
    std::cout << "aimkey " << (aimkey ? "enabled" : "disabled") << std::endl;
}

void set_fov(int fov) {

    globals::g_aimfov = fov; 
    std::cout << "FOV set to: " << fov << std::endl;
}

void set_smooth(int smooth) {
    globals::g_smooth = smooth;

    std::cout << "Smooth set to: " << smooth << std::endl;

}

void skelthickness(int skelthick) {
    globals::g_skeletonthickness = skelthick; 

    std::cout << "skelthick set to: " << skelthick << std::endl;

}

void snapthickness(int snapthick) {
    globals::g_line_thick = snapthick;

    std::cout << "snapthick set to: " << snapthick << std::endl;

}

void renderdistance(int distance) {
    globals::g_render_distance = distance;

    std::cout << "distance set to: " << distance << std::endl;

}

void boxthickness(int boxthic) {
    globals::g_box_thick = boxthic; 

    std::cout << "boxthic set to: " << boxthic << std::endl;

}

void enable_fov() {

    globals::g_render_fov = !globals::g_render_fov;
    std::cout << "fovv " << (globals::g_render_fov ? "enabled" : "disabled") << std::endl;


}

void enable_head() {

    globals::headesp = !globals::headesp;
    std::cout << "Head " << (globals::headesp ? "enabled" : "disabled") << std::endl;


}

void enable_crosshair() {

    globals::crosshair = !globals::crosshair;
    std::cout << "crosshair " << (globals::crosshair ? "enabled" : "disabled") << std::endl;


}

void enable_vsync() {

    globals::vsync = !globals::vsync;
    std::cout << "vsync " << (globals::vsync ? "enabled" : "disabled") << std::endl;


}

void enable_watermark() {

    globals::g_watermark = !globals::g_watermark;
    std::cout << "watermark " << (globals::g_watermark ? "enabled" : "disabled") << std::endl;


}

void outline() {

    globals::g_outline = !globals::g_outline;
    std::cout << "outline " << (globals::g_outline ? "enabled" : "disabled") << std::endl;


}

void enable_prediction() {

    globals::prediction = !globals::prediction;
    std::cout << "prediction " << (globals::prediction ? "enabled" : "disabled") << std::endl;


}

void enable_skeleton() {

    globals::g_skeleton = !globals::g_skeleton;
    std::cout << "Skeleton " << (globals::g_skeleton ? "enabled" : "disabled") << std::endl;


}

void ranked() {

    globals::g_ranked = !globals::g_ranked;
    std::cout << "Skeleton " << (globals::g_ranked ? "enabled" : "disabled") << std::endl;


}


void username() {

    globals::g_username = !globals::g_username;
    std::cout << "Username " << (globals::g_username ? "enabled" : "disabled") << std::endl;


}

void snapline() {

    globals::g_line = !globals::g_line;
    std::cout << "snapline " << (globals::g_line ? "enabled" : "disabled") << std::endl;


}

void distance() {

    globals::g_distance = !globals::g_distance;
    std::cout << "distance " << (globals::g_distance ? "enabled" : "disabled") << std::endl;


}

void enable_radaresp() {
    globals::radaresp = !globals::radaresp;
    std::cout << "Radar Esp " << (globals::radaresp ? "enabled" : "disabled") << std::endl;
}

void enable_triggerbot() {
    globals::triggerbot = !globals::triggerbot;
    std::cout << "Triggerbot " << (globals::triggerbot ? "enabled" : "disabled") << std::endl;
}

void enable_off_screen_arrow() {
    globals::oof_enable = !globals::oof_enable;
    std::cout << "off_screen_arrow " << (globals::oof_enable ? "enabled" : "disabled") << std::endl;
}

void enable_hitboxSelect(int selectedBone) {
    // Set the bone index based on the selected value
    globals::g_hitbox = selectedBone;

    // Log the selection
    std::cout << "Selected hitbox: " << globals::g_hitbox << std::endl;
}
