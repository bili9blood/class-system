<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";
</script>

<template>
  <q-layout flex="~ col">
    <q-header
      height-hint="98"
      bordered
      bg-transparent text-primary-content
    >
      <q-toolbar>
        <q-toolbar-title>
          <q-avatar square>
            <img :src="IconIco">
          </q-avatar>
          {{ appName }}
        </q-toolbar-title>
      </q-toolbar>

      <q-tabs align="left" />
    </q-header>

    <q-page-container flex-1>
      <slot />
    </q-page-container>

    <the-footer />
  </q-layout>
</template>
