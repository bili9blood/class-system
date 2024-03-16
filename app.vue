<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

useHead({
  title: appName,
  link: [{ rel: "icon", href: IconIco, sizes: "any" }],
});
</script>

<template>
  <NuxtLayout>
    <NuxtPage />
  </NuxtLayout>
</template>

<style>
html,
body,
#__nuxt {
  height: 100vh;
  margin: 0;
  padding: 0;
}
</style>
