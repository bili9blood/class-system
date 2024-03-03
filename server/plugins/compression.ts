import { useCompression } from "h3-compression";

export default defineNitroPlugin((nitro) => {
  nitro.hooks.hook("beforeResponse", async (event, { body }) => {
    await useCompression(event, { body });
  });
});
