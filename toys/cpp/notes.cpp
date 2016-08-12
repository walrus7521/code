
// The typedefs have a trailing underscore so that they have a different name
// than the original functions which are in DLLs/SOs; if they have the same name
// then the DLLs/SOs will try to call the functions in the executable and cause
// a segfault. However, the #defines don't change the name mangling, so the
// #defines allow the executable to use the same name as the DLLs/SOs without
// causing any name conflicts.
typedef uint32_t (*LibConfigFileNumVersionsFPtr)();
extern LibConfigFileNumVersionsFPtr LibConfigFileNumVersions_;
#define LibConfigFileNumVersions LibConfigFileNumVersions_


static std::unique_ptr<Library> configFileLib(nullptr);
static std::unique_ptr<Library> i2cLib(nullptr);
static std::unique_ptr<Library> calFixtureLib(nullptr);

    configFileLib = std::unique_ptr<Library>(nullptr);
    i2cLib = std::unique_ptr<Library>(nullptr);
    calFixtureLib = std::unique_ptr<Library>(nullptr);

