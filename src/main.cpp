#include "main.hpp"


using namespace GlobalNamespace;

static ModInfo modInfo;


// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}



MAKE_HOOK_MATCH(
    aasd_SaberBurnMarkArea_OnEnable, 
    &GlobalNamespace::SaberBurnMarkArea::OnEnable, 
    void, 
    GlobalNamespace::SaberBurnMarkArea* self
    getLogger().info("SaberBurnMarkArea OnEnable Was Called!")
) {
    int value = 0;
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "_fadeOutStrengthShaderPropertyID", value));
    aasd_SaberBurnMarkArea_OnEnable(self);
}



// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
    INSTALL_HOOK(getLogger(), aasd_SaberBurnMarkArea_OnEnable);
    getLogger().info("Installed all hooks!");
}