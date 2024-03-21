<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

useHead({
  title: appName,
  link: [{ rel: "icon", href: IconIco, sizes: "any" }],
});

const $r = useRouter();

function HandleLoginStatusChanged(logined: boolean | undefined) {
  if (logined === false)
    $r.push("/");
  else if (logined === true)
    $r.push("/auth/login");
}

HandleLoginStatusChanged(useClassStore().logined);

watch(storeToRefs(useClassStore()).logined, HandleLoginStatusChanged);
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
