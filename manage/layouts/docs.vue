<script setup lang="ts">
const $r = useRouter();

const { data: navigation } = await useAsyncData("navigation", () => fetchContentNavigation());

const nav_nodes = computed(() => RemoveDuplicatedContentNav(navigation.value ?? []));
</script>

<template>
  <div h-screen w-screen>
    <q-layout h-full>
      <the-header :nav="false" title="班级系统 | 使用文档">
        <template #tabs>
          <q-tabs>
            <q-route-tab to="/" label="管理端" />
            <q-route-tab to="/docs" label="使用文档" />
          </q-tabs>
        </template>
      </the-header>

      <q-drawer show-if-above side="left" bordered>
        <q-tree
          :nodes="nav_nodes"
          :selected="$r.currentRoute.value.path"
          label-key="title" node-key="_path"
          no-connectors default-expand-all selected-color="primary"
          @update:selected="$event && $r.push($event)"
        />
      </q-drawer>

      <q-page-container class="docs-container" h-full w-full items-center justify-center>
        <div h-full w-full overflow-auto bg-white px-4 py-8 text-4>
          <slot />
          <br select-none>
          <q-separator />
          <page-footer />
        </div>
      </q-page-container>
    </q-layout>
  </div>
</template>

<style lang="scss">
.docs-container {
  & > div {
    scroll-behavior: smooth !important;
  }
  h1 {
    font-size: 3em;
    font-weight: 800;
    line-height: 1.25em;
    letter-spacing: -0.01562em;

    margin-bottom: 0.5em;
    padding: 0.2em;
    border-radius: 0.1em;
    background-color: var(--q-secondary);
  }

  h2 {
    font-size: 2.25em;
    font-weight: 550;
    line-height: 1.75em;
    letter-spacing: -0.00833em;
  }

  h3 {
    font-size: 2em;
    font-weight: 500;
    line-height: 1.75em;
    letter-spacing: normal;
  }

  h2,
  h3 {
    border-bottom: 0.2rem dotted gray;
    margin-bottom: 0.8em;
  }

  ol,
  ul {
    padding: 0.75em 0;
    margin-left: 1em;
  }

  ol li {
    list-style: decimal;
  }

  ul li {
    list-style: initial;
  }

  blockquote {
    border-left: 0.25em solid var(--q-primary);
    padding-left: 1em;
  }

  a {
    color: var(--q-primary);
    &:hover {
      text-decoration: underline dotted;
    }
  }

  pre:has(code) {
    padding: 0.5em;
    margin-bottom: 1em;
    border: lightgrey 0.1em solid;
    border-radius: 0.5em;
  }

  p {
    margin-bottom: 0.5em;
  }
}
</style>
