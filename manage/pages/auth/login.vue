<script setup lang="ts">
definePageMeta({ layout: "auth" });

interface LoginForm {
  class_id?: string;
  password?: string;
}

const formData = ref<LoginForm>({});
const classes = (await useFetch("/api/classes")).data?.value?.data;
</script>

<template>
  <q-card>
    <q-card-section>
      <div text="8 center" font-btt select-none>
        登录
      </div>
    </q-card-section>
    <q-select
      v-model="formData.class_id"
      filled
      label="选择班级"
      :options="classes?.map(({ id }) => id)"
      :option-label="(_id) => classes?.find(({ id }) => _id === id)?.name"
    />

    <q-card-section>
      <q-form
        class="q-gutter-md"
      >
        <div>
          <q-btn type="submit" color="primary">
            登录
          </q-btn>
        </div>
      </q-form>
    </q-card-section>
  </q-card>
</template>
