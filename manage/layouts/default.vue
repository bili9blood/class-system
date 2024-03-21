<script setup lang="ts">
const bgImgUrl = (await useFetch("/api/daily_image")).data.value?.data;
</script>

<template>
  <div h-screen w-screen overflow-hidden>
    <div
      position-fixed hidden
      h-full w-full sm:block
    >
      <div :style="{ background: `url(${bgImgUrl})` }" class="bg-img" :draggable="false" object-cover />
    </div>

    <q-layout flex="~ col" h-full>
      <the-header tabs />

      <q-page-container flex-1>
        <div h-full w-full flex>
          <div flex-1 />
          <div w="65%" flex-2 h-full bg-white px-4 py-8>
            <slot />
            <br>
            <q-separator />
            <page-footer />
          </div>
          <div flex-1 />
        </div>
      </q-page-container>

      <TheFooter />
    </q-layout>
  </div>
</template>

<style scoped>
.bg-img {
  z-index: -1;
  filter: brightness(50%) blur(5px);
  background-size: 100%;
  background-repeat: no-repeat;
  background-position: center;
  width: 120%;
  height: 120%;
  position: relative;
  left: -10%;
  top: -10%;
  padding: 10%;
}
</style>
