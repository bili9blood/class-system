import antfu from "@antfu/eslint-config";
import nuxt from "./.nuxt/eslint.config.mjs";

export default antfu(
  {
    unocss: true,
    formatters: true,

    stylistic: {
      semi: true,
      quotes: "double",
    },

    rules: {
      "style/max-statements-per-line": 0,
    },
  },
  nuxt,
);
