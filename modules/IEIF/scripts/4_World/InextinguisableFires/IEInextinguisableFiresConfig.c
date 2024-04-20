
class IE_IF_FirePos
{
  string id;
  float x;
  float z;

  void IE_IF_FirePos(string _id, float xx, float zz)
  {
    id = _id;
    x = xx;
    z = zz;
  }
}

class IE_IF_Config
{

  static private const string DIR_PATH = "$profile:IE";
  static private const string FIRE_CONFIG_PATH = DIR_PATH + "\\InextinguisableFires.json";

  ref array<ref IE_IF_FirePos> fire_configs = new ref array<ref IE_IF_FirePos>;

  void Load()
  {
    if (!FileExist(DIR_PATH))
    {
      MakeDirectory(DIR_PATH);
    }

    if (FileExist(FIRE_CONFIG_PATH))
    { //If config exist load File
      string error;
      bool loaded;
      loaded = JsonFileLoader<array<ref IE_IF_FirePos>>.LoadFile(FIRE_CONFIG_PATH, fire_configs, error);

      if (loaded)
      {
        IEIF_LOG.Info("Loaded configuration");
      }
      else
      {
        IEIF_LOG.Error("Error loading configuration: " + error);
      }
    }
    else
    {
      fire_configs.Insert(new IE_IF_FirePos("Null_Fire", 0, 0));
      Save();
    }
  }

  void Save()
  {
    if (GetGame().IsServer())
    {
      JsonFileLoader<array<ref IE_IF_FirePos>>.JsonSaveFile(FIRE_CONFIG_PATH, fire_configs);
    }
  }

  bool IsFireAtPos(vector pos)
  {
    foreach (auto config: fire_configs) {
      if (Math.AbsFloat(config.x - pos[0]) < 1 && Math.AbsFloat(config.z - pos[2]) < 1)
      {
        return true;
      }
    }
    return false;
  }
}

static ref IE_IF_Config g_IE_IF_Config;
static ref IE_IF_Config GetIF_Config()
{
  if (!g_IE_IF_Config)
  {
    g_IE_IF_Config = new ref IE_IF_Config();
    if (GetGame().IsServer())
    {
      g_IE_IF_Config.Load();
    }

    IEIF_LOG.Info("[IEIF] Loaded settings");
  }

  return g_IE_IF_Config;
}


