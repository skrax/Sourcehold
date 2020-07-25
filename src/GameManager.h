#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>

#include "Assets.h"
#include "Parsers/CfgFile.h"
#include "Parsers/MlbFile.h"
#include "Rendering/Display.h"
#include "Rendering/Renderer.h"
#include "System/System.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Events {
class EventHandler;
}

namespace Parsers {
class TgxFile;
class Gm1File;
class AniFile;
class CfgFile;
}  // namespace Parsers

namespace Rendering {
class BinkVideo;
}

namespace Game {
bool InitManager(System::GameOptions &opt, Rendering::Resolution res);
void DestroyManager();

/**
 * Called periodically by the front end,
 * updates all the components and returns
 * false if the game was stopped
 */
bool Running();

/**
 * Override the game system paths
 */
void SetDataDirectory(ghc::filesystem::path dir);
void SetSaveDirectory(ghc::filesystem::path dir);

/**
 * Load all of the files which will remain in memory
 * for the entirety of the game from the current
 * data path.
 */
bool LoadGameData();

/**
 * Clear all the file caches, every call to the
 * getter functions will lead to a reload
 */
void ClearFileCache();

/**
 * Load and cache an asset, 'filename' is an
 * absolute path
 */
void Cache(ghc::filesystem::path filename);

/**
 * Delete a given entry from the file cache.
 * This will ensure that an asset will be freed once
 * every shared_ptr is destructed.
 */
void DeleteCacheEntry(ghc::filesystem::path filename);

void SaveConfig();
void ExitGame();

/**
 * Localization functions. These will get
 * a text string from the 'stronghold.mlb'
 * and 'sh.tex' files.
 */
std::wstring GetDescription(Assets::MissionDescription index);
std::wstring GetString(Assets::TextSection sec, uint16_t index);

double GetTime();
ghc::filesystem::path GetDirectory();
System::StrongholdEdition GetEdition();
Rendering::Resolution GetResolution();
int GetUsernameIndex();
Parsers::CfgFile &GetCfg();

/**
 * Asset getter functions.
 * All filenames are relative to the data directory
 */
std::shared_ptr<Parsers::TgxFile> GetTgx(ghc::filesystem::path filename);
std::shared_ptr<Parsers::Gm1File> GetGm1(ghc::filesystem::path filename);
std::shared_ptr<Parsers::AniFile> GetAni(ghc::filesystem::path filename);
std::shared_ptr<Rendering::BinkVideo> GetBik(ghc::filesystem::path filename);
}  // namespace Game
}  // namespace Sourcehold
