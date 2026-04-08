{
  "targets": [
    {
      "target_name": "hge_static",
      "type": "static_library",
      "include_dirs": [
        "include",
        "src/core"
      ],
      "sources": [
        "src/core/graphics.cpp",
        "src/core/ini.cpp",
        "src/core/input.cpp",
        "src/core/random.cpp",
        "src/core/resource.cpp",
        "src/core/sound.cpp",
        "src/core/system.cpp",
        "src/core/timer.cpp"
      ],
      "conditions": [
        ["OS=='mac'", {
          "sources": [
            "src/core/mac/system_mac.mm"
          ],
          "link_settings": {
            "libraries": [
              "-framework Cocoa"
            ]
          }
        }]
      ]
    },
    {
      "target_name": "hge_shared",
      "type": "shared_library",
      "include_dirs": [
        "include",
        "src/core"
      ],
      "sources": [
        "src/core/graphics.cpp",
        "src/core/ini.cpp",
        "src/core/input.cpp",
        "src/core/random.cpp",
        "src/core/resource.cpp",
        "src/core/sound.cpp",
        "src/core/system.cpp",
        "src/core/timer.cpp"
      ],
      "defines": [
        "HGEDLL"
      ],
      "conditions": [
        ["OS=='mac'", {
          "sources": [
            "src/core/mac/system_mac.mm"
          ],
          "link_settings": {
            "libraries": [
              "-framework Cocoa"
            ]
          }
        }]
      ]
    },
    {
      "target_name": "test_app",
      "type": "executable",
      "include_dirs": [
        "include"
      ],
      "sources": [
        "test_main.cpp"
      ],
      "dependencies": [
        "hge_static"
      ]
    }
  ]
}
