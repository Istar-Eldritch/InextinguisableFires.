class CfgPatches
{
  class IE_InextinguisableFires_Scripts
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
  class IE_InextinguisableFires_Scripts
  {
    type = "mod";

    dependencies[] = { "Game", "World", "Mission" };

    class defs
    {
      class gameScriptModule
      {
        value = "";
        files[] = {"IE/InextinguisableFires/scripts/3_Game"};
      };

      class worldScriptModule
      {
        value = "";
        files[] = {"IE/InextinguisableFires/scripts/4_World"};
      };

      class missionScriptModule
      {
        value = "";
        files[] = {"IE/InextinguisableFires/scripts/5_Mission"};
      };
    };
  };
};