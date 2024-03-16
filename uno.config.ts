import {
  defineConfig,
  presetAttributify,
  presetIcons,
  presetTypography,
  presetUno,
  transformerDirectives,
  transformerVariantGroup,
} from "unocss";

export default defineConfig({
  presets: [
    presetUno(),
    presetAttributify(),
    presetIcons({
      scale: 1.2,
    }),
    presetTypography(),
  ],

  theme: {
    colors: {
      "primary": "#2CABFC",
      "primary-content": "#2c3e50",
    },
  },

  transformers: [
    transformerDirectives(),
    transformerVariantGroup(),
  ],
});
