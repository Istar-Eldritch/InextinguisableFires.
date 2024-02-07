
class IE_IF_FirePos {
    string id;
    float x;
    float z;

    void IE_IF_FirePos(string _id, float xx, float zz) {
        id = _id;
        x = xx;
        z = zz;
    }
}

class IE_IF_Config {
  
  static private const string DIR_PATH = "$profile:IE";
  static private const string FIRE_CONFIG_PATH = DIR_PATH + "\\InextinguisableFires.json";
  
  ref array<ref IE_IF_FirePos> fire_configs = new ref array<ref IE_IF_FirePos>;
  
  void Load() {
    if (!FileExist(DIR_PATH)){
        MakeDirectory(DIR_PATH);
    }

    if (FileExist(FIRE_CONFIG_PATH)){ //If config exist load File
        CF_Log.Info("[IE_IF] Loading configuration");
        JsonFileLoader<array<ref IE_IF_FirePos>>.JsonLoadFile(FIRE_CONFIG_PATH, fire_configs);
    } else {
		fire_configs.Insert(new IE_IF_FirePos("Null_Fire", 0, 0));
		Save();
	}
  }
  
  void Save() {
	if (GetGame().IsServer()) {
         JsonFileLoader<array<ref IE_IF_FirePos>>.JsonSaveFile(FIRE_CONFIG_PATH, fire_configs);
	}
  }
	
  bool IsFireAtPos(vector pos) {
	foreach(auto config: fire_configs) {
		if (Math.AbsFloat(config.x - pos[0]) < 1 && Math.AbsFloat(config.z - pos[2]) < 1) {
			return true;
		}
	}
	return false;
  }

  void SetProp(string prop, string value) {
	TStringArray tokens = new TStringArray;
	prop.Split(".", tokens);

    auto id = tokens[0];
    IE_IF_FirePos firepos;
    bool newfirepos = false;
    foreach (auto p: fire_configs) {
        if (p.id == id) {
            firepos = p;
            break;
        }
    }
    if (!firepos) {
        newfirepos = true;
        firepos = new IE_IF_FirePos(id, 0, 0);
    }

    switch (tokens[1]) {
        case "x":
            firepos.x = value.ToFloat();
            break;
        case "z":
            firepos.z = value.ToFloat();
            break;
        default:
            CF_Log.Error("Unexpected prop " + prop + " setting on fuelconfig");
    }
    
    if (newfirepos) {
        fire_configs.Insert(firepos);
    }

    Save();

	if (GetGame().IsServer()) {
		SyncSetting(prop, value);
	}
  }
	
	void RemoveProp(string prop) {
		TStringArray tokens = new TStringArray;
		prop.Split(".", tokens);
		

        string id = tokens[0];
        for(int i = 0; i < fire_configs.Count(); i++) {
            if (fire_configs[i].id == id) {
                fire_configs.Remove(i);
                break;
            }
        }
        Save();
		
		if (GetGame().IsServer()) {
			SyncRemoveSetting(prop);
		}
	}

  void SyncAll() {
	CF_Log.Debug("[IE_IF] Requesting all configs");
	GetRPCManager().SendRPC("IE_IF", "IE_IF_SettingsOnSyncRPC", null, true);
  }

  void SyncSetting(string prop, string value) {
	CF_Log.Trace("[IE_IF] Sending update " + prop + " = " + value);
	GetRPCManager().SendRPC("IE_FC", "IE_IF_SettingsOnSyncRPC", new Param2<string, string>(prop, value), true);
  }
	
  void SyncRemoveSetting(string prop) {
	CF_Log.Trace("[IE_IF] Sending delete update " + prop);
	GetRPCManager().SendRPC("IE_FC", "IE_IF_SettingsDeleteSyncRPC", new Param1<string>(prop), true);
  }
	
  void IE_IF_SettingsDeleteSyncRPC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
    Param1<string> data;
    if (ctx.Read(data)) {
		CF_Log.Debug("[IE_IF] Got delete update " + data.param1);
		RemoveProp(data.param1);
    }
  }

  void IE_IF_SettingsOnSyncRPC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
    Param2<string, string> data;
    if (ctx.Read(data)) {
      CF_Log.Debug("[IE_IF] Got config update " + data.param1 + " = " + data.param2);
	  SetProp(data.param1, data.param2);
    } else if (GetGame().IsServer()) {
	  CF_Log.Debug("[IE_IF] Got config update request");

	  foreach (auto fire: fire_configs) {
			GetRPCManager().SendRPC("IE_IF", "IE_IF_SettingsDeleteSyncRPC", new Param2<string, string>(fire.id + ".x", "" + fire.x), true, sender, target);
			GetRPCManager().SendRPC("IE_IF", "IE_IF_SettingsDeleteSyncRPC", new Param2<string, string>(fire.id + ".z", "" + fire.z), true, sender, target);
	  }
    }
  }
}

static ref IE_IF_Config g_IE_IF_Config;
static ref IE_IF_Config GetIF_Config() {
    if (!g_IE_IF_Config) {
      g_IE_IF_Config = new ref IE_IF_Config();
	  if(GetGame().IsServer()) {
      	g_IE_IF_Config.Load();
	  }

      CF_Log.Info("[IE_IF] Loaded settings");
    }

    return g_IE_IF_Config;
}


