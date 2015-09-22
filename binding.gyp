{
  "targets": [
    {
      "target_name": "termb",
      "sources": [ "src/termb.cc"],
      "include_dirs": [
	  'src'
      ],
	  "msbuild_settings": {
			"Link": {
				"ImageHasSafeExceptionHandlers": "false"
			}
		}
    }
  ]
}
