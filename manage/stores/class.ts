import { acceptHMRUpdate, defineStore } from "pinia";
import { Md5 } from "ts-md5";
import type { PiniaPluginContext } from "pinia";

async function HandleAfterRestore(ctx: PiniaPluginContext) {
  const store = ctx.store as ReturnType<typeof useClassStore>;
  try {
    await store.login(store.class_id, store.password);
  }
  catch {
    storeToRefs(store).logined.value = false;
  }
  finally {
    storeToRefs(store).logined.value = true;
  }
}

export const useClassStore = defineStore("class", () => {
  const class_id = ref(0);
  const password = ref("");
  const logined = ref<boolean>();

  async function login(_class_id: number, _password: string) {
    const hashed_password = Md5.hashStr(_password + moment().format("YYYYMMDD")).toString();
    const result = await $fetch("/api/login", {
      body: {
        class_id: _class_id,
        password: hashed_password,
      },
      method: "POST",
    });

    if (result.code !== 200)
      throw result.message;

    class_id.value = _class_id;
    password.value = hashed_password;
  }

  return {
    class_id,
    password,
    logined,

    login,
  };
}, {
  persist: {
    afterRestore: HandleAfterRestore,
    paths: ["class_id", "password"],
  },
});

if (import.meta.hot)
  import.meta.hot.accept(acceptHMRUpdate(useClassStore, import.meta.hot));
