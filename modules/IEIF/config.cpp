class CfgPatches
{
  class IE_InextinguisableFires
  {
    units[]={};
    weapons[]={};
    requiredVersion=0.1;
    requiredAddons[]=
    {
      "DZ_Data",
      "DZ_Scripts",
      "JM_CF_Scripts"
    };
  };
};

class CfgMods
{
  class IE_InextinguisableFires
  {
    type = "mod";

    dependencies[] = { "Game", "World", "Mission" };

    class defs
    {
      class gameScriptModule
      {
        value = "";
        files[] = {"IEIF/scripts/3_Game"};
      };

      class worldScriptModule
      {
        value = "";
        files[] = {"IEIF/scripts/4_World"};
      };

      class missionScriptModule
      {
        value = "";
        files[] = {"IEIF/scripts/5_Mission"};
      };
    };
  };
};