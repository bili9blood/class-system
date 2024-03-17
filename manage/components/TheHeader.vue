<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";
</script>

<template>
  <q-header
    height-hint="98"
    elevated
    text-primary-content
  >
    <q-toolbar>
      <q-toolbar-title>
        <q-avatar square>
          <img :src="IconIco">
        </q-avatar>
        {{ appName }}
      </q-toolbar-title>

      <q-tabs align="right" hidden sm:block>
        <q-route-tab to="/">
          主页
        </q-route-tab>
        <q-route-tab to="/students">
          学生
        </q-route-tab>
      </q-tabs>
    </q-toolbar>
  </q-header>
</template>
