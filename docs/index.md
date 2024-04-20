# Inextinguisable Fires

This mod allows you to place fires on your server that will never get stinguised. The mod is server side.

This mods depends on [IEF](https://steamcommunity.com/sharedfiles/filedetails/?id=3199857963), if you only use this mod, you can set IEF as a server side mod only.

You must place fireplaces on your map by any means you seem fit, any fireplace will work as long as it inherits from `FireplaceBase` should work out of the box. You can place them by hand, using DayZ Editor, or whatever tool you want. You do need to know their exact coordinates. Once the fires are placed and you have their coordinates add them to your configuration file.

## Configuration

### IE/InextinguisableFires.json
```js
[
    {
        "id": "Test Fire", // Just a helper name for you to identify where this fire is located
        "x": 13387.1, // X coordinates of the fire
        "z": 5909.14 // Z coordinates of the fire.
    },
    {
        "id": "Coast",
        "x": 13451.5,
        "z": 5881.8
    }
]
```