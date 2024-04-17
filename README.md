# randar-wasm

Live version [here](https://hobune.stream/randar/).

This project implements the [example code from randar-explanation](https://github.com/spawnmason/randar-explanation?tab=readme-ov-file#complete-worked-example) in C/wasm to run it in your browser with cool visuals and stuff. All the processing happens client-side and nothing leaves your browser.

## Building and running

This repo contains a pre-built wasm file, so you can just host this page on a web server (eg `python3 -m http.server`) and use the site.

If you'd like to make changes to the C code and rebuild it, you'll need to [install and activate emsdk](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended), and then build `randar.c` with:

```bash
emcc -o randar.js randar.c -O3 -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']" -sWASM_BIGINT
```

## Credits

- Everyone who worked on Randar for the original exploit and [code](https://github.com/spawnmason/randar-explanation?tab=readme-ov-file#complete-worked-example).
- [Emscripten](https://emscripten.org/), for running C in the browser.
- [zip.js](https://gildas-lormeau.github.io/zip.js/), for unzipping ReplayMod files.