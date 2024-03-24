import {
  defineConfig,
  presetAttributify,
  presetTypography,
  presetUno,
  transformerDirectives,
  transformerVariantGroup,
} from "unocss";

export default defineConfig({
  presets: [
    presetUno(),
    presetAttributify(),
    presetTypography(),
  ],

  theme: {
    colors: {
      primary: "var(--q-primary)",
      secondary: "var(--q-secondary)",
      accent: "var(--q-accent)",
      dark: "var(--q-dark)",
      positive: "var(--q-positive)",
      negative: "var(--q-negative)",
      info: "var(--q-info)",
      warning: "var(--q-warning)",
    },
  },

  transformers: [
    transformerDirectives(),
    transformerVariantGroup(),
  ],
});
