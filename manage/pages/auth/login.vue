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
  <QCard>
    <QCardSection>
      <div text="8 center" font-btt select-none>
        登录
      </div>
    </QCardSection>
    <QSelect
      v-model="formData.class_id"
      filled
      label="选择班级"
      :options="classes?.map(({ id }) => id)"
      :option-label="(_id) => classes?.find(({ id }) => _id === id)?.name"
    />

    <QCardSection>
      <QForm
        class="q-gutter-md"
      >
        <div>
          <QBtn label="登录" type="submit" color="primary" />
        </div>
      </QForm>
    </QCardSection>
  </QCard>
</template>
