import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { viteStaticCopy } from "vite-plugin-static-copy";

// https://vitejs.dev/config/
export default defineConfig({
  base: "/fml-web/",
  plugins: [
    viteStaticCopy({
      targets: [
        {
          src: "./lib/fml_web.wasm",
          dest: ".",
        },
      ],
    }),
    react(),
  ],
});
