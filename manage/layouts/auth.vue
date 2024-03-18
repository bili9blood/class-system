<script setup lang="ts">
import LoginSvg from "~/resources/images/login.svg";
</script>

<template>
  <div h-screen w-screen>
    <QLayout h-full flex="~ col">
      <TheHeader :nav="false" />
      <QPageContainer flex-1>
        <div flex="~ items-center gap-4" h-full w-full bg-white px-8 py-4>
          <img :src="LoginSvg" :draggable="false" max-w="60%" hidden max-h="20%" md:block>
          <QSeparator vertical hidden md:block />
          <div flex-1>
            <slot />
          </div>
        </div>
      </QPageContainer>
      <QFooter bg-transparent>
        <PageFooter block />
      </QFooter>
    </QLayout>
  </div>
</template>
