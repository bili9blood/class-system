import { app_description } from "./constants";

export default defineNuxtConfig({
  modules: [
    "@vueuse/nuxt",
    "@unocss/nuxt",
    "@pinia/nuxt",
    "nuxt-module-eslint-config",
    "nuxt-quasar-ui",
    "@pinia-plugin-persistedstate/nuxt",
  ],

  imports: {
    dirs: ["manage/stores", "manage/utils"],
    presets: [
      { from: "moment", imports: [{ name: "default", as: "moment" }] },
    ],
  },

  components: {
    dirs: ["~/manage/components"],
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
    "~/resources/styles/quasar-variables.css",
    "~/resources/styles/fonts.css",
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
        { name: "description", content: app_description },
        { name: "apple-mobile-web-app-status-bar-style", content: "black-translucent" },
      ],
    },
  },

  dir: {
    assets: "resources",
    layouts: "manage/layouts",
    pages: "manage/pages",
    plugins: "manage/plugins",
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
    lang: "zh-CN",
    plugins: ["Dialog", "Notify"],
  },

});
