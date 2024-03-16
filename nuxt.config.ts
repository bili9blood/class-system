import { appDescription } from "./constants/index";

export default defineNuxtConfig({
  modules: [
    "@vueuse/nuxt",
    "@unocss/nuxt",
    "@pinia/nuxt",
    "nuxt-module-eslint-config",
    "nuxt-quasar-vite",
  ],

  imports: {
    presets: [
      { from: "moment", imports: [{ name: "default", as: "moment" }] },
    ],
  },

  experimental: {
    // when using generate, payload js assets included in sw precache manifest
    // but missing on offline, disabling extraction it until fixed
    payloadExtraction: false,
    renderJsonPayloads: true,
    typedPages: true,
  },

  css: [
    "@unocss/reset/tailwind.css",
  ],

  nitro: {
    imports: {
      presets: [
        { from: "moment", imports: [{ name: "default", as: "moment" }] },
        { from: "zod", imports: ["z"] },
      ],
    },
    esbuild: {
      options: {
        target: "es2015",
      },
    },
    prerender: {
      crawlLinks: false,
      routes: ["/"],
    },
  },

  app: {
    head: {
      viewport: "width=device-width,initial-scale=1",
      meta: [
        { name: "viewport", content: "width=device-width, initial-scale=1" },
        { name: "description", content: appDescription },
        { name: "apple-mobile-web-app-status-bar-style", content: "black-translucent" },
      ],
    },
  },

  dir: {
    assets: "resources",
  },

  devtools: {
    enabled: true,
  },

  features: {
    // For UnoCSS
    inlineStyles: false,
  },

  eslintConfig: {
    setup: false,
  },

  quasar: {
    config: {
      dark: false,
    },
  },

});
