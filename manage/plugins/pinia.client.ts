import { PiniaUndo } from "pinia-undo";
import type { NuxtApp } from "nuxt/app";

export default defineNuxtPlugin((_app) => {
  const app = _app as NuxtApp;
  app.$pinia.use(PiniaUndo);
});
