<script setup lang="ts">
const bgImgUrl: string = JSON.parse(await $fetch("/api/dailyImage", { headers: { "Accept-Encoding": "none" } })).data;
</script>

<template>
  <div h-screen w-screen overflow-hidden>
    <div
      position-fixed hidden
      h-full w-full sm:block
    >
      <div :style="{ background: `url(${bgImgUrl})` }" class="bg-img" :draggable="false" object-cover />
    </div>

    <QLayout flex="~ col" h-full>
      <TheHeader />

      <QPageContainer flex-1>
        <div h-full w-full flex>
          <div flex-1 />
          <div w="65%" flex-2 h-full bg-white>
            <slot />
            <QSeparator />
            <PageFooter />
          </div>
          <div flex-1 />
        </div>
      </QPageContainer>

      <TheFooter />
    </QLayout>
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
