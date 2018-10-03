
{
  "targets": [
    {
      "target_name": "lypuppies",
      "sources": [
        "lypuppies/binding/puppy.c"
      ],
      "include_dirs": [
        "bin/includes",
      ],
      "libraries": [
        "<(module_root_dir)/bin/liblypuppies.a"
      ]
    }
  ]
}