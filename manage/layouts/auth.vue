<template>
  <div h-screen w-screen overflow-hidden>
    <q-layout flex="~ col" h-full>
      <the-header :nav="false" />

      <q-page-container flex-1>
        <div h-full w-full flex>
          <div hidden flex-1 sm:block />
          <div sm:w="45%" flex-2 h-full w-full bg-white px-4 py-8>
            <slot />
          </div>
          <div hidden flex-1 sm:block />
        </div>
      </q-page-container>

      <page-footer />
    </q-layout>
  </div>
</template>
